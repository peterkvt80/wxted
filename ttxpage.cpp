/** ***************************************************************************
 * Description       : Class for a teletext page
 * Compiler          : C++
 *
 * Copyright (C) 2014-2020, Peter Kwan
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 *************************************************************************** **/
#include "ttxpage.h"

bool TTXPage::pageChanged=false;

TTXPage::TTXPage() : undoList(nullptr), m_current(nullptr)    //ctor
{
  m_Init();
}

static int instanceCount=0;

void TTXPage::m_Init()
{
  m_region=0;
  SetPageNumber(FIRSTPAGE); // Valid but unlikely page
  Setm_SubPage(nullptr); // Pointer to the next sub page
  for (int i=0;i<=MAXROW;i++)
  {
    m_pLine[i]=nullptr;
  }
  for (int i=0;i<6;i++)
  {
    SetFastextLink(i,0x8ff);
  }
  // Member variables
  m_destination="inserter";
  m_description="Description goes here";
  SetSourcePage("");
  SetShortFilename("");
  m_cycletimeseconds=8;
  m_cycletimetype='T';
  m_subcode=-1;
  m_pagestatus=0x8000;
  instance=instanceCount++;
  // std::cout << "[TTXPage::TTXPage()] instance=" << instance << std::endl;
  SetPageChanged(false);
}

TTXPage::~TTXPage()
{
  static int j=0;
  j++;
  for (int i=0;i<=MAXROW;i++)
  {
    if (m_pLine[i]!=nullptr)
    {
      delete m_pLine[i];
      m_pLine[i]=nullptr;
    }
  }
  /* Does this leave sub pages leaking memory?
     No. The destructor will cascade through the whole chain */
  if (Getm_SubPage()!=nullptr)
  {
    //std::cout << "~[TTXPage]: " << j << std::endl;
    delete m_SubPage;
    m_SubPage=nullptr;
  }
}

// See http://rtlalphanet.asp.tss.nl/RTL4/100s01 for examples
bool TTXPage::m_LoadVTX(std::string filename)
{
  std::cout << "Trying VTX" << std::endl;
  char buf[500];
  TTXPage* p=this;
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  // First 10 chars should be ham encoded. No error correction allowed
  filein.read(buf,9);
  for (int i=0;i<9;i++)
  {
    uint8_t ch=buf[i];
    switch (ch)
    {
    case 0x15: break;
    case 0x02: break;
    case 0x49: break;
    case 0x5e: break;
    case 0x64: break;
    case 0x73: break;
    case 0x38: break;
    case 0x2f: break;
    case 0xd0: break;
    case 0xc7: break;
    case 0x8c: break;
    case 0x9b: break;
    case 0xa1: break;
    case 0xb6: break;
    case 0xfd: break;
    case 0xea: break;
    default:
        return false; // Not a VTX if not HAM
    }
  }
  std::cout << std::endl;
  filein.read(buf,119); // This contains headery stuff to be decoded

  for (int line=1;line<25;line++)
  {
    filein.read(buf,42); // TODO: Check for a failed read and abandon
    std::string s(buf);
    p->SetRow(line,s);
  }


  for (int i=1;i<2000;i++)
  {
    filein.read(buf,1);
    uint8_t ch=buf[0];
    switch (ch)
    {
    case 0x15: std::cout << "<0>";break;
    case 0x02: std::cout << "<1>";break;
    case 0x49: std::cout << "<2>";break;
    case 0x5e: std::cout << "<3>";break;
    case 0x64: std::cout << "<4>";break;
    case 0x73: std::cout << "<5>";break;
    case 0x38: std::cout << "<6>";break;
    case 0x2f: std::cout << "<7>";break;
    case 0xd0: std::cout << "<8>";break;
    case 0xc7: std::cout << "<9>";break;
    case 0x8c: std::cout << "<a>";break;
    case 0x9b: std::cout << "<b>";break;
    case 0xa1: std::cout << "<c>";break;
    case 0xb6: std::cout << "<d>";break;
    case 0xfd: std::cout << "<e>";break;
    case 0xea: std::cout << "<f>";break;
    default:
        std::cout << (char)(buf[0] & 0x7f);
    }
  }
  std::cout << std::endl;
  return true;
  if ((buf[0]!=(char)0xFE) || (buf[1]!=(char)0x01) || (buf[2]!=(char)0x09))
  {
    filein.close();
    return false;
  }
  SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original
  // Next we load 24 lines  of 40 characters
  for (int i=0;i<24;i++)
  {
    filein.read(buf,40); // TODO: Check for a failed read and abandon
    buf[40]=0;
    std::string s(buf);
    p->SetRow(i,s);
  }
  p->SetRow(0,"         wxTED mpp DAY dd MTH \x3 hh:nn.ss"); // Overwrite anything in row 0 (usually empty)
  // With a pair of zeros at the end we can skip
  filein.close(); // Not sure that we need to close it
  p->Setm_SubPage(nullptr);
  SetPageChanged(false);
  return true;
}

bool TTXPage::m_LoadEP1(std::string filename)
{
    char buf[100];
    TTXPage* p=this;
    std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
    // First 6 chars should be FE 01 09 00 00 00
    filein.read(buf,6);
    if ((buf[0]!=(char)0xFE) || (buf[1]!=(char)0x01) || (buf[2]!=(char)0x09))
    {
        filein.close();
        return false;
    }
    SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original
    // Next we load 24 lines  of 40 characters
    for (int i=0;i<24;i++)
    {
        filein.read(buf,40); // TODO: Check for a failed read and abandon
        buf[40]=0;
        std::string s(buf);
        p->SetRow(i,s);
    }
    p->SetRow(0,"         wxTED mpp DAY dd MTH \x3 hh:nn.ss"); // Overwrite anything in row 0 (usually empty)
    // With a pair of zeros at the end we can skip
    filein.close(); // Not sure that we need to close it
    p->Setm_SubPage(nullptr);
    SetPageChanged(false);
    return true;
}

bool TTXPage::m_LoadVTP(std::string filename)
{
    char buf[0x100];
    TTXPage* p=this;
    int subPageCount=0;
    std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
    // First 6 chars should be 56 64 60 (VTP)
    filein.read(buf,3);
    if ((buf[0]!=(char)0x56) || (buf[1]!=(char)0x54) || (buf[2]!=(char)0x50))
    {
        filein.close();
        return false;
    }
    // Next 4 chars are <?> <pp> <m> <number of subpages> in hex
    filein.read(buf,4);
    SetPageNumber(buf[2]*0x10000+buf[1]*0x100);

    subPageCount=buf[3];
    if (subPageCount<1)
    {
      return false;
    }

    // Don't know what this stuff is. It is mostly 0
    // Possibly some fastext links
    filein.read(buf,0x6F);

    SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original file

    for (bool more=true;more && subPageCount>0;subPageCount--)
    {
      // Next we load 24 lines of 40 characters
      for (int i=0;i<24;i++)
      {
          filein.read(buf,40); // TODO: Check for a failed read and abandon
          if (filein.eof())
          {
            break;
          }
          buf[40]=0;
          std::string s(buf);
          p->SetRow(i,s);
      }
      filein.read(buf,10);
      // third byte of this group is the subcode
      p->SetSubCode(buf[2]);

      std::cout << std::hex << std::setw(2);
      for (int i=0;i<10;i++){std::cout << ((int)buf[i]) << " ";}
      std::cout << std::dec << std::endl;

      if (filein.eof())
      {
        more=false;
      }
      // Is there another subpage?
      if (more && subPageCount>1)
      {
        TTXPage* newSubPage=new TTXPage();  // Create a new instance for the subpage
        p->Setm_SubPage(newSubPage);        // Put in a link to it
        p=newSubPage;                       // And jump to the next subpage ready to populate
      }
    }
    // With a pair of zeros at the end we can skip
    filein.close(); // Not sure that we need to close it
    p->Setm_SubPage(nullptr);
    SetPageChanged(false);
    return true;
}

bool TTXPage::m_LoadTTX(std::string filename)
{
    char buf[1100]; // Don't think we need this much buffer. Just a line will do
    TTXPage* p=this;
    std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
    // First 0x61 chars are some sort of header. TODO: Find out what the format is to get metadata out
    filein.read(buf,0x61);

    // TODO: More validation for this format
    // File must start with CEBRA
    if ((buf[0]!='C') || (buf[1]!='E') || (buf[2]!='B') || (buf[3]!='R') || (buf[4]!='A'))
    {
        //char buf2[1100];
        // Not a CEBRA file. Could be a raw 1000 byte file?
        // get length of file:
        filein.seekg (0, filein.end);
        int length = filein.tellg();
        filein.seekg (0, filein.beg);
        std::cout << "length=" << length << std::endl;
        if (length==1000) // Raw file? Yes! // @todo Multipage
        {
            SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original
            // Next we load 24 lines of 40 characters
            for (int i=0;i<25;i++)
            {
                filein.read(buf,40);
                if (i==0)
                {
                    findPageNumber(buf);
                }

                for (int j=0;j<40;j++) if (buf[j]=='\0') buf[j]=ttxCodeAlphaBlue; // Should be Alpha black! But tricky!
                p->SetRow(i,buf);
            }

            filein.close();
            p->Setm_SubPage(nullptr);
            SetPageChanged(false);
            return true;
        }
        /// @todo teletext.org.uk ttx grabs
        if (length>1000) // Multiple raw page from teletext.co.uk
        {
            //wxTEDFrame * win = new wxTEDFrame(0);
            //win->OnMenuNew(event);
            //win->Show(true);
            /// @todo Open a new window with each page that we decode.
            //win->Page()->SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original
            // Next we load 24 lines of 40 characters
            for (int i=0;i<25;i++)
            {
                filein.read(buf,40);
                int pageNum;
                if (i==0)
                {
                    pageNum=findPageNumber(buf); // @todo Take the number of this page and put it in the meta data
                    if (pageNum>0x100) {
                        p->SetPageNumber(pageNum);
                    }
                }
                for (int j=0;j<40;j++) if (buf[j]=='\0') buf[j]=ttxCodeAlphaBlue; // Should be Alpha black! But tricky!
                p->SetRow(i,buf);
            }

            filein.close();
            p->Setm_SubPage(nullptr);
            SetPageChanged(false);
            return true;

        }
        // File failed to load
        filein.close();
        return false;
    }
    // Cebra file follows....
    SetSourcePage(filename+".tti"); // Add tti to ensure that we don't destroy the original
    // Next we load 24 lines  of 40 characters
    for (int i=0;i<24;i++)
    {
        filein.read(buf,7); // Skip preamble
        filein.read(buf,40); // TODO: Check for a failed read and abandon
        buf[40]=0;
        std::string s(buf);
        p->SetRow(i+1,s);
    }
    p->SetRow(0,"         wxTED mpp DAY dd MTH \x3 hh:nn.ss"); // Overwrite anything in row 0 (usually empty)

    filein.close();
    p->Setm_SubPage(nullptr);
    SetPageChanged(false);
    return true;
}

int TTXPage::findPageNumber(char* buf)
{
    int result=0;
    int state=0;
    char* p=buf;
    for (int i=0;i<40;i++)
    {
        switch (state)
        {
            // Looking for 1..8 magazine
        case 0: if (*p>='1' && *p<='8')
            {
                result=(*p-'0') << 4;
                state++;
            }
            break;
        case 1: if (*p>='0' && *p<='9')
            {
                result=(result+*p-'0') << 4;
                state++;
                break;
            }
            if (*p>='A' && *p<='F')
            {
                result=(result+*p-'A'+10) << 4;
                state++;
                break;
            }
            if (*p>='a' && *p<='f')
            {
                result=(result+*p-'0'+10) << 4;
                state++;
                break;
            }
            state=0;
            break;
        case 2:
            if (*p>='0' && *p<='9')
            {
                result=result+*p-'0';
            }
            else
            if (*p>='A' && *p<='F')
            {
                result=result+*p-'A'+10;
            }
            else
            if (*p>='a' && *p<='f')
            {
                result=result+*p-'0'+10;
            }
            else
            {
                state=0;
                break;
            }
            return result;
        }
        p++;
    }
    return -1;
}

bool TTXPage::m_LoadTTI(std::string filename)
{
    const std::string cmd[]={"DS","SP","DE","CT","PN","SC","PS","MS","OL","FL","RD","RE"};
    const int cmdCount = 12; // There are 12 possible commands, maybe DT and RT too on really old files
    unsigned int lineNumber;
    int lines=0;
    // Open the file
    std::ifstream filein(filename.c_str());
    TTXPage* p=this;
    char * ptr;
    int subcode;
    std::string subpage;
    int pageNumber;
    char m;
    for (std::string line; std::getline(filein, line, ','); )
    {
        // std::cout << line << std::endl; // Shows the command code
        bool found=false;
        for (int i=0;i<cmdCount && !found; i++)
        {
            // std::cout << "matching " << line << std::endl;
            if (!line.compare(cmd[i]))
            {
                found=true;
                // std::cout << "Matched " << line << std::endl;
                switch (i)
                {
                case 0 : // "DS" - Destination inserter name
                    // DS,inserter
                    // std::cout << "DS not implemented\n";
                    std::getline(filein, m_destination);
                    // std::cout << "DS read " << m_destination << std::endl;
                    break;
                case 1 : // "SP" - Source page file name
                    // SP is the path + name of the file from where is was loaded. Used also for Save.
                    // SP,c:\Minited\inserter\ONAIR\P100.tti
                    //std::cout << "SP not implemented\n";

                    std::getline(filein, line);
                    // std::getline(filein, m_sourcepage);
                    break;
                case 2 : // "DE" - Description
                    // DE,Read back page  20/11/07
                    //std::cout << "DE not implemented\n";
                    std::getline(filein, m_description);
                    break;
                case 3 : // "CT" - Cycle time (seconds). This is a per subpage function
                    // CT,8,T
                    // std::cout << "CT not implemented\n";
                    std::getline(filein, line, ',');
                    p->m_cycletimeseconds=atoi(line.c_str());
                    std::getline(filein, line);
                    p->m_cycletimetype=line[0]=='T'?'T':'C';
                    // TODO: CT is not decoded correctly
                    break;
                case 4 : // "PN" - Page Number mppss
                    // Where m=1..8
                    // pp=00 to ff (hex)
                    // ss=00 to 99 (decimal)
                    // PN,10000
                    std::getline(filein, line);
                    if (line.length()<3) // Must have at least three characters for a page number
                        break;
                    m=line[0];
                    if (m<'1' || m>'8') // Magazine must be 1 to 8
                        break;
                    pageNumber=std::strtol(line.c_str(), &ptr, 16);
                    std::cout << "Line=" << line << " " << "line length=" << line.length() << std::endl;
                    if (line.length()<5 && pageNumber<0x8ff) // Page number without subpage? Shouldn't happen but you never know.
                    {
                        pageNumber*=0x100;
                    }
                    else   // Normally has a subpage
                    {
                        subpage=line.substr(3,2);
                        std::cout << "Subpage=" << subpage << std::endl;
                        pageNumber=(pageNumber & 0xfff00) + std::strtol(subpage.c_str(),nullptr,10);
                    }
                    std::cout << "PN enters with m_PageNumber=" << std::hex << m_PageNumber << " pageNumber=" << std::hex << pageNumber << std::endl;
                    if (p->m_PageNumber!=FIRSTPAGE) // // Subsequent pages need new page instances
                    {
                        std::cout << "Created a new subpage" << std::endl;
                        TTXPage* newSubPage=new TTXPage();  // Create a new instance for the subpage
                        p->Setm_SubPage(newSubPage);            // Put in a link to it
                        p=newSubPage;                       // And jump to the next subpage ready to populate
                    }
                    p->SetPageNumber(pageNumber);

                    // std::cout << "PN =" << std::hex << m_PageNumber << "\n";
                    //if (m_PageNumber)
                    //    std::cout << "new page. TBA\n";
                    break;
                case 5 : // "SC" - Subcode
                    // SC,0000
                    std::getline(filein, line);
                    subcode=std::strtol(line.c_str(), &ptr, 16);
                    //std::cout << "SC: Subcode=" << subcode << std::endl;;

                    p->SetSubCode(subcode);
                    break;
                case 6 : // "PS" - Page status flags
                    // PS,8000
                    std::getline(filein, line);
                    m_pagestatus=std::strtol(line.c_str(), &ptr, 16);
                    // Don't copy the bits to the UI...
                    // because this may not be the root page.
                    break;
                case 7 : // "MS" - Mask
                    // MS,0
                    // std::cout << "MS not implemented\n";
                    std::getline(filein, line);
                    break;
                case 8 : // "OL" - Output line
                    // OL,9,ƒA-Z INDEX     ‡199ƒNEWS HEADLINES  ‡101
                    std::getline(filein, line, ',');
                    lineNumber=atoi(line.c_str());
                    std::getline(filein, line);
                    if (lineNumber>MAXROW) break;
                    // std::cout << "reading " << lineNumber << std::endl;
                    p->m_pLine[lineNumber]=new TTXLine(line);
                    // TODO: Change this implementation to use SetRow
                    // std::cout << lineNumber << ": OL partly implemented. " << line << std::endl;
                    if (lineNumber==28)
                    {
                      p->m_row28=new TTXRow28(line);
                    }
                    lines++;
                    break;
                case 9 : // "FL"; - Fastext links
                    // FL,104,104,105,106,F,100
                    // std::cout << "FL not implemented\n";
                    for (int fli=0;fli<6;fli++)
                    {
                        if (fli<5)
                            std::getline(filein, line, ',');
                        else
                            std::getline(filein, line); // Last parameter no comma
                        SetFastextLink(fli,std::strtol(line.c_str(), &ptr, 16));
                    }
                    break;
                case 10 : // "RD"; - not sure!
                    std::getline(filein, line);
                    break;
                case 11 : // "RE"; - Set page region code 0..f
                    std::getline(filein, line); // TODO: Implement this
                    m_region=std::strtol(line.c_str(), &ptr, 16);
                    break;
                default:
                    std::cout << "Command not understood " << line << std::endl;
                } // switch
            } // if matched command
            // If the command was not found then skip the rest of the line
        } // seek command
        if (!found) std::getline(filein, line);
    }
    filein.close(); // Not sure that we need to close it
    p->Setm_SubPage(nullptr);
    std::cout << "Finished reading TTI page. Line count=" << lines << std::endl;
    SetPageChanged(false);
    return (lines>0);
}

/* TODO: move the body of this out into a LoadPage function */
/** ctor
 *  Load a teletext page from file
 * \param filename : Name of teletext file to load
 * \param shortFilename : Filename without path
 */
TTXPage::TTXPage(std::string filename, std::string shortFilename) :
  m_PageNumber(0x100),
  m_SubPage(nullptr),
  undoList(nullptr),
  m_current(nullptr),
  m_loaded(false)
{
  //std::cout << "[TTXPage] file constructor" << std::endl;
  m_Init();
  SetSourcePage(filename);
  SetShortFilename(shortFilename);
  // Try all the possible formats.

  int type=1;
  SetRow(3,shortFilename);

  if (!m_loaded)
  {
    SetRow(1,"                                        ");
    if (m_LoadTTI(filename))
    {
      m_loaded=true;
    }
  }

  if (!m_loaded)
  {
    SetRow(1,"Trying VTX");
    if (m_LoadVTX(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    SetRow(1,"Trying VTP");
    if (m_LoadVTP(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    SetRow(1,"Trying EP1");
    if (m_LoadEP1(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    SetRow(1,"                                        ");
    if (m_LoadTTX(filename))
    {
        m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    SetRow(1,"Unable to load file");
    SetRow(3,shortFilename);
    SetRow(4,"?");
    SetRow(5,filename);
    SetSourcePage("Unable to load page");
    SetShortFilename("no page");
  }

  SetPageChanged(false);
  std::cout << "Finished reading page. Loaded=" << m_loaded << " type=" << type << std::endl;
}


TTXPage::TTXPage(const TTXPage& other) : undoList(0), m_current(nullptr)
{
  //copy ctor.
  std::cout << "Would be a great idea to implement the copy constructor" << std::endl;
}

TTXPage& TTXPage::operator=(const TTXPage& rhs)
{
  if (this == &rhs) return *this; // handle self assignment
  //assignment operator
  return *this;
}

TTXPage* TTXPage::GetPage(unsigned int pageNumber)
{
  //std::cout << "[TTXPage::GetPage]" << std::endl;
  TTXPage* p=this;
  for (;pageNumber>0 && p->m_SubPage!=nullptr;p=p->m_SubPage, pageNumber--);
  // Iterate down the page list to find the required page object
  return p;
}

void TTXPage::Undo(wxPoint& cursorloc)
{
  TEDEvent* tev=m_current; // This is the event we are going to undo
  if (!m_current) // Nothing to undo?
  {
    return;
  }
  // TODO: Check the event type
  char oldChar=tev->GetCharList()->GetOldChar();   // What character
  wxPoint loc=tev->GetCharList()->GetLoc();    // and where are we putting it?
  // Write to the edit window
  TTXLine* line=m_pLine[loc.y];
  line->SetCharAt(loc.x,oldChar);
  // Dump the Undo (or do we?) No, just move the m_current pointer. Keep it in case we want to do a Redo
  // Step back to the previous event
  TEDEvent* last=tev->GetlastEvent();
  if (last!=0)
  {
    m_current=last;
  }
  else
  {
    SetPageChanged(false);
  }
      // TTXPage::pageChanged=false; // No more UNDO? Clear the changed flag. (actually can never happen!)
  cursorloc=loc;
}

TTXLine* TTXPage::GetRow(unsigned int row)
{
  // std::cout << "[TTXPage::GetRow] getting row " << row << std::endl;
  if (row>MAXROW)
  {
    std::cout << "[TTXPage::GetRow]Invalid row requested: " << row << std::endl;
    return nullptr;
  }
  TTXLine* line=m_pLine[row];
  // Don't create row 0, as that is special.
  if (line==nullptr && row>0)
  {
    line=m_pLine[row]=new TTXLine("                                        ");
  }
  if (!line)
  {
    std::cout << "[TTXPage::GetRow] returning NULL " << std::endl;
  }
  return line;
}

void TTXPage::SetRow(unsigned int rownumber, std::string line)
{
  if (rownumber>MAXROW || rownumber<0) return;
  if (!m_pLine[rownumber])
  {
    m_pLine[rownumber]=new TTXLine(line); // Didn't exist before
  }
  else
  {
    m_pLine[rownumber]->Setm_textline(line);
  }
}

void TTXPage::AddEvent(EventType evt,wxPoint wxc,char oldChar, char newChar)
{
  if (oldChar==newChar) // No change?
  {
    return;
  }
  TEDEvent* tev=new TEDEvent(evt);
  CharChange* cc=nullptr;
  if (!undoList) // First time we need to set the root
  {
    undoList=tev;
    m_current=undoList;
  }
  else    // Subsequently we add to the list and move the current pointer to the end of the list
  {
    m_current->SetnextEvent(tev);
    tev->SetlastEvent(m_current);
    m_current=tev;
  }
  switch (evt)
  {
  case EventNone:
    break;
  case EventSave :    // Save to file (@todo)
    break;
  case EventKey :     // Keyboard press
    cc=new CharChange(); // A bit redundant. This is always executed
    tev->SetCharList(cc);
    // tev->SetCharList(cc); // not correct. Need to add to the end of the list NOT the root
    cc->AddChange(wxc,oldChar,newChar);
    break;
  case EventLanguage :     // No idea
    break;
  }
}

TEDEvent* TTXPage::GetUndo()
{
    return m_current;
}


/* Handle key presses and moving the cursor using (wxWidgets)
Keyboard has mappings according to country.
UK: [ = left arrow, ]=right arrow etc.
Shift F1..F8 are alpha colours
Ctrl  F1..F8 are graphics colours
Other control codes TBA.
*/
void TTXPage::SetCharAt(int code, int modifiers, wxPoint& cursorLoc, wxPoint& cursorSubLoc, bool ShowHeader)
{
    std::cout << "code=" << code << " modifiers=" << modifiers << std::endl;
    int yMin=1;     // If we show the header, then enable row 0
    if (ShowHeader)
    {
        yMin=0;
    }
    if (cursorLoc.y>24 || cursorLoc.y<yMin) return;       // Out of range. Don't allow row 0 either.

    // Do not allow DoubleHeight on row 23 or 24
    if (cursorLoc.y>22 && code==WXK_CONTROL_M) return;

    TTXLine* line=m_pLine[cursorLoc.y];

    // Is the line NULL? If so we had better make the line!
    if (!line)
    {
        // Create a line if it is null
        line=m_pLine[cursorLoc.y]=new TTXLine("                                        ");
    }

    // todo: Are there any more characters allowed in graphics mode? I think there are! CHECK!!!!

    // Move cursor a whole space if Alpha mode, or @ to _ (0x40 to 0x5f) or a control code.
    // In other words anything not an actual graphics code.
    bool AlphaMode=line->IsAlphaMode(cursorLoc.x);

     // std::cout << "Code trace 1=" << code << std::endl;
    /* If there is a key modifier then check for special functions */

    if (modifiers & wxMOD_SHIFT) // Alpha Colours
    {
        char ch=0;
        // std::cout << "alpha colour Code=" << code << std::endl;
        switch (code)
        {
            case WXK_F1: ch=ttxCodeAlphaRed;break;      // Shift-F1 red
            case WXK_F2: ch=ttxCodeAlphaGreen;break;    // Shift-F2 green
            case WXK_F3: ch=ttxCodeAlphaYellow;break;   // Shift-F3 yellow
            case WXK_F4: ch=ttxCodeAlphaBlue;break;     // Shift-F4 blue
            case WXK_F5: ch=ttxCodeAlphaMagenta;break;  // Shift-F5 magenta
            case WXK_F6: ch=ttxCodeAlphaCyan;break;     // Shift-F6 cyan
            case WXK_F7: ch=ttxCodeAlphaWhite;break;    // Shift-F7 white
            case WXK_F8: ch=0x80;break;                 // Shift-F8 black SPECIAL CASE!
            // case WXK_F9: InsertLine(); break; // Oh. We don't have the y location at this point
            default: ch=0; // not a valid shift code.
        }
        if (ch>0)
        {
            if (ch==0x80) ch=ttxCodeAlphaBlack; // Alpha black shenanigans
            char oldChar=line->SetCharAt(cursorLoc.x,ch);
            AddEvent(EventKey,cursorLoc,oldChar,ch);
            if (cursorLoc.x<39) cursorLoc.x++; // right
            SetPageChanged(true);
            return;
        }
    }
    if (modifiers & wxMOD_CONTROL) // Graphics Colours
    {
        char ch='?';
        switch (code) // Map key stroke to control code
        {
            // Graphics colours
            case WXK_F1: ch=ttxCodeGraphicsRed;break;       // Ctrl-F1 red
            case WXK_F2: ch=ttxCodeGraphicsGreen;break;     // Ctrl-F2 green
            case WXK_F3: ch=ttxCodeGraphicsYellow;break;
            case WXK_F4: ch=ttxCodeGraphicsBlue;break;
            case WXK_F5: ch=ttxCodeGraphicsMagenta;break;
            case WXK_F6: ch=ttxCodeGraphicsCyan;break;
            case WXK_F7: ch=ttxCodeGraphicsWhite;break;
            case WXK_F8: ch=ttxCodeGraphicsBlack;break;
            // Special codes
            // A=select all
            case WXK_CONTROL_H: ch=ttxCodeFlash;break;          // Ctrl-H: flash
            case WXK_CONTROL_I: ch=ttxCodeSteady;break;         // Ctrl-I: steady
            case WXK_CONTROL_J: ch=ttxCodeEndBox;break;         // Ctrl-J: end box
            case WXK_CONTROL_K: ch=ttxCodeStartBox;break;       // Ctrl-K: start box
            case WXK_CONTROL_L: ch=ttxCodeNormalHeight;break;   // Ctrl-L: normal height // :-(
            case WXK_CONTROL_M: ch=ttxCodeDoubleHeight;break;   // Ctrl-M: double height

            case WXK_CONTROL_R: ch=ttxCodeConcealDisplay;break;     // Ctrl-R: conceal display
            case WXK_CONTROL_E: ch=ttxCodeContiguousGraphics;
            std::cout << "GOT HERE" << std::endl;
            break; // Was Ctrl-D, and before that CTRL-Y
            case WXK_CONTROL_T: ch=ttxCodeSeparatedGraphics;break;  // Ctrl-T:
            case WXK_CONTROL_U: ch=ttxCodeBlackBackground;break;    // Ctrl-U:
            case WXK_CONTROL_B: ch=ttxCodeNewBackground;break;      // Ctrl-B:
            case WXK_CONTROL_W: ch=ttxCodeHoldGraphics;break;       // Ctrl-W:
            case WXK_CONTROL_X: ch=ttxCodeReleaseGraphics;break;    // Ctrl-X:
                        // Also want to delete!

            case WXK_DELETE:
                // Delete the whole row. Don't think this gets used!
                for (cursorLoc.x=0;cursorLoc.x<40;cursorLoc.x++)
                {
                    AddEvent(EventKey,cursorLoc,line->GetCharAt(cursorLoc.x),' ');
                }
                cursorLoc.x=0;
                line->ClearLine();
                std::cout << "TODO: [1] Implement AddChange " << std::endl;
                ch=0;
                code=0;
                break;
            // Would like to implement CTRL-ENTER, but no dice ;-(

/*            case WXK_RETURN:
                // Move to start of next row
                cursorLoc.x=0;
                if (cursorLoc<23)
                    cursorLoc.y++;
                ch=0;
                break;
                */
            default: ch=0;
        }
        if (ch>0)
        {
            std::cout << "Control code sent: " << (int)ch << std::endl;
            char oldChar;
            oldChar=line->SetCharAt(cursorLoc.x,ch);
            AddEvent(EventKey,cursorLoc,oldChar,ch);
            // Advance the cursor
            if (cursorLoc.x<39)
            {
              cursorLoc.x++; // right
            }
            SetPageChanged(true);
            return;
        }
    }

    // std::cout << "Code trace 2=" << code << std::endl;
    /* Some keys need remapping from English PC keyboard into the teletext world. TODO: Localizing */
    switch (GetLanguage())
    {
    case 0: // English
        if (code==35)  code=0x5f;   // Hash
        if (code==163) code=0x23;   // Pound sign
        if (code==172) code=0x7f;   // Hook symbol -> Bullet block
        break;
        // TODO: The other languages might have sensible mappings to apply
    default:;
    }

    char currentCh; // What is the current character that we are on?
    // currentCh=line->Getm_textline()[cursorLoc.x]; // LAME
    currentCh=line->GetCharAt(cursorLoc.x);
    AlphaMode=AlphaMode || (currentCh>='@' && currentCh<=0x5f) || currentCh<' '; // More accurately, AlphaMode should be called NotGraphicsMode

    if (code>=' ') // Cursor and printables
    {
        switch (code)
        {
        case WXK_DELETE : // all characters to the right shift one to the left
          {
            auto loc=cursorLoc;
            for (;loc.x<39;loc.x++)
            {
              char ch=line->GetCharAt(loc.x+1);
              AddEvent(EventKey,loc,line->GetCharAt(loc.x),ch);
              line->SetCharAt(loc.x,ch);
            }
            // Last character is stuffed with a space
            char ch=line->GetCharAt(39);
            AddEvent(EventKey,loc,ch,' ');
            line->SetCharAt(39,' ');
          }
          break;
        case WXK_HOME : // Move to start of line
            {
              uint8_t cursorX=cursorLoc.x;
              for (cursorLoc.x=0;cursorLoc.x<40;cursorLoc.x++)
              {
                if (line->GetCharAt(cursorLoc.x)>' ')
                {
                  if (cursorX==cursorLoc.x) // already at the start of text?
                  {
                    cursorLoc.x=0;
                  }
                  break;
                }
              }
            }
            if (cursorLoc.x==40) // Reached the end of the line?
            {
              cursorLoc.x=0;                // reset to the beginning
            }
            break;
        case WXK_END : // Move to end of line. (or if already there, the last printable character)
            {
              uint8_t cursorX=cursorLoc.x;
              for (cursorLoc.x=39;cursorLoc.x>0;cursorLoc.x--)
              {
                if (line->GetCharAt(cursorLoc.x)>' ')
                {
                  cursorLoc.x++; // Position at the start of the trailing blank space
                  if (cursorX==cursorLoc.x) // already at the end of text?
                  {
                    cursorLoc.x=39;
                  }
                  break;
                }
              }
            }
            if (cursorLoc.x==0) // Reached the start of the line?
            {
              cursorLoc.x=39;    // reset to the end
            }
            break;
        case WXK_LEFT : // left 314
            if (cursorLoc.x>8 || (cursorLoc.x>0 && cursorLoc.y>0)) // First 8 chars of header are off limits
            {
                if (AlphaMode)
                {
                    cursorLoc.x--;
                    cursorSubLoc.x=1;   // In case we land on a graphics
                }
                else
                {
                    //std::cout << "left graphics" << std::endl;
                    switch (cursorSubLoc.x)
                    {
                    case 0:
                        cursorLoc.x--;
                        cursorSubLoc.x=1;
                        break;
                    case 1:
                        cursorSubLoc.x=0;
                        break;
                    default : cursorSubLoc.x=0;
                    }
                }
            }
            break;
        case WXK_UP : // up 315
            if (AlphaMode)
            {
                if (cursorLoc.y>yMin) // 1 (no header) or 0 (header)
                {
                    // If we would move into the lower row of a double height, we need to decrement twice.
                    if (cursorLoc.y>2)
                    {
                      if (GetRow(cursorLoc.y-2)->HasDoubleHeight())
                      {
                        cursorLoc.y--;
                      }
                    }
                    cursorLoc.y--;
                    cursorSubLoc.y=2;
                    if (cursorLoc.x<8 && cursorLoc.y==0) cursorLoc.x=8; // Don't stumble into forbidden header area
                }
            }
            else
            {
              // @todo Implement up arrow across double height graphics. (was anyone daft enough to use this?)
                switch (cursorSubLoc.y)
                {
                case 0:
                    if (cursorLoc.y>yMin)
                    {
                        cursorLoc.y--;
                        cursorSubLoc.y=2;
                        if (cursorLoc.x<8 && cursorLoc.y==0) cursorLoc.x=8; // Don't stumble into forbidden header area
                    }
                    break;
                case 1:;
                case 2:
                    cursorSubLoc.y--;
                    break;
                default : cursorSubLoc.y=0;
                }
            }
            break;
        case WXK_DOWN : // down 317
            if (AlphaMode)
            {
                if (cursorLoc.y<24)
                {
                    // If the last location was the top half of a double height, we need to increment twice.
                    if (GetRow(cursorLoc.y)->HasDoubleHeight() && cursorLoc.y<23)
                    {
                      cursorLoc.y++;
                    }
                    cursorLoc.y++;
                    cursorSubLoc.y=0;
                }
            }
            else
            {
                // @todo Implement up/down over graphic areas.
                switch (cursorSubLoc.y)
                {
                case 0:;
                case 1:
                    cursorSubLoc.y++;
                    break;
                case 2:
                    if (cursorLoc.y<24)
                    {
                        cursorLoc.y++;
                        cursorSubLoc.y=0;
                    }
                    break;
                default : cursorSubLoc.y=0;
                }
            }
            break;
        case WXK_RIGHT : // right 316
            if (AlphaMode)
            {
                if (cursorLoc.x<39)
                {
                    cursorLoc.x++;
                    cursorSubLoc.x=0;
                }
            }
            else
            {
                // std::cout << "right graphics" << std::endl;
                switch (cursorSubLoc.x)
                {
                case 0:
                    cursorSubLoc.x=1;
                    break;
                case 1:
                    if (cursorLoc.x<39)
                    {
                        cursorLoc.x++;
                        cursorSubLoc.x=0;
                    }
                    break;
                default : cursorSubLoc.x=0;
                }
            }
            break;
        default :
            // std::cout << "Default branch taken in SetCharAt " << (int)code << " i=" << instance << std::endl;
            if (line)
            {
                // By now we should only have teletext codes. If the new code is NOT a graphic then treat it as a character
                if (code<0x80) // Only want basic ASCII codes
                {
                    SetPageChanged(true);

                    if (AlphaMode || (code>='@' && code<=0x5f) || code<' ')
                    {
                        // std::cout << "Setting alpha char " << (int)code << std::endl;
                        char oldChar=line->SetCharAt(cursorLoc.x,code);
                        AddEvent(EventKey,cursorLoc,oldChar,code);
                        if (cursorLoc.x<39)
                        {
                          cursorLoc.x++; // right
                        }
                        else
                        {
                            // If this is double height, we need to skip an extra line
                          if (cursorLoc.y<23 && line->HasDoubleHeight())
                          {
                            cursorLoc.y++;
                          }
                          if (cursorLoc.y<24)
                          {
                            cursorLoc.y++;
                            cursorLoc.x=0;
                            // If we have effects set up on the left edge we would lose it
                            // so we check the first three characters just in case
                            TTXLine* line2=m_pLine[cursorLoc.y];
                            // Allow for up to three control codes on a wrap
                            if ((int) line2->GetCharAt(cursorLoc.x)<20) cursorLoc.x++;
                            if ((int) line2->GetCharAt(cursorLoc.x)<20) cursorLoc.x++;
                            if ((int) line2->GetCharAt(cursorLoc.x)<20) cursorLoc.x++;
                          }

                        }

                    }
                    else
                    {
                        char bit=0;
                        char ch1=' ';
                        // If space was pressed in graphics mode then toggle the current pixel colour
                        switch (code)
                        {
                        case WXK_SPACE: // Toggle a graphics pixel
                            bit=0x00;
                            std::cout << "Toggle a graphics pixel" << std::endl;
                            switch (cursorSubLoc.x+cursorSubLoc.y*2)
                            {
                            case 0: bit=0x01;break;
                            case 1: bit=0x02;break;
                            case 2: bit=0x04;break;
                            case 3: bit=0x08;break;
                            case 4: bit=0x10;break;
                            case 5: bit=0x40;break;
                            }
                            break;
                        // qwaszx editing keys, one for each pixel in graphics mode
                        case 'q': bit=0x01;break;
                        case 'w': bit=0x02;break;
                        case 'a': bit=0x04;break;
                        case 's': bit=0x08;break;
                        case 'z': bit=0x10;break;
                        case 'x': bit=0x40;break;
                        // whole sixel operations
                        case 'r': bit=0x5f;break; // reverse
                        case 'f': bit=~line->GetLine()[cursorLoc.x] & 0x5f;break; // fill all
                        case 'c': bit= line->GetLine()[cursorLoc.x] & 0x5f;break; // clear all
                        default:bit=0;
                        }
                        if (bit>0) // If it was a graphic change, record it
                        {
                            char oldChar=line->SetCharAt(cursorLoc.x,ch1=line->GetLine()[cursorLoc.x]^bit);
                            AddEvent(EventKey,cursorLoc,oldChar,ch1);
                        }
                    }
                }
            }
            else
                std::cout << "Probably a good idea to determine why this is NULL and make a line if needed." << std::endl;
        }
    }
    else
    {
        // Deal with control codes that we might get sent
        // Backspace, line feed, carriage return. A lot of stuff to trap
        char oldChar;
        switch (code)
        {
        case WXK_BACK : // backspace 8
            if (cursorLoc.x>0) cursorLoc.x--;   // Move left if possible
            oldChar=line->SetCharAt(cursorLoc.x,' ');   // And clear the character that we land on
            AddEvent(EventKey,cursorLoc,oldChar,' ');
            break;
        case WXK_RETURN : // Double height
            oldChar=line->SetCharAt(cursorLoc.x,'\r');   // Insert a double height
            if (cursorLoc.x<39) cursorLoc.x++;   // Move right if possible
            AddEvent(EventKey,cursorLoc,oldChar,'\r');
        case WXK_TAB : // Insert space
          {
            auto loc=cursorLoc;
            for (loc.x=39;loc.x>cursorLoc.x;loc.x--)
            {
              char oldch=line->GetCharAt(loc.x);
              char newch=line->GetCharAt(loc.x-1);
              AddEvent(EventKey, loc, oldch, newch);
              line->SetCharAt(loc.x,newch);
            }
            // Last character is stuffed with a space
            AddEvent(EventKey, loc, line->GetCharAt(cursorLoc.x), ' ');
            line->SetCharAt(cursorLoc.x, ' '); // The current location is now a space
          }
          break;
        default:
            std::cout << "This key code is not implemented: " << code << std::endl;
        }
    }
}

void TTXPage::m_OutputLines(std::ofstream& ttxfile, TTXPage* p)
{
  ttxfile << "PN," << m_FormatPageNumber(p) << "\n";
  if (p->m_subcode<0)
  {
    ttxfile << "SC,0000" << "\n";
  }
  else
  {
    ttxfile << "SC," << std::dec << std::setw(4) << std::setfill('0') << p->m_subcode << "\n";   // Subcode for these lines
  }
  ttxfile << "PS," << std::setw(4) << std::setfill('X') << std::hex << p->m_pagestatus << std::endl;

  // that we can have individual timings and properties per page.
  ttxfile << "CT," << std::dec << p->m_cycletimeseconds << "," << p->m_cycletimetype << std::endl;

  ttxfile << "RE," << std::setw(1) << std::hex << p->m_region << std::endl;
  // @todo Add support for individual CT timers here.


  // The order is weird.
  // First output row 0
  // Then the enhancement packets
  // Then the normal text rowa
  std::string s=p->m_pLine[0]->GetMappedline7bit();
  ttxfile << "OL," << std::dec << 0 << "," << s << "\n";
  for (int j=0;j<MAXROW;j++)
  {
    int i=1+((24+j) % MAXROW); // Ensure that enhancement packets go out first. It helps with vbit
    if (p->m_pLine[i]!=nullptr && !p->m_pLine[i]->IsBlank()) // Skip empty lines
    {
        // This one for Andreas
//             std::string s=p->m_pLine[i]->GetMappedline(); // Choose the 7 bit output as it is more useful. TODO: Make this a menu option.
        // This one for Droidfax compatibility
      s=p->m_pLine[i]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful. TODO: Make this a menu option.
      ttxfile << "OL," << std::dec << i << "," << s << "\n";
  }
  }
  std::cout << "sent a subpage" << "\n";
}

std::string TTXPage::m_FormatPageNumber(TTXPage* p)
{
  std::ostringstream PN;
  int page=p->m_PageNumber;
  // Split the page number mppss
  int mpp=page >> 8; // This bit is hex
  int ss=page & 0xff; // But this bit is decimal
  PN << std::hex << std::setw(3) << mpp << std::setfill('0') << std::dec << std::setw(2) << ss;
  return PN.str();
}

bool TTXPage::SavePageDefault()
{
  return SavePage(GetSourcePage());
}


/* 8 bit save */
bool TTXPage::SavePage(std::string filename)
{
  std::ofstream ttxfile(filename.c_str()); // TODO: Save and Save as
  SetSourcePage(filename);
  // Fix up subcodes.
  // Subcodes need to be ascending starting from 1
  if (Getm_SubPage())
  {
    // Fix up subcodes.
    // Subcodes need to be ascending starting from 1
    int sc=1;
    int pageNum=this->GetPageNumber() & 0xfff00; // Mask off the original subcode
    for (TTXPage* p=this;p!=nullptr;p=p->m_SubPage)
    {
      p->SetSubCode(sc);            // Monotonic subcode
      p->SetPageNumber(pageNum + (sc & 0xff)); // Fix the page number too. (@todo: sc needs to be decimal, not hex)
      sc++;
    }
  }
  if (ttxfile.is_open())
  {
    ttxfile << std::dec ;
    std::cout << "[TTXPage::SavePage] filename=" << filename << std::endl;
    ttxfile << "DE," << m_description << std::endl;
    //ttxfile << "PN," << std::hex << std::setprecision(5) << m_PageNumber << std::endl;
    ttxfile << "DS," << m_destination << std::dec << std::endl;
    ttxfile << "SP," << GetSourcePage() << std::endl; // SP is set every time there is a save
    // My spidey instincts tell me that this code could be factorised
    m_OutputLines(ttxfile, this);
    ttxfile << std::hex;
    // Don't output null links
    if (m_fastextlinks[0]!=0x8ff)
    {
      ttxfile << "FL,"
      << m_fastextlinks[0] << ","
      << m_fastextlinks[1] << ","
      << m_fastextlinks[2] << ","
      << m_fastextlinks[3] << ","
      << m_fastextlinks[4] << ","
      << m_fastextlinks[5] << std::endl;
    }
    ttxfile << std::dec;
    // Now also have to traverse the rest of the page tree
    if (Getm_SubPage())
    {
      if (Getm_SubPage()->m_subcode>=0) // Shouldn't have to test this!
      {
        std::cout << "m_SubPage=" << std::hex << Getm_SubPage() << std::endl;
        for (TTXPage* p=this->m_SubPage;p!=nullptr;p=p->m_SubPage)
        {
          m_OutputLines(ttxfile, p);
          // Subpages now have an identical copy of the main fastext links
          // Don't output null links
          if (m_fastextlinks[0]!=0x8ff)
          {
            ttxfile << std::hex;
            ttxfile << "FL,"
            << m_fastextlinks[0] << ","
            << m_fastextlinks[1] << ","
            << m_fastextlinks[2] << ","
            << m_fastextlinks[3] << ","
            << m_fastextlinks[4] << ","
            << m_fastextlinks[5] << std::endl;
            ttxfile << std::dec;
          }
        }
      }
    }
  }
  else
  {
    return false; // fail
  }
  SetPageChanged(false);
  return true; // success
}

bool TTXPage::IsAlphaMode(wxPoint loc)
{
  bool result=true;
  // Check that the parameter is valid
  if (loc.x<0 || loc.x>39 || loc.y<1 || loc.y>24) return result;
  // Get pointer to the relevant line
  TTXLine* line=m_pLine[loc.y];
  if (line)
  {
    result=line->IsAlphaMode(loc.x);
  }
  return result;
}

int TTXPage::GetPageCount()
{
  int count=0;
  int subcode=0;
  for (TTXPage* p=this;p!=nullptr;p=p->m_SubPage)
  {
     // std::cout <<"Get page count happens here, subcode=" << subcode << " " << (int)p << std::endl;
     if (p)
     {
        p->SetSubCode(subcode++);   // Always redo the subcodes
     }
      count++;
  }
  //std::cout << "GetPageCount returns " << count << std::endl;
  return count;
}

void TTXPage::CopyMetaData(TTXPage* page)
{
  m_PageNumber=page->m_PageNumber;
  for (int i=0;i<6;i++)
  {
    SetFastextLink(i,page->GetFastextLink(i));
  }

  m_destination=page->m_destination;  // DS
  SetSourcePage(page->GetSourcePage());// SP
  m_description=page->m_description;  // DE
  m_cycletimeseconds=page->m_cycletimeseconds;     // CT
  m_cycletimetype=page->m_cycletimetype;       // CT
  m_subcode=page->m_subcode;              // SC
  m_pagestatus=page->m_pagestatus;           // PS
  m_region=page->m_region;            // RE
}

void TTXPage::SetLanguage(int language)
{
  language=language & 0x07;   // Limit language 0..7
  m_pagestatus=m_pagestatus & ~0x0380; // Clear the old language bits
  m_pagestatus=m_pagestatus | (language << 7);   // Shift the language bits into the right place and OR them in
  // std::cout << "Set Language: PS," << std::setw(4) << std::setfill('X') << std::hex << m_pagestatus << std::endl;
}

int TTXPage::GetLanguage()
{
  int language;
  language=(m_pagestatus >> 7) & 0x07;
  // std::cout << "Get Language PS," << std::setw(4) << std::setfill('X') << std::hex << m_pagestatus << std::endl;
  return language;
}

void TTXPage::SetPageNumber(int page)
{
  if ((page<0x10000) || (page>0x8ff99))
  {
    std::cout << "Page number is out of range: " << page << std::endl;
  }
  if (page<0x10000) page=0x10000;
  if (page>0x8ff99) page=0x8ff99;

  if (m_PageNumber!=page)
  {
    SetPageChanged(true);
  }
  m_PageNumber=page;
}

int TTXPage::GetFastextLink(int link)
{
  if (link<0 || link>5)
  {
    return 0;
  }
  return m_fastextlinks[link];
}

void TTXPage::SetFastextLink(int link, int value)
{
  if (link<0 || link>5 || value>0x8ff)
  {
    m_fastextlinks[link]=0x8ff; // When no particular page is specified
    return;
  }
  m_fastextlinks[link]=value;
}


// @todo This doesn't support undo/redo
void TTXPage::InsertLine(wxPoint& cursorLoc)
{
  int y=cursorLoc.y;
  for (int i=23;i>y;i--)
  {
    std::string line=GetRow(i-1)->GetLine();
    SetRow(i, line);
  }
  SetRow(y,"                                        ");
}

// @todo This doesn't support undo/redo
void TTXPage::DeleteLine(wxPoint& cursorLoc)
{
  int y=cursorLoc.y;
  for (int i=y;i<23;i++)
  {
    std::string line=GetRow(i+1)->GetLine();
    SetRow(i, line);
  }
  SetRow(23,"                                        ");
}
