/***************************************************************
 * Name:      wxTEDMain.cpp
 * Purpose:   Teletext editor Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan (http://www.teastop.co.uk)
 * License:
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
 * The author disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 *************************************************************************** **/

#include "wxTEDMain.h"
#include <wx/msgdlg.h>
#include "wx/wx.h"
#include <winver.h>

//(*InternalHeaders(wxTEDFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/dcbuffer.h>


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxTEDFrame)
const long wxTEDFrame::ID_PANEL1 = wxNewId();
const long wxTEDFrame::ID_NOTEBOOK1 = wxNewId();
const long wxTEDFrame::idNewPage = wxNewId();
const long wxTEDFrame::idOpenPage = wxNewId();
const long wxTEDFrame::idSavePage = wxNewId();
const long wxTEDFrame::isSavePageAs = wxNewId();
const long wxTEDFrame::idPublish = wxNewId();
const long wxTEDFrame::idPublishSettings = wxNewId();
const long wxTEDFrame::idExportTTX40 = wxNewId();
const long wxTEDFrame::idMenuQuit = wxNewId();
const long wxTEDFrame::idNewWindow = wxNewId();
const long wxTEDFrame::idUndo = wxNewId();
const long wxTEDFrame::idCut = wxNewId();
const long wxTEDFrame::idCopy = wxNewId();
const long wxTEDFrame::idPaste = wxNewId();
const long wxTEDFrame::idSelectAll = wxNewId();
const long wxTEDFrame::idInsertPage = wxNewId();
const long wxTEDFrame::idDeleteSubPage = wxNewId();
const long wxTEDFrame::idLanguageEnglish = wxNewId();
const long wxTEDFrame::idLanguageFrench = wxNewId();
const long wxTEDFrame::idLanguageSwedish = wxNewId();
const long wxTEDFrame::idLanguageCzechSlovak = wxNewId();
const long wxTEDFrame::idLanguageGerman = wxNewId();
const long wxTEDFrame::idLanguageSpanish = wxNewId();
const long wxTEDFrame::idLanguageItalian = wxNewId();
const long wxTEDFrame::idLanguageUnused = wxNewId();
const long wxTEDFrame::ID_MENUITEM1 = wxNewId();
const long wxTEDFrame::ID_REGION0 = wxNewId();
const long wxTEDFrame::ID_REGION1 = wxNewId();
const long wxTEDFrame::ID_REGION2 = wxNewId();
const long wxTEDFrame::ID_REGION3 = wxNewId();
const long wxTEDFrame::ID_REGION4 = wxNewId();
const long wxTEDFrame::ID_REGION6 = wxNewId();
const long wxTEDFrame::ID_REGION8 = wxNewId();
const long wxTEDFrame::ID_REGION10 = wxNewId();
const long wxTEDFrame::ID_REGION = wxNewId();
const long wxTEDFrame::idPageNumber = wxNewId();
const long wxTEDFrame::ID_MENUITEMSHOWHEADER = wxNewId();
const long wxTEDFrame::ID_HIDECONCEAL = wxNewId();
const long wxTEDFrame::idSpecialKeys = wxNewId();
const long wxTEDFrame::idMenuAbout = wxNewId();
const long wxTEDFrame::ID_STATUSBAR1 = wxNewId();
const long wxTEDFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxTEDFrame,wxFrame)
    //(*EventTable(wxTEDFrame)
    //*)
    EVT_PAINT(wxTEDFrame::OnPaint)
    EVT_SIZE(wxTEDFrame::OnSize)
    EVT_LEFT_DOWN(wxTEDFrame::OnLeftDown)
    EVT_CHAR(wxTEDFrame::OnChar)
    EVT_KEY_DOWN(wxTEDFrame::OnKeyDown)
    EVT_KEY_UP(wxTEDFrame::OnKeyUp)
    EVT_TIMER(ID_TIMER1 ,wxTEDFrame::OnTimer)
    EVT_ERASE_BACKGROUND(wxTEDFrame::OnEraseBackground)
END_EVENT_TABLE()

void wxTEDFrame::OnEraseBackground(wxEraseEvent& event)
{
    // NULL method!
    std::cout << "Erase..." << std::endl;
}

void wxTEDFrame::OnSize(wxSizeEvent& event)
{
    // std::cout << "Resize..." << std::endl;
    m_resize(event.GetSize());
}

void wxTEDFrame::OnChar(wxKeyEvent& event)
{
    int code=event.GetKeyCode();
    int modifiers=event.GetModifiers();
    // std::cout << "Key event..." << code << std::endl;
    // We look at a few codes which apply to a page set rather than just a single page
    TEDEvent* tev;
    switch (code)
    {
    case WXK_PAGEUP:
        // std::cout << "Page up will get next page of a multiple page carousel" << std::endl;
        iPageCount=m_rootPage->GetPageCount();
        iPage++;
        if (iPage>=iPageCount) iPage=iPageCount-1;
        m_currentPage=m_rootPage->GetPage(iPage);
        //std::cout << "iPage= " << iPage << std::endl;
        break;
    case WXK_PAGEDOWN:
        // std::cout << "Page down will get previous page of a multiple page carousel" << std::endl;
        iPageCount=m_rootPage->GetPageCount();
        iPage--;
        if (iPage<0) iPage=0;
        m_currentPage=m_rootPage->GetPage(iPage);
        //std::cout << "iPage= " << iPage << std::endl;
        break;
    case WXK_F11: // Reveal concealed text
        m_reveal=!m_reveal;
        break;
    case WXK_CONTROL_Y:
        // std::cout << "CTRL-Y test" << std::endl; // Testing
        tev=m_currentPage->GetUndo();
        if (tev!=NULL)
            tev->dump();
        break;
    case WXK_CONTROL_Z:
        // std::cout << "CTRL-Z undo" << std::endl;
        // tev=m_currentPage->GetUndo();
        m_currentPage->Undo(m_cursorPoint);
        break;
    default:
        m_currentPage->SetCharAt(code, modifiers, m_cursorPoint, m_subPixelPoint, MenuItemShowHeader->IsChecked());
    }

    //std::cout << "Cursor = " << m_cursorPoint.x << "." << m_subPixelPoint.x << ", "
    //     << m_cursorPoint.y << "." << m_subPixelPoint.y << ", "  << std::endl;
    m_cursorIsAlpha=m_currentPage->IsAlphaMode(m_cursorPoint);
    m_blinkToggle=true; // HCI: Make cursor moves immediately visible
    Refresh();
}

void wxTEDFrame::OnTimer(wxTimerEvent& event)
{
    // Only blink while focused otherwise stay on.
    // std::cout << "blink=" << m_blinkToggle << " m_focused=" << m_focused << std::endl;
    if (m_blinkToggle && m_focused)
        m_blinkToggle=false;
    else
        m_blinkToggle=true;

    wxString s=GetTitle();
    if (m_currentPage)
    // Paint it
    Refresh();
}

bool wxTEDFrame::isMosaic(char ch)
{
    ch&=0x7f;
    return (ch>=0x20 && ch<0x40) || ch>=0x60;
}

/* new--old description. Don't use old codes. They no longer work in VBIT.
 * %%#  mpp page number
 *  %d   dd date, two digits
 *  %e      date without leading 0
 *  %m   uu month
 *  %y   yy year
 * %%a  DAY day
 * %%b  MTH month
 *  %H   hh hour
 *  %M   nn minute
 *  %S   ss second
 *
 * Example ARD. "mpp<cyan>ARDtext<white>Mo dd.uu.yy hh:nn:ss"
 * @todo We do not yet implement two character day codes
 * as is possible in German dd so you have to edit it every day!
 */
void wxTEDFrame::GenerateHeader(TTXLine* line)
{
    // line->Setm_textline(std::string("Pxxx    101 TEDFAX Mon 15 Nov   21:12.38"));
    //                AAAAAAAAaabbbbbbbbbbccccccccccddDDDDDDDD
    std::ostringstream val;

    time_t rawtime;
    tm * timeinfo;
    rawtime=time(NULL);
    timeinfo=localtime(&rawtime);

    std::string str=line->GetLine();
    int i;


    for (i=0;i<8;i++) // First 8 characters are not taken from the header
        str[i]=' ';
    int k=m_rootPage->GetPageNumber()/0x100;
    if (k<0x100 && k>0x8ff)
        k=0x100;
    val << std::hex << k;
    str[0]='P';
    str.replace(1,3,val.str()); // Replace the first 4 characters with the page number

    // Magazine and page number
    i=str.find("mpp");
    if (i<=0) i=str.find("%%#");
    if (i>0)
    {
        str.replace(i,3,val.str());
    }

    // two digit date with leading 0
    i=str.find("dd");
    if (i<=0) i=str.find("%d");
    if (i>0)
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
        str.replace(i,2,val.str());
    }

    // Three character day name
    i=str.find("DAY");
    if (i<=0) i=str.find("%%a");
    if (i>0)
    {
        char day[10];
        char* p=day;
        strftime(p,4,"%a",timeinfo);
        str.replace(i,3,p);
    }

    // Three character month name
    i=str.find("MTH");
    if (i<=0) i=str.find("%%b");
    if (i>0)
    {
        char month[10];
        char* p=month;
        strftime(p,4,"%b",timeinfo);
        str.replace(i,3,p);
    }

    // Hours - two digits 24 hour
    i=str.find("hh");
    if (i<=0) i=str.find("%H");
    if (i>31) // Clock hours
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_hour;
        str.replace(i,2,val.str());
    }

    // Minutes - two digits
    i=str.find("nn");
    if (i<=0) i=str.find("%M");
    if (i>31) // Clock minutes
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_min;
        str.replace(i,2,val.str());
    }

    // Month - two digits
    i=str.find("uu");
    if (i<=0) i=str.find("%m");
    if (i>8) // uu Month (two digits)
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_mon+1;
        str.replace(i,2,val.str());
    }

    // Seconds - two digits
    i=str.find("ss");
    if (i<=0) i=str.find("%S");
    if (i>31) // Clock seconds
    {
        val.str("");
        val << std::setw(2) << std::setfill('0') << std::dec << timeinfo->tm_sec;
        str.replace(i,2,val.str());
    }

    // Year - two digits
    i=str.find("yy");
    if (i<=0) i=str.find("%Y");
    if (i>0)
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_year % 100;
        str.replace(i,2,val.str());
    }

    // std::cout << "GenerateHeader exits with str=" << str << std::endl;
    line->Setm_textline(str);
}


void wxTEDFrame::m_resize(wxSize clientSize)
{
    wxSize ttxSize;
    // What is the target client size?
    //std::cout << "Current window size " << std::dec << clientSize.GetWidth() << " " << clientSize.GetHeight() << std::endl;
    // What is the current font size?
    wxFont wf=GetFont();
    // Iterate for best fit
    int i;
    for (i=8;i<100;i++)
    {
    //std::cout << "Current font size " << std::dec << m_fontSize[i].GetWidth() << " " << m_fontSize[i].GetHeight() << std::endl;
        // Fit widtj
        if (clientSize.GetWidth()<m_fontSize[i].GetWidth()+10) // allow 10 pixels, I think the border is included
            break;
        // or fit height
        if (clientSize.GetHeight()<m_fontSize[i].GetHeight()*26+40)
            break;
    }
    // Don't make it too small
    if (i>8) i--;
    // Set it as the system font
    wf.SetPointSize(i);
    SetFont(wf);
    /* font metrics */
    ttxSize=GetTextExtent("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDD");
    m_ttxW=ttxSize.GetWidth()/40;
    m_ttxH=ttxSize.GetHeight(); // 18;




    Refresh();
    // std::cout << "New font size (pts) " << GetFont().GetPointSize() << std::endl;
}

void wxTEDFrame::OnPaint(wxPaintEvent& event)
{
    /*
    static uint32_t count=0;
    std::cout << "[OnPaint]PAINT! " << count++ << std::endl;
    // std::cout << "P" << count++ << std::endl;
    */
    if (this->IsIconized()) return; // If Iconized we shouldn't draw anything

    wxAutoBufferedPaintDC paintDC(this);
//    wxAutoBufferedPaintDC paintDC(Panel1);

//    paintDC.SetColour(wxColour(255,255,255));
   // paintDC.DrawText(_("blah"),wxPoint(50,50));

    // redraw the whole teletext page
    // std::cout << "Trace 1" << std::endl;



    /* colours */
    const wxColour* fg=wxWHITE;
    const wxColour* bg=wxBLACK;


    wxBitmap doubleHeightBitmap(m_ttxW*40,m_ttxH*2);    // The image buffer for double height. (Sized for a single height plus generous fudge factor)

    wxMemoryDC doubleHeightDC;
    doubleHeightDC.SelectObject(doubleHeightBitmap);  // The device context for double height text

    // Copy the font settings over
    wxFont wf=GetFont();
    doubleHeightDC.SetFont(wf);

    /* Fill the background */
    paintDC.SetPen(*wxTRANSPARENT_PEN);
    paintDC.SetBrush(wxBrush(*wxBLACK_BRUSH));
    doubleHeightDC.SetPen(*wxTRANSPARENT_PEN);
    doubleHeightDC.SetBrush(wxBrush(*wxBLACK_BRUSH));
    int w,h;
    paintDC.GetSize(&w, &h);
    paintDC.DrawRectangle(wxPoint(0,0),wxSize(w,h));
    // paintDC.DrawRectangle(wxPoint(0,0),wxSize(40*m_ttxW,24*m_ttxH));
    // TODO: Black out rows if they are NULL, to avoid old text getting stuck

    paintDC.SetBackgroundMode(wxSOLID); // Otherwise the background colour is transparent!
    doubleHeightDC.SetBackgroundMode(wxSOLID); // Otherwise the background colour is transparent!

    wxColour* magenta=new wxColour(255,0,255); // remember to delete this
    /* page */
    TTXPage* p=m_currentPage; // Load the root page, but soon we really want to implement for subpages
    // std::cout << "Trace 2" << std::endl;
    int firstRow=1;
    if (MenuItemShowHeader->IsChecked())
        firstRow=0;
    TTXLine row0;
    for (unsigned int row=firstRow;row<25;row++)
//    for (int row=24;row>=firstRow;row--)
    {
        bool graphicsMode=false;
        bool separated=false;
        bool doubleheight=false;
        bool skipnextrow=false;
        bool flashing=false;
        bool hold=false;
        char holdChar=' ';
        bool concealed=false;

        fg=wxWHITE;
        bg=wxBLACK;

        doubleHeightDC.SetBackground(*wxBLACK_BRUSH); //  wxBLACK_BRUSH. Change this to GREY to track down bugs
        doubleHeightDC.Clear();

        // std::cout << "Trace 3. Row=" << row << std::endl;

        // TTXPage* p=page.GetPage(0);
        TTXLine* line=p->GetRow(row);

        // TODO: Replace this with a call to the header
        if (m_cursorPoint.y>0 && row==0) // If we are actually in the header, then edit the raw header
        {

            if (line==NULL)
            {
                p->SetRow(row,"XXXXXXXXTEDFAX mpp DAY dd MTH \x3 hh:nn.ss"); // Could put in a sample header here
                //             aaaaaaaaaabbbbbbbbbbccccccccccd  ddddddddd
                line=p->GetRow(row);
            }
            row0=*line; // Copy the contents of line to row
            line=&row0;   // Now point line to row so we don't erase the original line
            GenerateHeader(line);
        }

        // std::cout << "Trace 4" << std::endl;
        if (line!=NULL)
        {
            std::string str=line->GetLine();
            str=str.substr(0,40);
            for (int col=0;col<40;col++) // Look at each character on the line
            {
                // std::cout << "Trace 5" << std::endl;
                char ch=' ';
                wchar_t ch2=ch;
                // Check the Set-before code
                switch (str[col])
                {
                // If a case is ignored, you'll find it in the set-after section
                case ttxCodeAlphaBlack :
                case ttxCodeAlphaRed :
                case ttxCodeAlphaGreen :
                case ttxCodeAlphaYellow :
                case ttxCodeAlphaBlue :
                case ttxCodeAlphaMagenta :
                case ttxCodeAlphaCyan :
                case ttxCodeAlphaWhite :
                    hold=false;
                case ttxCodeFlash :
                    break;
                case ttxCodeSteady :
                    flashing=false;
                    break;
                case ttxCodeEndBox :
                case ttxCodeStartBox :
                    break;
                case ttxCodeNormalHeight :
                    doubleheight=false;
                    break;
                case ttxCodeDoubleHeight : // Double height
                case ttxCodeGraphicsBlack : // Graphics black (level 2.5+)
                case ttxCodeGraphicsRed : // Graphics red
                case ttxCodeGraphicsGreen : // Graphics green
                case ttxCodeGraphicsYellow : // Graphics yellow
                case ttxCodeGraphicsBlue : // Graphics blue
                case ttxCodeGraphicsMagenta : // Graphics magenta
                case ttxCodeGraphicsCyan : // Graphics cyan
                case ttxCodeGraphicsWhite : // Graphics white
                    break;
                case ttxCodeConcealDisplay : // Conceal display
                    concealed=true;
                    break;
                case ttxCodeContiguousGraphics : // Contiguous graphics
                    separated=false;
                    break;
                case ttxCodeSeparatedGraphics : // Separated gfx
                    separated=true;
                    break;
                case ttxCodeBlackBackground : // Background black
                    bg=wxBLACK;
                    break;
                case ttxCodeNewBackground : // New background
                    bg=fg;
                    break;
                case ttxCodeHoldGraphics : // Hold gfx (set at)
                    hold=true;
                    break;
                case ttxCodeReleaseGraphics : // Release gfx (set after)
                    break;
                case 14:; // Ignore shift in/shift out and avoid them falling into default
                case 15:;
                    break;
                default :
                    // std::cout << "Trace OL:ordinary character " << ch << std::endl;
                    ch=str[col] & 0x7f;
                    ch2=str[col];
                    ch2=mapTextChar(ch2);
                    // holdchar records the last mosaic character sent out
                    if (isMosaic(ch))
                    {
                        holdChar=ch;  // In case we encounter hold mosaics (Space doesn't count as a mosaic)
                    }
                }

                if (concealed && !m_reveal) // Replace text with spaces
                {
                    ch=' ';
                    holdChar=' '; /// @todo restore to space
                    ch2=' ';
                }
                if (graphicsMode && (isMosaic(ch) || hold) ) // Draw graphics. Either mosaic (but not capital A..Z) or in hold mode
                {
                    int j=0x01;
                    // Not sure if this is a rule. If we send a new mosaic code while in hold, it replaces the current mosaic.
                    // This fixes the Oracle P689 christmas bug
                    if (hold)
                    {
                        ch=holdChar;  // Carry on hold
                    }

                    for (int i=0;i<6;i++) // for each of the six pixels in this character
                    {
                        if (ch & j)
                        {
                            if (m_blinkToggle || !flashing)
                            {
                                paintDC.SetBrush(wxBrush(*fg)); // Normal
                                doubleHeightDC.SetBrush(*fg); // Normal
                            }
                            else
                            {
                                paintDC.SetBrush(wxBrush(*bg)); // Blinked off
                                doubleHeightDC.SetBrush(*bg); // blink off
                            }
                        }
                        else // Pixel is not set
                        {
                            paintDC.SetBrush(wxBrush(*bg));
                            doubleHeightDC.SetBrush(*bg); // off
                        }
                        j<<=1;
                        if (j==0x20) j<<=1; // Skip the alphabet exception
                        int k=separated?-2:1; // Add or subtract a line
                        paintDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                                      row*m_ttxH+(i/2)*m_ttxH/3),
                                              wxSize(k+m_ttxW/2,k+m_ttxH/3));
                        if (doubleheight)
                            doubleHeightDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                                                 (i/2)*m_ttxH/3),
                                              wxSize(k+m_ttxW/2,k+m_ttxH/3));
                    }

                } // Graphic block
                else
                {
                    if (m_blinkToggle || !flashing)
                        paintDC.SetTextForeground(*fg); // Normal
                    else
                        paintDC.SetTextForeground(*bg); // Blink off
                    paintDC.SetTextBackground(*bg);
                    paintDC.DrawText(_(ch2),wxPoint(col*m_ttxW,row*m_ttxH));
                    if (doubleheight)
                    {
                        if (m_blinkToggle || !flashing)
                            doubleHeightDC.SetTextForeground(*fg); // Normal
                        else
                            doubleHeightDC.SetTextForeground(*bg); // blink off
                        doubleHeightDC.SetTextBackground(*bg);
                        doubleHeightDC.DrawText(_(ch2),wxPoint(col*m_ttxW,0));
                    }
                }
                if (doubleheight)
                    paintDC.StretchBlit(wxPoint(col*m_ttxW,row*m_ttxH),wxSize(m_ttxW,m_ttxH*2), // dest
                                    &doubleHeightDC,
                                    wxPoint(col*m_ttxW,0),wxSize(m_ttxW,m_ttxH)); //src
                // Set-after codes implemented here, also the show markup
                paintDC.SetTextForeground(*wxWHITE);
                paintDC.SetTextBackground(*wxLIGHT_GREY);
                switch (str[col])
                {
                case ttxCodeAlphaBlack :
                    fg=wxBLACK;
                    concealed=false;    // Side effect of colour. It cancels a conceal.
                    graphicsMode=false;
                    break;
                case ttxCodeAlphaRed :
                    fg=wxRED;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaGreen :
                    fg=wxGREEN;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaYellow :
                    fg=wxYELLOW;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaBlue :
                    fg=wxBLUE;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaMagenta :
                    fg=magenta; // wxMAGENTA
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaCyan :
                    fg=wxCYAN;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeAlphaWhite :
                    fg=wxWHITE;
                    concealed=false;
                    graphicsMode=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\x03B1'),wxPoint(col*m_ttxW,row*m_ttxH)); // graphic sample
                    }
                    break;
                case ttxCodeFlash :
                    flashing=true;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText(_((wxChar)L'\xEFC6'),wxPoint(col*m_ttxW,row*m_ttxH)); // italic f
                    }
                    break;
                case ttxCodeEndBox :
                    std::cout << "End Box not implemented" << std::endl;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText(_((wxChar)L'\xEF57'),wxPoint(col*m_ttxW,row*m_ttxH)); // down arrow
                    }
                    break;
                case ttxCodeStartBox :
                    std::cout << "Start box not implemented" << std::endl;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText(_((wxChar)L'\xEF56'),wxPoint(col*m_ttxW,row*m_ttxH)); // down arrow
                    }
                    break;
                case ttxCodeNormalHeight : // Normal height
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText(_((wxChar)L'\xEF5E'),wxPoint(col*m_ttxW,row*m_ttxH)); // down arrow
                    }
                    break;
                case ttxCodeDoubleHeight : // Double height
                    doubleheight=true;
                    skipnextrow=true;   // ETSI: Don't use content from next row
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText(_((wxChar)L'\xEF5D'),wxPoint(col*m_ttxW,row*m_ttxH)); // up arrow
                    }
                   break;
                case ttxCodeGraphicsBlack : // Graphics black
                    concealed=false;
                    graphicsMode=true;
                    fg=wxBLACK;
                    if (m_ShowMarkup) paintDC.DrawText(_('¬'),wxPoint(col*m_ttxW,row*m_ttxH)); // hmm
                    break;
                case ttxCodeGraphicsRed : // Graphics red
                    concealed=false;
                    graphicsMode=true;
                    fg=wxRED;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsGreen : // Graphics green
                    concealed=false;
                    graphicsMode=true;
                    fg=wxGREEN;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsYellow : // Graphics yellow
                    concealed=false;
                    graphicsMode=true;
                    fg=wxYELLOW;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsBlue : // Graphics blue
                    concealed=false;
                    graphicsMode=true;
                    fg=wxBLUE;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsMagenta : // Graphics magenta
                    concealed=false;
                    graphicsMode=true;
                    fg=magenta;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsCyan : // Graphics cyan
                    concealed=false;
                    graphicsMode=true;
                    fg=wxCYAN;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeGraphicsWhite : // Graphics white
                    concealed=false;
                    graphicsMode=true;
                    fg=wxWHITE;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*fg);
                        paintDC.DrawText(_((wxChar)L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)); // Show a blob where a control code is
                    }
                    break;
                case ttxCodeConcealDisplay : // Conceal display
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('?',wxPoint(col*m_ttxW,row*m_ttxH)); // question mark
                    }
                    break;
                case ttxCodeContiguousGraphics : // Contiguous graphics
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('c',wxPoint(col*m_ttxW,row*m_ttxH)); // (c)ontiguous
                    }
                    break;
                case ttxCodeSeparatedGraphics : // Separated gfx
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('s',wxPoint(col*m_ttxW,row*m_ttxH)); // (s)eparate
                    }
                    break;
                case ttxCodeBlackBackground : // Background black

                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('b',wxPoint(col*m_ttxW,row*m_ttxH)); // b for black background
                    }
                    break;
                case ttxCodeNewBackground : // New background
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('n',wxPoint(col*m_ttxW,row*m_ttxH)); // n for new background
                    }
                    break;

                case ttxCodeHoldGraphics : // Hold gfx
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('h',wxPoint(col*m_ttxW,row*m_ttxH)); // (h)old
                    }
                    break;
                case ttxCodeReleaseGraphics : // Separated gfx
                    hold=false;
                    if (m_ShowMarkup)
                    {
                        paintDC.SetTextForeground(*wxWHITE);
                        paintDC.DrawText('r',wxPoint(col*m_ttxW,row*m_ttxH)); // (r)elease
                    }
                    break;

                default:;
                    // If this is a graphics cell, draw the cell outline
                    if (graphicsMode && m_ShowMarkup)
                    {
                        paintDC.SetPen(*wxGREY_PEN);
                        paintDC.DrawLine(col*m_ttxW,row*m_ttxH,(col+1)*m_ttxW,(row+1)*m_ttxH);

                        //paintDC.DrawText('g',wxPoint(col*m_ttxW,row*m_ttxH)); // (r)elease

                    }
                }//case

            } // each character on this row
            if (skipnextrow) row++; // Don't use next row if there was any double height

        } // row not null?
        /* else
            std::cout << "row is null " << row << std::endl; */
    }
    delete magenta;
    // cursor
    if (m_blinkToggle==true)
    {
        paintDC.SetPen(*wxBLACK_PEN); // outline on
        paintDC.SetBrush(wxBrush(*wxWHITE));
            // In the current page, get the line that the cursor is on, and test if it is double height
        bool doubleHeight;
        doubleHeight=m_currentPage->GetRow(m_cursorPoint.y)->IsDoubleHeight(); // @todo Extend to deal with double height transitions.
        if (m_cursorIsAlpha)
        {
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW,m_cursorPoint.y*m_ttxH),wxSize(m_ttxW,m_ttxH));
            if (doubleHeight)
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW,m_cursorPoint.y*m_ttxH),wxSize(m_ttxW,m_ttxH*2));
        }
        else
        {
            int halfw=m_ttxW/2;
            int thirdh=m_ttxH/3;
            if (doubleHeight)
            {
                thirdh*=2;
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW+m_subPixelPoint.x*halfw,
                                              m_cursorPoint.y*m_ttxH+m_subPixelPoint.y*thirdh),
                                      wxSize(halfw,thirdh));
            }
            else
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW+m_subPixelPoint.x*halfw,
                                              m_cursorPoint.y*m_ttxH+m_subPixelPoint.y*thirdh),
                                      wxSize(halfw,thirdh));

        }
        paintDC.SetPen(*wxTRANSPARENT_PEN);
    }
    m_SetStatus();

    // Marquee.
    // TODO: Make the marquee and cursor mutually exclusive
    wxPen pen(*wxWHITE,1,wxSHORT_DASH);
    paintDC.SetPen(pen); // outline on
    wxCoord x1,y1,x2,y2;
    x1=m_MarqueeStart.x*m_ttxW;
    x2=m_MarqueeEnd.x  *m_ttxW;
    y1=m_MarqueeStart.y*m_ttxH;
    y2=m_MarqueeEnd.y  *m_ttxH;
    // Backwards?
    if (x1>x2) x1+=m_ttxW;
    if (y1>y2) y1+=m_ttxH;
    // Draw a box
    // TODO: Marquee crawling ants
    paintDC.DrawLine(x1,y1,x2,y1); // Top
    paintDC.DrawLine(x1,y1,x1,y2); // Left
    paintDC.DrawLine(x2,y1,x2,y2); // Right
    paintDC.DrawLine(x1,y2,x2,y2); // Bottom



    // std::cout << "[OnPaint] exits " << std::endl;
}

wchar_t wxTEDFrame::mapTextChar(wchar_t ch)
{
    return MapChar(ch,m_currentPage->GetLanguage(),m_currentPage->GetRegion());
}

void wxTEDFrame::m_SetStatus()
{
    std::ostringstream str;
    std::ostringstream s;

    std::ostringstream code;
    wchar_t ch;
    wxPoint c=m_cursorPoint;
    wxPoint d=m_subPixelPoint;
    TTXLine* line=m_currentPage->GetRow(c.y);
    str << "P" << iPage+1 << "/" << iPageCount << ", ";
    if (line!=NULL)
    {
        ch=line->GetLine()[c.x] & 0x7f;
        switch (ch)
        {
            case ttxCodeAlphaBlack:    code<<"Alpha black=Shift F8";break;
            case ttxCodeAlphaRed:      code<<"Alpha Red=Shift F1";break;
            case ttxCodeAlphaGreen:    code<<"Alpha Green=Shift F2";break;
            case ttxCodeAlphaYellow:   code<<"Alpha Yellow=Shift F3";break;
            case ttxCodeAlphaBlue:     code<<"Alpha Blue=Shift F4";break;
            case ttxCodeAlphaMagenta:  code<<"Alpha Magenta=Shift F5";break;
            case ttxCodeAlphaCyan:     code<<"Alpha Cyan=Shift F6";break;
            case ttxCodeAlphaWhite:    code<<"Alpha White=Shift F7";break;
            case ttxCodeFlash:         code<<"Flash=Ctrl-H";break;
            case ttxCodeSteady:        code<<"Steady=Ctrl-I";break;
            case ttxCodeEndBox:        code<<"End box=Ctrl-J";break;
            case ttxCodeStartBox:      code<<"Start box=Ctrl-K";break;
            case ttxCodeNormalHeight:  code<<"Normal height=Ctrl-L";break;
            case ttxCodeDoubleHeight:  code<<"Double height=Ctrl-M";break;
            case ttxCodeGraphicsRed:   code<<"Graphics Red=Ctrl-F1";break;
            case ttxCodeGraphicsGreen: code<<"Graphics Green=Ctrl-F2";break;
            case ttxCodeGraphicsYellow: code<<"Graphics Yellow=Ctrl-F3";break;
            case ttxCodeGraphicsBlue:  code<<"Graphics Blue=Ctrl-F4";break;
            case ttxCodeGraphicsMagenta: code<<"Graphics Magenta=Ctrl-F5";break;
            case ttxCodeGraphicsCyan:  code<<"Graphics Cyan=Ctrl-F6";break;
            case ttxCodeGraphicsWhite: code<<"Graphics White=Ctrl-F7";break;
            case ttxCodeConcealDisplay: code<<"Conceal=Shift W (F11 toggle)";break;
            case ttxCodeContiguousGraphics: code<<"Contiguous graphics";break;
            case ttxCodeSeparatedGraphics: code<<"Separated graphics=Ctrl-T";break;
            case ttxCodeBlackBackground: code<<"Black background=Ctrl-U";break;
            case ttxCodeNewBackground: code<<"New background=Ctrl-B";break;
            case ttxCodeHoldGraphics:  code<<"Hold graphics=Ctrl-W";break;
            case ttxCodeReleaseGraphics: code<<"Release graphics=Ctrl-X";break;
            case ' ': code<<"Space";break;
            default: code << "unknown " << (int)ch;
        }
    }
    else
        ch='?';
    if (m_currentPage->IsAlphaMode(m_cursorPoint))
    {
        if (ch>' ')
        {
            ch=mapTextChar(ch);
            //std::string s2=ch;
            //s2[0]=ch;
            code<<(char)ch;
        }
        str << "(" << c.x << "," << c.y <<") char=" << code.str(); // Alpha
    }
    else
        str << "(" << c.x << "." << d.x << "," << c.y << "." << d.y <<") " << code.str(); // Graphics
    StatusBar1->SetLabelText(str.str());
}

wxTEDFrame::wxTEDFrame(wxWindow* parent,wxWindowID id) : m_ttxW(15), m_ttxH(20), m_subPixelPoint(wxPoint(0,0)), m_cursorIsAlpha(true)
 , m_dragging(false), m_MarqueeStart(wxPoint(0,0)), m_currentPage(NULL)
{
    // std::cout << "[wxTEDFrame] Entered" << std::endl;
    m_parentWindow=parent;
    m_ShowMarkup=false;
    m_Released=true;
    m_blinkToggle=false;
    m_propertiesDlg=new PageSettingsDialog(this,1000);

    m_reveal=true; // As this is an editor, reveal the text by default.

    m_clip = new wxClipboard();

    // config
    m_config=new wxConfig("wxTED");

    //(*Initialize(wxTEDFrame)
    wxMenu* MenuHelp;
    wxMenuItem* MenuItemAbout;
    wxMenu* Menu1;
    wxMenuItem* MenuItemQuit;
    wxMenuBar* MenuBar1;

    Create(parent, wxID_ANY, _("wxTED 1.22"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    wxFont thisFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("teletext2"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(400,24), 0, _T("ID_NOTEBOOK1"));
    Notebook1->Disable();
    Notebook1->Hide();
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxSize(392,332), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Notebook1->AddPage(Panel1, _("P1"), false);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idNewPage, _("New\tCTRL-N"), _("Create a new page"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, idOpenPage, _("Open\tCTRL-O"), _("Open a teletext page"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItemSave = new wxMenuItem(Menu1, idSavePage, _("Save\tCTRL-S"), _("Save a teletext page"), wxITEM_NORMAL);
    Menu1->Append(MenuItemSave);
    MenuItemSave->Enable(false);
    MenuItemSaveAs = new wxMenuItem(Menu1, isSavePageAs, _("Save as"), _("Save a teletext page with a different name"), wxITEM_NORMAL);
    Menu1->Append(MenuItemSaveAs);
    Menu1->AppendSeparator();
    MenuItemPublish = new wxMenuItem(Menu1, idPublish, _("Publish"), _("Publish the page to an inserter"), wxITEM_NORMAL);
    Menu1->Append(MenuItemPublish);
    MenuItemPublishSettings = new wxMenuItem(Menu1, idPublishSettings, _("Publish settings..."), _("Choose publish method"), wxITEM_NORMAL);
    Menu1->Append(MenuItemPublishSettings);
    MenuItemExportTTX40 = new wxMenuItem(Menu1, idExportTTX40, _("Export edit.tf"), _("Open page on edit.tf website"), wxITEM_NORMAL);
    Menu1->Append(MenuItemExportTTX40);
    MenuItemQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItemQuit);
    Menu1->AppendSeparator();
    MenuItem4 = new wxMenuItem(Menu1, idNewWindow, _("New Window"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItemUndo = new wxMenuItem(Menu3, idUndo, _("Undo\tCTRL-Z"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItemUndo);
    Menu3->AppendSeparator();
    MenuItem11 = new wxMenuItem(Menu3, idCut, _("Cut"), _("Cut the selected area"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    MenuItem11->Enable(false);
    MenuItemCopy = new wxMenuItem(Menu3, idCopy, _("Copy\tCTRL-C"), _("Copy the selected area"), wxITEM_NORMAL);
    Menu3->Append(MenuItemCopy);
    MenuItemPaste = new wxMenuItem(Menu3, idPaste, _("Paste\tCTRL-V"), _("Paste text from the clipboard"), wxITEM_NORMAL);
    Menu3->Append(MenuItemPaste);
    MenuItemSelectAll = new wxMenuItem(Menu3, idSelectAll, _("Select All\tCTRL-A"), _("Select the entire page"), wxITEM_NORMAL);
    Menu3->Append(MenuItemSelectAll);
    Menu3->AppendSeparator();
    MenuItemInsertSubpage = new wxMenuItem(Menu3, idInsertPage, _("Insert subpage after this one"), _("Add a subpage after this page"), wxITEM_NORMAL);
    Menu3->Append(MenuItemInsertSubpage);
    MenuItemDeletePage = new wxMenuItem(Menu3, idDeleteSubPage, _("Delete this subpage"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItemDeletePage);
    MenuBar1->Append(Menu3, _("Edit"));
    MenuPresentation = new wxMenu();
    MenuItemLanguage = new wxMenu();
    MenuItemEnglish = new wxMenuItem(MenuItemLanguage, idLanguageEnglish, _("English"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemEnglish);
    MenuItemFrench = new wxMenuItem(MenuItemLanguage, idLanguageFrench, _("French"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemFrench);
    MenuItemSwedish = new wxMenuItem(MenuItemLanguage, idLanguageSwedish, _("Swedish/Finnish/Hungarian"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemSwedish);
    MenuItemCzech = new wxMenuItem(MenuItemLanguage, idLanguageCzechSlovak, _("Czech/Slovak"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemCzech);
    MenuItemGerman = new wxMenuItem(MenuItemLanguage, idLanguageGerman, _("German"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemGerman);
    MenuItemSpanish = new wxMenuItem(MenuItemLanguage, idLanguageSpanish, _("Spanish/Portuguese"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemSpanish);
    MenuItemItalian = new wxMenuItem(MenuItemLanguage, idLanguageItalian, _("Italian"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemItalian);
    MenuItemUnused = new wxMenuItem(MenuItemLanguage, idLanguageUnused, _("Unused"), wxEmptyString, wxITEM_RADIO);
    MenuItemLanguage->Append(MenuItemUnused);
    MenuItemUnused->Enable(false);
    MenuPresentation->Append(ID_MENUITEM1, _("Language"), MenuItemLanguage, wxEmptyString);
    MenuItem2 = new wxMenu();
    MenuItemRegion0 = new wxMenuItem(MenuItem2, ID_REGION0, _("0: Eng/Ger/Swe/Fin/Hun/Ita/Fre/Por/Spa/Cze/Slo"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion0);
    MenuItemRegion1 = new wxMenuItem(MenuItem2, ID_REGION1, _("1: Pol/Ger/Swe/Fin/Hun/Ita/Fre/Cze/Slo"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion1);
    MenuItemRegion2 = new wxMenuItem(MenuItem2, ID_REGION2, _("2: Eng/Fre/Swe-Fin-Hun/Tur/Ger/Por-Spa/Ita"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion2);
    MenuItemRegion3 = new wxMenuItem(MenuItem2, ID_REGION3, _("3: Ser/Cro/Slovenian/Romanian"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion3);
    MenuItemRegion4 = new wxMenuItem(MenuItem2, ID_REGION4, _("4: Ser-Cro/Ger/Est/Lit/Rus-Bul/Ukr/Cze-Slo"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion4);
    MenuItemRegion6 = new wxMenuItem(MenuItem2, ID_REGION6, _("6: Tur/Gre"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion6);
    MenuItemRegion8 = new wxMenuItem(MenuItem2, ID_REGION8, _("8: Eng/Fre/Arabic"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion8);
    MenuItemRegion10 = new wxMenuItem(MenuItem2, ID_REGION10, _("10: Hebrew/Arabic"), wxEmptyString, wxITEM_RADIO);
    MenuItem2->Append(MenuItemRegion10);
    MenuPresentation->Append(ID_REGION, _("Region"), MenuItem2, wxEmptyString);
    MenuItemPageNumber = new wxMenuItem(MenuPresentation, idPageNumber, _("Properties..."), _("Set the page number for transmission"), wxITEM_NORMAL);
    MenuPresentation->Append(MenuItemPageNumber);
    MenuItemShowHeader = new wxMenuItem(MenuPresentation, ID_MENUITEMSHOWHEADER, _("Show header"), wxEmptyString, wxITEM_CHECK);
    MenuPresentation->Append(MenuItemShowHeader);
    MenuItemShowHeader->Check(true);
    MenuItemConcealToggle = new wxMenuItem(MenuPresentation, ID_HIDECONCEAL, _("Toggle Conceal"), wxEmptyString, wxITEM_NORMAL);
    MenuPresentation->Append(MenuItemConcealToggle);
    MenuBar1->Append(MenuPresentation, _("Presentation"));
    MenuHelp = new wxMenu();
    MenuItemSpecialKeys = new wxMenuItem(MenuHelp, idSpecialKeys, _("Special keys"), _("Show the special function key table"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItemSpecialKeys);
    MenuItemAbout = new wxMenuItem(MenuHelp, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItemAbout);
    MenuBar1->Append(MenuHelp, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    LoadPageFileDialog = new wxFileDialog(this, _("Select teletext file"), wxEmptyString, wxEmptyString, _("TTI files (*.tti, *.ttix)|*.tti;*.ttix|EP1 files (*.ep1)|*.ep1|TTX files (*.ttx)|*.ttx|VTX files (*.vtx)|*.vtx|All files|*.*"), wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    m_Timer1.SetOwner(this, ID_TIMER1);
    m_Timer1.Start(456, false);
    FileDialogSaveAs = new wxFileDialog(this, _("Save file as..."), wxEmptyString, wxEmptyString, _("TTI files (*.tti, *.ttix)|*.tti;*.ttix"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(idNewPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuNew);
    Connect(isSavePageAs,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuSaveAs);
    Connect(idPublish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemPublish);
    Connect(idPublishSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemPublishSettings);
    Connect(idExportTTX40,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemExportTTX40Selected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnQuit);
    Connect(idNewWindow,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemNewWindow);
    Connect(idUndo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemCopySelected);
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemPasteSelected);
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemSelectAllSelected);
    Connect(idInsertPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemInsertSubpage);
    Connect(idDeleteSubPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemDeletePage);
    Connect(idLanguageEnglish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageFrench,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSwedish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageCzechSlovak,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageGerman,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSpanish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageItalian,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageUnused,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(ID_REGION0,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(idPageNumber,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemProperties);
    Connect(ID_HIDECONCEAL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemConcealToggle);
    Connect(idSpecialKeys,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuSpecialKeys);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wxTEDFrame::OnClose);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&wxTEDFrame::OnKeyDown);
    Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&wxTEDFrame::OnKeyUp);
    Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&wxTEDFrame::OnSetFocus);
    Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&wxTEDFrame::OnKillFocus);
    Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&wxTEDFrame::OnLeftUp);
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&wxTEDFrame::OnMouseMove);
    Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&wxTEDFrame::OnMouseWheel);
    //*)

    Connect(idOpenPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnOpen);
    Connect(idSavePage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnSave);

    // Precompute the Font metrics
    wxFont wf=GetFont();
    wxSize ttxSize;
    for (int i=100;i>7;i--)
    {
        wf.SetPointSize(i);
        SetFont(wf);
        ttxSize=GetTextExtent("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDD");
        m_fontSize[i]=ttxSize;
    }
    wf.SetPointSize(10);    // Set it back to what it should be
    SetFont(wf);

    StatusBar1->SetFont(wf); // No idea why this has the wrong font size

    m_resize(GetSize()); // Adjust the font to fit the available space

    /* Initial page */
    m_currentPage=m_rootPage = new TTXPage("BBC100.tti","");
    m_setLanguage();

    iPageCount=m_rootPage->GetPageCount();
    iPage=0;

    SetTitle(_("wxTED ")+VERSION_STRING);

    m_rootPage->SetSourcePage(""); // Prevent an accidental Save


    SetBackgroundStyle(wxBG_STYLE_PAINT);

    m_cursorPoint=wxPoint(0,1);

    m_focused=true;

    //Notebook1->AddPage(Panel1,"TAB 1"); // see http://www.codeprogress.com/cpp/libraries/wxwidgets/showWxExample.php?index=35&key=wxNotebookBackgroundImage
    //Notebook1->AddPage(Panel1,"TAB 2");
    //Notebook1->AddPage(Panel1,"TAB 3");

    // Persistence
    this->SetName("wxTED");
    wxPersistenceManager::Get().RegisterAndRestore((wxFrame*)this);

    m_publish_ftp_server=m_config->Read("/wxted/FTP/Server");
    m_publish_ftp_username=m_config->Read("/wxted/FTP/Username");
    m_publish_ftp_password=m_config->Read("/wxted/FTP/Password");
    m_publish_ftp_remote=m_config->Read("/wxted/FTP/Remote");

    SetRegionMenu(m_currentPage->GetRegion()); // Region language


// wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    wxPoint wxP;
    wxP.x=50;
    wxP.y=50;
    wxSize wxS;
    wxS.SetWidth(200);
    wxS.SetHeight(600);


    helpFrame=new HelpFrame(this->GetDefaultItem(),1,wxP,wxS);

    // std::cout << "Finished starting frame" << std::endl;
}

wxTEDFrame::~wxTEDFrame()
{
    delete helpFrame;
    delete m_config;
    if (m_rootPage!=NULL)
    {
        delete m_rootPage;
        m_rootPage=NULL;
    }
    //(*Destroy(wxTEDFrame)
    //*)
}

void wxTEDFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxTEDFrame::OnOpen(wxCommandEvent& event)
{
    std::string str;
    if (LoadPageFileDialog->ShowModal() == wxID_CANCEL)
        return;     // the user bottled out
    if (m_rootPage!=NULL) delete m_rootPage; // Delete the root page. All subpages will go too.
    str=LoadPageFileDialog->GetPath().ToStdString();

    wxString filename=LoadPageFileDialog->GetFilename();
    // std::cout << "the filename was " << filename << std::endl;
    // std::cout << "Loading a teletext page " << str << std::endl;
    m_rootPage = new TTXPage(str,filename.ToStdString());
    MenuItemSave->Enable(true);

    iPageCount=m_rootPage->GetPageCount();

    wxPaintEvent Pevent(0); // Make a dummy event
    m_setLanguage();
    iPage=0;
    m_currentPage=m_rootPage;

    SetRegionMenu(m_currentPage->GetRegion()); // Region language

    SetTitle(m_rootPage->GetSourcePage());
    OnPaint(Pevent);    // Refresh with the new page

    // m_parentWindow->Refresh();
    // Force an update now
    Refresh();
    Update();
}

void wxTEDFrame::OnSave(wxCommandEvent& event)
{
    bool result=m_rootPage->SavePageDefault(); // Write the file back where it came from
    if (!result)
    {
        wxString msg="File NOT saved.\nUse Save As and choose a new name";
        wxMessageBox(msg, _("Error"));
    }
}

void wxTEDFrame::OnMenuSaveAs(wxCommandEvent& event)
{
    if (FileDialogSaveAs->ShowModal() == wxID_CANCEL)
        return;     // the user bottled out
    std::string str=FileDialogSaveAs->GetPath().ToStdString();
    // std::cout << "Saving page to " << str << std::endl;
    bool result=m_rootPage->SavePage(str);
    if (!result)
    {
        wxString msg="File NOT saved.\nUse Save As and choose a new name";
        wxMessageBox(msg, _("Error"));
    }
    else // Set the filename
    {
        wxString filename=FileDialogSaveAs->GetFilename();
        m_rootPage->SetSourcePage(str);
        m_rootPage->SetShortFilename(filename.ToStdString());
        SetTitle(str);
        MenuItemSave->Enable(true);
    }

}

void wxTEDFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg="Cross platform teletext editor\n(c) 2014-2015, Peter Kwan.\nteastop.co.uk/teletext/wxted";
    wxMessageBox(msg, _("Welcome to wxTED ")+VERSION_STRING);
}

void wxTEDFrame::OnMenuNew(wxCommandEvent& event)
{
    // std::cout << "New page" << std::endl;
    delete m_rootPage;
    m_rootPage=new TTXPage();
    SetTitle("");
    m_setLanguage();
    SetRegionMenu(0);
    iPageCount=0;
    iPage=0;
    m_currentPage=m_rootPage;
}

void wxTEDFrame::OnMenuItemPublish(wxCommandEvent& event)
{
    // If the page has no filename, we can not save it. Do Save As or load another page.
    // We probably alao want to prevent Publishing a page with unsaved work in it. TODO.
    wxString sp=m_rootPage->GetSourcePage();
    wxString spShort=m_rootPage->GetShortFilename();
    if (sp.IsEmpty())
    {
        wxString msg="To publish this Page, do Save As first";
        wxMessageBox(msg, _("Page not sent"));
        return;
    }

    // Work out the source
    LPCTSTR source=sp.ToStdWstring().c_str();

    // Work out the destination
    LPCTSTR path=m_publish_ftp_remote;
    TCHAR buff[100]=_T("");
    LPTSTR destination=buff;
    _tcscat(destination,path);
    _tcscat(destination,spShort.ToStdWstring().c_str());

    // And do the send
    int result=send(m_publish_ftp_server,m_publish_ftp_username,m_publish_ftp_password,source,destination);
    // std::cout << "result of publish=" << result << std::endl;
    if (result)
    {
        wxString msg="Publish failed";
        wxMessageBox(msg, _("Page not sent"));
    }
    else
    {
        StatusBar1->SetLabel("FTP Finished OK"); // This doesn't work!
        //std::cout << "Publish OK. source=" << _(source) << " destination=" << _(destination ) << std::endl;
    }
}

void wxTEDFrame::OnMenuItemUndo(wxCommandEvent& event)
{
    // TODO: Grey out this option when there is nothing to undo.
    m_currentPage->Undo(m_cursorPoint);
}

void wxTEDFrame::OnKillFocus(wxFocusEvent& event)
{
    //std::cout << "Lost focus" << std::endl;
    m_focused=false;
    event.Skip(true); // allow default handling
}

void wxTEDFrame::OnSetFocus(wxFocusEvent& event)
{
    //std::cout << "Got focus" << std::endl;;
    m_focused=true;
    event.Skip(true); // allow default handling
}

void wxTEDFrame::OnMenuItemInsertSubpage(wxCommandEvent& event)
{
    //std::cout << "Insert page after #" << iPage << std::endl;
    TTXPage* p;
    TTXPage* childPage;
    // Create a new page
    p=new TTXPage();
    m_setLanguage();
    SetRegionMenu(m_currentPage->GetRegion()); // Region language
    iPage++;
    // Save the child page pointer
    childPage=m_currentPage->Getm_SubPage();
    // Set the child pointer to the new child page
    m_currentPage->Setm_SubPage(p);
    // Make the new page the current one
    m_currentPage=p;
    // Set the child pointer to the saved pointer
    m_currentPage->Setm_SubPage(childPage);

    // Recalculate the subcode sequence.
    iPageCount=m_rootPage->GetPageCount();
    //std::cout << "Suspect that we are in trouble AFTER this" << std::endl;

    // Put up a welcome message
    std::ostringstream str;
    //std::cout << "Trace1" << std::endl;
    str << "New subpage inserted " << iPage+1 << "/" << iPageCount;
    //std::cout << "Trace2" << std::endl;
    m_currentPage->SetRow(1,str.str());
    //std::cout << "Trace3" << std::endl;
}

void wxTEDFrame::OnMenuItemDeletePage(wxCommandEvent& event)
{
    // How many pages do we have?
    int count=m_rootPage->GetPageCount();
    // Can't delete the last remaining page
    if (count<2)
        return;
    // Delete the current page...

    // If we are on the first page we move to the second page.
    // This is more complicated because it affects the page pointers and the metadata.
    if (m_currentPage==m_rootPage)
    {
        TTXPage* p=m_rootPage->Getm_SubPage(); // This is the new root
        p->CopyMetaData(m_rootPage);            // As the root, it needs the metadata
        m_rootPage->Setm_SubPage(NULL);         // Unlink the old root node
        delete m_rootPage;                      // Dump the old root object
        m_rootPage=p;                           // And set the page pointers to the new root page
        m_currentPage=p;
    }
    else
    {
        // We are not on the first page, we go to the previous page.
        // Seek the parent page p
        TTXPage* p=m_rootPage;
        for (;p->Getm_SubPage()!=m_currentPage && p->Getm_SubPage()!=NULL;p=p->Getm_SubPage());
        if (p->Getm_SubPage()==m_currentPage)
            std::cout << "Hurrah, found parent object" << std::endl;
        else
        {
            std::cout << "Boo. Can not locate. Your code does not work" << std::endl;
            return;
        }
        // Before we delete the page, save the pointer to the next sub page
        TTXPage* nextSub=m_currentPage->Getm_SubPage();
        //std::cout << "Trace1 nextSub=" << (int)nextSub << std::endl;
        // Delete the page.
        m_currentPage->Setm_SubPage(NULL); // Break the link before delete, or the rest of the chain vanishes!
        delete m_currentPage;
        //std::cout << "Trace2 p=" << (int)p << "  p->Next=" << (int)p->Getm_SubPage() << std::endl;
        // Make the parent the current page
        m_currentPage=p;
        //std::cout << "Trace3 m_currentPage=" << (int) m_currentPage << std::endl;
        // Repair the page chain by relinking the next subpage.
        p->Setm_SubPage(nextSub);
        //std::cout << "Trace4" << std::endl;
        // Fix the counters
        if (iPage>0) iPage--;
        //std::cout << "Trace5" << std::endl;
    }
    // Recalculate the subcode sequence.
    iPageCount=m_rootPage->GetPageCount();
    // std::cout << "Trace6" << std::endl;
}

void wxTEDFrame::OnMenuItemLanguage(wxCommandEvent& event)
{
    int language=event.GetId()-(MenuItemEnglish->GetId() & 0x07);
    m_currentPage->SetLanguage(language);
    //std::cout << "Language handler " << m_currentPage->GetLanguage() << std::endl;
}

void wxTEDFrame::m_setLanguage()
{
//    std::cout << "m_setLanguage " << m_rootPage->GetLanguage() << std::endl;
    int language=m_currentPage->GetLanguage();
    // idLanguageEnglish
    /*
    MenuItemEnglish->Check(true);break;
    MenuItemFrench ->Check(true);break;
    MenuItemSwedish->Check(true);break;
    MenuItemCzech  ->Check(true);break;
    MenuItemGerman ->Check(true);break;
    MenuItemSpanish->Check(true);break;
    MenuItemItalian->Check(true);break;
    */
    switch (language)
    {
    case 0: MenuItemEnglish->Check(true);break;
    case 1: MenuItemFrench ->Check(true);break;
    case 2: MenuItemSwedish->Check(true);break;
    case 3: MenuItemCzech  ->Check(true);break;
    case 4: MenuItemGerman ->Check(true);break;
    case 5: MenuItemSpanish->Check(true);break;
    case 6: MenuItemItalian->Check(true);break;
    case 7: MenuItemUnused ->Check(true);break;
    }
}

void wxTEDFrame::OnMenuItemProperties(wxCommandEvent& event)
{
    // Copy dialog values from page
    std::ostringstream value("");

    // Page Number
    value << std::hex << m_rootPage->GetPageNumber();    // Get Page Number formatted as a hex string
    std::string s=value.str();
    m_propertiesDlg->TextCtrlPageNumber->SetValue(_(s)); // And put it in the dialog

    // Description
    m_propertiesDlg->TextCtrlDescription->SetValue(_(m_rootPage->GetDescription()));
    // Page Status flags
    int ps=m_rootPage->GetPageStatus();
    m_propertiesDlg->CheckBoxC4ErasePage ->SetValue((ps & PAGESTATUS_C4_ERASEPAGE)  >0);
    m_propertiesDlg->CheckBoxC5Newsflash ->SetValue((ps & PAGESTATUS_C5_NEWSFLASH)  >0);
    m_propertiesDlg->CheckBoxC6Subtitle  ->SetValue((ps & PAGESTATUS_C6_SUBTITLE)   >0);
    m_propertiesDlg->CheckBoxC7SuppressHeader->SetValue((ps & PAGESTATUS_C7_SUPPRESSHDR)>0);
    m_propertiesDlg->CheckBoxC8Update    ->SetValue((ps & PAGESTATUS_C8_UPDATE     )>0);
    m_propertiesDlg->CheckBoxTransmitPage->SetValue((ps & PAGESTATUS_TRANSMITPAGE)  >0);
    // Counter/Timer
    value.str("");
    value << std::dec << m_rootPage->GetCycleTime();    // The cycle count / time (seconds)
    s=value.str();
    m_propertiesDlg->TextCtrlCycleTime->SetValue(_(s)); // And put it in the dialog

    char mode=m_rootPage->GetCycleTimeMode();
    if (mode=='C')
        m_propertiesDlg->RadioBoxCycleMode->SetSelection(0);
    else
        m_propertiesDlg->RadioBoxCycleMode->SetSelection(1);

    // FASTEXT Link
    value.str("");
    value << std::hex << m_rootPage->GetFastextLink(0);
    m_propertiesDlg->TextCtrlFastext1->SetValue(value.str());
    value.str("");
    value << std::hex << m_rootPage->GetFastextLink(1);
    m_propertiesDlg->TextCtrlFastext2->SetValue(value.str());
    value.str("");
    value << std::hex << m_rootPage->GetFastextLink(2);
    m_propertiesDlg->TextCtrlFastext3->SetValue(value.str());
    value.str("");
    value << std::hex << m_rootPage->GetFastextLink(3);
    m_propertiesDlg->TextCtrlFastext4->SetValue(value.str());

    // FASTEXT Index
    value.str("");
    value << std::hex << m_rootPage->GetFastextLink(5);
    m_propertiesDlg->TextCtrlFastextIndex->SetValue(value.str());

    // Properties are now populated. Now show the dialog

    int result=m_propertiesDlg->ShowModal();

    if (result==wxID_CANCEL)
    {
        return;
    }


    // Now extract the parameters from the dialog and put them back in the loaded page

    if (result==wxID_OK)
    {
        char * ptr;
        bool b;

        int mask=PAGESTATUS_C4_ERASEPAGE | PAGESTATUS_C5_NEWSFLASH | PAGESTATUS_C6_SUBTITLE | PAGESTATUS_C7_SUPPRESSHDR |
        PAGESTATUS_C8_UPDATE | PAGESTATUS_TRANSMITPAGE; // Other flags are irrelevant
        ps&=~mask;   // Remove all the bits that we test

        // Page Number
        int pageNum;
        pageNum=std::strtol(m_propertiesDlg->TextCtrlPageNumber->GetValue().ToStdString().c_str(), &ptr, 16);
        m_rootPage->SetPageNumber(pageNum);
        //std::cout << "Page number=" << std::hex << pageNum << std::endl;

        // Page Status
        b=m_propertiesDlg->CheckBoxC4ErasePage     ->GetValue();    if (b) ps|=PAGESTATUS_C4_ERASEPAGE;
        b=m_propertiesDlg->CheckBoxC5Newsflash     ->GetValue();    if (b) ps|=PAGESTATUS_C5_NEWSFLASH;
        b=m_propertiesDlg->CheckBoxC6Subtitle      ->GetValue();    if (b) ps|=PAGESTATUS_C6_SUBTITLE;
        b=m_propertiesDlg->CheckBoxC7SuppressHeader->GetValue();    if (b) ps|=PAGESTATUS_C7_SUPPRESSHDR;
        b=m_propertiesDlg->CheckBoxC8Update        ->GetValue();    if (b) ps|=PAGESTATUS_C8_UPDATE;
        b=m_propertiesDlg->CheckBoxTransmitPage    ->GetValue();    if (b) ps|=PAGESTATUS_TRANSMITPAGE;

        m_rootPage->SetPageStatus(ps); // Put ps back into the object
        //std::cout << "Page status=" << std::hex << ps << std::endl;

        // Description
        m_rootPage->SetDescription(m_propertiesDlg->TextCtrlDescription->GetValue().ToStdString()); // Description

        // Counter/Timer
        std::string str=m_propertiesDlg->TextCtrlCycleTime->GetValue().ToStdString(); // Read the time from the dialog
        m_rootPage->SetCycleTime(atoi(str.c_str()));    // The cycle count / time (seconds)

        char ctmode=(m_propertiesDlg->RadioBoxCycleMode->GetSelection())==0?'C':'T';
        m_rootPage->SetCycleTimeMode(ctmode);

        // Fastext
        // Changed to ensure that ALL subpages have the same fastext links. It makes VBIT work much better
        //.. Hmm doesn't work
        int link;
        link=std::strtol(m_propertiesDlg->TextCtrlFastext1->GetValue().ToStdString().c_str(), &ptr, 16);
        // m_rootPage->SetFastextLink(0,link);
        for (TTXPage* p=m_rootPage;p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(0,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext2->GetValue().ToStdString().c_str(), &ptr, 16);
        //m_rootPage->SetFastextLink(1,link);
        for (TTXPage* p=m_rootPage;p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(1,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext3->GetValue().ToStdString().c_str(), &ptr, 16);
        //m_rootPage->SetFastextLink(2,link);
        for (TTXPage* p=m_rootPage;p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(2,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext4->GetValue().ToStdString().c_str(), &ptr, 16);
        // m_rootPage->SetFastextLink(3,link);
        for (TTXPage* p=m_rootPage;p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(3,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastextIndex->GetValue().ToStdString().c_str(), &ptr, 16);
        // m_rootPage->SetFastextLink(5,link);
        for (TTXPage* p=m_rootPage;p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(5,link);
    }
}

int send(LPCTSTR ftp, LPCTSTR user, LPCTSTR pass, LPCTSTR pathondisk, LPTSTR nameonftp)
{

	HINTERNET hInternet;
	HINTERNET hFtpSession;
	hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	if(hInternet==NULL)
	{
	    std::cout << "[send] InternetOpen Failed" << std::endl;
		return 1;
	}
	std::cout << "Connecting with ftp=" << _(ftp) << " user=" << _(user) << " pass=" << _(pass) << std::endl;
	hFtpSession = InternetConnect(hInternet,(LPTSTR)ftp , INTERNET_DEFAULT_FTP_PORT, (LPTSTR)user, (LPTSTR)pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
	if(hFtpSession==NULL)
	{
	    std::cout << "[send] InternetConnect Failed" << std::endl;
		return 1;
	}
	int x = FtpPutFile(hFtpSession, (LPTSTR)pathondisk, (LPTSTR)nameonftp, FTP_TRANSFER_TYPE_ASCII, 0);
	int y=GetLastError();
	std::cout << "y=" << y << std::endl;
	Sleep(1000);
	InternetCloseHandle(hFtpSession);
	InternetCloseHandle(hInternet);
	if(x==0)
	{
	    std::cout << "[send] FtpPutFile Failed" << std::endl;
		return 1;
	}
	if(x==1)
	{
		return 0;
	}
	return 1;
}

void wxTEDFrame::OnMenuItemPublishSettings(wxCommandEvent& event)
{
    // Create the dialog object
    PublishSetupDialog dlg(this,1001);
    // Load the dialog fields
    dlg.TextCtrlFTPServer->SetValue(m_publish_ftp_server);
    dlg.TextCtrlFTPUsername->SetValue(m_publish_ftp_username);
    dlg.TextCtrlFTPPassword->SetValue(m_publish_ftp_password);
    dlg.TextCtrlFTPRemote->SetValue(m_publish_ftp_remote);
    // Show the dialog
    int result=dlg.ShowModal();

    // If Cancel then forget about it
    if (result==wxID_CANCEL)
    {
        return;
    }

    // Extract the new settings
    m_publish_ftp_server=dlg.TextCtrlFTPServer->GetValue();
    m_publish_ftp_username=dlg.TextCtrlFTPUsername->GetValue();
    m_publish_ftp_password=dlg.TextCtrlFTPPassword->GetValue();
    m_publish_ftp_remote=dlg.TextCtrlFTPRemote->GetValue();

    m_config->Write("/wxted/FTP/Server"  ,m_publish_ftp_server);
    m_config->Write("/wxted/FTP/Username",m_publish_ftp_username);
    m_config->Write("/wxted/FTP/Password",m_publish_ftp_password);
    m_config->Write("/wxted/FTP/Remote"  ,m_publish_ftp_remote);

}

void wxTEDFrame::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() && TTXPage::pageChanged )
    {
        if ( wxMessageBox("The file has not been saved... continue closing?",
                          "Please confirm",
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();
            return;
        }
    }

    Destroy();  // you may also do:  event.Skip();
                // since the default event handler does call Destroy(), too
}

void wxTEDFrame::OnMenuItemConcealToggle(wxCommandEvent& event)
{
    m_reveal=!m_reveal;
}

void wxTEDFrame::OnMouseWheel(wxMouseEvent& event)
{
   // Want to click up and down the pages
   //int delta=event.GetWheelDelta();
   int rotate=event.GetWheelRotation();
   //std::cout << "Wheel Delta is " << delta << " Distance=" << rotate << std::endl;
   iPageCount=m_rootPage->GetPageCount();
   if (rotate>=0)
   {
        iPage++;
        if (iPage>=iPageCount) iPage=iPageCount-1;
   }
   if (rotate<0)
   {
        iPage--;
        if (iPage<0) iPage=0;
   }
   m_currentPage=m_rootPage->GetPage(iPage);
}

void wxTEDFrame::OnLeftUp(wxMouseEvent& event)
{
    m_dragging=false;
    // TODO: When left button goes up this ends a drag.
    wxPoint p=event.GetPosition(); // This is  pointless. What was I going to do?
    p.x/=m_ttxW;
    p.y/=m_ttxH;
    // std::cout << "end a drag at " << p.x << ", " << p.y << std::endl;

}



void wxTEDFrame::OnMouseMove(wxMouseEvent& event)
{
    // TODO: Extend this to highlight links on rollover
    // TODO: When left button moves, continue drag.
    if (!event.LeftIsDown()) // OnLeftUp only fires if you are over the frame.
        m_dragging=false;
    if (m_dragging)
    {
        wxPoint p=event.GetPosition();
        p.x/=m_ttxW;
        p.y/=m_ttxH;
        if (p.x>40) p.x=40;
        if (p.y>=25) p.y=25;
        m_MarqueeEnd=p; // Marquee end
        // std::cout << "continue drag at " << p.x << ", " << p.y << std::endl;
    }

}

void wxTEDFrame::OnLeftDown(wxMouseEvent& event) // Left Mouse down
{
    m_dragging=true;

//    std::cout << "Left button pressed..." << std::endl;
    wxPoint save=m_cursorPoint;
    m_cursorPoint=event.GetPosition();
    // Adjust to character location
    m_cursorPoint.x/=m_ttxW;
    m_cursorPoint.y/=m_ttxH;
    // Revert if clicked outside the page
    if (m_cursorPoint.x<0 || m_cursorPoint.x>39 || m_cursorPoint.y<0 || m_cursorPoint.y>24)
        m_cursorPoint=save;
    else
    {
        m_blinkToggle=true; // HCI: Make cursor moves immediately visible
        Refresh();
    }
    // std::cout << "(x,y)=(" << m_cursorPoint.x << ", " << m_cursorPoint.y << ")" << std::endl;

    m_MarqueeStart=m_cursorPoint; // In case we start a marquee
    m_MarqueeEnd=m_cursorPoint;

    // Skip(); // TODO: Is this needed? Probably is!
}


void wxTEDFrame::OnMenuItemCopySelected(wxCommandEvent& event)
{
    // *thinks*
    // How can we cut and paste between instances of wxTED because that would be really useful.
    // What data did we just copy?
    //std::cout << m_MarqueeStart.x << "," << m_MarqueeStart.y << "    " << m_MarqueeEnd.x  << "," << m_MarqueeEnd.y << std::endl;
    // These are the coordinates
    int x1=m_MarqueeStart.x;
    int y1=m_MarqueeStart.y;
    int x2=m_MarqueeEnd.x;
    int y2=m_MarqueeEnd.y;

    // Flip left right if needed
    if (x1>x2)
    {
        x1=m_MarqueeEnd.x;
        x2=m_MarqueeStart.x;
    }
    // Flip up down if needed
    if (y1>y2)
    {
        y1=m_MarqueeEnd.y;
        y2=m_MarqueeStart.y;
    }
    wxString wxs;
    wxs.Pad((y2-y1)*(x2-x1+1),'X');    // Make a blank array.
    // row
    int ix=0;
    for (int y=y1;y<y2;y++)
    {
        TTXLine* line=m_currentPage->GetRow(y);
        for (int x=x1;x<x2;x++)
        {
            wxChar wxc=line->GetCharAt(x);
            // std::cout << "char=" << (char)wxc << std::endl;
            if (wxc==0x0d) wxc=0x8d;    // Protect double height
            wxs[ix++]=wxc;
        }
        wxs[ix++]=0xff; // need some special character
    }
    //std::cout << "wxs=" << _(wxs) << std::endl;
    CopyTextToClipboard(_(wxs));
}

void wxTEDFrame::CopyTextToClipboard(wxString text)
{
   if (m_clip->Open())
   {
      m_clip->Clear();
      m_clip->SetData( new wxTextDataObject( text ) );
      m_clip->Flush();
      m_clip->Close();
   }
}

wxString wxTEDFrame::GetTextFromClipboard()
{
   wxString wxs;
   if (m_clip->Open())
   {
      if (m_clip->IsSupported( wxDF_TEXT ))
      {
          wxTextDataObject data;
          m_clip->GetData(data);
          wxs=data.GetText();
      }
      else
        wxs="";
      m_clip->Close();
   }
   return wxs;
}

/** Paste
 * One sneaky trick, is if the URL starts
 * http://editor.teletext40.com
 * then we assume that the clipboard contains a URL from the teletext40 editor and should be decoded as such.
 */
void wxTEDFrame::OnMenuItemPasteSelected(wxCommandEvent& event)
{
   wxString wxs;
   wxs=GetTextFromClipboard();
   /// @todo Make this more general to identify a valid hash string
   if ((wxs.Find("http://editor.teletext40.com")!=wxNOT_FOUND) ||  // Paste a teletext40 URL?
    (wxs.Find("www.uniquecodeanddata.co.uk/editor")!=wxNOT_FOUND) ||     // Paste a uniquecodeandadata URL?
    (wxs.Find("edit.tf")!=wxNOT_FOUND))     // Paste edit.tf URL?
   {
       load_from_hash(m_currentPage,wxs.char_str());
   }
   else
   {
       // Now paste this text at the location m_cursorPoint
       // A NULL char is the end of a line. Note: This will conflict with AlphaBlack code.
       wxChar ch;
       int x=m_cursorPoint.x;
       int y=m_cursorPoint.y;
       TTXLine* line=m_currentPage->GetRow(y++);
       for (uint16_t i=0;i<wxs.Length();i++)
       {
            ch=wxs[i];
            if (ch==0xff)
            {
                line=m_currentPage->GetRow(y++);
                x=m_cursorPoint.x;
            }
            else
                if (x<=40 && y<=25) // Clip to frame!
                    line->SetCharAt(x++,ch);
            if (y>25) break;    // Off the bottom of the page? We are done.
       }
   }
   //std::cout << "Paste=" << wxs << std::endl;
}

void wxTEDFrame::OnMenuItemSelectAllSelected(wxCommandEvent& event)
{
    m_MarqueeStart=wxPoint(0,0);
    m_MarqueeEnd=wxPoint(40,25);
}

void wxTEDFrame::OnMenuItemRegionSelected(wxCommandEvent& event)
{
    int region=event.GetId()-MenuItemRegion0->GetId();
    // Map menu numbers to regions
    switch (region)
    {
    case 0: region=0;
        break;
    case 1: region=1;
        break;
    case 2: region=2;
        break;
    case 3: region=3;
        break;
    case 4: region=4;
        break;
    case 5: region=6; // Turkish and Greek
        break;
    case 6: region=8; // English/French/Arabic;
        break;
    case 7: region=10; // Hebrew/Arabic
        break;
    default: region=0;
    }
    std::cout << "Region changed to " << region << std::endl;
    // TODO: Remember the reserved regions we need to map over
    // Note that the C12,C13,C14 bits determine the order of the languages
    // and we reverse them from transmission order.
    // See Table 32: Function of Default G0 and G2 Character Set Designation and National Option
    // Selection bits in packets X/28/0 Format 1, X/28/4, M/29/0 and M/29/4

    SetRegionMenu(region);
}

void wxTEDFrame::SetRegionMenu(int region)
{
    // Enable everything
    MenuItemEnglish->Enable(true);
    MenuItemFrench->Enable(true);
    MenuItemSwedish->Enable(true);
    MenuItemCzech->Enable(true);
    MenuItemGerman->Enable(true);
    MenuItemSpanish->Enable(true);
    MenuItemItalian->Enable(true);
    MenuItemUnused->Enable(true);
    switch (region) // Admittedly, the first 5 are redundant!
    {
    case 0:
        MenuItemEnglish->SetItemLabel(_("English"));
        MenuItemFrench->SetItemLabel (_("French"));
        MenuItemSwedish->SetItemLabel(_("Swedish/Finnish/Hungarian"));
        MenuItemCzech->SetItemLabel  (_("Czech/Slovak"));
        MenuItemGerman->SetItemLabel (_("German"));
        MenuItemSpanish->SetItemLabel(_("Portuguese/Spanish"));
        MenuItemItalian->SetItemLabel(_("Italian"));
        MenuItemUnused->SetItemLabel (_("Unused")); MenuItemUnused->Enable(false);
        break;
    case 1:
        MenuItemEnglish->SetItemLabel(_("Polish"));
        MenuItemFrench->SetItemLabel (_("French"));
        MenuItemSwedish->SetItemLabel(_("Swedish/Finnish/Hungarian"));
        MenuItemCzech->SetItemLabel  (_("Czech/Slovak"));
        MenuItemGerman->SetItemLabel (_("German"));
        MenuItemSpanish->SetItemLabel(_("Unused")); MenuItemSpanish->Enable(false);
        MenuItemItalian->SetItemLabel(_("Italian"));
        MenuItemUnused->SetItemLabel (_("Unused")); MenuItemUnused->Enable(false);
        break;
    case 2:
        MenuItemEnglish->SetItemLabel(_("English"));
        MenuItemFrench->SetItemLabel (_("French"));
        MenuItemSwedish->SetItemLabel(_("Swedish/Finnish/Hungarian"));
        MenuItemCzech->SetItemLabel  (_("Turkish"));
        MenuItemGerman->SetItemLabel (_("German"));
        MenuItemSpanish->SetItemLabel(_("Portuguese/Spanish"));
        MenuItemItalian->SetItemLabel(_("Italian"));
        MenuItemUnused->SetItemLabel (_("Unused")); MenuItemUnused->Enable(false);
        break;
    case 3:
        MenuItemEnglish->SetItemLabel(_("Unused")); MenuItemEnglish->Enable(false);
        MenuItemFrench->SetItemLabel (_("Unused")); MenuItemFrench->Enable(false);
        MenuItemSwedish->SetItemLabel(_("Unused")); MenuItemSwedish->Enable(false);
        MenuItemCzech->SetItemLabel  (_("Unused")); MenuItemCzech->Enable(false);
        MenuItemGerman->SetItemLabel (_("Unused")); MenuItemGerman->Enable(false);
        MenuItemSpanish->SetItemLabel(_("Serbian/Croatian/Slovenian"));
        MenuItemItalian->SetItemLabel(_("Unused")); MenuItemItalian->Enable(false);
        MenuItemUnused->SetItemLabel (_("Rumanian"));
        break;
    case 4:
        MenuItemEnglish->SetItemLabel(_("Serbian/Croatian"));
        MenuItemFrench->SetItemLabel (_("Russian/Bulgarian"));
        MenuItemSwedish->SetItemLabel(_("Estonian"));
        MenuItemCzech->SetItemLabel  (_("Czech/Slovak"));
        MenuItemGerman->SetItemLabel (_("German"));
        MenuItemSpanish->SetItemLabel(_("Ukrainian"));
        MenuItemItalian->SetItemLabel(_("Lettish/Lithuanian"));
        MenuItemUnused->SetItemLabel (_("Unused")); MenuItemUnused->Enable(false);
        break;
    case 6: // Turkish and Greek
        MenuItemEnglish->SetItemLabel(_("Unused")); MenuItemEnglish->Enable(false);
        MenuItemFrench->SetItemLabel (_("Unused")); MenuItemFrench->Enable(false);
        MenuItemSwedish->SetItemLabel(_("Unused")); MenuItemSwedish->Enable(false);
        MenuItemCzech->SetItemLabel  (_("Turkish"));
        MenuItemGerman->SetItemLabel (_("Unused")); MenuItemGerman->Enable(false);
        MenuItemSpanish->SetItemLabel(_("Unused")); MenuItemSpanish->Enable(false);
        MenuItemItalian->SetItemLabel(_("Unused")); MenuItemItalian->Enable(false);
        MenuItemUnused->SetItemLabel (_("Greek"));
        break;
    case 8: // English/French/Arabic;
        MenuItemEnglish->SetItemLabel(_("English"));
        MenuItemFrench->SetItemLabel (_("French"));
        MenuItemSwedish->SetItemLabel(_("Unused")); MenuItemSwedish->Enable(false);
        MenuItemCzech->SetItemLabel  (_("Unused")); MenuItemCzech->Enable(false);
        MenuItemGerman->SetItemLabel (_("Unused")); MenuItemGerman->Enable(false);
        MenuItemSpanish->SetItemLabel(_("Unused")); MenuItemSpanish->Enable(false);
        MenuItemItalian->SetItemLabel(_("Unused")); MenuItemItalian->Enable(false);
        MenuItemUnused->SetItemLabel (_("Arabic"));
        break;
    case 10: // Hebrew/Arabic
        MenuItemEnglish->SetItemLabel(_("Unused")); MenuItemEnglish->Enable(false);
        MenuItemFrench->SetItemLabel (_("Unused")); MenuItemFrench->Enable(false);
        MenuItemSwedish->SetItemLabel(_("Unused")); MenuItemSwedish->Enable(false);
        MenuItemCzech->SetItemLabel  (_("Unused")); MenuItemCzech->Enable(false);
        MenuItemGerman->SetItemLabel (_("Unused")); MenuItemGerman->Enable(false);
        MenuItemSpanish->SetItemLabel(_("Hebrew"));
        MenuItemItalian->SetItemLabel(_("Unused")); MenuItemItalian->Enable(false);
        MenuItemUnused->SetItemLabel (_("Arabic"));
        break;
    default: region=0;
    }
    m_currentPage->SetRegion(region);
    int language=m_currentPage->GetLanguage();
    switch (language)
    {
    case 0: MenuItemEnglish->Check(true);break;
    case 1: MenuItemFrench ->Check(true);break;
    case 2: MenuItemSwedish->Check(true);break;
    case 3: MenuItemCzech  ->Check(true);break;
    case 4: MenuItemGerman ->Check(true);break;
    case 5: MenuItemSpanish->Check(true);break;
    case 6: MenuItemItalian->Check(true);break;
    case 7: MenuItemUnused ->Check(true);break;
    }
    switch (region)
    {
    case 0:  MenuItemRegion0 ->Check(true);break;
    case 1:  MenuItemRegion1 ->Check(true);break;
    case 2:  MenuItemRegion2 ->Check(true);break;
    case 3:  MenuItemRegion3 ->Check(true);break;
    case 4:  MenuItemRegion4 ->Check(true);break;
    case 6:  MenuItemRegion6 ->Check(true);break;
    case 8:  MenuItemRegion8 ->Check(true);break;
    case 10: MenuItemRegion10->Check(true);break;
    }
}

void wxTEDFrame::OnMenuSpecialKeys(wxCommandEvent& event)
{
    helpFrame->Show(true);
}

void wxTEDFrame::OnMenuItemExportTTX40Selected(wxCommandEvent& event)
{

    // Extract a character array
    uint8_t cc[24][40];
    for (uint8_t y=0;y<24;y++)
    {
        TTXLine* line=m_currentPage->GetRow(y);
        for (uint8_t x=0;x<40;x++)
        {
            uint8_t c=line->GetCharAt(x) & 0x7f;
            cc[y][x]=c;
        }
    }
    // Convert to a teletext 40 URL
    // TODO: Implement character set
    char page[1200];
    save_to_hash(1, page,cc);
    CopyTextToClipboard(page);
    // Launch a browser with the URL
    // Widen the URL
    std::wstring w;
    std::copy(page,page+strlen(page),back_inserter(w));
    const wchar_t *wstr = w.c_str();

    ShellExecute (NULL, L"open", wstr, NULL, NULL, SW_SHOWNORMAL);
}

void wxTEDFrame::OnKeyDown(wxKeyEvent& event)
{
    int k=event.GetKeyCode();
    if (k==WXK_ALT && m_Released)
    {
        m_ShowMarkup=!m_ShowMarkup;
        m_Released=false;
    }
    event.Skip(true);
}

void wxTEDFrame::OnKeyUp(wxKeyEvent& event)
{
    int k=event.GetKeyCode();
    if (k==WXK_ALT)
    {
        m_Released=true;
    }
    event.Skip(true);
}

void wxTEDFrame::OnMenuItemNewWindow(wxCommandEvent& event)
{
	wxTEDFrame * win = new wxTEDFrame(0);
	win->OnMenuNew(event);
	win->Show(true);
}
