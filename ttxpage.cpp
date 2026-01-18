/** ***************************************************************************
 * Description       : Class for a teletext page
 * Compiler          : C++
 *
 * Copyright (C) 2014-2026, Peter Kwan
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

TTXPage::TTXPage() :
  undoList(nullptr)    //ctor
{
  m_Init();
}

void TTXPage::m_Init()
{
  // Resize the vector to hold the required number of rows
  m_pLine.resize(MAXROW + 1);
  // All lines are instanced. However, all spaces will be skipped in the save
  for (unsigned int i = 0; i <= MAXROW; ++i)
  {
    m_pLine[i] = std::make_unique<TTXLine>();
    if (i>0)
    {
      m_pLine[i].get()->SetRow("                                        ");
    }
    else
    {
      m_pLine[i].get()->SetRow("        wxTED Header mpp        %H:%M.%S");
    }
  }

  m_row28 = std::shared_ptr<TTXRow28>(new TTXRow28());
  for (int i=0;i<6;i++)
  {
    SetFastextLink(i,0x8ff);
  }

  m_cycleTimeSeconds = 8;
  m_cycleTimeType = 'T';
  m_pageStatus=0x8000;

}

TTXPage::~TTXPage()
{
}

TTXPage::TTXPage(const TTXPage& other) :
  undoList(0),
  m_current(nullptr)
{
    m_pLine.clear();
    for (const auto& line : other.m_pLine) {
        if (line) {
            // Assumes TTXLine has a copy constructor
            m_pLine.push_back(std::make_unique<TTXLine>(*line));
        } else {
            m_pLine.push_back(nullptr);
        }
    }
    // copy other members.. @todo?
}

TTXPage& TTXPage::operator=(const TTXPage& rhs)
{
  if (this == &rhs) return *this; // handle self assignment
  //assignment operator
  return *this;
}

void TTXPage::Undo(wxPoint& cursorloc)
{
  std::shared_ptr<TEDEvent> tev=m_current; // This is the event we are going to undo
  if (!m_current) // Nothing to undo?
  {
    return;
  }
  // TODO: Check the event type
  char oldChar=tev->GetCharList()->GetOldChar();   // What character
  wxPoint loc=tev->GetCharList()->GetLoc();    // and where are we putting it?
  // Write to the edit window
  TTXLine* line=m_pLine[loc.y].get();
  if (line==nullptr) return;
  line->SetCharAt(loc.x,oldChar);
  // Dump the Undo (or do we?) No, just move the m_current pointer. Keep it in case we want to do a Redo
  // Step back to the previous event
  std::shared_ptr<TEDEvent> last=tev->GetlastEvent();
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

TTXLine* TTXPage::GetRow(unsigned int rowNumber) {
  if (rowNumber > MAXROW)
  {
    return nullptr;
  }
  // Not sure what we do with the default contents?
  return m_pLine[rowNumber].get(); // Return the raw pointer from the unique_ptr
}

void TTXPage::SetRow(unsigned int rownumber, std::string line)
{
  // Line number out of range
  if (rownumber>MAXROW)
  {
    return;
  }
  m_pLine[rownumber]->SetRow(line);
}

void TTXPage::AddEvent(EventType evt,wxPoint wxc,char oldChar, char newChar)
{
  if (oldChar==newChar) // No change?
  {
    return;
  }
  std::shared_ptr<TEDEvent> tev(new TEDEvent(evt));
  std::shared_ptr<CharChange>cc(nullptr);
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
    cc=std::shared_ptr<CharChange>(new CharChange()); // A bit redundant. This is always executed
    tev->SetCharList(cc);
    // tev->SetCharList(cc); // not correct. Need to add to the end of the list NOT the root
    cc->AddChange(wxc,oldChar,newChar);
    break;
  case EventLanguage :     // No idea
    break;
  }
}

std::shared_ptr<TEDEvent> TTXPage::GetUndo()
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

    TTXLine* line=m_pLine[cursorLoc.y].get();

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
            if (static_cast<unsigned char>(ch)==0x80) ch=ttxCodeAlphaBlack; // Alpha black shenanigans
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
    switch (GetLanguage(true))
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
                            TTXLine* line2=m_pLine[cursorLoc.y].get();
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
            break;
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
        case WXK_ESCAPE:; // G0G2 toggle
          line->SetCharAt(cursorLoc.x,'\x1b');
          if (cursorLoc.x<39) cursorLoc.x++;   // Move right if possible
          break;
        default:
            std::cout << "This key code is not implemented: " << code << std::endl;
        }
    }
}

void TTXPage::OutputLines(std::ofstream& ttxfile, int mpp)
{
  // Page number mpp comes from TTXPageSet but subcode ss comes from TTXPage
  ttxfile << "PN," << std::hex;
  if (m_subCode<0) // no subpages
  {
    ttxfile << (mpp & 0xfff00) << "00\n";
    ttxfile << "SC,0000" << "\n";
  }
  else
  {
    ttxfile << (mpp & 0xfff00) + m_subCode << "\n";
    ttxfile << "SC," << std::dec << std::setw(4) << std::setfill('0') << m_subCode << "\n";   // Subcode for these lines
  }
  ttxfile << "PS," << std::setw(4) << std::setfill('X') << std::hex << m_pageStatus << std::endl;

  // that we can have individual timings and properties per page.
  ttxfile << "CT," << std::dec << m_cycleTimeSeconds << "," << m_cycleTimeType << std::endl;

  // @todo Add support for individual CT timers here.

  // Handle enhancement packets here
  if (m_pLine[25]!=nullptr && !m_pLine[25]->IsBlank()) // Placeholder: Just copy the packet for now
  {
    std::string s=m_pLine[25]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful.
    ttxfile << "OL,25," << s << "\n";
  }

  if (m_pLine[26]!=nullptr && !m_pLine[26]->IsBlank()) // Placeholder: Just copy the packet for now
  {
    std::string s=m_pLine[26]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful.
    ttxfile << "OL,26," << s << "\n";
  }

  if (m_pLine[27]!=nullptr && !m_pLine[27]->IsBlank()) // Placeholder: Just copy the packet for now
  {
    std::string s=m_pLine[27]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful.
    ttxfile << "OL,27," << s << "\n";
  }

  std::string x28string = m_row28->encode(); // Packet 28 palette and language enhancement
  if (x28string != "")
  {
    ttxfile << "OL,28," << x28string << std::endl;
  }

  if (m_pLine[29]!=nullptr && !m_pLine[29]->IsBlank()) // Placeholder: Just copy the packet for now
  {
    std::string s=m_pLine[29]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful.
    ttxfile << "OL,29," << s << "\n";
  }

  // Output row 0. Inserters usually discard row 0. However they are useful for online viewers
  if (m_pLine[0] != nullptr)
  {
    std::string s=m_pLine[0]->GetMappedline7bit();
    ttxfile << "OL," << std::dec << 0 << "," << s << "\n";
  }

  // Then the normal text rows
  for (int i = 1; i < 25; ++i)
  {
    if (m_pLine[i]!=nullptr && !m_pLine[i]->IsBlank()) // Skip empty lines
    {
      std::string s=m_pLine[i]->GetMappedline7bit(); // Choose the 7 bit output as it is more useful. TODO: Make this a menu option.
      ttxfile << "OL," << std::dec << i << "," << s << "\n";
    }
  }
  std::cout << "sent a subpage" << "\n";
}

// @ todo Move into TTXPageSet
//std::string TTXPage::m_FormatPageNumber(std::shared_ptr<TTXPage> p)
//{
//  std::ostringstream PN;
  //int page=p->m_PageNumber;
  //// Split the page number mppss
  //int mpp=page >> 8; // This bit is hex
  //int ss=page & 0xff; // But this bit is decimal
  //PN << std::hex << std::setw(3) << mpp << std::setfill('0') << std::dec << std::setw(2) << ss;
  //return PN.str();
//}


bool TTXPage::IsAlphaMode(wxPoint loc)
{
  bool result=true;
  // Check that the parameter is valid
  if (loc.x<0 || loc.x>39 || loc.y<1 || loc.y>24) return result;
  // Get pointer to the relevant line
  TTXLine* line=m_pLine[loc.y].get();
  if (line)
  {
    result=line->IsAlphaMode(loc.x);
  }
  return result;
}


void TTXPage::SetLanguage(int language, bool UsePrimary)
{
  language=language & 0x07;   // Limit language 0..7
  m_pageStatus=m_pageStatus & ~0x0380; // Clear the old language bits
  m_pageStatus=m_pageStatus | (language << 7);   // Shift the language bits into the right place and OR them in
  // std::cout << "Set Language: PS," << std::setw(4) << std::setfill('X') << std::hex << m_pageStatus << std::endl;
  // @todo have to send this back to  m_row28
  m_row28->SetLanguage(language, UsePrimary); // Set the primary language
}

int TTXPage::GetLanguage(bool primary)
{
  int language;
  // language=(m_pageStatus >> 7) & 0x07;
  // std::cout << "Get Language PS," << std::setw(4) << std::setfill('X') << std::hex << m_pageStatus << std::endl;
  language = m_row28->Language(primary);
  return language;
}

int TTXPage::GetRegion(bool primary)
{
  unsigned int region = m_row28->Region(primary);
  return region;
}

void TTXPage::SetRegion(int language, bool primary)
{
  m_row28->SetRegion(language, primary);
}

int TTXPage::GetFastextLink(int link)
{
  if (link<0 || link>5)
  {
    return 0;
  }
  return m_fastextLinks[link];
}

void TTXPage::SetFastextLink(int link, int value)
{
  if (link<0 || link>5 || value>0x8ff)
  {
    m_fastextLinks[link]=0x8ff; // When no particular page is specified
    return;
  }
  m_fastextLinks[link]=value;
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

unsigned int TTXPage::Remap(unsigned int colour, bool useForeground)
{
  return m_row28->Remap(colour, useForeground);
}

bool TTXPage::GetPageChanged()
{
  return pageChanged;
}

