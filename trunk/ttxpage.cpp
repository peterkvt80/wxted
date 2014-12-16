/** ***************************************************************************
 * Description       : Class for a teletext page
 * Compiler          : C++
 *
 * Copyright (C) 2014, Peter Kwan
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
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 *************************************************************************** **/
 #include "ttxpage.h"

TTXPage::TTXPage() : undoList(0), m_current(0)    //ctor
{
    m_Init();
}

static int instanceCount=0;

void TTXPage::m_Init()
{
    SetPageNumber(FIRSTPAGE); // Valid but unlikely page
    Setm_SubPage(NULL); // Pointer to the next sub page
    for (int i=0;i<25;i++)
    {
        m_pLine[i]=NULL;
    }
    for (int i=0;i<6;i++)
    {
        SetFastextLink(i,0x100);
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

}

TTXPage::~TTXPage()
{
    static int j=0;
    j++;
    // std::cout << "[~TTXPage]" << std::endl;
    for (int i=0;i<25;i++)
    {
        // std::cout << "Deleting line " << i << std::endl;
        if (m_pLine[i]!=NULL)
        {
            delete m_pLine[i];
            m_pLine[i]=NULL;
        }
    }
    /* Does this leave sub pages leaking memory?
       No. The destructor will cascade through the whole chain */
    if (Getm_SubPage()!=NULL)
    {
        //std::cout << "~[TTXPage]: " << j << std::endl;
        delete m_SubPage;
        m_SubPage=NULL;
    }
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
    p->Setm_SubPage(NULL);
    return true;
}

bool TTXPage::m_LoadTTX(std::string filename)
{
    char buf[100];
    TTXPage* p=this;
    std::ifstream filein(filename.c_str(), std::ios::binary | std::ios::in);
    // First 0x61 chars are some sort of header. TODO: Find out what the format is to get metadata out
    filein.read(buf,0x61);

    // TODO: More validation for this format
    // File must start with CEBRA
    if ((buf[0]!='C') || (buf[1]!='E') || (buf[2]!='B') || (buf[3]!='R') || (buf[4]!='A'))
    {
        filein.close();
        return false;
    }

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
    p->Setm_SubPage(NULL);
    return true;
}

bool TTXPage::m_LoadTTI(std::string filename)
{
    const std::string cmd[]={"DS","SP","DE","CT","PN","SC","PS","MS","OL","FL","RD"};
    const int cmdCount = 11; // There are 10 possible commands, maybe DT and RT too on really old files
    unsigned int lineNumber;
    int lines=0;
    // Open the file
    std::ifstream filein(filename.c_str());
    TTXPage* p=this;
    char * ptr;
    int subcode;
    int pageNumber;
    for (std::string line; std::getline(filein, line, ','); )
    {
        // This shows the command code:
        //std::cout << line << std::endl;
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
                case 3 : // "CT" - Cycle time (seconds)
                    // CT,8,T
                    // std::cout << "CT not implemented\n";
                    std::getline(filein, line, ',');
                    m_cycletimeseconds=atoi(line.c_str());
                    std::getline(filein, line);
                    m_cycletimetype=line[0]=='T'?'T':'C';
                    // TODO: CT is not decoded correctly
                    break;
                case 4 : // "PN" - Page Number mppss
                    // PN,10000
                    std::getline(filein, line);
                    pageNumber=std::strtol(line.c_str(), &ptr, 16);
                    // std::cout << "PN enters with m_PageNumber=" << m_PageNumber << " param=" << pageNumber << std::endl;
                    if (p->m_PageNumber!=FIRSTPAGE) // // Subsequent pages need new page instances
                    {
                        // std::cout << "Created a new subpage" << std::endl;
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
                    if (lineNumber>24) break;
                    // std::cout << "reading " << lineNumber << std::endl;
                    p->m_pLine[lineNumber]=new TTXLine(line);
                    // TODO: Change this implementation to use SetRow
                    // std::cout << lineNumber << ": OL partly implemented. " << line << std::endl;
                    lines++;
                    break;
                case 9 : // "FL"; - Fastext links
                    // FL,104,104,105,106,F,100
                    // std::cout << "FL not implemented\n";
                    for (int fli=0;fli<6;fli++)
                    {
                        std::getline(filein, line, ',');
                        SetFastextLink(fli,std::strtol(line.c_str(), &ptr, 16));
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
    p->Setm_SubPage(NULL);
    std::cout << "Finished reading TTI page. Line count=" << lines << std::endl;
    return true;
}

/* TODO: move the body of this out into a LoadPage function */
/** ctor
 *  Load a teletext page from file
 * \param filename : Name of teletext file to load
 * \param shortFilename : Filename without path
 */
TTXPage::TTXPage(std::string filename, std::string shortFilename) : undoList(NULL), m_current(NULL)
{
    //std::cout << "[TTXPage] file constructor" << std::endl;
    bool loaded=false;
    m_Init();
    SetSourcePage(filename);
    SetShortFilename(shortFilename);
    // Try all the possible formats. EP1 first
    if (m_LoadEP1(filename))
        loaded=true;

    if (!loaded)
        if (m_LoadTTX(filename))
            loaded=true;

    if (!loaded)
        if (m_LoadTTI(filename))
            loaded=true;

    std::cout << "Finished reading page. Loaded=" << loaded << std::endl;
}


TTXPage::TTXPage(const TTXPage& other) : undoList(0), m_current(NULL)
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
    for (;pageNumber>0 && p->m_SubPage!=NULL;p=p->m_SubPage, pageNumber--);
    // Iterate down the page list to find the required page object
    return p;
}

void TTXPage::Undo(wxPoint& cursorloc)
{
    TEDEvent* tev=m_current; // This is the event we are going to undo
    if (m_current==NULL) // Nothing to undo?
        return;
    // TODO: Check the event type
    char oldChar=tev->GetCharList()->GetOldChar();   // What character
    wxPoint loc=tev->GetCharList()->GetLoc();    // and where are we putting it?
    // Write to the edit window
    TTXLine* line=m_pLine[loc.y];
    line->SetCharAt(loc.x,oldChar);
    // Dump the Undo (or do we?) No, just move the m_current pointer. Keep it in case we want to do a Redo
    // Step back to the previous event
    TEDEvent* last=tev->GetlastEvent();
    if (last!=0) m_current=last;
    cursorloc=loc;
}

TTXLine* TTXPage::GetRow(unsigned int row)
{
    // std::cout << "[TTXPage::GetRow] getting row " << row << std::endl;
    if (row>=25 || row<0)
    {
        std::cout << "[TTXPage::GetRow]Invalid row requested: " << row << std::endl;
        return NULL;
    }
    TTXLine* line=m_pLine[row];
    // Don't create row 0, as that is special.
    if (line==NULL && row>0)
        line=m_pLine[row]=new TTXLine("                                        ");
    return line;
}

void TTXPage::SetRow(unsigned int rownumber, std::string line)
{
    if (m_pLine[rownumber]==NULL)
        m_pLine[rownumber]=new TTXLine(line); // Didn't exist before
    else
        m_pLine[rownumber]->Setm_textline(line);
}

void TTXPage::AddEvent(EventType evt,wxPoint wxc,char oldchar, char newchar)
{
    TEDEvent* tev=new TEDEvent(evt);
    CharChange* cc=NULL;
    if (undoList==NULL) // First time we need to set the root
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
    case EventSave :    // Save to file
        break;
    case EventKey :     // Keyboard press
        cc=new CharChange(); // A bit redundant. This is always executed
        tev->SetCharList(cc);
        // tev->SetCharList(cc); // not correct. Need to add to the end of the list NOT the root
        cc->AddChange(wxc,oldchar,newchar);
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
    int yMin=1;     // If we show the header, then enable row 0
    if (ShowHeader)
        yMin=0;
    if (cursorLoc.y>24 || cursorLoc.y<yMin) return;       // Out of range. Don't allow row 0 either.

    // Do not allow DoubleHeight on row 23 or 24
    if (cursorLoc.y>22 && code==WXK_CONTROL_M) return;

    TTXLine* line=m_pLine[cursorLoc.y];

    // Is the line NULL? If so we had better make the line!
    if (line==NULL)
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
        char ch;
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
            default: ch=0;
        }
        if (ch>0)
        {
            char oldChar=line->SetCharAt(cursorLoc.x,ch);
            AddEvent(EventKey,cursorLoc,oldChar,ch);
            if (cursorLoc.x<39) cursorLoc.x++; // right
            return;
        }
    }
    if (modifiers & wxMOD_CONTROL) // Graphics Colours
    {
        char ch;
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
            // Special codes
            case WXK_CONTROL_H: ch=ttxCodeFlash;break;          // Ctrl-H: flash
            case WXK_CONTROL_I: ch=ttxCodeSteady;break;         // Ctrl-I: steady
            case WXK_CONTROL_J: ch=ttxCodeEndBox;break;         // Ctrl-J: end box
            case WXK_CONTROL_K: ch=ttxCodeStartBox;break;       // Ctrl-K: stsrt box
            case WXK_CONTROL_L: ch=ttxCodeNormalHeight;break;   // Ctrl-L: normal height // :-(
            case WXK_CONTROL_M: ch=ttxCodeDoubleHeight;break;   // Ctrl-M: double height

            case WXK_CONTROL_R: ch=ttxCodeConcealDisplay;break;     // Ctrl-R: conceal display
            case WXK_CONTROL_Y: ch=ttxCodeContiguousGraphics;break; // Ctrl-Y:
            case WXK_CONTROL_T: ch=ttxCodeSeparatedGraphics;break;  // Ctrl-T:
            case WXK_CONTROL_U: ch=ttxCodeBlackBackground;break;    // Ctrl-U:
            case WXK_CONTROL_B: ch=ttxCodeNewBackground;break;      // Ctrl-B:
            case WXK_CONTROL_W: ch=ttxCodeHoldGraphics;break;       // Ctrl-W:
            case WXK_CONTROL_X: ch=ttxCodeReleaseGraphics;break;    // Ctrl-X:
            default: ch=0;
        }
        if (ch>0)
        {
            std::cout << "Control code sent: " << (int)ch << std::endl;
            char oldChar;
            oldChar=line->SetCharAt(cursorLoc.x,ch);
            AddEvent(EventKey,cursorLoc,oldChar,ch);
            if (cursorLoc.x<39) cursorLoc.x++; // right
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
        case WXK_HOME : // Move to start of line
            cursorLoc.x=0;
            break;
        case WXK_END : // Move to end of line. (TODO: Only move to the last non space character on the line)
            cursorLoc.x=39;
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
                    cursorLoc.y--;
                    cursorSubLoc.y=2;
                    if (cursorLoc.x<8 && cursorLoc.y==0) cursorLoc.x=8; // Don't stumble into forbidden header area
                }
            }
            else
            {
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
                    cursorLoc.y++;
                    cursorSubLoc.y=0;
                }
            }
            else
            {
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
            // std::cout << "Default branch taken in SetCharAt " << (int)code << "i=" << instance << std::endl;
            if (line!=NULL)
            {
                // By now we should only have teletext codes. If the new code is NOT a graphic then treat it as a character
                if (code<0x80) // Only want basic ASCII codes
                {
                    if (AlphaMode || (code>='@' && code<=0x5f) || code<' ')
                    {
                        // std::cout << "Setting alpha char " << (int)code << std::endl;
                        char oldChar=line->SetCharAt(cursorLoc.x,code);
                        AddEvent(EventKey,cursorLoc,oldChar,code);
                        if (cursorLoc.x<39) cursorLoc.x++; // right
                    }
                    else
                    {
                        // If space was pressed in graphics mode then toggle the current pixel colour
                        if (code==WXK_SPACE)
                        {
                            char bit;
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
                            char ch1;
                            char oldChar=line->SetCharAt(cursorLoc.x,ch1=line->GetLine()[cursorLoc.x]^bit);
                            AddEvent(EventKey,cursorLoc,oldChar,ch1);
                        }
                        else std::cout << "Key ignored" << std::endl;
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
            // Also want to delete!
            if (cursorLoc.x>0) cursorLoc.x--;   // Move left if possible
            oldChar=line->SetCharAt(cursorLoc.x,' ');   // And clear the character that we land on
            std::cout << "TODO: Implement AddChange" << std::endl;
            break;
        case WXK_RETURN : // Double height
            oldChar=line->SetCharAt(cursorLoc.x,'\r');   // Insert a double height
            if (cursorLoc.x<39) cursorLoc.x++;   // Move right if possible
            std::cout << "TODO: Implement AddChange" << std::endl;
        default:
            std::cout << "This key code is not implemented: " << code << std::endl;
        }
    }

}

void TTXPage::m_OutputLines(std::ofstream& ttxfile, TTXPage* p)
{
    ttxfile << "PN," << std::hex << std::setw(5) << p->m_PageNumber << "\n";
    if (p->m_subcode<0)
        ttxfile << "SC,0000" << "\n";
    else
        ttxfile << "SC," << std::dec << std::setw(4) << std::setfill('0') << p->m_subcode << "\n";   // Subcode for these lines
    for (int i=0;i<25;i++)
    {
        if (p->m_pLine[i]!=NULL) // Skip empty lines
        {
            std::string s=p->m_pLine[i]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful. TODO: Make this a menu option.
            ttxfile << "OL," << std::dec << i << "," << s << "\n";
        }
    }
    std::cout << "sent a subpage" << "\n";
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
    if (ttxfile.is_open())
    {
        ttxfile << std::dec ;
        std::cout << "[TTXPage::SavePage] filename=" << filename << std::endl;
        ttxfile << "DE," << m_description << std::endl;
        //ttxfile << "PN," << std::hex << std::setprecision(5) << m_PageNumber << std::endl;
        ttxfile << "DS," << m_destination << std::dec << std::endl;
        ttxfile << "SP," << GetSourcePage() << std::endl; // SP is set every time there is a save
        ttxfile << "CT," << m_cycletimeseconds << "," << m_cycletimetype << std::dec << std::endl;
        ttxfile << "PS," << std::setw(4) << std::setfill('X') << std::hex << m_pagestatus << std::endl;
        m_OutputLines(ttxfile, this);
        // Now also have to traverse the rest of the page tree
        if (Getm_SubPage()!=NULL)
        {
            if (Getm_SubPage()->m_subcode>=0) // Shouldn't have to test this!
            {
                std::cout << "m_SubPage=" << std::hex << Getm_SubPage() << std::endl;
                for (TTXPage* p=this->m_SubPage;p!=NULL;p=p->m_SubPage)
                    m_OutputLines(ttxfile, p);

            }
        }
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
    else
        return false; // fail
    return true; // success
}

bool TTXPage::IsAlphaMode(wxPoint loc)
{
    bool result=true;
    // Check that the parameter is valid
    if (loc.x<0 || loc.x>39 || loc.y<1 || loc.y>24) return result;
    // Get pointer to the relevant line
    TTXLine* line=m_pLine[loc.y];
    if (line==NULL) return true;    // Empty line by definition is alpha

    result=line->IsAlphaMode(loc.x);
    //if (result)
    //    std::cout << "Character is Alpha" << std::endl;
    //else
    //    std::cout << "Character is Graphics" << std::endl;
    return result;
}

int TTXPage::GetPageCount()
{
    int count=0;
    int subcode=0;
    for (TTXPage* p=this;p!=NULL;p=p->m_SubPage)
    {
       // std::cout <<"Get page count happens here, subcode=" << subcode << " " << (int)p << std::endl;
       if (p!=NULL)
            p->SetSubCode(subcode++);   // Always redo the subcodes
        count++;
    }
    //std::cout << "GetPageCount returns " << count << std::endl;
    return count;
}

void TTXPage::CopyMetaData(TTXPage* page)
{
    m_PageNumber=page->m_PageNumber;
    for (int i=0;i<6;i++)
        SetFastextLink(i,page->GetFastextLink(i));

    m_destination=page->m_destination;  // DS
    SetSourcePage(page->GetSourcePage());// SP
    m_description=page->m_description;  // DE
    m_cycletimeseconds=page->m_cycletimeseconds;     // CT
    m_cycletimetype=page->m_cycletimetype;       // CT
    m_subcode=page->m_subcode;              // SC
    m_pagestatus=page->m_pagestatus;           // PS
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
    //std::cout << "PageNumber changed from " << std::hex << m_PageNumber << " to ";
    m_PageNumber=page;
    //std::cout << std::hex << m_PageNumber << std::endl;
}

int TTXPage::GetFastextLink(int link)
{
    if (link<0 || link>5)
        return 0;
    return m_fastextlinks[link];
}

void TTXPage::SetFastextLink(int link, int value)
{
    if (link<0 || link>5 || value>0x8ff)
        return;
    m_fastextlinks[link]=value;
}






