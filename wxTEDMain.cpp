/***************************************************************
 * Name:      wxTEDMain.cpp
 * Purpose:   Code for Application Frame
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
 * The author disclaim all warranties with regard to this
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
const long wxTEDFrame::idProperties = wxNewId();
const long wxTEDFrame::idPublish = wxNewId();
const long wxTEDFrame::idPublishSettings = wxNewId();
const long wxTEDFrame::idMenuQuit = wxNewId();
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
const long wxTEDFrame::ID_MENUITEM1 = wxNewId();
const long wxTEDFrame::idPageNumber = wxNewId();
const long wxTEDFrame::ID_MENUITEMSHOWHEADER = wxNewId();
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
    default:
        m_currentPage->SetCharAt(code, modifiers, m_cursorPoint, m_subPixelPoint, MenuItemShowHeader->IsChecked());
    }

    //std::cout << "Cursor = " << m_cursorPoint.x << "." << m_subPixelPoint.x << ", "
    //     << m_cursorPoint.y << "." << m_subPixelPoint.y << ", "  << std::endl;
    m_cursorIsAlpha=m_currentPage->IsAlphaMode(m_cursorPoint);
    m_blinkToggle=true; // HCI: Make cursor moves immediately visible
    Refresh();
}

void wxTEDFrame::OnLeftDown(wxMouseEvent& event) // Left Mouse down
{
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
    std::cout << "(x,y)=(" << m_cursorPoint.x << ", " << m_cursorPoint.y << ")" << std::endl;
    // Skip(); // Is this needed? Probably is!
}

void wxTEDFrame::OnTimer(wxTimerEvent& event)
{
    // Only blink while focused otherwise stay on.
    // std::cout << "blink=" << m_blinkToggle << " m_focused=" << m_focused << std::endl;
    if (m_blinkToggle && m_focused)
        m_blinkToggle=false;
    else
        m_blinkToggle=true;
    // Paint it
    Refresh();
}

/* mpp page number
 * dd date
 * nn month
 * yy year
 * DAY day
 * MTH month
 * hh hour
 * nn minute
 * ss second
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

    i=str.find("mpp");
    if (i>0)
    {
        str.replace(i,3,val.str());
    }

    i=str.find("dd");
    if (i>0)
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
        str.replace(i,2,val.str());
    }

    i=str.find("DAY");
    if (i>0)
    {
        char day[10];
        char* p=day;
        strftime(p,4,"%a",timeinfo);
        str.replace(i,3,p);
    }

    i=str.find("MTH");
    if (i>0)
    {
        char month[10];
        char* p=month;
        strftime(p,4,"%b",timeinfo);
        str.replace(i,3,p);
    }

    i=str.find("hh");
    if (i>31) // Clock hours
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_hour;
        str.replace(i,2,val.str());
    }

    i=str.find("nn");
    if (i>31) // Clock minutes
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_min;
        str.replace(i,2,val.str());
    }
    if (i>8) // nn Day of month
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_mon+1;
        str.replace(i,2,val.str());
    }

    i=str.find("ss");
    if (i>31) // Clock seconds
    {
        val.str("");
        val << std::setw(2) << std::setfill('0') << std::dec << timeinfo->tm_sec;
        str.replace(i,2,val.str());
    }


    i=str.find("yy");
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
    // std::cout << "Current window size " << clientSize.GetWidth() << std::endl;
    // What is the current font size?
    wxFont wf=GetFont();
    // Iterate for best fit
    int i;
    for (i=8;i<100;i++)
    {
        if (clientSize.GetWidth()<m_fontSize[i].GetWidth()+10) // allow 10 pixels, I think the border is included
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
    {
        bool graphics=false;
        bool separated=false;
        bool doubleheight=false;
        bool flashing=false;
        bool hold=false;
        char holdChar=' ';


        fg=wxWHITE;
        bg=wxBLACK;

        doubleHeightDC.SetBackground(*wxBLACK_BRUSH);
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
                switch (str[col]) // TODO: Replace all of these with teletext codes
                {
                case ttxCodeAlphaBlack :    // Invalid Farrimond mode. Might want to make this black fg.
                    fg=wxBLACK;
                    graphics=false;
                    break;
                case ttxCodeAlphaRed :
                    fg=wxRED;
                    graphics=false;
                    break;
                case ttxCodeAlphaGreen :
                    fg=wxGREEN;
                    graphics=false;
                    break;
                case ttxCodeAlphaYellow :
                    fg=wxYELLOW;
                    graphics=false;
                    break;
                case ttxCodeAlphaBlue :
                    fg=wxBLUE;
                    graphics=false;
                    break;
                case ttxCodeAlphaMagenta :
                    fg=magenta; // wxMAGENTA
                    graphics=false;
                    break;
                case ttxCodeAlphaCyan :
                    fg=wxCYAN;
                    graphics=false;
                    break;
                case ttxCodeAlphaWhite :
                    fg=wxWHITE;
                    graphics=false;
                    break;
                case ttxCodeFlash :
                    flashing=true;
                    break;
                case ttxCodeSteady :
                    flashing=false;
                    break;
                case ttxCodeEndBox :
                    std::cout << "End Box not implemented" << std::endl;
                    break;
                case ttxCodeStartBox :
                    std::cout << "Start box not implemented" << std::endl;
                    break;
                case ttxCodeNormalHeight : // Normal height. Not sure this is ever used.
                    doubleheight=false;
                    break;
                case ttxCodeDoubleHeight : // Double height
                    doubleheight=true;
                    break;
                case ttxCodeGraphicsRed : // Graphics red
                    graphics=true;
                    fg=wxRED;
                    break;
                case ttxCodeGraphicsGreen : // Graphics green
                    graphics=true;
                    fg=wxGREEN;
                    break;
                case ttxCodeGraphicsYellow : // Graphics yellow
                    graphics=true;
                    fg=wxYELLOW;
                    break;
                case ttxCodeGraphicsBlue : // Graphics blue
                    graphics=true;
                    fg=wxBLUE;
                    break;
                case ttxCodeGraphicsMagenta : // Graphics magenta
                    graphics=true;
                    fg=magenta;
                    break;
                case ttxCodeGraphicsCyan : // Graphics cyan
                    graphics=true;
                    fg=wxCYAN;
                    break;
                case ttxCodeGraphicsWhite : // Graphics white
                    graphics=true;
                    fg=wxWHITE;
                    break;
                case ttxCodeConcealDisplay : // Conceal display
                    std::cout << "Conceal not implemented" << std::endl;
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
                case ttxCodeHoldGraphics : // Hold gfx
                    hold=true;
                    break;
                case ttxCodeReleaseGraphics : // Separated gfx
                    hold=false;
                    break;
                case 14:; // Ignore shift in/shift out and avoid them falling into default
                case 15:;
                case 16:;
                    break;
                default :
                    // std::cout << "Trace OL:ordinary character " << ch << std::endl;
                    ch=str[col] & 0x7f;
                    ch2=str[col];
                    ch2=mapTextChar(ch2);
                    if ((ch>0x20 && ch<0x40) || ch>=0x60) holdChar=ch;  // In case we encounter hold mosaics (Space doesn't count as a mosaic)
                }
                if (graphics && ((ch>=0x20 && ch<0x40) || ch>=0x60) ) // Graphics (but not capital A..Z)
                {
                    if (hold)
                        ch=holdChar;
                    int j=0x01;
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
                        int k=separated?-1:1; // Add or subtract a line
                        paintDC.DrawRectangle(wxPoint(           col*m_ttxW + (i % 2)*m_ttxW/2,
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
            } // each character on this row
            // The line is drawn. Do we need to double height it?
            if (doubleheight)
            {
                // Write into a bitmap and stretch blit it into the main DC at double height
                paintDC.StretchBlit(wxPoint(0,row*m_ttxH),wxSize(40*m_ttxW,m_ttxH*2), // dest
                                    &doubleHeightDC,
                                    wxPoint(0,0),wxSize(40*m_ttxW,m_ttxH)); //src
                row++;  // Skip the next row or it will overwrite the lower half of the blit
            }
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
        if (m_cursorIsAlpha)
        {
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW,m_cursorPoint.y*m_ttxH),wxSize(m_ttxW,m_ttxH));
        }
        else
        {
            int halfw=m_ttxW/2;
            int thirdh=m_ttxH/3;
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW+m_subPixelPoint.x*halfw,
                                          m_cursorPoint.y*m_ttxH+m_subPixelPoint.y*thirdh),
                                  wxSize(halfw,thirdh));
        }
        paintDC.SetPen(*wxTRANSPARENT_PEN);
    }
    m_SetStatus();
    // std::cout << "[OnPaint] exits " << std::endl;
}

wchar_t wxTEDFrame::mapTextChar(wchar_t ch)
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    switch (m_rootPage->GetLanguage())
    {
    case 0 : // English
        // Nat. opt. 1
        if (ch=='#')  ch=0x00A3; // 2/3 # is mapped to pound sign
        //if (ch=='$')  ch=0x0024; // 2/4 Dollar sign (no change!)
        //if (ch=='@')  ch=0x0040; // 4/0 No change
        if (ch=='[')  ch=0x2190; // 5/B Left arrow.
        if (ch=='\\') ch=0xbd;   // 5/C Half
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D Right arrow.
        if (ch=='^')  ch=0x2191; // 5/E Up arrow.
        if (ch=='_')  ch=0x0023; // 5/F Underscore is hash sign
        if (ch=='`')  ch=0x2014; // 6/0 Centre dash. The full width dash e731
        if (ch=='{')  ch=0xbc;   // 7/B Quarter
        if (ch=='|')  ch=0x2016; // 7/C Double pipe
        if (ch=='}')  ch=0xbe;   // 7/D Three quarters
        if (ch=='~')  ch=0x00f7; // 7/E Divide
        // Another mapping but not in the nat. opts.
        break;
    case 1 : // French
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e9; // 2/3 e acute
        if (ch=='$')  ch=0x00ef; // 2/4 i umlaut
        if (ch=='@')  ch=0x00e0; // 4/0 a grave
        if (ch=='[')  ch=0x00eb; // 5/B e umlaut
        if (ch=='\\') ch=0x00ea; // 5/C e circumflex
        // Nat. opt. 2
        if (ch==']')  ch=0x00f9; // 5/D u grave
        if (ch=='^')  ch=0x00ee; // 5/E i circumflex
        if (ch=='_')  ch='#';    // 5/F #
        if (ch=='`')  ch=0x00e8; // 6/0 e grave
        if (ch=='{')  ch=0x00e2; // 7/B a circumflex
        if (ch=='|')  ch=0x00f4; // 7/C o circumflex
        if (ch=='}')  ch=0x00fb; // 7/D u circumflex
        if (ch=='~')  ch=0x00e7; // 7/E c cedilla
        break;
    case 2 : // Swedish
        // Nat. opt. 1
        if (ch=='#')  ch='#'; // 2/3 hash
        if (ch=='$')  ch=0x00a4; // 2/4 currency bug
        if (ch=='@')  ch=0x00c9; // 4/0 E acute
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d4; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00c5; // 5/D A ring
        if (ch=='^')  ch=0x00dc; // 5/E U umlaut
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00d6; // 7/C o umlaut
        if (ch=='}')  ch=0x00e5; // 7/D a ring
        if (ch=='~')  ch=0x00fc; // 7/E u umlaut
        break;
    case 3 : // Czech/Slovak
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 hash
        if (ch=='$')  ch=0x016f; // 2/4 u ring
        if (ch=='@')  ch=0x010d; // 4/0 c caron
        if (ch=='[')  ch=0x0165; // 5/B t caron
        if (ch=='\\') ch=0x017e; // 5/C z caron
        // Nat. opt. 2
        if (ch==']')  ch=0x00fd; // 5/D y acute
        if (ch=='^')  ch=0x00ed; // 5/E i acute
        if (ch=='_')  ch=0x0159; // 5/F r caron
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e1; // 7/B a acute
        if (ch=='|')  ch=0x011b; // 7/C e caron
        if (ch=='}')  ch=0x00fa; // 7/D u acute
        if (ch=='~')  ch=0x0161; // 7/E s caron
        break;
    case 4 : // German
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 # is not mapped
        if (ch=='$')  ch=0x0024; // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a7; // 4/0 Section sign
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00dc; // 5/D U umlaut
        if (ch=='^')  ch='^';    // 5/E Caret (not mapped)
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00b0; // 6/0 Masculine ordinal indicator
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00f6; // 7/C o umlaut
        if (ch=='}')  ch=0x00fc; // 7/D u umlaut
        if (ch=='~')  ch=0x00df; // 7/E SS
        break;
    case 5 : // Spanish/Portuguese
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e7; // 2/3 c cedilla
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a1; // 4/0 inverted exclamation mark
        if (ch=='[')  ch=0x00e1; // 5/B a acute
        if (ch=='\\') ch=0x00e9; // 5/C e acute
        // Nat. opt. 2
        if (ch==']')  ch=0x00ed; // 5/D i acute
        if (ch=='^')  ch=0x00f3; // 5/E o acute
        if (ch=='_')  ch=0x00fa; // 5/F u acute
        if (ch=='`')  ch=0x00bf; // 6/0 Inverted question mark
        if (ch=='{')  ch=0x00fc; // 7/B u umlaut
        if (ch=='|')  ch=0x00f1; // 7/C n tilde
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00e0; // 7/E a grave
        break;
    case 6 : // Italian
        // Nat. opt. 1
        if (ch=='#')  ch=0x00a3; // 2/3 Pound
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00e9; // 4/0 e acute
        if (ch=='[')  ch=0x00b0; // 5/B ring
        if (ch=='\\') ch=0x00e7; // 5/C c cedilla
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D right arrow
        if (ch=='^')  ch=0x2191; // 5/E up arrow
        if (ch=='_')  ch='#';    // 5/F hash
        if (ch=='`')  ch=0x00f9; // 6/0 u grave
        if (ch=='{')  ch=0x00e0; // 7/B a grave
        if (ch=='|')  ch=0x00f2; // 7/C o grave
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00ec; // 7/E i grave
        break;
    default:
        std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;;
    }
    // More language mappings including Greek
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)
    return ch;
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
            case ttxCodeAlphaBlack:    code<<"Alpha black";break;
            case ttxCodeAlphaRed:      code<<"Alpha Red";break;
            case ttxCodeAlphaGreen:    code<<"Alpha Green";break;
            case ttxCodeAlphaYellow:   code<<"Alpha Yellow";break;
            case ttxCodeAlphaBlue:     code<<"Alpha Blue";break;
            case ttxCodeAlphaMagenta:  code<<"Alpha Magenta";break;
            case ttxCodeAlphaCyan:     code<<"Alpha Cyan";break;
            case ttxCodeAlphaWhite:    code<<"Alpha White";break;
            case ttxCodeFlash:         code<<"Flash";break;
            case ttxCodeSteady:        code<<"Steady";break;
            case ttxCodeEndBox:        code<<"End box";break;
            case ttxCodeStartBox:      code<<"Start box";break;
            case ttxCodeNormalHeight:  code<<"Normal height";break;
            case ttxCodeDoubleHeight:  code<<"Double height";break;
            case ttxCodeGraphicsRed:   code<<"Graphics Red";break;
            case ttxCodeGraphicsGreen: code<<"Graphics Green";break;
            case ttxCodeGraphicsYellow: code<<"Graphics Yellow";break;
            case ttxCodeGraphicsBlue:  code<<"Graphics Blue";break;
            case ttxCodeGraphicsMagenta: code<<"Graphics Magenta";break;
            case ttxCodeGraphicsCyan:  code<<"Graphics Cyan";break;
            case ttxCodeGraphicsWhite: code<<"Graphics White";break;
            case ttxCodeConcealDisplay: code<<"Conceal";break;
            case ttxCodeContiguousGraphics: code<<"Continguous graphics";break;
            case ttxCodeSeparatedGraphics: code<<"Separated graphics";break;
            case ttxCodeBlackBackground: code<<"Black background";break;
            case ttxCodeNewBackground: code<<"New background";break;
            case ttxCodeHoldGraphics:  code<<"Hold graphics";break;
            case ttxCodeReleaseGraphics: code<<"Release graphics";break;
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

wxTEDFrame::wxTEDFrame(wxWindow* parent,wxWindowID id) : m_currentPage(NULL), m_ttxW(15), m_ttxH(20), m_cursorIsAlpha(true), m_subPixelPoint(wxPoint(0,0))
{
    // std::cout << "[wxTEDFrame] Entered" << std::endl;
    m_parentWindow=parent;
    m_blinkToggle=false;
    m_propertiesDlg=new PageSettingsDialog(this,1000);

    m_publish_ftp_server=FTP_SERVER;
    m_publish_ftp_username=FTP_USER;
    m_publish_ftp_password=FTP_PASSWORD;

    //(*Initialize(wxTEDFrame)
    wxMenu* MenuHelp;
    wxMenuItem* MenuItemAbout;
    wxMenu* Menu1;
    wxMenuItem* MenuItemQuit;
    wxMenuBar* MenuBar1;

    Create(parent, wxID_ANY, _("wxTED 1.02"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
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
    MenuItem4 = new wxMenuItem(Menu1, idSavePage, _("Save\tCTRL-S"), _("Save a teletext page"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItemSaveAs = new wxMenuItem(Menu1, isSavePageAs, _("Save as"), _("Save a teletext page with a different name"), wxITEM_NORMAL);
    Menu1->Append(MenuItemSaveAs);
    Menu1->AppendSeparator();
    MenuItemProperties = new wxMenuItem(Menu1, idProperties, _("Properties"), _("Page properties"), wxITEM_NORMAL);
    Menu1->Append(MenuItemProperties);
    MenuItemPublish = new wxMenuItem(Menu1, idPublish, _("Publish"), _("Publish the page to an inserter"), wxITEM_NORMAL);
    Menu1->Append(MenuItemPublish);
    MenuItemPublishSettings = new wxMenuItem(Menu1, idPublishSettings, _("Publish settings..."), _("Choose publish method"), wxITEM_NORMAL);
    Menu1->Append(MenuItemPublishSettings);
    MenuItemQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItemQuit);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItemUndo = new wxMenuItem(Menu3, idUndo, _("Undo"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItemUndo);
    MenuItemUndo->Enable(false);
    Menu3->AppendSeparator();
    MenuItem11 = new wxMenuItem(Menu3, idCut, _("Cut"), _("Cut the selected area"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    MenuItem11->Enable(false);
    MenuItem12 = new wxMenuItem(Menu3, idCopy, _("Copy"), _("Copy the selected area"), wxITEM_NORMAL);
    Menu3->Append(MenuItem12);
    MenuItem12->Enable(false);
    MenuItem13 = new wxMenuItem(Menu3, idPaste, _("Paste"), _("Paste text from the clipboard"), wxITEM_NORMAL);
    Menu3->Append(MenuItem13);
    MenuItem13->Enable(false);
    MenuItem14 = new wxMenuItem(Menu3, idSelectAll, _("Select All"), _("Select the entire page"), wxITEM_NORMAL);
    Menu3->Append(MenuItem14);
    MenuItem14->Enable(false);
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
    MenuPresentation->Append(ID_MENUITEM1, _("Language"), MenuItemLanguage, wxEmptyString);
    MenuItemPageNumber = new wxMenuItem(MenuPresentation, idPageNumber, _("Properties"), _("Set the page number for transmission"), wxITEM_NORMAL);
    MenuPresentation->Append(MenuItemPageNumber);
    MenuItemShowHeader = new wxMenuItem(MenuPresentation, ID_MENUITEMSHOWHEADER, _("Show header"), wxEmptyString, wxITEM_CHECK);
    MenuPresentation->Append(MenuItemShowHeader);
    MenuBar1->Append(MenuPresentation, _("Presentation"));
    MenuHelp = new wxMenu();
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
    LoadPageFileDialog = new wxFileDialog(this, _("Select teletext file"), wxEmptyString, wxEmptyString, _("*.tti*"), wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    m_Timer1.SetOwner(this, ID_TIMER1);
    m_Timer1.Start(456, false);
    FileDialogSaveAs = new wxFileDialog(this, _("Save file as..."), wxEmptyString, wxEmptyString, _("*.tti"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(idNewPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuNew);
    Connect(isSavePageAs,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuSaveAs);
    Connect(idProperties,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemProperties);
    Connect(idPublish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemPublish);
    Connect(idPublishSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemPublishSettings);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnQuit);
    Connect(idUndo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idInsertPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemInsertSubpage);
    Connect(idDeleteSubPage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemDeletePage);
    Connect(idLanguageEnglish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageFrench,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSwedish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageCzechSlovak,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageGerman,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSpanish,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageItalian,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idPageNumber,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnMenuItemProperties);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTEDFrame::OnAbout);
    Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&wxTEDFrame::OnSetFocus);
    Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&wxTEDFrame::OnKillFocus);
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
    m_rootPage = new TTXPage("BBC100.tti","");
    m_setLanguage();
    iPageCount=m_rootPage->GetPageCount();
    iPage=0;

    m_rootPage->SetSourcePage(""); // Prevent an accidental Save
    m_currentPage=m_rootPage;

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    m_cursorPoint=wxPoint(0,1);

    m_focused=true;

    //Notebook1->AddPage(Panel1,"TAB 1"); // see http://www.codeprogress.com/cpp/libraries/wxwidgets/showWxExample.php?index=35&key=wxNotebookBackgroundImage
    //Notebook1->AddPage(Panel1,"TAB 2");
    //Notebook1->AddPage(Panel1,"TAB 3");

    std::cout << "Finished starting frame" << std::endl;
}

wxTEDFrame::~wxTEDFrame()
{
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
    std::cout << "the filename was " << filename << std::endl;
    std::cout << "Loading a teletext page " << str << std::endl;
    m_rootPage = new TTXPage(str,filename.ToStdString());
    iPageCount=m_rootPage->GetPageCount();

    wxPaintEvent Pevent(0); // Make a dummy event
    m_setLanguage();
    iPage=0;
    m_currentPage=m_rootPage;
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
    std::cout << "Saving page to " << str << std::endl;
    bool result=m_rootPage->SavePage(str);
    if (!result)
    {
        wxString msg="File NOT saved.\nUse Save As and choose a new name";
        wxMessageBox(msg, _("Error"));
    }
}

void wxTEDFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg="Cross platform teletext editor\n(c) 2014, Peter Kwan.\nteastop.co.uk/teletext/wxted";
    wxMessageBox(msg, _("Welcome to wxTED 1.02"));
}

void wxTEDFrame::OnMenuNew(wxCommandEvent& event)
{
    std::cout << "New page" << std::endl;
    delete m_rootPage;
    m_rootPage=new TTXPage();
    m_setLanguage();
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
        wxMessageBox(msg, _("Not saved"));
        return;
    }

    // Work out the source
    LPCTSTR source=sp.ToStdWstring().c_str();

    // Work out the destination
    LPCTSTR path=_T("htdocs/teletext/wxted/");
    TCHAR buff[100]=_T("");
    LPTSTR destination=buff;
    _tcscat(destination,path);
    _tcscat(destination,spShort.ToStdWstring().c_str());

    // And do the send
    int result=send(FTP_SERVER,FTP_USER,FTP_PASSWORD,source,destination);
    std::cout << "result of publish=" << result << std::endl;
}

void wxTEDFrame::OnMenuItemUndo(wxCommandEvent& event)
{
    wxString msg="Edit: None of this is implemented";
    wxMessageBox(msg, _("Not implemented"));
}

void wxTEDFrame::OnKillFocus(wxFocusEvent& event)
{
    std::cout << "Lost focus" << std::endl;
    m_focused=false;
    event.Skip(true); // allow default handling
}

void wxTEDFrame::OnSetFocus(wxFocusEvent& event)
{
    std::cout << "Got focus" << std::endl;;
    m_focused=true;
    event.Skip(true); // allow default handling
}

void wxTEDFrame::OnMenuItemInsertSubpage(wxCommandEvent& event)
{
    std::cout << "Insert page after #" << iPage << std::endl;
    TTXPage* p;
    TTXPage* childPage;
    // Create a new page
    p=new TTXPage();
    m_setLanguage();
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

    std::cout << "Suspect that we are in trouble AFTER this" << std::endl;

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
        std::cout << "Trace1 nextSub=" << (int)nextSub << std::endl;
        // Delete the page.
        m_currentPage->Setm_SubPage(NULL); // Break the link before delete, or the rest of the chain vanishes!
        delete m_currentPage;
        std::cout << "Trace2 p=" << (int)p << "  p->Next=" << (int)p->Getm_SubPage() << std::endl;
        // Make the parent the current page
        m_currentPage=p;
        std::cout << "Trace3 mCurrentPage=" << (int) m_currentPage << std::endl;
        // Repair the page chain by relinking the next subpage.
        p->Setm_SubPage(nextSub);
        std::cout << "Trace4" << std::endl;
        // Fix the counters
        if (iPage>0) iPage--;
        std::cout << "Trace5" << std::endl;
    }
    // Recalculate the subcode sequence.
    iPageCount=m_rootPage->GetPageCount();
    // std::cout << "Trace6" << std::endl;
}

void wxTEDFrame::OnMenuItemLanguage(wxCommandEvent& event)
{
    int language=event.GetId()-(MenuItemEnglish->GetId() & 0x07);
    m_rootPage->SetLanguage(language);
    std::cout << "Language handler " << m_rootPage->GetLanguage() << std::endl;

}

void wxTEDFrame::m_setLanguage()
{
    std::cout << "m_setLanguage " << m_rootPage->GetLanguage() << std::endl;
    int language=m_rootPage->GetLanguage();
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
        std::cout << "Page number=" << std::hex << pageNum << std::endl;

        // Page Status
        b=m_propertiesDlg->CheckBoxC4ErasePage     ->GetValue();    if (b) ps|=PAGESTATUS_C4_ERASEPAGE;
        b=m_propertiesDlg->CheckBoxC5Newsflash     ->GetValue();    if (b) ps|=PAGESTATUS_C5_NEWSFLASH;
        b=m_propertiesDlg->CheckBoxC6Subtitle      ->GetValue();    if (b) ps|=PAGESTATUS_C6_SUBTITLE;
        b=m_propertiesDlg->CheckBoxC7SuppressHeader->GetValue();    if (b) ps|=PAGESTATUS_C7_SUPPRESSHDR;
        b=m_propertiesDlg->CheckBoxC8Update        ->GetValue();    if (b) ps|=PAGESTATUS_C8_UPDATE;
        b=m_propertiesDlg->CheckBoxTransmitPage    ->GetValue();    if (b) ps|=PAGESTATUS_TRANSMITPAGE;

        m_rootPage->SetPageStatus(ps); // Put ps back into the object
        std::cout << "Page status=" << std::hex << ps << std::endl;

        // Description
        m_rootPage->SetDescription(m_propertiesDlg->TextCtrlDescription->GetValue().ToStdString()); // Description

        // Counter/Timer
        std::string str=m_propertiesDlg->TextCtrlCycleTime->GetValue().ToStdString(); // Read the time from the dialog
        m_rootPage->SetCycleTime(atoi(str.c_str()));    // The cycle count / time (seconds)

        char ctmode=(m_propertiesDlg->RadioBoxCycleMode->GetSelection())==0?'C':'T';
        m_rootPage->SetCycleTimeMode(ctmode);
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
	std::cout << "tryna connect with ftp=" << ftp << " user=" << user << " pass=" << pass << std::endl;
	hFtpSession = InternetConnect(hInternet,(LPTSTR)ftp , INTERNET_DEFAULT_FTP_PORT, (LPTSTR)user, (LPTSTR)pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
	// hFtpSession = InternetConnect(hInternet,L"ftp.plus.net" , INTERNET_DEFAULT_FTP_PORT,L"teastop", L"passkey6", INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
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
    // Show the dialog
    int result=dlg.ShowModal();

    // If Cancel then forget about it
    if (result==wxID_CANCEL)
    {
        return;
    }

    // Extract the new settings


}
