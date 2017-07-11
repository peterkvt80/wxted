/** This code adapted from Simon Rawles
 *  by Peter Kwan
 *  with contributions from Alistair Cree.
 *
// Copyright (C) 2015  Simon Rawles
//
// The JavaScript code in this page is free software: you can
// redistribute it and/or modify it under the terms of the GNU
// General Public License (GNU GPL) as published by the Free Software
// Foundation, either version 3 of the License, or (at your option)
// any later version.  The code is distributed WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
//
// As additional permission under GNU GPL version 3 section 7, you
// may distribute non-source (e.g., minimized or compacted) forms of
// that code without the copy of the GNU GPL normally required by
// section 4, provided you include this license notice and a URL
// through which recipients can access the Corresponding Source.
 */
 #include "teletext40.h"
 using namespace std;

 void load_from_hash(TTXPage* page, char* str)
 {
     const char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
     char* hashstring=strchr(str,'#'); // Find the start of hash string
     // @todo Get the metadata

     if (hashstring){
         hashstring=strchr(hashstring,':');// move past metadata
         if (hashstring){
             // Is it valid length?
             hashstring++;
             uint16_t len=strlen(hashstring);
             if (len<1120) return;

             // Initialise before the loop
             uint8_t currentCode=0;
             uint8_t outBit=0x40;
             uint8_t outCol=0;
             uint8_t outRow=0; // Teletext40 uses the header row
             char line[40];
             char* pos;
            // for (int i=0;i<40;i++)line[i]=0;
             for (uint16_t i=0; i<1167; i++)
             {
                char ch=*hashstring ;
                hashstring++;
                pos=strchr(base64,ch);
                if (pos==NULL)
                {
                    std::cout << "can not find character " << ch << std::endl;
                }
                uint32_t code=(pos-base64) &0xff;


                for (uint8_t b=0x20;b>0;b>>=1) // Source bit mask
                {
                    if ((b&code)>0)
                    {
                        currentCode|=outBit;
                    }
                    outBit>>=1; // next output bit
                    if (outBit==0) // Character done?
                    {
                        assert(currentCode<0x80);
                        line[outCol]=currentCode; // Save the character
                        currentCode=0;
                        outBit=0x40;
                        assert(outCol<40);
                        outCol++;   // next column
                        if (outCol>=40)
                        {
                            page->SetRow(outRow,std::string(line));
                            outCol=0;
                            outRow++;
                        }
                    }
                } // bit mask
             } // For each encoded source char
             // @todo At this point, if the first row contains a page number in the right place, use it as an initial value
             // parse the rest of the string which is a set of :key=value pairs eg.
             // :PN=550:PS=400c:SC=2
             printf("hashstring=%s\n",hashstring);
             char * pair = strtok(hashstring,":");
             while (pair) {
                char * eq=strchr(pair,'=');
                if (!eq) return; // oops!
                char * key=pair;
                *eq=0;
                eq++;
                char * value=eq;
                if (strcmp,"PN",key) {
                  int page_num=std::strtol(value,NULL,16);
                  page->SetPageNumber(page_num*0x100);
                }
                if (strcmp,"SC",key) {
                  int subcode_num=std::strtol(value,NULL,16); // @todo Is this hex? Can't remember
                  page->SetSubCode(subcode_num);
                }
                if (strcmp,"PS",key) {
                  int status_num=std::strtol(value,NULL,16);
                  page->SetPageStatus(status_num);
                }
                value=strtok(NULL,":");
             }
         } // if hashstring metadata
     } // if hashstring
 }

// Similarly, we want to save the page to the hash. This simply
// converts the character set and page data into a hex string and
// puts it there.
/**
 * \param cset A character set 0-Eng 1-Ger 2-Swe 3-Ita 4-Bel 5-ASCII 6=Heb 7=Cyr
 * \param website The website prefix eg. "http://edit.tf"
 */
void save_to_hash(int cset, char* encoding, uint8_t cc[25][40], char* website, TTXPage* page)
{

	// Construct the metadata as described above.
	uint8_t metadata = cset;
	// if ( blackfg != 0 ) { metadata += 8; } // wxTED says NO
	//encoding += metadata.toString(16);
	//encoding += ":";
	sprintf(encoding,"%s/#%d:",website,metadata);

	// Construct a base-64 array by iterating over each character
	// in the frame.
	uint8_t b64[1300];
	for (uint16_t i=0;i<1300;i++) b64[i]=0;
	uint16_t framebit=0;
	for (uint8_t r=0; r<25; r++) // Now include fastext
	{
		for (uint8_t c=0; c<40; c++)
		{
      char ch=cc[r][c];
			for (uint8_t b=0; b<7; b++) // 7 bits per teletext character
      {
				// Read a bit and write a bit.
				uint8_t bitval = ch & ( 1 << ( 6 - b ));
				if (bitval)
        {
          // Work out the position of the character in the
          // base-64 encoding and the bit in that position.
          uint16_t b64bitoffset = framebit % 6;
          uint16_t b64charoffset = ( framebit - b64bitoffset ) / 6;
          b64[b64charoffset] |= 1 << ( 5 - b64bitoffset );
        }
				framebit++;
			}
		}
	}

	// Encode bit-for-bit.
	uint8_t sz=strlen(encoding);
	char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
	for (uint16_t i = 0; i < 1167; i++)
  {
		encoding[i+sz] = base64[((int)b64[i]) ];
	}
	{
	  char *p = &encoding[1167+sz];
	  int pagenumber=page->GetPageNumber();
	  int subcode=page->GetSubCode();
	  int status=page->GetPageStatus();
	  sprintf(p,":PN=%03x:SC=%04x:PS=%04X",pagenumber >> 8, subcode, status);
	}
	// encoding[1167+sz]=0;
}

