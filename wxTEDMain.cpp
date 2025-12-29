/***************************************************************
 * Name:      wxTEDMain.cpp
 * Purpose:   Teletext editor Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan
 * License:
  *
 * Copyright (C) 2014-2025, Peter Kwan
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

#if defined(__WXMSW_DISABLED__)
#include <winver.h>
#endif

//(*InternalHeaders(wxTEDFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)
#include <wx/dcbuffer.h>

// include <wx/filename.h>
#include <wx/stdpaths.h>

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
const wxWindowID wxTEDFrame::ID_PANEL1 = wxNewId();
const wxWindowID wxTEDFrame::idNewPage = wxNewId();
const wxWindowID wxTEDFrame::idNewFromTemplate = wxNewId();
const wxWindowID wxTEDFrame::idOpenPage = wxNewId();
const wxWindowID wxTEDFrame::idSavePage = wxNewId();
const wxWindowID wxTEDFrame::isSavePageAs = wxNewId();
const wxWindowID wxTEDFrame::idExportTTX40 = wxNewId();
const wxWindowID wxTEDFrame::isExportZxnet = wxNewId();
const wxWindowID wxTEDFrame::idMenuQuit = wxNewId();
const wxWindowID wxTEDFrame::idNewWindow = wxNewId();
const wxWindowID wxTEDFrame::idUndo = wxNewId();
const wxWindowID wxTEDFrame::idCut = wxNewId();
const wxWindowID wxTEDFrame::idCopy = wxNewId();
const wxWindowID wxTEDFrame::idPaste = wxNewId();
const wxWindowID wxTEDFrame::idSelectAll = wxNewId();
const wxWindowID wxTEDFrame::isInsertLine = wxNewId();
const wxWindowID wxTEDFrame::isDeleteLine = wxNewId();
const wxWindowID wxTEDFrame::idInsertPage = wxNewId();
const wxWindowID wxTEDFrame::idDeleteSubPage = wxNewId();
const wxWindowID wxTEDFrame::idLanguageEnglish = wxNewId();
const wxWindowID wxTEDFrame::idLanguageFrench = wxNewId();
const wxWindowID wxTEDFrame::idLanguageSwedish = wxNewId();
const wxWindowID wxTEDFrame::idLanguageCzechSlovak = wxNewId();
const wxWindowID wxTEDFrame::idLanguageGerman = wxNewId();
const wxWindowID wxTEDFrame::idLanguageSpanish = wxNewId();
const wxWindowID wxTEDFrame::idLanguageItalian = wxNewId();
const wxWindowID wxTEDFrame::idLanguageUnused = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM1 = wxNewId();
const wxWindowID wxTEDFrame::idPageNumber = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEMSHOWHEADER = wxNewId();
const wxWindowID wxTEDFrame::ID_SHOWCONTROL = wxNewId();
const wxWindowID wxTEDFrame::ID_HIDECONCEAL = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage0 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage1 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage2 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage3 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage4 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage5 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage6 = wxNewId();
const wxWindowID wxTEDFrame::idMainLanguage7 = wxNewId();
const wxWindowID wxTEDFrame::ID_MAINLANGUAGE = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION0 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION1 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION3 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION4 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION6 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION8 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION10 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUMAINREGION = wxNewId();
const wxWindowID wxTEDFrame::idSecondLanguage0 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM2 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM3 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM4 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM5 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM6 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM7 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUITEM8 = wxNewId();
const wxWindowID wxTEDFrame::ID_SECOND_REGION = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R0 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R1 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R2 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R3 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R4 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R6 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R8 = wxNewId();
const wxWindowID wxTEDFrame::ID_REGION2R10 = wxNewId();
const wxWindowID wxTEDFrame::ID_MENUSECONDREGION = wxNewId();
const wxWindowID wxTEDFrame::ID_PALETTE = wxNewId();
const wxWindowID wxTEDFrame::x28enhance = wxNewId();
const wxWindowID wxTEDFrame::idRun = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode = wxNewId();
const wxWindowID wxTEDFrame::idRadioBounce = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode0 = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode1 = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode2 = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode3 = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode4 = wxNewId();
const wxWindowID wxTEDFrame::idRadioMode5 = wxNewId();
const wxWindowID wxTEDFrame::idSpecialKeys = wxNewId();
const wxWindowID wxTEDFrame::idMenuAbout = wxNewId();
const wxWindowID wxTEDFrame::ID_STATUSBAR1 = wxNewId();
const wxWindowID wxTEDFrame::ID_TIMER1 = wxNewId();
//*)


BEGIN_EVENT_TABLE(wxTEDFrame,wxFrame)
    //(*EventTable(wxTEDFrame)
    EVT_PAINT(wxTEDFrame::OnPaint)
    EVT_SIZE(wxTEDFrame::OnSize)
    EVT_LEFT_DOWN(wxTEDFrame::OnLeftDown)
    EVT_CHAR(wxTEDFrame::OnChar)
    EVT_KEY_DOWN(wxTEDFrame::OnKeyDown)
    EVT_KEY_UP(wxTEDFrame::OnKeyUp)
    EVT_TIMER(ID_TIMER1 ,wxTEDFrame::OnTimer)
    EVT_ERASE_BACKGROUND(wxTEDFrame::OnEraseBackground)
    EVT_MENU_OPEN(wxTEDFrame::OnMenuOpen)
    EVT_MENU_CLOSE(wxTEDFrame::OnMenuClose)
    //*)
END_EVENT_TABLE()

void wxTEDFrame::OnEraseBackground(wxEraseEvent& event)
{
  // NULL method! Something to help with double buffering flashing.
  // std::cout << "Erase..." << std::endl;
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
  std::cout << "[OnChar]Key event..." << code << std::endl;
  // We look at a few codes which apply to a page set rather than just a single page
  // If none of these codes apply, we send the character to the page
  std::shared_ptr<TEDEvent> tev;
  // Toggle invisible control codes?
  if (m_escapeMode)
  {
    if (code=='Q' || code=='q' || code=='X' || code=='x') // Codes and Grid are combined in wxTED
    {
      m_ShowMarkup=!m_ShowMarkup;
      MenuItemShowCodes-> Check(m_ShowMarkup);
      code=WXK_ESCAPE;
    }
  }
  // hack for preview mode. Any keyboard key cancels preview mode
  if (m_previewCarouselMode)
  {
      if (code>0) // Cancel preview mode
      {
          m_previewCarouselMode = false;
          SetTitle(previewSavedCaption); // Restore the previous caption
          m_Timer1.Start(456);
          // We don't want to issue a random edit key so quit now
          return;
      }
      else
      {
          if (PreviewNormal->IsChecked())
          {
              // The timing comes from the file.
              int seconds = pageSet->CurrentPage()->GetCycleTime();
              m_Timer1.Start(seconds * 1000);
          }
          if (m_previewForwards)
          {
            if (m_bounceMode && pageSet->CurrentPageIndex()+1 >= pageSet->GetPageCount())
            {
              m_previewForwards = false; // reverse direction
              code = WXK_PAGEDOWN;
            }
            else
            {
              code = WXK_PAGEUP;
            }
          }
          else
          {
            if (pageSet->CurrentPageIndex() == 0) // backwards loop carousel
            {
              m_previewForwards = true; // Bounce back
              code = WXK_PAGEUP;
            }
            else
            {
              code = WXK_PAGEDOWN;  // Bouncing down
            }
          }
      }
  }
  switch (code)
  {
  case WXK_ESCAPE:
    m_escapeMode=!m_escapeMode;
    break;
  case WXK_PAGEUP:
    // std::cout << "Page up will get next page of a multiple page carousel" << std::endl;
    if (m_cursorPoint.y<1)
    {
      m_cursorPoint.y=1;
    }
    pageSet->NextPage();

    paletteFrame->SetX28(pageSet->CurrentPage()->GetX28Row()); // Update PaletteFrame in case we have it open

    // Take the languages and regions and update the menu selections
    SetRegionMenu(pageSet->CurrentPage()->GetRegion(true), true); // true is primary
    // @todo Secondary language


    // If the page is now off screen, scroll left to bring the right edge aligned with the window
    {
      auto rightEdge=(pageSet->CurrentPageIndex()+1)*m_ttxW*41; // Distance from first page to end of current page
      uint32_t mappedEdge=rightEdge-m_ttxW+m_offset.x; // Edge that we want mapped to the right hand side of the client frame space
      uint32_t clientWidth=GetClientSize().GetWidth();
      if (mappedEdge>clientWidth)
      {
        m_offset.x=clientWidth-rightEdge-m_ttxW; // Scroll left to bring the right side into frame
      }
    }
    break;
  case WXK_PAGEDOWN:
    // std::cout << "Page down will get previous page of a multiple page carousel" << std::endl;
    pageSet->PreviousPage();
    SetRegionMenu(pageSet->CurrentPage()->GetRegion(true), true); // true is primary
    // @todo Secondary language

    paletteFrame->SetX28(pageSet->CurrentPage()->GetX28Row()); // Update PaletteFrame in case we have it open
    // If the page is now off screen, scroll left to bring the right edge aligned with the window
    {
      int leftEdge = pageSet->CurrentPageIndex() * m_ttxW * 41; // Distance from first page to left edge of current page
      int mappedEdge = leftEdge - m_ttxW + m_offset.x; // Edge that we want mapped to client frame space
      std::cout << std::dec << "iPage= " << pageSet->CurrentPageIndex() << " mappedEdge=" << mappedEdge << " leftEdge=" << leftEdge << std::endl;
      if (mappedEdge<0 || mappedEdge>GetClientSize().GetWidth())
      {
        m_offset.x=-leftEdge; // Scroll left to bring the right side into frame
      }
    }
    break;
  case WXK_F11: // Reveal concealed text
    m_reveal=!m_reveal;
    break;
  case WXK_CONTROL_Y: // Ah. This is why we can't use CTRL-Y as a special key. This was for debugging undo.
    // std::cout << "CTRL-Y test" << std::endl; // Testing
    tev = pageSet->CurrentPage()->GetUndo();
    if (tev!=NULL)
    {
      tev->dump();
    }
    break;
  case WXK_CONTROL_Z:
    // std::cout << "CTRL-Z undo" << std::endl;
    // tev=pageSet->CurrentPage()->GetUndo();
    pageSet->CurrentPage()->Undo(m_cursorPoint);
    break;
    // Moved this to ttxpage as it acts on the page
  //case WXK_TAB: // This will insert a space
//    std::cout << "Insert a space TBA" << std::endl;
    //break;
  default:
    // If the last key pressed was escape, we are doing an edit.tf style escape
    if (m_escapeMode)
    {
      m_escapeMode=false;
      // Find the key that was pressed, and map it to a native keycode
      switch (code)
      {
      case 'r': ;
      case '1': modifiers=wxMOD_SHIFT;   code=WXK_F1;break; // alpha red
      case 'R': ;
      case '!': modifiers=wxMOD_CONTROL; code=WXK_F1;break; // mosaic red
      case 'g': ;
      case '2': modifiers=wxMOD_SHIFT;   code=WXK_F2;break; // alpha green
      case 'G': ;
      case '"': modifiers=wxMOD_CONTROL; code=WXK_F2;break; // mosaic green
      case 'y': ;
      case '3': modifiers=wxMOD_SHIFT;   code=WXK_F3;break; // alpha yellow
      case 'Y': ;
      case '£': modifiers=wxMOD_CONTROL; code=WXK_F3;break; // mosaic yellow
      case 'b': ;
      case '4': modifiers=wxMOD_SHIFT;   code=WXK_F4;break; // alpha blue
      case 'B': ;
      case '$': modifiers=wxMOD_CONTROL; code=WXK_F4;break; // mosaic blue
      case 'm': ;
      case '5': modifiers=wxMOD_SHIFT;   code=WXK_F5;break; // alpha magenta
      case 'M': ;
      case '%': modifiers=wxMOD_CONTROL; code=WXK_F5;break; // mosaic magenta
      case 'c': ;
      case '6': modifiers=wxMOD_SHIFT;   code=WXK_F6;break; // alpha cyan
      case 'C': ;
      case '^': modifiers=wxMOD_CONTROL; code=WXK_F6;break; // mosaic cyan
      case 'w': ;
      case '7': modifiers=wxMOD_SHIFT;   code=WXK_F7;break; // alpha white
      case 'W': ;
      case '&': modifiers=wxMOD_CONTROL; code=WXK_F7;break; // mosaic white
      case 'k': ;
      case '0': modifiers=wxMOD_SHIFT;   code=WXK_F8;break; // alpha black
      case 'K': ;
      case ')': modifiers=wxMOD_CONTROL; code=WXK_F8;break; // mosaic black
      case 'i': modifiers=wxMOD_SHIFT;   code=WXK_F9;break; // insert line
      case 'I': modifiers=wxMOD_CONTROL; code=WXK_F9;break; // delete line
      case 'N': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_B;   break; // new background
      case 'n': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_U;   break; // black background
      case 'f': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_I;   break; // steady
      case 'F': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_H;   break; // flash
      case 'h': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_X;   break; // release
      case 'H': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_W;   break; // hold
      case 'd': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_L;   break; // normal height
      case 'D': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_M;   break; // double height
      case 'O': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_R;   break; // conceal
      case 'S': modifiers=wxMOD_CONTROL; code=WXK_CONTROL_T;   break; // separate graphics
      case 's': /*
        if (m_controlModifier)
        {
          std::cout << "Implement ESC CTRL S " << std::endl; // ctrl-s Insert an ESC (language toggle)
        }
        else */
        {
          modifiers=wxMOD_CONTROL; code=WXK_CONTROL_E; // contiguous
        }
        break;
      case 'J': modifiers=wxMOD_NONE;    code=172;   break; // hook maps to text block

      // @todo Lots more codes
      // asc(20) is ctrl-s which can be used for ESC which is the language toggle code
      }
      std::cout << "[wxTEDFrame::OnChar] code = " << (int)code << std::endl;
    } // edit.tf escape mode
    pageSet->CurrentPage()->SetCharAt(code, modifiers, m_cursorPoint, m_subPixelPoint, MenuItemShowHeader->IsChecked());
  }

  //std::cout << "Cursor = " << m_cursorPoint.x << "." << m_subPixelPoint.x << ", "
  //     << m_cursorPoint.y << "." << m_subPixelPoint.y << ", "  << std::endl;
  m_cursorIsAlpha=pageSet->CurrentPage()->IsAlphaMode(m_cursorPoint);
  m_blinkToggle=true; // HCI: Make cursor moves immediately visible
  Refresh();
  event.Skip();
}

void wxTEDFrame::OnTimer(wxTimerEvent& event)
{
  // Only blink while focused otherwise stay on.
  // Don't show the cursor in preview mode.
  // std::cout << "blink=" << m_blinkToggle << " m_focused=" << m_focused << std::endl;

  if ((m_blinkToggle && m_focused) || m_previewCarouselMode)
      m_blinkToggle=false;
  else
      m_blinkToggle=true;

  if (m_previewCarouselMode)
  {
      wxKeyEvent pageup(wxEVT_CHAR);
      //auto pageup = wxKeyEvent(WXK_PAGEUP);
      OnChar(pageup);
  }

  Refresh(false); // Paint it
}

bool wxTEDFrame::isMosaic(char ch)
{
    ch&=0x7f;
    return (ch>=0x20 && ch<0x40) || ch>=0x60;
}

/* new--old description. Don't use old codes. They no longer work in VBIT.
 * %%£  mpp page number
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
    for (i=0; i<8; i++) // First 8 characters are not taken from the header
    {
      str[i]=' ';
    }
    int k=pageSet->GetPageNumber()/0x100;
    if (k<0x100 || k>0x8ff)
    {
      k=0x100;
    }
    val << std::hex << k;
    str[0]='P';
    str.replace(1,3,val.str()); // Replace the first 4 characters with the page number

    // Magazine and page number
    i=str.find("mpp");
    if (i<=0) i=str.find("%%#");
    if (i<=0) i=str.find("%%£");
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
    if (i<=0) i=str.find("%y");
    if (i>0)
    {
        val.str("");
        val << std::dec << std::setw(2) << std::setfill('0') << timeinfo->tm_year % 100;
        str.replace(i,2,val.str());
    }

    // std::cout << "GenerateHeader exits with str=" << str << std::endl;
    line->SetRow(str);
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
        // Fit width
        if (clientSize.GetWidth()<m_fontSize[i].GetWidth()+10) // allow 10 pixels, I think the border is included
            break;
        // or fit height
        if (clientSize.GetHeight()<m_fontSize[i].GetHeight()*27+40)
            break;
    }
    // Don't make it too small
    if (i>6) i--;
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
    if (this->IsIconized()) return; // If Iconized we shouldn't draw anything

    wxPoint offset=m_offset;

    wxBufferedPaintDC paintDC(this);

    // redraw the whole teletext page

    /* colours */
    unsigned int fg = ttxCodeAlphaWhite;
    unsigned int bg = ttxCodeAlphaBlack;

    wxBitmap doubleHeightBitmap(m_ttxW*40,m_ttxH*2);    // The image buffer for double height. (Sized for a single height plus generous fudge factor)

    wxMemoryDC doubleHeightDC;
    doubleHeightDC.SelectObject(doubleHeightBitmap);  // The device context for double height text

    // Copy the font settings over
    wxFont wf=GetFont();
    doubleHeightDC.SetFont(wf);

    /* Fill the background */
    paintDC.SetPen(*wxTRANSPARENT_PEN);
    doubleHeightDC.SetPen(*wxTRANSPARENT_PEN);
    //if (m_ShowMarkup)
    //{
        //doubleHeightDC.SetPen(*wxGREY_PEN);
        //paintDC.SetPen(*wxGREY_PEN);
    //}
    // SetTTXBrushColour(*wxBLACK_BRUSH);
    paintDC.SetBrush(wxBrush(*wxBLACK_BRUSH));
    doubleHeightDC.SetBrush(wxBrush(*wxBLACK_BRUSH));
    int w,h;
    paintDC.GetSize(&w, &h);
    paintDC.DrawRectangle(wxPoint(0,0),wxSize(w,h));
    // paintDC.DrawRectangle(wxPoint(0,0),wxSize(40*m_ttxW,24*m_ttxH));
    // TODO: Black out rows if they are NULL, to avoid old text getting stuck

    paintDC.SetBackgroundMode(wxSOLID); // Otherwise the background colour is transparent!
    doubleHeightDC.SetBackgroundMode(wxSOLID); // Otherwise the background colour is transparent!

    wxColour* magenta=new wxColour(255,0,255); // wxMagenta is not a thing

    /* page */

    // Assume horizontal subpages for now
    for (int i=0; i<pageSet->GetPageCount(); ++i)
    {
      TTXPage* p = pageSet->GetPage(i); // Get an observer pointer
      if (offset.x > this->GetClientSize().GetWidth())  // Don't bother to render pages outside of the window
      {
        break;
      }
      // Some lambdas because we want functions with access to the local environment
      auto SetTTXForegroundColour = [&](const unsigned int colour)
      {
        // Find the teletext colour index
        // Map it through the X28 clut
        unsigned int clrRemap = p->Remap(colour, true); // 12 bit value returned
        // Split the colour back to RGB
        unsigned char R = (clrRemap >> 8) & 0x0f;
        unsigned char G = (clrRemap >> 4) & 0x0f;
        unsigned char B = (clrRemap) & 0x0f;
        const wxColour* wxc = new wxColour(R<<4 | R, G<<4 | G, B<<4 | B); // ttxCode2wxColour(colour);
        doubleHeightDC.SetTextForeground(*wxc);
        paintDC.SetTextForeground(*wxc);
      };

      auto SetTTXBackgroundColour = [&](const unsigned int colour)
      {
        unsigned int clrRemap = p->Remap(colour, false); // 12 bit value returned
        // Split the colour back to RGB
        unsigned char R = (clrRemap >> 8) & 0x0f;
        unsigned char G = (clrRemap >> 4) & 0x0f;
        unsigned char B = (clrRemap) & 0x0f;
        const wxColour* wxc = new wxColour(R<<4 | R, G<<4 | G, B<<4 | B); // ttxCode2wxColour(colour);
        doubleHeightDC.SetTextBackground(*wxc);
        paintDC.SetTextBackground(*wxc);
      };

      auto SetTTXBrushColour = [&](const unsigned int colour, bool foreground)
      {
        unsigned int clrRemap = p->Remap(colour, foreground); // 12 bit value returned
        // Split the colour back to RGB
        unsigned char R = (clrRemap >> 8) & 0x0f;
        unsigned char G = (clrRemap >> 4) & 0x0f;
        unsigned char B = (clrRemap) & 0x0f;
        const wxColour* wxc = new wxColour(R<<4 | R, G<<4 | G, B<<4 | B); // ttxCode2wxColour(colour);
        paintDC.SetBrush(wxBrush(*wxc));
        doubleHeightDC.SetBrush(wxBrush(*wxc));
      };



      // Skip frames that are completely on the left of the window
      if (offset.x+(static_cast<int>(m_ttxW)*41)<0)
      {
        //std::cout << "Skipped drawing frame Xo=" << std::dec << offset.x << " " << m_ttxW*41 << std::endl;
        offset.x+=m_ttxW*41;
        continue;
      }

      auto addMarkup=(p==pageSet->CurrentPage()) && m_ShowMarkup;
      if (addMarkup)
      {
        doubleHeightDC.SetPen(*wxGREY_PEN);
        paintDC.SetPen(*wxGREY_PEN);
      }
      else
      {
        paintDC.SetPen(*wxTRANSPARENT_PEN);
        doubleHeightDC.SetPen(*wxTRANSPARENT_PEN);
      }


      TTXLine row0;
      int firstRow=1;
      if (MenuItemShowHeader->IsChecked())
      {
        firstRow=0;
      }
      for (unsigned int row=firstRow;row<25;row++)
      {
          bool graphicsMode=false;
          bool separated=false;
          bool doubleHeight=false;
          bool skipnextrow=false;
          bool flashing=false;
          bool hold=false;
          char holdChar=' ';
          bool concealed=false;
          bool toggleG0Set = true;

          fg = ttxCodeAlphaWhite;
          bg = ttxCodeAlphaBlack;

          doubleHeightDC.SetBackground(*wxBLACK_BRUSH); //  wxBLACK_BRUSH. Change this to GREY to track down bugs
          doubleHeightDC.Clear();

          // std::shared_ptr<TTXPage> p=page.GetPage(0);
          TTXLine* line=p->GetRow(row);

          if (m_cursorPoint.y>0 && row==0) // If we are actually in the header, then edit the raw header
          {

              if (line==NULL)
              {
                  p->SetRow(row,"XXXXXXXXTEEFAX %%# %%a %d %%b \x3 %H:%M.%S"); // Could put in a sample header here
                  //             aaaaaaaaaabbbbbbbbbbccccccccccd  ddddddddd
                  line=p->GetRow(row);
              }
              row0=*line; // Copy the contents of line to row
              line=&row0;   // Now point line to row so we don't erase the original line
              GenerateHeader(line);
          }

          //std::cout << "Trace 4" << std::endl;
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
                      break;
                  case ttxCodeFlash :
                      break;
                  case ttxCodeSteady :
                      flashing=false;
                      break;
                  case ttxCodeEndBox :
                  case ttxCodeStartBox :
                      break;
                  case ttxCodeNormalHeight :
                      doubleHeight=false;
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
                  case ttxCodeSwitch : // Default <==> Second G0 switch
                      toggleG0Set = !toggleG0Set;
                      break;
                  case ttxCodeBlackBackground : // Background black
                      bg = ttxCodeAlphaBlack;
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
                      ch2=mapTextChar(ch2, toggleG0Set);
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
                      // If we send a new mosaic code while in hold, it replaces the current mosaic.
                      if (hold)
                      {
                          ch=holdChar;  // Carry on hold
                      }

                      for (int i=0;i<6;i++) // for each of the six pixels in this character
                      {
                          bool pixelSet=(ch & j) && (m_blinkToggle || !flashing);

                          j<<=1;
                          if (j==0x20) j<<=1; // Skip the alphabet exception

                          // Draw the full sized pixel in background colour
                          SetTTXBrushColour(bg, false);
                          //paintDC.SetBrush(wxBrush(*ttxCode2wxColour(bg)));
                          //doubleHeightDC.SetBrush(wxBrush(*ttxCode2wxColour(bg)));
                          int k=1; // Full size pixel
                          if (doubleHeight)
                          {
                              doubleHeightDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                                               (i/2)*m_ttxH/3)+offset,
                                                wxSize(k+m_ttxW/2,k+m_ttxH/3));
                          }
                          else
                          {
                              paintDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                          row*m_ttxH+(i/2)*m_ttxH/3)+offset,
                                          wxSize(k+m_ttxW/2,k+m_ttxH/3));
                          }
                          // Now draw the actual pixel
                          if (pixelSet)
                          {
                              SetTTXBrushColour(fg, true);
                              // paintDC.SetBrush(wxBrush(*fg));
                              if (separated) k=-2; // Thin border around the pixel
                              if (doubleHeight)
                              {
                                  //doubleHeightDC.SetBrush(wxBrush(*fg));
                                  doubleHeightDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                                        (i/2)*m_ttxH/3)+offset,
                                                    wxSize(k+m_ttxW/2,k+m_ttxH/3));
                              }
                              else
                              {
                                  paintDC.DrawRectangle(wxPoint(col*m_ttxW + (i % 2)*m_ttxW/2,
                                                row*m_ttxH+(i/2)*m_ttxH/3)+offset,
                                                wxSize(k+m_ttxW/2,k+m_ttxH/3));
                              }
                          }
                      }

                  } // Graphic block
                  else
                  {
                      // Foreground colour
                      if (m_blinkToggle || !flashing)
                      {
                          // paintDC.SetTextForeground(*fg); // Normal
                          SetTTXForegroundColour(fg); // Normal
                          //doubleHeightDC.SetTextForeground(*fg); // Normal
                      }
                      else
                      {
                          //paintDC.SetTextForeground(*bg); // Blink off
                          SetTTXForegroundColour(bg); // Blink off
                          doubleHeightDC.SetTextForeground(bg); // blink off
                      }
                      // Background colour
                      SetTTXBackgroundColour(bg);
                      //doubleHeightDC.SetTextBackground(*bg);
                      //paintDC.SetTextBackground(*bg);

                      if (doubleHeight)
                      {
                          doubleHeightDC.DrawText(wxString(ch2), wxPoint(col*m_ttxW,0)); // No offset! The device context is not the main screen
                      }
                      else // Single height
                      {
                          paintDC.DrawText(wxString(ch2), wxPoint(col*m_ttxW, row*m_ttxH) + offset);
                          if (row<23)
                              paintDC.DrawText(_(" "),wxPoint(col*m_ttxW,(row+1)*m_ttxH)+offset); // Draw background in case this row contains a double height
                      }
                  }
                  if (doubleHeight)
                      paintDC.StretchBlit(wxPoint(col*m_ttxW,row*m_ttxH)+offset,wxSize(m_ttxW,m_ttxH*2), // dest
                                      &doubleHeightDC,
                                      wxPoint(col*m_ttxW,0),wxSize(m_ttxW,m_ttxH)); //src
                  // Set-after codes implemented here, also the show markup
                  paintDC.SetTextForeground(*wxWHITE);

                  paintDC.SetTextBackground(*wxLIGHT_GREY);
                  switch (str[col])
                  {
                  case ttxCodeAlphaBlack :
                      fg=ttxCodeAlphaBlack;
                      concealed=false;    // Side effect of colour. It cancels a conceal.
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);

                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaRed :
                      fg=ttxCodeAlphaRed;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);

                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaGreen :
                      fg=ttxCodeAlphaGreen;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaYellow :
                      fg=ttxCodeAlphaYellow;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaBlue :
                      fg=ttxCodeAlphaBlue;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaMagenta :
                      fg=ttxCodeAlphaMagenta;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaCyan :
                      fg=ttxCodeAlphaCyan;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeAlphaWhite :
                      fg=ttxCodeAlphaWhite;
                      concealed=false;
                      graphicsMode=false;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\x03B1'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // graphic sample
                      }
                      break;
                  case ttxCodeFlash :
                      flashing=true;
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEFC6'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // italic f
                      }
                      break;
                  case ttxCodeSteady :
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEFC9'), wxPoint(col*m_ttxW, row*m_ttxH) + offset); // italic i
                      }
                      break;
                  case ttxCodeEndBox :
                      // std::cout << "End Box not implemented" << std::endl;
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEF57'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // down arrow
                      }
                      break;
                  case ttxCodeStartBox :
                      // std::cout << "Start box not implemented" << std::endl;
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEF56'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // down arrow
                      }
                      break;
                  case ttxCodeNormalHeight : // Normal height
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEF5E'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // down arrow
                      }
                      break;
                  case ttxCodeDoubleHeight : // Double height
                      doubleHeight=true;
                      skipnextrow=true;   // ETSI: Don't use content from next row
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\xEF5D'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // up arrow
                      }
                     break;
                  case ttxCodeGraphicsBlack : // Graphics black
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaBlack;
                      if (addMarkup)
                      {
                        // paintDC.SetTextForeground(*fg);
                        SetTTXForegroundColour(fg);
                        paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsRed : // Graphics red
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaRed;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsGreen : // Graphics green
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaGreen;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsYellow : // Graphics yellow
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaYellow;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsBlue : // Graphics blue
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaBlue;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsMagenta : // Graphics magenta
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaMagenta;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsCyan : // Graphics cyan
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaCyan;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeGraphicsWhite : // Graphics white
                      concealed=false;
                      graphicsMode=true;
                      fg=ttxCodeAlphaWhite;
                      if (addMarkup)
                      {
                          // paintDC.SetTextForeground(*fg);
                          SetTTXForegroundColour(fg);
                          paintDC.DrawText(wxString(L'\xE6F6'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // Show a blob where a control code is
                      }
                      break;
                  case ttxCodeConcealDisplay : // Conceal display
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('?',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // question mark
                      }
                      break;
                  case ttxCodeContiguousGraphics : // Contiguous graphics
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('c',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // (c)ontiguous
                      }
                      break;
                  case ttxCodeSeparatedGraphics : // Separated gfx
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('s',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // (s)eparate
                      }
                      break;
                  case ttxCodeSwitch : // Go/G2 code toggle
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText(wxString(L'\x5dd'),wxPoint(col*m_ttxW,row*m_ttxH)+offset); // code switch Rectangle
                      }
                      break;
                  case ttxCodeBlackBackground : // Background black
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('b',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // b for black background
                      }
                      break;
                  case ttxCodeNewBackground : // New background
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('n',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // n for new background
                      }
                      break;

                  case ttxCodeHoldGraphics : // Hold gfx
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('h',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // (h)old
                      }
                      break;
                  case ttxCodeReleaseGraphics : // Separated gfx
                      hold=false;
                      if (addMarkup)
                      {
                          paintDC.SetTextForeground(*wxWHITE);
                          paintDC.DrawText('r',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // (r)elease
                      }
                      break;

                  default:;

  #if 0
                      // If this is a graphics cell, draw the cell outline
                      if (graphicsMode && addMarkup)
                      {
                          paintDC.SetPen(*wxGREY_PEN);
                          paintDC.SetPen(*wxBLUE_PEN);
                          paintDC.DrawLine(col*m_ttxW,row*m_ttxH,(col+1)*m_ttxW,(row+1)*m_ttxH);
                          //paintDC.DrawText('g',wxPoint(col*m_ttxW,row*m_ttxH)+offset); // (r)elease

                      }
  #endif
                  }//case

              } // each character on this row
              if (skipnextrow) row++; // Don't use next row if there was any double height

          } // row not null?
          /* else
              std::cout << "row is null " << row << std::endl; */
      } // For each text row
      offset.x+=m_ttxW*41; // The next subpage is drawn with a one character gap
    } // for each page that we can show
    delete magenta;
    // cursor

    if (m_blinkToggle==true)
    {
        wxPoint dx(m_ttxW*41*pageSet->CurrentPageIndex(),0); // The page offset
        dx+=m_offset; // Add the slide offset

        paintDC.SetPen(*wxBLACK_PEN); // outline on
        paintDC.SetBrush(wxBrush(*wxWHITE));
            // In the current page, get the line that the cursor is on, and test if it is double height
        bool doubleHeight;
        doubleHeight=pageSet->CurrentPage()->GetRow(m_cursorPoint.y)->IsDoubleHeight(m_cursorPoint.x); // @todo Extend to deal with double height transitions.
        if (m_cursorIsAlpha) // Alpha cursor
        {
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW,m_cursorPoint.y*m_ttxH)+dx,wxSize(m_ttxW,m_ttxH));
            if (doubleHeight)
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW,m_cursorPoint.y*m_ttxH)+dx,wxSize(m_ttxW,m_ttxH*2));
        }
        else // Graphics cursor
        {
            // Outline the whole character location, but 2 lines bigger.
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW-2,m_cursorPoint.y*m_ttxH-2)+dx, // left
                                      wxSize(2,m_ttxH+4));
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW-2,m_cursorPoint.y*m_ttxH-2)+dx, // top
                                      wxSize(m_ttxW+4,2));
            paintDC.DrawRectangle(wxPoint((m_cursorPoint.x+1)*m_ttxW,m_cursorPoint.y*m_ttxH-2)+dx, // right
                                      wxSize(2,m_ttxH+4));
            paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW-2,(m_cursorPoint.y+1)*m_ttxH)+dx, // bottom
                                      wxSize(m_ttxW+4,2));
            int halfw=m_ttxW/2;
            int thirdh=m_ttxH/3;
            if (doubleHeight)
            {
                thirdh*=2;
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW+m_subPixelPoint.x*halfw,
                                              m_cursorPoint.y*m_ttxH+m_subPixelPoint.y*thirdh)+dx,
                                      wxSize(halfw,thirdh));
            }
            else
                paintDC.DrawRectangle(wxPoint(m_cursorPoint.x*m_ttxW+m_subPixelPoint.x*halfw,
                                              m_cursorPoint.y*m_ttxH+m_subPixelPoint.y*thirdh)+dx,
                                      wxSize(halfw,thirdh));

        }
        paintDC.SetPen(*wxTRANSPARENT_PEN);
    } // cursor

    m_SetStatus();

    // Marquee.
    // TODO: Make the marquee and cursor mutually exclusive
    wxPen pen(*wxWHITE,1,wxPENSTYLE_SHORT_DASH);
    paintDC.SetBrush(*wxTRANSPARENT_BRUSH); // no fill

    paintDC.SetPen(pen); // outline on
    {
      wxPoint loc(m_MarqueeStart);
      wxSize siz(m_MarqueeEnd.x-loc.x, m_MarqueeEnd.y-loc.y);

      loc.x*=m_ttxW;
      loc.y*=m_ttxH;
      siz.x*=m_ttxW;
      siz.y*=m_ttxH;

      // Draw a box TODO: Marquee crawling ants
      paintDC.DrawRectangle(m_offset+loc+wxSize(pageSet->CurrentPageIndex()*m_ttxW*41,0), siz);
    }

    // Outline the current frame around the current page
    paintDC.SetPen(*wxWHITE_PEN); // outline on
    wxSize sz(static_cast<int>(m_ttxW*40.5), m_ttxH*25);
    wxPoint loc(m_offset.x+pageSet->CurrentPageIndex()*m_ttxW*41,0);
    paintDC.DrawRectangle(loc,sz);
    // std::cout << "[OnPaint] exits " << std::endl;
} // OnPaint

wchar_t wxTEDFrame::mapTextChar(wchar_t ch, bool primary)
{
  return MapChar(ch, pageSet->CurrentPage()->GetLanguage(primary), pageSet->CurrentPage()->GetRegion(primary));
}

void wxTEDFrame::m_SetStatus()
{
    std::ostringstream str;
    std::ostringstream s;

    std::ostringstream code;
    wchar_t ch;
    wxPoint c=m_cursorPoint;
    wxPoint d=m_subPixelPoint;

    if (m_inhibitStatus)
    {
      return;
    }

    TTXLine* line=pageSet->CurrentPage()->GetRow(c.y);
    if (pageSet->GetPage(0)->GetPageChanged())
      str << "* ";
    str << "P" << pageSet->CurrentPageIndex()+1 << "/" << pageSet->GetPageCount() << ", ";
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
            case ttxCodeGraphicsBlack: code<<"Graphics White=Ctrl-F8";break;
            case ttxCodeConcealDisplay: code<<"Conceal=Shift W (F11 toggle)";break;
            case ttxCodeContiguousGraphics: code<<"Contiguous graphics=Ctrl-D";break;
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
    if (pageSet->CurrentPage()->IsAlphaMode(m_cursorPoint))
    {
        if (ch>' ')
        {
            ch=mapTextChar(ch, true);
            //std::string s2=ch;
            //s2[0]=ch;
            code<<(char)ch;
        }
        str << "(" << c.x << "," << c.y <<") char=" << code.str(); // Alpha
    }
    else
        str << "(" << c.x << "." << d.x << "," << c.y << "." << d.y <<") " << code.str(); // Graphics
    if (m_escapeMode) // Confirm to the user that they pressed Escape
    {
      str << " Escape...";
    }
    StatusBar1->SetLabelText(str.str());
}

wxTEDFrame::wxTEDFrame(wxWindow* parent, wxWindowID id, wxString initialPage)
    : m_escapeMode(false)
    , m_controlModifier(false)
    , m_menuCount(0)
    , m_inhibitStatus(false)
    , m_ShowMarkup(false)
    , m_Released(true)
    , m_ttxW(15)
    , m_ttxH(20)
    , m_subPixelPoint(wxPoint(0,0))
    , m_cursorIsAlpha(true)
    , m_dragging(false)
    , m_MarqueeStart(wxPoint(0,0))
    , m_offset(wxPoint(0,0))
    , m_slideOrigin(wxPoint(0,0))
    , m_slidePages(false)
    , m_focused(true)
    , m_propertiesDlg(new PageSettingsDialog(this,1000))
    , m_config(new wxConfig("wxTED"))

{
  pageSet = std::make_unique<TTXPageSet>();
  pageSet->debug("one");
    m_parentWindow=parent;
    m_blinkToggle=false;

    m_reveal=true; // As this is an editor, reveal the text by default.

    //(*Initialize(wxTEDFrame)
    wxMenu* Menu1;
    wxMenu* MenuHelp;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItemAbout;
    wxMenuItem* MenuItemQuit;

    Create(parent, wxID_ANY, _("wxTED Teletext Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(-1,-1));
    Move(wxPoint(-1,-1));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    Hide();
    SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
    wxFont thisFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("teletext2"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(1,1), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(-1,-1));
    Panel1->SetFocus();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idNewPage, _("New\tCTRL-N"), _("Create a new page"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItemTemplate = new wxMenuItem(Menu1, idNewFromTemplate, _("New from template"), _("New page set up for graphics"), wxITEM_NORMAL);
    Menu1->Append(MenuItemTemplate);
    MenuItem3 = new wxMenuItem(Menu1, idOpenPage, _("Open\tCTRL-O"), _("Open a teletext page"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItemSave = new wxMenuItem(Menu1, idSavePage, _("Save\tCTRL-S"), _("Save a teletext page"), wxITEM_NORMAL);
    Menu1->Append(MenuItemSave);
    MenuItemSaveAs = new wxMenuItem(Menu1, isSavePageAs, _("Save as"), _("Save a teletext page with a different name"), wxITEM_NORMAL);
    Menu1->Append(MenuItemSaveAs);
    Menu1->AppendSeparator();
    MenuItemExportTTX40 = new wxMenuItem(Menu1, idExportTTX40, _("Export edit.tf"), _("Open page on edit.tf website"), wxITEM_NORMAL);
    Menu1->Append(MenuItemExportTTX40);
    MenuExportZxnet = new wxMenuItem(Menu1, isExportZxnet, _("Export ZxNet"), _("Edit page in ZxNet"), wxITEM_NORMAL);
    Menu1->Append(MenuExportZxnet);
    MenuItemQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItemQuit);
    Menu1->AppendSeparator();
    MenuItem4 = new wxMenuItem(Menu1, idNewWindow, _("New Window"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItemUndo = new wxMenuItem(Menu3, idUndo, _("Undo\tCTRL-Z"), _("Undo the last edit"), wxITEM_NORMAL);
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
    MenuInsertLine = new wxMenuItem(Menu3, isInsertLine, _("Insert line"), _("Insert a line below"), wxITEM_NORMAL);
    Menu3->Append(MenuInsertLine);
    MenuDeleteLine = new wxMenuItem(Menu3, isDeleteLine, _("Delete line"), _("Delete the current line"), wxITEM_NORMAL);
    Menu3->Append(MenuDeleteLine);
    Menu3->AppendSeparator();
    MenuItemInsertSubpage = new wxMenuItem(Menu3, idInsertPage, _("Insert subpage after this one"), _("Add a subpage after this page"), wxITEM_NORMAL);
    Menu3->Append(MenuItemInsertSubpage);
    MenuItemDeletePage = new wxMenuItem(Menu3, idDeleteSubPage, _("Delete this subpage"), _("Delete subpage from this carousel"), wxITEM_NORMAL);
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
    MenuItemPageNumber = new wxMenuItem(MenuPresentation, idPageNumber, _("Properties..."), _("Set the page number for transmission"), wxITEM_NORMAL);
    MenuPresentation->Append(MenuItemPageNumber);
    MenuItemShowHeader = new wxMenuItem(MenuPresentation, ID_MENUITEMSHOWHEADER, _("Show header"), _("Show/hide header row"), wxITEM_CHECK);
    MenuPresentation->Append(MenuItemShowHeader);
    MenuItemShowHeader->Check(true);
    MenuItemShowCodes = new wxMenuItem(MenuPresentation, ID_SHOWCONTROL, _("Show control codes"), _("Show invisible codes"), wxITEM_CHECK);
    MenuPresentation->Append(MenuItemShowCodes);
    MenuItemConcealToggle = new wxMenuItem(MenuPresentation, ID_HIDECONCEAL, _("Toggle Conceal"), _("Conceal/show hidden text"), wxITEM_NORMAL);
    MenuPresentation->Append(MenuItemConcealToggle);
    MenuPresentation->AppendSeparator();
    MenuItem5 = new wxMenu();
    MenuMainLanguage = new wxMenu();
    MenuItemEnglishX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage0, _("English"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemEnglishX28);
    MenuItemFrenchX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage1, _("French"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemFrenchX28);
    MenuItemSwedishX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage2, _("Swedish/Finnish/Hungarian"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemSwedishX28);
    MenuItemCzechX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage3, _("Czech/Slovak"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemCzechX28);
    MenuItemGermanX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage4, _("German"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemGermanX28);
    MenuItemSpanishX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage5, _("Spanish/Portuguese"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemSpanishX28);
    MenuItemItalianX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage6, _("Italian"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemItalianX28);
    MenuItemUnusedX28 = new wxMenuItem(MenuMainLanguage, idMainLanguage7, _("Unused"), wxEmptyString, wxITEM_RADIO);
    MenuMainLanguage->Append(MenuItemUnusedX28);
    MenuItemUnusedX28->Enable(false);
    MenuItem5->Append(ID_MAINLANGUAGE, _("Main language"), MenuMainLanguage, wxEmptyString);
    MenuMainRegion = new wxMenu();
    MenuItemRegion0 = new wxMenuItem(MenuMainRegion, ID_REGION0, _("0: Eng/Ger/Swe/Fin/Hun/Ita/Fre/Por/Spa/Cze/Slo"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion0);
    MenuItemRegion1 = new wxMenuItem(MenuMainRegion, ID_REGION1, _("1: Pol/Ger/Swe/Fin/Hun/Ita/Fre/Cze/Slo"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion1);
    MenuItemRegion2 = new wxMenuItem(MenuMainRegion, ID_REGION2, _("2: Eng/Fre/Swe-Fin-Hun/Tur/Ger/Por-Spa/Ita"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion2);
    MenuItemRegion3 = new wxMenuItem(MenuMainRegion, ID_REGION3, _("3: Ser/Cro/Slovenian/Romanian"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion3);
    MenuItemRegion4 = new wxMenuItem(MenuMainRegion, ID_REGION4, _("4: Ser-Cro/Ger/Est/Lit/Rus-Bul/Ukr/Cze-Slo"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion4);
    MenuItemRegion6 = new wxMenuItem(MenuMainRegion, ID_REGION6, _("6: Tur/Gre"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion6);
    MenuItemRegion8 = new wxMenuItem(MenuMainRegion, ID_REGION8, _("8: Eng/Fre/Arabic"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion8);
    MenuItemRegion10 = new wxMenuItem(MenuMainRegion, ID_REGION10, _("10: Hebrew/Arabic"), _("Language group"), wxITEM_RADIO);
    MenuMainRegion->Append(MenuItemRegion10);
    MenuItem5->Append(ID_MENUMAINREGION, _("Main region"), MenuMainRegion, wxEmptyString);
    MenuSecondLanguage = new wxMenu();
    MenuItem2ndLang0 = new wxMenuItem(MenuSecondLanguage, idSecondLanguage0, _("English"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang0);
    MenuItem2ndLang1 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM2, _("French"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang1);
    MenuItem2ndLang2 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM3, _("Swedish"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang2);
    MenuItem2ndLang3 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM4, _("Czech"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang3);
    MenuItem2ndLang4 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM5, _("German"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang4);
    MenuItem2ndLang5 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM6, _("Spanish"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang5);
    MenuItem2ndLang6 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM7, _("Italian"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang6);
    MenuItem2ndLang7 = new wxMenuItem(MenuSecondLanguage, ID_MENUITEM8, _("Unused"), wxEmptyString, wxITEM_RADIO);
    MenuSecondLanguage->Append(MenuItem2ndLang7);
    MenuItem2ndLang7->Enable(false);
    MenuItem5->Append(ID_SECOND_REGION, _("Second language"), MenuSecondLanguage, wxEmptyString);
    MenuSecondRegion = new wxMenu();
    MenuItemRegionB0 = new wxMenuItem(MenuSecondRegion, ID_REGION2R0, _("0: Eng/Ger/Swe/Fin/Hun/Ita/Fre/Por/Spa/Cze/Slo"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB0);
    MenuItemRegionB1 = new wxMenuItem(MenuSecondRegion, ID_REGION2R1, _("1: Pol/Ger/Swe/Fin/Hun/Ita/Fre/Cze/Slo"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB1);
    MenuItemRegionB2 = new wxMenuItem(MenuSecondRegion, ID_REGION2R2, _("2: Eng/Fre/Swe-Fin-Hun/Tur/Ger/Por-Spa/Ita"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB2);
    MenuItemRegionB3 = new wxMenuItem(MenuSecondRegion, ID_REGION2R3, _("3: Ser/Cro/Slovenian/Romanian"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB3);
    MenuItemRegionB4 = new wxMenuItem(MenuSecondRegion, ID_REGION2R4, _("4: Ser-Cro/Ger/Est/Lit/Rus-Bul/Ukr/Cze-Slo"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB4);
    MenuItemRegionB6 = new wxMenuItem(MenuSecondRegion, ID_REGION2R6, _("6: Tur/Gre"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB6);
    MenuItemRegionB8 = new wxMenuItem(MenuSecondRegion, ID_REGION2R8, _("8: Eng/Fre/Arabic"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB8);
    MenuItemRegionB10 = new wxMenuItem(MenuSecondRegion, ID_REGION2R10, _("10: Hebrew/Arabic"), wxEmptyString, wxITEM_RADIO);
    MenuSecondRegion->Append(MenuItemRegionB10);
    MenuItem5->Append(ID_MENUSECONDREGION, _("Second region"), MenuSecondRegion, wxEmptyString);
    MenuItemPalette = new wxMenuItem(MenuItem5, ID_PALETTE, _("Palette..."), _("Colours"), wxITEM_NORMAL);
    MenuItem5->Append(MenuItemPalette);
    MenuPresentation->Append(x28enhance, _("X28 enhancements"), MenuItem5, wxEmptyString);
    MenuBar1->Append(MenuPresentation, _("Presentation"));
    MenuCarousel = new wxMenu();
    PreviewRun = new wxMenuItem(MenuCarousel, idRun, _("Run"), wxEmptyString, wxITEM_NORMAL);
    MenuCarousel->Append(PreviewRun);
    MenuCarousel->AppendSeparator();
    ModeLoop = new wxMenuItem(MenuCarousel, idRadioMode, _("Loop"), wxEmptyString, wxITEM_RADIO);
    MenuCarousel->Append(ModeLoop);
    ModeBounce = new wxMenuItem(MenuCarousel, idRadioBounce, _("Bounce"), _("Bounce animation"), wxITEM_RADIO);
    MenuCarousel->Append(ModeBounce);
    MenuCarousel->AppendSeparator();
    PreviewNormal = new wxMenuItem(MenuCarousel, idRadioMode0, _("Normal"), _("Normal carousel timing"), wxITEM_RADIO);
    MenuCarousel->Append(PreviewNormal);
    Preview30fps = new wxMenuItem(MenuCarousel, idRadioMode1, _("30 fps"), _("Frame rate"), wxITEM_RADIO);
    MenuCarousel->Append(Preview30fps);
    Preview25fps = new wxMenuItem(MenuCarousel, idRadioMode2, _("25 fps"), wxEmptyString, wxITEM_RADIO);
    MenuCarousel->Append(Preview25fps);
    Preview12fps = new wxMenuItem(MenuCarousel, idRadioMode3, _("12 fps"), wxEmptyString, wxITEM_RADIO);
    MenuCarousel->Append(Preview12fps);
    Preview6fps = new wxMenuItem(MenuCarousel, idRadioMode4, _("6 fps"), wxEmptyString, wxITEM_RADIO);
    MenuCarousel->Append(Preview6fps);
    Preview2fps = new wxMenuItem(MenuCarousel, idRadioMode5, _("2 fps"), wxEmptyString, wxITEM_RADIO);
    MenuCarousel->Append(Preview2fps);
    MenuBar1->Append(MenuCarousel, _("Carousel"));
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
    LoadPageFileDialog = new wxFileDialog(this, _("Select teletext file"), wxEmptyString, wxEmptyString, _("TTI files (*.tti, *.ttix)|*.tti;*.ttix|EP1 files (*.ep1)|*.ep1|TTX files (*.ttx)|*.ttx|VTP files (*.vtp)|*.vtp|VTX files (*.vtx)|*.vtx|All files|*.*"), wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    m_Timer1.SetOwner(this, ID_TIMER1);
    m_Timer1.Start(456, false);
    FileDialogSaveAs = new wxFileDialog(this, _("Save file as..."), wxEmptyString, wxEmptyString, _("TTI files (*.tti, *.ttix)|*.tti;*.ttix"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Panel1->Connect(wxEVT_ERASE_BACKGROUND, (wxObjectEventFunction)&wxTEDFrame::OnEraseBackground, NULL, this);
    Panel1->Connect(wxEVT_KEY_DOWN, (wxObjectEventFunction)&wxTEDFrame::OnKeyDown, NULL, this);
    Panel1->Connect(wxEVT_KEY_UP, (wxObjectEventFunction)&wxTEDFrame::OnKeyUp, NULL, this);
    Panel1->Connect(wxEVT_CHAR, (wxObjectEventFunction)&wxTEDFrame::OnChar, NULL, this);
    Panel1->Connect(wxEVT_SET_FOCUS, (wxObjectEventFunction)&wxTEDFrame::OnSetFocus, NULL, this);
    Panel1->Connect(wxEVT_KILL_FOCUS, (wxObjectEventFunction)&wxTEDFrame::OnKillFocus, NULL, this);
    Panel1->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&wxTEDFrame::OnLeftDown, NULL, this);
    Panel1->Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&wxTEDFrame::OnLeftUp, NULL, this);
    Panel1->Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&wxTEDFrame::OnRightDown, NULL, this);
    Panel1->Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&wxTEDFrame::OnRightUp, NULL, this);
    Panel1->Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&wxTEDFrame::OnMouseWheel, NULL, this);
    Connect(idNewPage, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuNew);
    Connect(idNewFromTemplate, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuNewFromTemplate);
    Connect(idOpenPage, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuOpenPage);
    Connect(idSavePage, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnSave);
    Connect(isSavePageAs, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuSaveAs);
    Connect(idExportTTX40, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemExportTTX40Selected);
    Connect(isExportZxnet, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemZXNetSelected);
    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnQuit);
    Connect(idNewWindow, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemNewWindow);
    Connect(idUndo, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCut, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemUndo);
    Connect(idCopy, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemCopySelected);
    Connect(idPaste, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemPasteSelected);
    Connect(idSelectAll, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemSelectAllSelected);
    Connect(isInsertLine, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuInsertLineSelected);
    Connect(isDeleteLine, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuDeleteLineSelected);
    Connect(idInsertPage, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemInsertSubpage);
    Connect(idDeleteSubPage, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemDeletePage);
    Connect(idLanguageEnglish, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageFrench, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSwedish, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageCzechSlovak, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageGerman, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageSpanish, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageItalian, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idLanguageUnused, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguage);
    Connect(idPageNumber, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemProperties);
    Connect(ID_SHOWCONTROL, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemShowCodesSelected);
    Connect(ID_HIDECONCEAL, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemConcealToggle);
    Connect(idMainLanguage0, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage5, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage6, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(idMainLanguage7, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageX28);
    Connect(ID_REGION0, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION6, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION8, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(ID_REGION10, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionSelected);
    Connect(idSecondLanguage0, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM5, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM6, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM7, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_MENUITEM8, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemLanguageB);
    Connect(ID_REGION2R0, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R6, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R8, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_REGION2R10, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemRegionBSelected);
    Connect(ID_PALETTE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuItemPaletteSelected);
    Connect(idRun, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewRunSelected);
    Connect(idRadioMode, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioBounce, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioMode0, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewNormalSelected);
    Connect(idRadioMode1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioMode2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioMode3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioMode4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idRadioMode5, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnPreviewSpeed);
    Connect(idSpecialKeys, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnMenuSpecialKeys);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxTEDFrame::OnAbout);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&wxTEDFrame::OnClose);
    Connect(wxEVT_PAINT, (wxObjectEventFunction)&wxTEDFrame::OnPaint);
    Connect(wxEVT_ERASE_BACKGROUND, (wxObjectEventFunction)&wxTEDFrame::OnEraseBackground);
    Connect(wxEVT_SET_FOCUS, (wxObjectEventFunction)&wxTEDFrame::OnSetFocus);
    Connect(wxEVT_KILL_FOCUS, (wxObjectEventFunction)&wxTEDFrame::OnKillFocus);
    Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&wxTEDFrame::OnLeftUp);
    Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&wxTEDFrame::OnMouseWheel);
    Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&wxTEDFrame::OnRightDown);
    Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&wxTEDFrame::OnRightUp);
    Connect(wxEVT_MOTION, (wxObjectEventFunction)&wxTEDFrame::OnMouseMove);
    Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&wxTEDFrame::OnMouseWheel);
    //*)

    MenuBar = MenuBar1; // @todo [!] This is a risk as Menubar1 has no guarantee of existing outside of this constructor
    // Presumably it it stored somewhere on a wxWidgets structure that we can traverse?
    PrimaryLanguage[0] = MenuItemEnglish;
    PrimaryLanguage[1] = MenuItemFrench;
    PrimaryLanguage[2] = MenuItemSwedish;
    PrimaryLanguage[3] = MenuItemCzech;
    PrimaryLanguage[4] = MenuItemGerman;
    PrimaryLanguage[5] = MenuItemSpanish;
    PrimaryLanguage[6] = MenuItemItalian;
    PrimaryLanguage[7] = MenuItemUnused;

    PrimaryLanguageX28[0] = MenuItemEnglishX28;
    PrimaryLanguageX28[1] = MenuItemFrenchX28;
    PrimaryLanguageX28[2] = MenuItemSwedishX28;
    PrimaryLanguageX28[3] = MenuItemCzechX28;
    PrimaryLanguageX28[4] = MenuItemGermanX28;
    PrimaryLanguageX28[5] = MenuItemSpanishX28;
    PrimaryLanguageX28[6] = MenuItemItalianX28;
    PrimaryLanguageX28[7] = MenuItemUnusedX28;

    SecondLanguage[0] = MenuItem2ndLang0;
    SecondLanguage[1] = MenuItem2ndLang1;
    SecondLanguage[2] = MenuItem2ndLang2;
    SecondLanguage[3] = MenuItem2ndLang3;
    SecondLanguage[4] = MenuItem2ndLang4;
    SecondLanguage[5] = MenuItem2ndLang5;
    SecondLanguage[6] = MenuItem2ndLang6;
    SecondLanguage[7] = MenuItem2ndLang7;

    PrimaryRegion[0] = MenuItemRegion0;
    PrimaryRegion[1] = MenuItemRegion1;
    PrimaryRegion[2] = MenuItemRegion2;
    PrimaryRegion[3] = MenuItemRegion3;
    PrimaryRegion[4] = MenuItemRegion4;
    PrimaryRegion[5] = MenuItemRegion6;
    PrimaryRegion[6] = MenuItemRegion8;
    PrimaryRegion[7] = MenuItemRegion10;

    SecondRegion[0] = MenuItemRegionB0;
    SecondRegion[1] = MenuItemRegionB1;
    SecondRegion[2] = MenuItemRegionB2;
    SecondRegion[3] = MenuItemRegionB3;
    SecondRegion[4] = MenuItemRegionB4;
    SecondRegion[5] = MenuItemRegionB6;
    SecondRegion[6] = MenuItemRegionB8;
    SecondRegion[7] = MenuItemRegionB10;

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
    pageSet = std::make_unique<TTXPageSet>(initialPage.ToStdString(),"");
    m_setLanguage(true);

    std::cerr  << "[wxTEDFrame::wxTEDFrame]initialPage=" << initialPage << std::endl;

    if (initialPage=="wxtedsplash.tti") // Started with default page
    {
      SetTitle(_("wxTED ")+VERSION_STRING);
      pageSet->SetSourcePage(""); // Prevent an accidental Save of the default page
    }
    else
    {
      // Typically when a page file is double clicked.
      //MenuItemSave->Enable(true);
      EnableSave(true);
      SetTitle(initialPage.ToStdString());
    }

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    m_cursorPoint=wxPoint(0,1);

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

    SetRegionMenu(pageSet->CurrentPage()->GetRegion(true), true); // Region language [!] @todo Add second language but probably on an X28 config dialog


// wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    wxPoint wxP;
    wxP.x=50;
    wxP.y=50;
    wxSize wxS;
    wxS.SetWidth(200);
    wxS.SetHeight(600);


    helpFrame=new HelpFrame(this->GetDefaultItem(),1,wxP,wxS);


    paletteFrame = new PaletteFrame(this->GetDefaultItem(), 1, wxPoint(100,100), wxSize(500, 200));

    pageSet->GetPage(0)->SetPageChanged(false);

    // Compatibility.
    // Windows: Panel1 must be hidden or it makes an ugly rectangle on the screen
    // Linux: Panel1 must not be hidden as keyboard events will not be captured
#ifdef __WXMSW__
    Panel1->Hide();
#endif
    // std::cout << "Finished starting frame" << std::endl;
}

wxTEDFrame::~wxTEDFrame()
{
    delete helpFrame;
    delete paletteFrame;
    delete m_config;
    //(*Destroy(wxTEDFrame)
    LoadPageFileDialog->Destroy();
    FileDialogSaveAs->Destroy();
    //*)
}

void wxTEDFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxTEDFrame::OnSave(wxCommandEvent& event)
{
  if (m_escapeMode) // edit.tf escape?
  {
    // Special hack. esc ctrl-s writes an ESC character. (Toggle G0 G2 language)
    std::cout << "[OnSave] swap G0 g2 " << std::endl;
    pageSet->CurrentPage()->SetCharAt(WXK_ESCAPE, 0, m_cursorPoint, m_subPixelPoint, MenuItemShowHeader->IsChecked());
    m_escapeMode = false;
  }
  else
  {
    bool result=pageSet->SavePageDefault(); // Write the file back where it came from
    if (!result)
    {
        wxString msg="File NOT saved.\nUse Save As and choose a new name";
        wxMessageBox(msg, _("Error"));
    }
  }
}

void wxTEDFrame::OnMenuSaveAs(wxCommandEvent& event)
{
    // std::clog << "[OnMenuSaveAs] enters" << std::endl;
    wxFileDialog
      saveFileDialog(this,
                      _("Save file as..."),
                        m_path, wxEmptyString,
                       _("TTI files (*.tti, *.ttix)|*.tti;*.ttix"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    auto dialog_result = saveFileDialog.ShowModal();

    if (dialog_result == wxID_CANCEL)
    {
        return;     // the user bottled out
    }
    std::string str=saveFileDialog.GetPath().ToStdString();
    // std::cout << "Saving page to " << str << std::endl;
    bool result=pageSet->SavePage(str);
    if (!result)
    {
        wxString msg="File NOT saved.\nUse Save As and choose a new name";
        wxMessageBox(msg, _("Error"));
    }
    else // Set the filename
    {
        wxString filename=saveFileDialog.GetFilename();
        pageSet->SetSourcePage(str);
        pageSet->SetShortFilename(filename.ToStdString());
        SetTitle(str);
        // MenuItemSave->Enable(true);
        EnableSave(true);
    }

}

void wxTEDFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg="Teletext editor\n(c) 2014-2025, Peter Kwan.\nwxTED";
    wxMessageBox(msg, _("Welcome to wxTED ")+VERSION_STRING);
}

void wxTEDFrame::OnMenuNew(wxCommandEvent& event)
{
  if ( pageSet->GetPage(0)->GetPageChanged() )
  {
    if ( wxMessageBox("Wipe everything and start a new page?",
                      "Please confirm",
                      wxICON_WARNING | wxCANCEL | wxCANCEL_DEFAULT) == wxCANCEL )
    {
      return;
    }
  }

  // std::cout << "New page" << std::endl;
  // @todo - If the page has changed and not been saved, trap that here
  pageSet = std::make_unique<TTXPageSet>(); // Assigning a new TTXPageSet destroys the old one
  SetTitle(_("wxTED ")+VERSION_STRING);
  pageSet->SetSourcePage(""); // Prevent an accidental Save of the default page
  m_setLanguage(true);
  SetRegionMenu(0, true);
  ShowCarouselMenu();
}

void wxTEDFrame::OnMenuItemPublish(wxCommandEvent& event)
{
#ifdef __WXMSW_DISABLED__
    // If the page has no filename, we can not save it. Do Save As or load another page.
    // We probably alao want to prevent Publishing a page with unsaved work in it. TODO.
    wxString sp=pageSet->GetPage(0)->GetSourcePage();
    wxString spShort=pageSet->GetPage(0)->GetShortFilename();
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
#endif // __WXMSW__
#ifdef __UNIX__
        wxString msg="Publish to FTP not implemented for UNIX";
        wxMessageBox(msg, _("Page not sent"));
#endif // __UNIX__endif
}

void wxTEDFrame::OnMenuItemUndo(wxCommandEvent& event)
{
    // TODO: Grey out this option when there is nothing to undo.
    pageSet->CurrentPage()->Undo(m_cursorPoint);
}

void wxTEDFrame::OnKillFocus(wxFocusEvent& event)
{
    //std::cout << "Lost focus" << std::endl;
    m_focused=false;
    event.Skip(true); // allow default handling
}

void wxTEDFrame::OnSetFocus(wxFocusEvent& event)
{
  std::cout << "Got focus" << std::endl;;
  m_focused=true;
  event.Skip(true); // allow default handling
}

void wxTEDFrame::OnMenuOpen(wxMenuEvent& event)
{
  m_menuCount++;
  if (!m_escapeMode)
  {
    std::cout << "Menu open" << std::endl;
    // @todo Add something to show the menu hint for a reasonable time
    m_inhibitStatus=true;
  }
  event.Skip();
}

void wxTEDFrame::OnMenuClose(wxMenuEvent& event)
{
  m_menuCount--;
  if (!m_escapeMode)
  {
    std::cout << "Menu close" << std::endl;
    // Don't enable status again until all menus are closed.
    if (!m_menuCount)
    {
      m_inhibitStatus=false;
    }
    // If we are in preview mode, we just changed a setting, so run the handler to update everything
    if (m_previewCarouselMode)
    {
      std::cout << "Refresh preview settings" << std::endl;
      UpdatePreview();
    }
  }
  event.Skip();
}

void OnMenuOpen(wxPaintEvent& event); // On opening the menu

void wxTEDFrame::OnMenuItemInsertSubpage(wxCommandEvent& event)
{
  pageSet->InsertPageAfter();
  // TODO Reposition the page offset
  ShowCarouselMenu();
}

void wxTEDFrame::OnMenuItemDeletePage(wxCommandEvent& event)
{
  pageSet->DeletePage();
  ShowCarouselMenu();
}

void wxTEDFrame::OnMenuItemLanguage(wxCommandEvent& event)
{
  int language = (event.GetId() - MenuItemEnglish->GetId()) & 0x07;
  pageSet->CurrentPage()->SetLanguage(language, true);
  // Update the X28 checked item
  PrimaryLanguageX28[language]->Check(true);
  std::cout << "Language handler " << pageSet->CurrentPage()->GetLanguage(true) << std::endl;
}

void wxTEDFrame::OnMenuItemLanguageX28(wxCommandEvent& event)
{
  int language = (event.GetId()- MenuItemEnglishX28->GetId()) & 0x07;
  pageSet->CurrentPage()->SetLanguage(language, true);
  // Update the original language checked item
  PrimaryLanguage[language]->Check(true);
  std::cout << "Language handler " << pageSet->CurrentPage()->GetLanguage(true) << std::endl;
}


void wxTEDFrame::OnMenuItemLanguageB(wxCommandEvent& event)
{
    int language = (event.GetId() - MenuItem2ndLang0->GetId()) & 0x07;
    pageSet->CurrentPage()->SetLanguage(language, false);
    std::cout << "Language handler " << pageSet->CurrentPage()->GetLanguage(false) << std::endl;
}

void wxTEDFrame::m_setLanguage(bool UsePrimary)
{
//    std::cout << "m_setLanguage " << pageSet->GetPage(0)->GetLanguage() << std::endl;
  int language=pageSet->CurrentPage()->GetLanguage(UsePrimary);
  wxMenuItem** languages = UsePrimary ? PrimaryLanguage : SecondLanguage;
  languages[language]->Check(true);
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
    /*
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
    */
}

void wxTEDFrame::OnMenuItemProperties(wxCommandEvent& event)
{
    // Copy dialog values from page
    std::ostringstream value("");

    // Page Number
    value << std::hex << pageSet->GetPageNumber();    // Get Page Number formatted as a hex string
    wxString s = wxString(value.str());
    m_propertiesDlg->TextCtrlPageNumber->SetValue(s); // And put it in the dialog

    // Description (per page set)
    m_propertiesDlg->TextCtrlDescription->SetValue(wxString(pageSet->GetDescription()));
    // Page Status flags (per subpage)
    int ps=pageSet->CurrentPage()->GetPageStatus();
    m_propertiesDlg->CheckBoxC4ErasePage ->SetValue((ps & PAGESTATUS_C4_ERASEPAGE)  >0);
    m_propertiesDlg->CheckBoxC5Newsflash ->SetValue((ps & PAGESTATUS_C5_NEWSFLASH)  >0);
    m_propertiesDlg->CheckBoxC6Subtitle  ->SetValue((ps & PAGESTATUS_C6_SUBTITLE)   >0);
    m_propertiesDlg->CheckBoxC7SuppressHeader->SetValue((ps & PAGESTATUS_C7_SUPPRESSHDR)>0);
    m_propertiesDlg->CheckBoxC8Update    ->SetValue((ps & PAGESTATUS_C8_UPDATE     )>0);
    m_propertiesDlg->CheckBoxTransmitPage->SetValue((ps & PAGESTATUS_TRANSMITPAGE)  >0);
    // Counter/Timer
    value.str("");

    // per subpage
    value << std::dec << pageSet->CurrentPage()->GetCycleTime();    // The cycle count / time (seconds)
    s = wxString(value.str());
    m_propertiesDlg->TextCtrlCycleTime->SetValue(s); // And put it in the dialog

    char mode=pageSet->CurrentPage()->GetCycleTimeMode();
    if (mode=='C')
        m_propertiesDlg->RadioBoxCycleMode->SetSelection(0);
    else
        m_propertiesDlg->RadioBoxCycleMode->SetSelection(1);

    // FASTEXT Link
    value.str("");
    value << std::hex << pageSet->CurrentPage()->GetFastextLink(0);
    m_propertiesDlg->TextCtrlFastext1->SetValue(value.str());
    value.str("");
    value << std::hex << pageSet->CurrentPage()->GetFastextLink(1);
    m_propertiesDlg->TextCtrlFastext2->SetValue(value.str());
    value.str("");
    value << std::hex << pageSet->CurrentPage()->GetFastextLink(2);
    m_propertiesDlg->TextCtrlFastext3->SetValue(value.str());
    value.str("");
    value << std::hex << pageSet->CurrentPage()->GetFastextLink(3);
    m_propertiesDlg->TextCtrlFastext4->SetValue(value.str());

    // FASTEXT Index
    value.str("");
    value << std::hex << pageSet->CurrentPage()->GetFastextLink(5);
    m_propertiesDlg->TextCtrlFastextIndex->SetValue(value.str());

    // Properties are now populated. Now show the dialog

    int result=m_propertiesDlg->ShowModal();

    if (result==wxID_CANCEL)
    {
        return;
    }


    // Extract the parameters from the dialog and put them back in the loaded page

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
        pageSet->SetPageNumber(pageNum);
        //std::cout << "Page number=" << std::hex << pageNum << std::endl;

        // Page Status
        b=m_propertiesDlg->CheckBoxC4ErasePage     ->GetValue();    if (b) ps|=PAGESTATUS_C4_ERASEPAGE;
        b=m_propertiesDlg->CheckBoxC5Newsflash     ->GetValue();    if (b) ps|=PAGESTATUS_C5_NEWSFLASH;
        b=m_propertiesDlg->CheckBoxC6Subtitle      ->GetValue();    if (b) ps|=PAGESTATUS_C6_SUBTITLE;
        b=m_propertiesDlg->CheckBoxC7SuppressHeader->GetValue();    if (b) ps|=PAGESTATUS_C7_SUPPRESSHDR;
        b=m_propertiesDlg->CheckBoxC8Update        ->GetValue();    if (b) ps|=PAGESTATUS_C8_UPDATE;
        b=m_propertiesDlg->CheckBoxTransmitPage    ->GetValue();    if (b) ps|=PAGESTATUS_TRANSMITPAGE;

        pageSet->CurrentPage()->SetPageStatus(ps); // Put ps back into the object
        //std::cout << "Page status=" << std::hex << ps << std::endl;

        // Description
        pageSet->SetDescription(m_propertiesDlg->TextCtrlDescription->GetValue().ToStdString()); // Description

        // Counter/Timer. NOTE: This is a per subpage property
        std::string str=m_propertiesDlg->TextCtrlCycleTime->GetValue().ToStdString(); // Read the time from the dialog
        pageSet->CurrentPage()->SetCycleTime(atoi(str.c_str()));    // The cycle count / time (seconds)

        char ctmode=(m_propertiesDlg->RadioBoxCycleMode->GetSelection())==0?'C':'T';
        pageSet->GetPage(0)->SetCycleTimeMode(ctmode);

        // Fastext
        // Changed to ensure that ALL subpages have the same fastext links. It makes VBIT work much better
        //.. Hmm doesn't work
        /* TODO FIX THIS MESS
        int link;
        link=std::strtol(m_propertiesDlg->TextCtrlFastext1->GetValue().ToStdString().c_str(), &ptr, 16);
        // pageSet->GetPage(0)->SetFastextLink(0,link);
        for (std::shared_ptr<TTXPage> p=pageSet->GetPage(0);p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(0,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext2->GetValue().ToStdString().c_str(), &ptr, 16);
        //pageSet->GetPage(0)->SetFastextLink(1,link);
        for (std::shared_ptr<TTXPage> p=pageSet->GetPage(0);p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(1,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext3->GetValue().ToStdString().c_str(), &ptr, 16);
        //pageSet->GetPage(0)->SetFastextLink(2,link);
        for (std::shared_ptr<TTXPage> p=pageSet->GetPage(0);p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(2,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastext4->GetValue().ToStdString().c_str(), &ptr, 16);
        // pageSet->GetPage(0)->SetFastextLink(3,link);
        for (std::shared_ptr<TTXPage> p=pageSet->GetPage(0);p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(3,link);
        link=std::strtol(m_propertiesDlg->TextCtrlFastextIndex->GetValue().ToStdString().c_str(), &ptr, 16);
        // pageSet->GetPage(0)->SetFastextLink(5,link);
        for (std::shared_ptr<TTXPage> p=pageSet->GetPage(0);p!=NULL;p=p->Getm_SubPage()) p->SetFastextLink(5,link);
          */
    }
}

// FTP publish is only implemented in Windows
#ifdef __WXMSW_DISABLED__
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
#endif // __WXMSW__

void wxTEDFrame::OnMenuItemPublishSettings(wxCommandEvent& event)
{
    #ifdef __WXMSW_DISABLED__
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
#endif // __WXMSW__

}

void wxTEDFrame::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() && pageSet->GetPage(0)->GetPageChanged() )
    {
        if ( wxMessageBox("The file has not been saved... continue closing?",
                          "Please confirm",
                          wxICON_WARNING | wxCANCEL | wxCANCEL_DEFAULT) == wxCANCEL )
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
   if (rotate>=0)
   {
        pageSet->NextPage();
   }
   if (rotate<0)
   {
        pageSet->PreviousPage();
   }
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
  auto xloc=event.GetPosition().x;
  // std::cout << std::dec <<"Mouse move, yay!" << xloc <<  std::endl;
  auto leftX = m_offset.x;
  int rightX = leftX + m_ttxW * 41 * pageSet->GetPageCount();
  if (xloc < leftX || xloc > rightX)
  {
    wxSetCursor (wxCursor (wxCURSOR_NO_ENTRY));
  }
  else
  {
    wxSetCursor (wxCursor (wxCURSOR_DEFAULT));
  }
  // Is the cursor over a valid page?
  // Set the cursor accordingly

    // TODO: Extend this to highlight links on rollover
    // TODO: When left button moves, continue drag.
    if (!event.LeftIsDown()) // OnLeftUp only fires if you are over the frame.
    {
      OnLeftUp(event);
    }
    if (m_dragging)
    {
        wxPoint p=event.GetPosition();
        p.x-=m_offset.x; // Which page are we on? 40 Characters + 1 space.
        p.x/=m_ttxW;
        p.x-=pageSet->CurrentPageIndex()*41;
        p.y/=m_ttxH;
        if (p.x>40) p.x=40;
        if (p.y>=25) p.y=25;
        m_MarqueeEnd=p; // Marquee end
    }

    // Page slide with right mouse button
    if (!event.RightIsDown())
    {
      m_slidePages=false;
    }
    if (m_slidePages)
    {
        wxPoint p=event.GetPosition();
        m_offset.x=p.x-m_slideOrigin.x;
        //p.x/=m_ttxW;
        //p.y/=m_ttxH;
        //if (p.x>40) p.x=40;
        //if (p.y>=25) p.y=25;
        //m_MarqueeEnd=p; // Marquee end
        //std::cout << "continue slide at " << p.x << ", " << p.y << " m_offset.x=" << m_offset.x << std::dec << std::endl;
    }

}

void wxTEDFrame::OnLeftDown(wxMouseEvent& event) // Left Mouse down
{
  // Must be over an actual page or we ignore the click
  int x=event.GetPosition().x;
  if (x>=m_offset.x && x<=m_offset.x+static_cast<int>(m_ttxW*41) * pageSet->GetPageCount())
  {
    m_dragging=true;

//    std::cout << "Left button pressed..." << std::endl;
    wxPoint save=m_cursorPoint;
    m_cursorPoint=event.GetPosition();
    // Adjust to slide offset
    m_cursorPoint.x-=m_offset.x;

    // Adjust to character location
    m_cursorPoint.x/=m_ttxW;
    m_cursorPoint.y/=m_ttxH;
    // Need to think about the page number (each page 40 characters + one space)
    auto page=m_cursorPoint.x/41; // 40 Characters + 1 space
    std::cout << "Page " << page << std::endl;
    pageSet->SelectPage(page);
    // iPage=page; // Set the page index
    // pageSet->CurrentPage=pageSet->GetPage(iPage); // and set the pointer as the new current page


    // Now we know the page, where in the page did we click?
    m_cursorPoint.x%=41;

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
  event.Skip(); // wsfn Not sure if this is needed
}


void wxTEDFrame::OnMenuItemCopySelected(wxCommandEvent& event)
{
    // *thinks*
    // How can we cut and paste between instances of wxTED because that would be really useful.
    // What data did we just copy?
    std::cout << m_MarqueeStart.x << "," << m_MarqueeStart.y << "    " << m_MarqueeEnd.x  << "," << m_MarqueeEnd.y << std::endl;
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
        TTXLine* line=pageSet->CurrentPage()->GetRow(y);
        if (!line)
        {
          std::cout << "[wxTEDMain::wxTEDFrame] We got a null line, we are about to crash" << std::endl;
        }
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
    CopyTextToClipboard(wxs);
}

void wxTEDFrame::CopyTextToClipboard(wxString text)
{
   if (wxTheClipboard->Open())
   {
      wxTheClipboard->Clear();
      wxTheClipboard->SetData( new wxTextDataObject( text ) );
      wxTheClipboard->Flush();
      wxTheClipboard->Close();
   }
}

wxString wxTEDFrame::GetTextFromClipboard()
{
   wxString wxs;
   if (wxTheClipboard->Open())
   {
      if (wxTheClipboard->IsSupported( wxDF_TEXT ))
      {
          wxTextDataObject data;
          wxTheClipboard->GetData(data);
          wxs=data.GetText();
      }
      else
        wxs="";
      wxTheClipboard->Close();
   }
   return wxs;
}

/** Paste
 * One sneaky trick, is if the URL contains one of the following
 * http://editor.teletext40.com (obsolete)
 * edit.tf
 * zxnet.co.uk/editor
 * www.uniquecodeanddata.co.uk/editor
 * then we assume that the clipboard contains a URL from the teletext40 editor and should be decoded as such.
 */
void wxTEDFrame::OnMenuItemPasteSelected(wxCommandEvent& event)
{
   wxString wxs;
   wxs=GetTextFromClipboard();
   /// @todo Make this more general to identify a valid hash string
   if ((wxs.Find("http://editor.teletext40.com")!=wxNOT_FOUND) ||  // Paste obsolete teletext40 URL?
    (wxs.Find("www.uniquecodeanddata.co.uk/editor")!=wxNOT_FOUND) ||     // Paste a uniquecodeandadata URL?
    (wxs.Find("zxnet.co.uk/editor")!=wxNOT_FOUND) ||     // Paste a zxnet.co.uk URL? Alistair
    (wxs.Find("edit.tf")!=wxNOT_FOUND) || // Simon
    (wxs.Find("teletextarchaeologist.org/editor")!=wxNOT_FOUND) // Jason
       )     // Paste edit.tf URL?
   {
     // @todo [!] paste into the current subpage
     // so how are we going to handle pageSet->CurrentPage?
       load_from_hash(pageSet.get(), wxs.char_str());
   }
   else
   {
       // Now paste this text at the location m_cursorPoint
       // A NULL char is the end of a line. Note: This will conflict with AlphaBlack code.
       wxChar ch;
       int x=m_cursorPoint.x;
       int y=m_cursorPoint.y;
       TTXLine* line=pageSet->CurrentPage()->GetRow(y++);
       for (uint16_t i=0;i<wxs.Length();i++)
       {
            ch=wxs[i];
            if (ch==0xff)
            {
                line=pageSet->CurrentPage()->GetRow(y++);
                x=m_cursorPoint.x;
            }
            else
                if (x<=40 && y<=25 && line) // Clip to frame!
                {
                  line->SetCharAt(x++,ch);
                }
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
    int region=event.GetId() - MenuItemRegion0->GetId();
    SetRegion(region, true); // Primary region
}

void wxTEDFrame::OnMenuItemRegionBSelected(wxCommandEvent& event)
{
  int region=event.GetId() - MenuItemRegionB0->GetId();
  SetRegion(region, false); // Second region
}

void wxTEDFrame::SetRegion(int region, bool UsePrimary)
{
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

  SetRegionMenu(region, UsePrimary);
  pageSet->CurrentPage()->SetRegion(region, UsePrimary);
}

void wxTEDFrame::SetRegionMenu(int region, bool UsePrimary)
{
  wxMenuItem** languages = UsePrimary ? PrimaryLanguage : SecondLanguage;
    switch (region)
    {
    case 0:
      {
        std::string langStrings[8] = {"English", "French", "Swedish/Finnish/Hungarian","Czech/Slovak", "German", "Portuguese/Spanish", "Italian", "Unused"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 1:
      {
        std::string langStrings[8] = {"Polish", "French", "Swedish/Finnish/Hungarian","Czech/Slovak", "German", "Unused", "Italian", "Unused"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 2:
      {
        std::string langStrings[8] = {"English", "French", "Swedish/Finnish/Hungarian","Turkish", "German", "Portuguese/Spanish", "Italian", "Unused"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 3:
      {
        std::string langStrings[8] = {"Unused", "Unused", "Unused", "Unused", "Unused", "Serbian/Croatian/Slovenian", "Unused", "Rumanian"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 4:
      {
        std::string langStrings[8] = {"Serbian/Croatian", "Russian/Bulgarian", "Estonian", "Czech/Slovak", "German", "Ukrainian", "Lettish/Lithuanian", "Unused"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 6: // Turkish and Greek
      {
        std::string langStrings[8] = {"Unused", "Unused", "Unused", "Turkish", "Unused", "Unused", "Unused", "Greek"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 8: // English/French/Arabic;
      {
        std::string langStrings[8] = {"English", "French", "Unused", "Unused", "Unused", "Unused", "Unused", "Arabic"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    case 10: // Hebrew/Arabic
      {
        std::string langStrings[8] = {"Unused", "Unused", "Unused", "Unused", "Unused", "Hebrew", "Unused", "Arabic"};
        for (auto i(0); i < 8; ++i)
        {
            languages[i]->SetItemLabel(langStrings[i]);
        }
      }
      break;
    default:
      std::cout << "[wxTEDMain::SetRegionMenu] ERROR: Bad region = " << region << std::endl;
      region=0;
    }

    // Disable the unused menu items
    for (auto lang(0); lang < 8; ++lang)
    {
       wxString s = languages[lang]->GetItemLabel();
       languages[lang]->Enable(s.compare(wxString("Unused")) != 0);
    }

    // Now check the appropriate menu item
    pageSet->CurrentPage()->SetRegion(region, UsePrimary);
    int language=pageSet->CurrentPage()->GetLanguage(UsePrimary);
    // Is language not checkable?
    if (!languages[language]->IsCheckable())
    {
      for (int lan = 0; lan < 8; ++lan)
      {
        if (languages[lan]->IsCheckable())
        {
          language = lan; // Found a language that is valid
          std::cout << "[SetRegionMenu] found valid language = " << language << std::endl;
          break;
        }
      }
    }

   std::cout << "[SetRegionMenu] " << std::endl;
   for (int i=0;i<8;i++)
   {
    std::cout << "[SetRegionMenu] language[" << i <<"] = " << languages[i]->GetItemLabel() << std::endl;

   }

    if (!languages[language]->IsCheckable())
    {
      std::cout << "[SetRegionMenu] ERROR: Failure is inevitable. language = " << language<< std::endl;
    }
    else
    {
      languages[language]->Check(true);
      // Check against the current region, as it might not already be checked
      wxMenuItem** regions = UsePrimary ? PrimaryRegion : SecondRegion;
      // Map X28 region back to a menu item
      region = region < 5
      ? region
      : region == 6
      ? 5
      : region == 8
      ? 6
      : region == 10
      ? 7
      : 0;

      regions[region]->Check(true);
    }
}

void wxTEDFrame::OnMenuSpecialKeys(wxCommandEvent& event)
{
    helpFrame->SetFont(GetFont()); // [fail to!] Use teletext font for help
    helpFrame->Show(true);
}

void wxTEDFrame::OnMenuItemExportTTX40Selected(wxCommandEvent& event)
{

  // Extract a character array
  uint8_t cc[25][40];
  for (uint8_t y=0;y<25;y++)
  {
    TTXLine* line=pageSet->CurrentPage()->GetRow(y);
    for (uint8_t x=0;x<40;x++)
    {
        uint8_t c=line->GetCharAt(x) & 0x7f;
        cc[y][x]=c;
    }
    //@todo Implement page number substitution for row 0 header
    if (y==0)
    {
      for (int i=0;i<8;i++) // First 8 characters are not taken from the header
          cc[y][i]=' ';
      int k=pageSet->GetPageNumber()/0x100;
      if (k<0x100 && k>0x8ff)
          k=0x100;
      std::ostringstream val;
      val << std::hex << k;
      cc[y][0]='P';
      cc[y][1]=val.str()[0];
      cc[y][2]=val.str()[1];
      cc[y][3]=val.str()[2];
    }
  }
  // Convert to a teletext 40 URL
  // TODO: Implement character set
  char page[1300];
  save_to_hash(1, page,cc, "http://edit.tf", pageSet.get());
  CopyTextToClipboard(page);
  // Launch a browser with the URL
  // Widen the URL
  std::wstring w;
  std::copy(page,page+strlen(page),back_inserter(w));

  wxLaunchDefaultBrowser(w);

}

void wxTEDFrame::OnKeyDown(wxKeyEvent& event)
{
  auto key = event.GetKeyCode();
  auto modifier = event.GetModifiers();
  std::cout << "TRACE1-OnKeyDown... modifier = " << modifier << " key = " << key << std::endl;

  if ((modifier == wxMOD_ALTGR) && m_Released) // ALTGR does not work on Linux
  {
      m_ShowMarkup=!m_ShowMarkup;
      m_Released=false;
  }
  if (modifier == wxMOD_CONTROL) // Only really used to add language switching code ESC
  {
    m_controlModifier = true;
  }
  event.Skip();
}

void wxTEDFrame::OnKeyUp(wxKeyEvent& event)
{
  std::cout << "TRACE2:OnKeyUp..." << std::endl;
  auto modifier = event.GetModifiers();

  // int k=event.GetKeyCode();
  if (modifier == WXK_ALT)
  {
      m_Released=true;
  }
  if (modifier == wxMOD_CONTROL)
  {
    m_controlModifier = false;
  }
  event.Skip();
}

void wxTEDFrame::OnMenuItemNewWindow(wxCommandEvent& event)
{
	wxTEDFrame * win = new wxTEDFrame(nullptr);
	win->OnMenuNew(event);
	win->Show(true);
}

void wxTEDFrame::OnMenuItemZXNetSelected(wxCommandEvent& event)
{
  // Extract a character array
  uint8_t cc[25][40];
  for (uint8_t y=0;y<25;y++)
  {
    TTXLine* line=pageSet->CurrentPage()->GetRow(y);
    for (uint8_t x=0;x<40;x++)
    {
        uint8_t c=line->GetCharAt(x) & 0x7f;
        cc[y][x]=c;
    }
    //@todo Implement page number substitution for row 0 header
    if (y==0)
    {
      for (int i=0;i<8;i++) // First 8 characters are not taken from the header
          cc[y][i]=' ';
      int k=pageSet->GetPageNumber()/0x100;
      if (k<0x100 && k>0x8ff)
          k=0x100;
      std::ostringstream val;
      val << std::hex << k;
      cc[y][0]='P';
      cc[y][1]=val.str()[0];
      cc[y][2]=val.str()[1];
      cc[y][3]=val.str()[2];
    }
  }
  // Convert to a teletext 40 URL
  // TODO: Implement character set
  char page[1300];
  save_to_hash(1, page,cc, "http://zxnet.co.uk/teletext/editor", pageSet.get());
  CopyTextToClipboard(page);
  // Launch a browser with the URL
  // Widen the URL
  std::wstring w;
  std::copy(page,page+strlen(page),back_inserter(w));
  wxLaunchDefaultBrowser(w);
}

void wxTEDFrame::OnRightDown(wxMouseEvent& event)
{
  wxPoint wxp=event.GetPosition();
  std::cout << "x=" << wxp.x << " y=" << wxp.y << std::endl;
  // find the actual character row/column
  // Must be over an actual page or we ignore the click
  int x=event.GetPosition().x;
  if (x>=m_offset.x && x<=m_offset.x+static_cast<int>(m_ttxW*41) * pageSet->GetPageCount())
  {

    std::cout << "Right button pressed..." << std::endl;
//    wxPoint save=m_cursorPoint;
    m_cursorPoint=event.GetPosition();
    // Adjust to slide offset
    m_cursorPoint.x-=m_offset.x;

    // Adjust to character location
    m_cursorPoint.x/=m_ttxW;
    m_cursorPoint.y/=m_ttxH;

    // What character is at this position?
    TTXLine* line=pageSet->CurrentPage()->GetRow(m_cursorPoint.y);
    if (!line)
    {
      std::cout << "[wxTEDFrame::OnRightDown] We got a null line, we are about to crash" << std::endl;
    }
    wxChar wxc=line->GetCharAt(m_cursorPoint.y);
    std::cout << "[wxTEDFrame::OnRightDown] char clicked on = " << wxc << std::endl;

// For some reason, I can't use the symbol picker under Ubuntu
#ifdef __WXMSW_DISABLED__
    wxString InitialChar = "\xc8"; // The AE ligature
    SymbolPickerDialog1->SetSymbol(InitialChar); // Ligature AE is at the start of the interesting characters
    SymbolPickerDialog1->SetFromUnicode(true); // Definitely want unicode
    SymbolPickerDialog1->SetFontName("teletext2"); // This is our only allowed font
    SymbolPickerDialog1->ShowModal();
    auto ch = SymbolPickerDialog1->GetSymbolChar();
    std::cout << "[wxTEDFrame::OnRightDown] ch = " << ch << std::endl;
#endif
  }



  m_slideOrigin=event.GetPosition()-m_offset;
  m_slidePages=true;
}

void wxTEDFrame::OnRightUp(wxMouseEvent& event)
{
  // drag ended - Move the offset to match the drag
  m_slidePages=false;
}

void wxTEDFrame::OnMenuNewFromTemplate(wxCommandEvent& event)
{
  // Templates subfolder holds template pages
  // Get path to our executable
  wxFileName f(wxStandardPaths::Get().GetExecutablePath());
  wxString appPath(f.GetPath());
  // Path to templates
  appPath+="\\Templates";
  std::cout << "wxstring=" << appPath;

  // auto savepath=LoadPageFileDialog->GetDirectory();
  LoadPageFileDialog->SetMessage("Open a new teletext page from template");
  LoadPageFileDialog->SetDirectory(appPath);

  if (LoadPageFileDialog->ShowModal() != wxID_CANCEL)
  {
    auto pathStr=LoadPageFileDialog->GetPath().ToStdString();

    wxString filename=LoadPageFileDialog->GetFilename();
    pageSet = std::make_unique<TTXPageSet>(pathStr,filename.ToStdString());

    // Change the filename so that we can't overwrite it by mistake.
    pageSet->SetShortFilename("");
    pageSet->SetSourcePage("");
    pageSet->SetPageNumber(0x1ff00); // Invalid

    // Protect the template, do not enable save
    EnableSave(false);

    m_setLanguage(true);
    m_offset.x=0;

    SetRegionMenu(pageSet->GetPage(0)->GetRegion(true), true); // Region language

    SetTitle("Template");

    // Update the palette in case it is visible
    paletteFrame->SetX28(pageSet->GetPage(0)->GetX28Row());

    // TODO FIX THIS pageSet->CurrentPage=pageSet->GetPage(0);

    // Force an update now
    Refresh();
    Update();
    ShowCarouselMenu();
  }

}

// Delete the current line, shifting lines below up one
// Fastext row is NOT included
// @todo Map this to ESC-I
void wxTEDFrame::OnMenuDeleteLineSelected(wxCommandEvent& event)
{
  pageSet->CurrentPage()->DeleteLine(m_cursorPoint);
}

// Scroll lines below down one, and leave current line blank
// Fastext row is NOT included
// @todo Map ESC-i onto this
void wxTEDFrame::OnMenuInsertLineSelected(wxCommandEvent& event)
{
  pageSet->CurrentPage()->InsertLine(m_cursorPoint);
}

// This does nothing. Where are my events going?
void wxTEDFrame::OnPanel1KeyDown(wxKeyEvent& event)
{
    std::cout << "[wxTEDFrame::OnPanel1KeyDown]" << std::endl;
        event.Skip();

}


void wxTEDFrame::OnPanel1Char(wxKeyEvent& event)
{
    std::cout << "[wxTEDFrame::OnPanel1Char]" << std::endl;
    event.Skip();
}


void wxTEDFrame::OnPanelTEMPORARYPaint(wxPaintEvent& event)
{
}

void wxTEDFrame::OnPanel1LeftDClick(wxMouseEvent& event)
{
    std::cout << "[wxTEDFrame::OnPanel1LeftDClick]" << std::endl;
    event.Skip();
}

void wxTEDFrame::OnMenuOpenPage(wxCommandEvent& event)
{
    std::string str;
    LoadPageFileDialog->SetMessage("Open teletext page");
    LoadPageFileDialog->SetDirectory(m_path);
    if (LoadPageFileDialog->ShowModal() == wxID_CANCEL)
    {
      return;     // the user bottled out
    }
    str=LoadPageFileDialog->GetPath().ToStdString();

    m_path = LoadPageFileDialog->GetDirectory().ToStdString(); // Save the path

    wxString filename=LoadPageFileDialog->GetFilename();
    std::cout << "the filename was " << filename << std::endl;
    std::cout << "Loading a teletext page " << str << " path " << m_path << std::endl;
    // @TODO, we might want to warn the user that they are destroying the previous page
    pageSet = std::make_unique<TTXPageSet>(str, filename.ToStdString());

    // MenuItemSave->Enable(pageSet->GetPage(0)->IsLoaded()); // Enable save if we had a good load
    EnableSave(pageSet->IsLoaded());

    m_setLanguage(true);
    m_offset.x=0;

    SetRegionMenu(pageSet->CurrentPage()->GetRegion(true), true); // Primary Region language
    SetRegionMenu(pageSet->CurrentPage()->GetRegion(false), false); // Secondary Region language

    SetTitle(pageSet->GetSourcePage());

    // Update the palette in case it is visible
    paletteFrame->SetX28(pageSet->CurrentPage()->GetX28Row());


    // Force an update now
    Refresh();
    Update();
    ShowCarouselMenu();
}

/// Preview a carousel.
void wxTEDFrame::OnPreviewRunSelected(wxCommandEvent& event)
{
    // Enter Preview mode.
    // Cancelled by any key
    m_previewCarouselMode = true;

    previewSavedCaption = GetTitle(); // Save the caption for later
    SetTitle("Carousel running. Press any key to stop"); // Set a new caption
    UpdatePreview();
}

void wxTEDFrame::UpdatePreview()
{
    int timer_period{456};
    if (PreviewNormal->IsChecked()) timer_period = 456; // Normal (Time of the blink)
    if (Preview30fps->IsChecked()) timer_period = (1000/30); // 30 fps
    if (Preview25fps->IsChecked()) timer_period = (1000/25); // 25 fps
    if (Preview12fps->IsChecked()) timer_period = (1000/12); // 12 fps
    if (Preview6fps->IsChecked()) timer_period = (1000/6); // 6 fps
    if (Preview2fps->IsChecked()) timer_period = (1000/2); // 2 fps
    m_Timer1.Start(timer_period);
    m_normalMode = PreviewNormal->IsChecked();
    m_bounceMode = ModeBounce->IsChecked();
}

void wxTEDFrame::ShowCarouselMenu()
{
    const bool show{ pageSet->GetPageCount() > 1 };
    MenuBar->EnableTop(3, show); // Third row is carousel.
}

void wxTEDFrame::OnPreviewSpeed(wxCommandEvent& event)
{
    UpdatePreview();
}

void wxTEDFrame::OnPreviewNormalSelected(wxCommandEvent& event)
{
    UpdatePreview();
}

/// Maps the standard colours only. X28 mapping is more complex.
const wxColour* wxTEDFrame::ttxCode2wxColour(const unsigned int colour) // Given a ttxCode 0..7 return a wxColour
{
  switch (colour)
  {
    case 0: return wxBLACK;
    case 1: return wxRED;
    case 2: return wxGREEN;
    case 3: return wxYELLOW;
    case 4: return wxBLUE;
    case 5: return new wxColour(0xff, 0x00, 0xff); // Magenta
    case 6: return wxCYAN;
    case 7: return wxWHITE;
    default:
      return(new wxColour(0xff, 0x88, 0x00));
  }
}

/// Opens the colour table frame
void wxTEDFrame::OnMenuItemPaletteSelected(wxCommandEvent& event)
{
  // "todo Get cluts from the X28 row if it exists and populate the palette
  std::shared_ptr<TTXRow28> x28row;
  x28row = pageSet->CurrentPage()->GetX28Row(); // @todo If we change subpage, do we set the correct page???
  paletteFrame->SetX28(x28row);
  paletteFrame->Show(true);
}



void wxTEDFrame::OnMenuItemShowCodesSelected(wxCommandEvent& event)
{
  bool checked = MenuItemShowCodes-> IsChecked();
  m_ShowMarkup=checked;
}
