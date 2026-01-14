#include "ttxpageset.h"

/** ctor
 *  Load a teletext page from file
 * \param filename : Name of teletext file to load
 * \param shortFilename : Filename without path
 */
TTXPageSet::TTXPageSet()
{
  m_Init();
}


/** ctor
 *  Load a teletext page from file
 * \param filename : Name of teletext file to load
 * \param shortFilename : Filename without path
 */
TTXPageSet::TTXPageSet(std::string filename, std::string shortFilename)
{
  m_Init();
  //ctor
  //std::cout << "[TTXPage] file constructor" << std::endl;
  SetSourcePage(filename);
  SetShortFilename(shortFilename);

  std::ifstream file(filename);
  auto p = GetPage(0);
  if (not file.good())
  {
    p->SetRow(5,filename);
    p->SetRow(8,"Q7#####################################k");
    p->SetRow(9,"Q5ASoftware Failure. Your teletext    Qj");
    p->SetRow(10,"Q5Apage could not be loaded.          Qj");
    p->SetRow(11,"Q5                                    Qj");
    p->SetRow(12,"Q5A    Guru Meditation _baadf00d      Qj");
    p->SetRow(13,"Q-,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.");
    p->SetRow(14,"Q                                       ");
    p->SetRow(15,"Q                   `&)0                ");
    p->SetRow(16,"Q                  `%h4*0               ");
    p->SetRow(17,"Q                 `% j5 *0              ");
    p->SetRow(18,"Q                `&  b1  )0             ");
    p->SetRow(19,"Q                uppprqpppz             ");
    SetSourcePage("Unable to load page");
    SetShortFilename("no page");

    return;
  }
  file.close();

  // Try all the possible formats.
 int type=1;
  if (!m_loaded) // [!] Will never be set
  {
    p->SetRow(1,"                                        ");
    if (m_LoadTTI(filename))
    {
      m_loaded=true;
    }
  }

  if (!m_loaded)
  {
    p->SetRow(1,"Trying T42");
    if (m_LoadT42(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    p->SetRow(1,"Trying VTX");
    if (m_LoadVTX(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    p->SetRow(1,"Trying VTP");
    if (m_LoadVTP(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    p->SetRow(1,"Trying EP1");
    if (m_LoadEP1(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    p->SetRow(1,"                                        ");
    if (m_LoadTTX(filename))
    {
      m_loaded=true;
    }
    type++;
  }

  if (!m_loaded)
  {
    p->SetRow(1,"Unable to load file");
    p->SetRow(3,shortFilename);
    p->SetRow(4,"?");
    p->SetRow(5,filename);
    SetSourcePage("Unable to load page");
    SetShortFilename("no page");
  }

  SetPageChanged(false);
  std::cout << "Finished reading page. Loaded=" << m_loaded << " type=" << type << std::endl;
}

void TTXPageSet::m_Init()
{
  m_destination="inserter";
  m_description="Description goes here";
  SetSourcePage("");
  SetShortFilename("");
  m_currentPageIndex = 0,
  undoList = nullptr,
  m_current = nullptr,
  m_loaded = false;
  // std::vector<std::unique_ptr<TTXPage>> pages; /// Where all the pages are stored
  pages.emplace_back(std::make_unique<TTXPage>()); /// @todo Replace this with AddPage function
  SetPageNumber(FIRSTPAGE); // Valid but unlikely page
  SetPageChanged(false);
}

TTXPageSet::~TTXPageSet()
{
  //dtor
}

bool TTXPageSet::m_LoadT42(std::string filename)
{
  auto p = GetPage(0); // @todo Placeholder. T42 can do carousels
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  if (not filein.good())
  {
    return false;
  }

  // T42 is raw teletext data.
  std::cout << "Trying T42" << std::endl;
  T42* t42;
  char buf[500];
  bool ok{false};

  // todo Decode the packet to see what we do
  // header/text line/fastext/other.
  bool page_done{false};
  for (uint8_t i = 0; !page_done; i++)
  {
      // Read in a packet
      filein.read(buf,42); // TODO: Check for a failed read and abandon
      t42 = new T42(buf);
      // What sort of packet is it?
      int mag = t42->GetMag();
      int row = t42->GetRow();
      // @todo row 0 should extract the page number and flags
      std::cout << "[TTXPageSet::m_LoadT42] packet = " << mag << "/" << row << std::endl;
      // End of file should also terminate

      if (mag < 8) ok = true;

      if (row > 0)
      {
          // @todo None of this should happen for row 0
          if (mag == 0xff || row == 0xff || filein.eof())
          {
              page_done = true;
              ok = false;
          }
          else
          {
                std::string s(&buf[2]);
                p->SetRow(row,s);
          }
      }
      else // Row 0 header
      {
          HeaderPacket header_packet{*t42};
          char str[50];
          strncpy(str, "        ",8);
          strncat(str, header_packet.GetHeading(),24);
          strncat(str, header_packet.GetTime(),8);
          auto page_number=((header_packet.GetMag()) % 8) * 0x100 + header_packet.GetPageNumber();
          SetPageNumber(page_number * 0x100); // Because we use old MRG mppss page numbers
          // @todo Add subcode. Although I think this is now implied by the vector slot
          p->SetRow(0,str);

          std::cout << "[load t42] str = " << str << std::setw(4) << " page number = " << page_number << std::endl;
      }
  }
  // Open the file
  // Process packets
  // Expect a row 0 with header details and a magazine
  // Then a number of lines each with the same magazine
  // and a row number.
  // There are probably other rows too.
  // The load is terminated by another row 0 or the end of data.
 //   for (int line=1;line<25;line++)
  //{
//    filein.read(buf,42); // TODO: Check for a failed read and abandon
    //std::string s(buf);
    //p->SetRow(line,s);
  //}

  filein.close();
  return ok;
}

// See http://rtlalphanet.asp.tss.nl/RTL4/100s01 for examples
bool TTXPageSet::m_LoadVTX(std::string filename)
{
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  if (not filein.good())
  {
    return false;
  }

  std::cout << "Trying VTX" << std::endl;
  char buf[500];
  auto p = GetPage(0);

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
  p->SetRow(0,"         wxTED %%# %%a %d %%b \x3 %H:%M.%S"); // Overwrite anything in row 0 (usually empty)
  // With a pair of zeros at the end we can skip
  filein.close(); // Not sure that we need to close it
  SetPageChanged(false);
  return true;
}

bool TTXPageSet::m_LoadEP1(std::string filename)
{
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  if (not filein.good())
  {
    return false;
  }

  char buf[100];
  auto p = GetPage(0);

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
  p->SetRow(0,"         wxTED %%# %%a %d %%b \x3 %H:%M.%S"); // Overwrite anything in row 0 (usually empty)
  // With a pair of zeros at the end we can skip
  filein.close(); // Not sure that we need to close it
  SetPageChanged(false);
  return true;
}

bool TTXPageSet::m_LoadVTP(std::string filename)
{
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  if (not filein.good())
  {
    return false;
  }

  char buf[0x100];
  auto p = GetPage(0);
  int subPageCount=0;

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
      auto p = GetPage(0); /// @todo Extend this for multiple pages
      // Do we have to add a page to the pages vector? @todo
      // p->Setm_SubPage(newSubPage);        // Put in a link to it
      // p=newSubPage;                       // And jump to the next subpage ready to populate
    }
  }
  // With a pair of zeros at the end we can skip
  filein.close(); // Not sure that we need to close it
  SetPageChanged(false);
  return true;
}

bool TTXPageSet::m_LoadTTX(std::string filename)
{
  std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
  if (not filein.good())
  {
    return false;
  }

  char buf[1100]; // Don't think we need this much buffer. Just a line will do
  auto p = GetPage(0);

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
                      SetPageNumber(pageNum);
                  }
              }
              for (int j=0;j<40;j++) if (buf[j]=='\0') buf[j]=ttxCodeAlphaBlue; // Should be Alpha black! But tricky!
              p->SetRow(i,buf);
          }

          filein.close();
          // p->Setm_SubPage(nullptr);
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
  p->SetRow(0,"         wxTED %%# %%a %d %%b \x3 %H:%M.%S"); // Overwrite anything in row 0 (usually empty)

  filein.close();
  // p->Setm_SubPage(nullptr);
  SetPageChanged(false);
  return true;
}

bool TTXPageSet::m_LoadTTI(std::string filename)
{
    const std::string cmd[]={"DS","SP","DE","CT","PN","SC","PS","MS","OL","FL","RD"};
    const int cmdCount(11); // Number of possible commands, maybe DT and RT too on really old files
    unsigned int lineNumber;
    int lines=0;
    // Open the file
    std::ifstream filein(filename.c_str());
    if (not filein.good())
    {
      return false;
    }

    // Clear pages and start a new page.
    pages.clear();
    pages.emplace_back(std::make_unique<TTXPage>());
    auto p = pages[0].get(); // Page pointer

    char * ptr;
    int subcode;
    std::string subpage;
    int pageNumber;
    char m;
    for (std::string line; std::getline(filein, line, ','); )
    {
         std::cout << line << std::endl; // Shows the command code
        bool found=false;
        for (int i=0;i<cmdCount && !found; i++)
        {
            // std::cout << "matching " << line << std::endl;
            if (!line.compare(cmd[i]))
            {
                found=true;
                std::cout << "Matched " << line << std::endl;
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
                    std::getline(filein, m_description);
                    std::cout << "DE read : " << m_description << std::endl;

                    break;
                case 3 : // "CT" - Cycle time (seconds). This is a per subpage function
                    // CT,8,T
                    // std::cout << "CT not implemented\n";
                    std::getline(filein, line, ',');
                    p->SetCycleTime(atoi(line.c_str()));
                    std::getline(filein, line);
                    p->SetCycleTimeMode(line[0]=='T'?'T':'C');
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
                        pageNumber*=0x100; // Shift to make a five digit number
                    }
                    else   // Normally has a subpage
                    {
                        subpage=line.substr(3,2);
                        std::cout << "Subpage=" << subpage << std::endl;
                        pageNumber=(pageNumber & 0xfff00) + std::strtol(subpage.c_str(),nullptr,10);
                    }
                    std::cout << "PN enters with m_PageNumber=" << std::hex << m_PageNumber << " pageNumber=" << std::hex << pageNumber << std::endl;
                    if (m_PageNumber!=FIRSTPAGE) // // Subsequent pages need new page instances
                    {
                      std::cout << "Created a new subpage" << std::endl;
                      pages.emplace_back(std::make_unique<TTXPage>()); // make the page
                      p = pages.back().get(); // get a pointer to the next page
                    }
                    SetPageNumber(pageNumber);
                    // @todo Probably want to set a subpage number, or do we just imply it from the index in the vector?

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
                    // @todo Pretty sure that this needs to be in TTXPage
                    // m_pageStatus=std::strtol(line.c_str(), &ptr, 16);
                    p->SetPageStatus(std::strtol(line.c_str(), &ptr, 16));
                    // Don't copy the bits to the UI...
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
                    if (lineNumber>MAXROW)
                    {
                      break;
                    }
                    // std::cout << "reading " << lineNumber << std::endl;
                    p->SetRow(lineNumber, line);
                    if (lineNumber==28)
                    {
                      p->SetRow28(std::make_shared<TTXRow28>(line));
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
                        p->SetFastextLink(fli,std::strtol(line.c_str(), &ptr, 16));
                    }
                    break;
                case 10 : // "RD"; - not sure!
                    std::getline(filein, line);
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
    // Setm_SubPage(nullptr);
    std::cout << "Finished reading TTI page. Line count=" << lines << ", page count = " << pages.size() << std::endl;
    p->SetPageChanged(false);
    SetPageChanged(false);
    return (lines>0);
}

bool TTXPageSet::GetPageChanged()
{
  // Page number or something like that changed?
  if (pageChanged)
  {
    return true;
  }
  // One of the page list has changed?
  for (const auto& p : pages )
  {
    if (p->GetPageChanged())
    {
      return true;
    }
  }
  return false;
}

bool TTXPageSet::SavePageDefault()
{
  return SavePage(GetSourcePage());
}


/* 8 bit save */
bool TTXPageSet::SavePage(std::string filename)
{
  std::ofstream ttxfile(filename.c_str());
  if (ttxfile.is_open())
  {
    SetSourcePage(filename);
    // Fix up subcodes.
    // Weird rule. Not sure if it is a real one:
    // If there is only one page, the subcode should be 0
    // If there are subpages the subcode should be ascending starting from 1
    int sc = 0;
    if (pages.size() > 1)
    {
      sc = 1;
    }
    int pageNum=this->GetPageNumber() & 0xfff00; // Mask off the original subcode
    ttxfile << std::dec ;
    std::cout << "[TTXPage::SavePage] filename=" << filename << std::endl;
    ttxfile << "DE," << m_description << std::endl;
    //ttxfile << "PN," << std::hex << std::setprecision(5) << m_PageNumber << std::endl;
    ttxfile << "DS," << m_destination << std::dec << std::endl;
    ttxfile << "SP," << GetSourcePage() << std::endl; // SP is set every time there is a save
    for (auto const& p : pages)
    {
      p->SetSubCode(sc);            // Monotonic subcode
      SetPageNumber(pageNum + (sc & 0xff)); // Fix the page number too. (@todo: sc needs to be decimal, not hex)
      sc++;
      // My spidey instincts tell me that this code could be factorised
      p->OutputLines(ttxfile, GetPageNumber());
      ttxfile << std::hex;
      // Output links if any link is valid
      if ( p->GetLink(0) != 0x8ff || p->GetLink(1) != 0x8ff || p->GetLink(2) != 0x8ff || p->GetLink(3) != 0x8ff )
      {
        ttxfile << "FL,"
        << p->GetLink(0) << ","
        << p->GetLink(1) << ","
        << p->GetLink(2) << ","
        << p->GetLink(3) << ","
        << p->GetLink(4) << ","
        << p->GetLink(5) << std::endl;
      }
      ttxfile << std::dec;
    }
  }
  else
  {
    return false; // fail
  }
  SetPageChanged(false);
  return true; // success
}

void TTXPageSet::SetPageNumber(int mppss)
{
  if ((mppss<0x10000) || (mppss>0x8ff99))
  {
    // std::cout << "Page number is out of range: " << mppss << std::endl;
    if (mppss>=0x100 && mppss <=0x8ff) // Fix a missing subcode ss if only mpp is supplied
    {
      mppss *= 0x100;
    }
  }
  // Clip limits
  if (mppss<0x10000)
  {
    mppss=0x10000;
  }
  else
  if (mppss>0x8ff99)
  {
    mppss=0x8ff99;
  }

  // Don't flag a subcode change as a page change
  if ((m_PageNumber & 0x8ff00) != (mppss & 0x8ff00))
  {
    SetPageChanged(true);
  }
  m_PageNumber=mppss;

  // subcode ss is implied by the position in the pages vector
}

int TTXPageSet::GetPageNumber()
{
  unsigned int mpp = m_PageNumber & 0xfff00; // Strip the subcode
  // The subcode is decimal 00..99
  // but we need to store it in a hex encoded variable
  unsigned int subCode = m_currentPageIndex;
  unsigned tens = subCode / 10;
  unsigned units = subCode % 10;
  subCode = tens * 0x10 + units;
  return mpp | subCode;
}


int TTXPageSet::findPageNumber(char* buf)
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

// Page management. Current page, add page, delete page
TTXPage* TTXPageSet::CurrentPage()
{
  return pages[m_currentPageIndex].get();
}

TTXPage* TTXPageSet::PreviousPage()
{
  if (m_currentPageIndex == 0)
  {
    if (pages.size() > 1)
    {
      m_currentPageIndex = pages.size() - 1;
    }
  }
  else
  {
    m_currentPageIndex--;
  }
  std::cout << "Prev: Selected page " << m_currentPageIndex << std::endl;
  return pages[m_currentPageIndex].get();
}

TTXPage* TTXPageSet::NextPage()
{
  m_currentPageIndex++;
  if (m_currentPageIndex >= pages.size())
  {
    m_currentPageIndex = 0;
  }
  std::cout << "Next: Selected page " << m_currentPageIndex << std::endl;
  return pages[m_currentPageIndex].get();
}

TTXPage* TTXPageSet::SelectPage(int pageIndex)
{
  if (pageChanged < pages.size())
  {
    m_currentPageIndex = pageIndex;
  }
  return pages[m_currentPageIndex].get();
}

void TTXPageSet::debug(std::string message)
{
//  std::cout << "pageSet size = " << pages.size() << " " << message << std::endl;
}

void TTXPageSet::InsertPageAfter() // Insert a new page after the current page
{
  // We can't just emplace back our way out of this one
  // 1. Ensure the index is within valid bounds
  if (m_currentPageIndex >= 0 && m_currentPageIndex < static_cast<int>(pages.size()))
  {
    // 2. Insert after the current index (m_currentPageIndex + 1)
    // std::move is required because unique_ptr cannot be copied
    pages.insert(pages.begin() + m_currentPageIndex + 1, std::make_unique<TTXPage>());

    // 3. Update the index to the newly created page
    m_currentPageIndex++;
  }
  else if (pages.empty())
  {
      // Handle case where list is empty
      pages.push_back(std::make_unique<TTXPage>());
      m_currentPageIndex = 0;
  }
  std::ostringstream str;
  str << "New subpage inserted " << CurrentPageIndex() << "/" << pages.size();
  CurrentPage()->SetRow(1,str.str());


  /* TODO!! 1) Copy region and language flags from previous page
     TODO. 2) Add little message to indicate that this is a new page
    //std::cout << "Insert page after #" << iPage << std::endl;
    std::shared_ptr<TTXPage> p;
    std::shared_ptr<TTXPage> childPage;
    // Create a new page
    p = std::shared_ptr<TTXPage>(new TTXPage());
    m_setLanguage(true);
    SetRegionMenu(pageSet->CurrentPage()->GetRegion(true), true); // Region language [!] Move to dialog and add second G0
    iPage++;
    // Save the child page pointer
    childPage=pageSet->CurrentPage()->Getm_SubPage();
    // Set the child pointer to the new child page
    pageSet->CurrentPage()->Setm_SubPage(p);
    // Make the new page the current one
    pageSet->CurrentPage()=p;
    // Set the child pointer to the saved pointer
    pageSet->CurrentPage()->Setm_SubPage(childPage);

    // Recalculate the subcode sequence.
    m_iPageCount=pageSet->GetPage(0)->GetPageCount();

    // Put up a welcome message
    std::ostringstream str;
    str << "New subpage inserted " << iPage+1 << "/" << m_iPageCount;
    pageSet->CurrentPage()->SetRow(1,str.str());
    // pageSet->GetPage(0)->pageChanged=true;
    ShowPreviewMenu();
    */

}

void TTXPageSet::DeletePage() // Delete the current page
{
  if (m_currentPageIndex >= 0 && // Index is not negative?
      m_currentPageIndex < static_cast<int>(pages.size() - 1)) // Index is in range and the page vector has more than one page
  {
    // Erase the element at the current index
    // This automatically deletes the TTXPage object
    pages.erase(pages.begin() + m_currentPageIndex);

    // Update index to the previous page, or 0 if there is only one item.
    m_currentPageIndex = std::max(0, m_currentPageIndex - 1);
  }
}
