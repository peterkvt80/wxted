/***************************************************************
 * Name:      wxTEDMain.h
 * Purpose:   Defines Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan (c) 2014-2025
 * License:
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

#ifndef WXTEDMAIN_H
#define WXTEDMAIN_H

//(*Headers(wxTEDFrame)
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
//*)
#include <wx/clipbrd.h>
#include <wx/config.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
/*
<wx/confbase.h> - Base config class.
<wx/fileconf.h> - wxFileConfig class.
// <wx/msw/regconf.h> - wxRegConfig class, see also wxRegKey.
*/

#include "HelpFrame.h"
#include "PaletteFrame.h"
#include <sstream>
#include <memory>
#include "ttxpage.h"
#include "ttxrow28.h"
#include "ttxpageset.h"
#include "PageSettingsDialog.h"
#include "mapchar.h"


// Version number
#define VERSION_STRING wxT("1.58")

// Hacky stand in for Magenta
#define wxMAGENTA wxLIGHT_GREY

// Publish setup
#include "PublishSetupDialog.h"

// Export to teletext40
#include "teletext40.h"

class wxTEDFrame: public wxFrame
{
    public:

        wxTEDFrame(wxWindow* parent, wxWindowID id = -1, wxString initialPage="wxtedsplash.tti");
        virtual ~wxTEDFrame();
        //inline std::shared_ptr<TTXPage> Page(){return m_rootPage;};

    private:

      bool m_escapeMode; /// True if the last key pressed was Escape
      bool m_controlModifier; /// True if the control key is currently active
      int m_menuCount;      // How many menus are open
      bool m_inhibitStatus; // Inhibit the status bar while menus are up

      bool m_ShowMarkup; // If true, we show ttx markup
      bool m_Released;   // If true, m_ShowMarkup can be toggled

      /** Set up the primary or second region menu
       *  @param region - The X28 region number 0,1,2,3,4,6,8,10
       *  @param UsePrimary - True = Primary language, false = Second language
       */
      void SetRegionMenu(int region, bool UsePrimary);

      unsigned int m_ttxW; /// Font width
      unsigned int m_ttxH; /// Font height

      // Cursor
      wxPoint m_cursorPoint; /// Cursor location (in character coordinates)
      wxPoint m_subPixelPoint; /// Sub-pixel location when in graphics mode
      bool m_blinkToggle;  /// Blink state
      bool m_cursorIsAlpha; /// Selects graphics or alpha
      void m_SetStatus(); /// Shows cursor location and character info

      bool m_reveal;  /// True if we should reveal concealed text

      // Copy buffer
      bool m_dragging;
      wxPoint m_MarqueeStart;
      wxPoint m_MarqueeEnd;
      void CopyTextToClipboard(wxString text);
      wxString GetTextFromClipboard();

      // Page
      void m_resize(wxSize event);
      wchar_t mapTextChar(wchar_t ch, bool primary);  /// Maps a teletext character to a teletext2 font

      //int m_iPageCount;   /// How many pages in this set?
      //int iPage;          /// Which page are we looking at?
      wxPoint m_offset;   /// The offset of the current page

      bool m_EnableSave = false; /// Initial page we need to protect against overwriting
      void EnableSave(bool enable = true){m_EnableSave = enable;}; /// If true then ctrl-s is allowed to save the page

      wxPoint m_slideOrigin;  /// X,Y Origin of a slide
      bool m_slidePages;      /// True if we are sliding the page with the right mouse key

      bool m_focused; /// Frame

      bool m_previewCarouselMode{false};    /// Preview carousel mode.
      bool m_normalMode{true};      /// Normal mode means using the page's animation timings
      bool m_bounceMode{false};     /// Does the animation direction bounce?
      bool m_previewForwards{true}; /// true = forwards, false = backwards

      void ShowCarouselMenu(); /// Show/hide the carousel menu as appropriate. Call when the page count changes.

      std::string m_path{""}; /// Path of the last file that was loaded (Do we need to set this to dot? What about Windows?)


      // Properties Dialog
      PageSettingsDialog* m_propertiesDlg;

      // Config
      wxConfig *m_config;

      // Help
      HelpFrame* helpFrame;

      // Palette
      PaletteFrame* paletteFrame;


      // Publishing
      wxString m_publish_ftp_server;
      wxString m_publish_ftp_username;
      wxString m_publish_ftp_password;
      wxString m_publish_ftp_remote;

      // Header
      /** Takes a teletext header template and does the field substitutions
       * \param line of text to transform
       */
      void GenerateHeader(TTXLine* line);

      // Items in language menu lists
      wxMenuItem* PrimaryLanguage[8];
      wxMenuItem* PrimaryLanguageX28[9]; // This should always match PrimaryLanguage
      wxMenuItem* SecondLanguage[8];

      // Items in region menu lists
      wxMenuItem* PrimaryRegion[8];
      wxMenuItem* SecondRegion[8];

      void SetRegion(int region, bool UsePrimary);

      std::unique_ptr<TTXPageSet> pageSet;

      //(*Handlers(wxTEDFrame)
      void OnQuit(wxCommandEvent& event);
      void OnAbout(wxCommandEvent& event);
      void OnMenuNew(wxCommandEvent& event);
      void OnMenuSaveAs(wxCommandEvent& event);
      void OnMenuItemProperties(wxCommandEvent& event);
      void OnMenuItemPublish(wxCommandEvent& event);
      void OnMenuItemUndo(wxCommandEvent& event);
      void OnKillFocus(wxFocusEvent& event);
      void OnSetFocus(wxFocusEvent& event);
      void OnMenuItemInsertSubpage(wxCommandEvent& event);
      void OnMenuItemDeletePage(wxCommandEvent& event);
      void OnMenuItemLanguageSelected(wxCommandEvent& event);
      void OnMenuItemLanguage(wxCommandEvent& event);
      void OnMenuItemPublishSettings(wxCommandEvent& event);
      void OnClose(wxCloseEvent& event);
      void OnMenuItemConcealToggle(wxCommandEvent& event);
      void OnMouseWheel(wxMouseEvent& event);
      void OnLeftUp(wxMouseEvent& event);
      void OnMouseMove(wxMouseEvent& event);
      void OnMenuItemCopySelected(wxCommandEvent& event);
      void OnMenuItemPasteSelected(wxCommandEvent& event);
      void OnMenuItemSelectAllSelected(wxCommandEvent& event);
      void OnMenuItemRegionSelected(wxCommandEvent& event);
      void OnMenuSpecialKeys(wxCommandEvent& event);
      void OnMenuItemExportTTX40Selected(wxCommandEvent& event);
      void OnKeyDown(wxKeyEvent& event);
      void OnKeyUp(wxKeyEvent& event);
      void OnPanel1Paint(wxPaintEvent& event);
      void OnMenuItemNewWindow(wxCommandEvent& event);
      void OnMenuItemZXNetSelected(wxCommandEvent& event);
      void OnRightDown(wxMouseEvent& event);
      void OnRightUp(wxMouseEvent& event);
      void OnPanel1MouseMove(wxMouseEvent& event);
      void OnPanel1Paint1(wxPaintEvent& event);
      void OnMenuNewFromTemplate(wxCommandEvent& event);
      void OnMenuDeleteLineSelected(wxCommandEvent& event);
      void OnMenuInsertLineSelected(wxCommandEvent& event);
      void OnPanel1KeyDown(wxKeyEvent& event);
      void OnLeftDown(wxMouseEvent& event);
      void OnPaint(wxPaintEvent& event);
      void OnSize(wxSizeEvent& event);
      void OnChar(wxKeyEvent& event);
      void OnTimer(wxTimerEvent& event);
      void OnEraseBackground(wxEraseEvent& event);
      void OnSave(wxCommandEvent& event);
      void OnMenuOpen(wxMenuEvent& event); // On opening the menu
      void OnMenuClose(wxMenuEvent& event); // On closing the menu
      void OnPanel1Char(wxKeyEvent& event);
      void OnPanelTEMPORARYPaint(wxPaintEvent& event);
      void OnPanel1LeftDClick(wxMouseEvent& event);
      void OnMenuOpenPage(wxCommandEvent& event);
      void OnMenuPreviewModeSelected(wxCommandEvent& event);
      void OnPreviewRunSelected(wxCommandEvent& event);
      void OnPreviewSpeed(wxCommandEvent& event);
      void OnPreviewNormalSelected(wxCommandEvent& event);
      void OnMenuItemPaletteSelected(wxCommandEvent& event);
      void OnMenuItemRegionBSelected(wxCommandEvent& event);
      void OnMenuItemLanguageB(wxCommandEvent& event);
      void OnMenuItemLanguageX28(wxCommandEvent& event);
      void OnMenuItemShowCodesSelected(wxCommandEvent& event);
      //*)

      /* Set the language menu radio option */
      void m_setLanguage(bool UsePrimary);

      /**
       * \return true if the character is in the range of mosaics, not including A-Z.
       */
      bool isMosaic(char ch);

      /// Update the preview settings (speed and mode)
      void UpdatePreview();
      std::string previewSavedCaption;

      static const wxColour* ttxCode2wxColour(const unsigned int); // Given a ttxCode 0..7 return a wxColour

      wxSize m_fontSize[100];

      wxWindow* m_parentWindow;

      //(*Identifiers(wxTEDFrame)
      static const wxWindowID ID_PANEL1;
      static const wxWindowID idNewPage;
      static const wxWindowID idNewFromTemplate;
      static const wxWindowID idOpenPage;
      static const wxWindowID idSavePage;
      static const wxWindowID isSavePageAs;
      static const wxWindowID idExportTTX40;
      static const wxWindowID isExportZxnet;
      static const wxWindowID idMenuQuit;
      static const wxWindowID idNewWindow;
      static const wxWindowID idUndo;
      static const wxWindowID idCut;
      static const wxWindowID idCopy;
      static const wxWindowID idPaste;
      static const wxWindowID idSelectAll;
      static const wxWindowID isInsertLine;
      static const wxWindowID isDeleteLine;
      static const wxWindowID idInsertPage;
      static const wxWindowID idDeleteSubPage;
      static const wxWindowID idLanguageEnglish;
      static const wxWindowID idLanguageFrench;
      static const wxWindowID idLanguageSwedish;
      static const wxWindowID idLanguageCzechSlovak;
      static const wxWindowID idLanguageGerman;
      static const wxWindowID idLanguageSpanish;
      static const wxWindowID idLanguageItalian;
      static const wxWindowID idLanguageUnused;
      static const wxWindowID ID_MENUITEM1;
      static const wxWindowID idPageNumber;
      static const wxWindowID ID_MENUITEMSHOWHEADER;
      static const wxWindowID ID_SHOWCONTROL;
      static const wxWindowID ID_HIDECONCEAL;
      static const wxWindowID idMainLanguage0;
      static const wxWindowID idMainLanguage1;
      static const wxWindowID idMainLanguage2;
      static const wxWindowID idMainLanguage3;
      static const wxWindowID idMainLanguage4;
      static const wxWindowID idMainLanguage5;
      static const wxWindowID idMainLanguage6;
      static const wxWindowID idMainLanguage7;
      static const wxWindowID ID_MAINLANGUAGE;
      static const wxWindowID ID_REGION0;
      static const wxWindowID ID_REGION1;
      static const wxWindowID ID_REGION2;
      static const wxWindowID ID_REGION3;
      static const wxWindowID ID_REGION4;
      static const wxWindowID ID_REGION6;
      static const wxWindowID ID_REGION8;
      static const wxWindowID ID_REGION10;
      static const wxWindowID ID_MENUMAINREGION;
      static const wxWindowID idSecondLanguage0;
      static const wxWindowID ID_MENUITEM2;
      static const wxWindowID ID_MENUITEM3;
      static const wxWindowID ID_MENUITEM4;
      static const wxWindowID ID_MENUITEM5;
      static const wxWindowID ID_MENUITEM6;
      static const wxWindowID ID_MENUITEM7;
      static const wxWindowID ID_MENUITEM8;
      static const wxWindowID ID_SECOND_REGION;
      static const wxWindowID ID_REGION2R0;
      static const wxWindowID ID_REGION2R1;
      static const wxWindowID ID_REGION2R2;
      static const wxWindowID ID_REGION2R3;
      static const wxWindowID ID_REGION2R4;
      static const wxWindowID ID_REGION2R6;
      static const wxWindowID ID_REGION2R8;
      static const wxWindowID ID_REGION2R10;
      static const wxWindowID ID_MENUSECONDREGION;
      static const wxWindowID ID_PALETTE;
      static const wxWindowID x28enhance;
      static const wxWindowID idRun;
      static const wxWindowID idRadioMode;
      static const wxWindowID idRadioBounce;
      static const wxWindowID idRadioMode0;
      static const wxWindowID idRadioMode1;
      static const wxWindowID idRadioMode2;
      static const wxWindowID idRadioMode3;
      static const wxWindowID idRadioMode4;
      static const wxWindowID idRadioMode5;
      static const wxWindowID idSpecialKeys;
      static const wxWindowID idMenuAbout;
      static const wxWindowID ID_STATUSBAR1;
      static const wxWindowID ID_TIMER1;
      //*)

      static const long idMenuOpen;
      static const long idMenuClose;

      //(*Declarations(wxTEDFrame)
      wxFileDialog* FileDialogSaveAs;
      wxFileDialog* LoadPageFileDialog;
      wxMenu* Menu3;
      wxMenu* MenuCarousel;
      wxMenu* MenuItem5;
      wxMenu* MenuItem7;
      wxMenu* MenuItemLanguage;
      wxMenu* MenuMainRegion;
      wxMenu* MenuPresentation;
      wxMenu* MenuSecondLanguage;
      wxMenu* MenuSecondRegion;
      wxMenuItem* MenuDeleteLine;
      wxMenuItem* MenuExportZxnet;
      wxMenuItem* MenuInsertLine;
      wxMenuItem* MenuItem11;
      wxMenuItem* MenuItem1;
      wxMenuItem* MenuItem2ndLang0;
      wxMenuItem* MenuItem2ndLang1;
      wxMenuItem* MenuItem2ndLang2;
      wxMenuItem* MenuItem2ndLang3;
      wxMenuItem* MenuItem2ndLang4;
      wxMenuItem* MenuItem2ndLang5;
      wxMenuItem* MenuItem2ndLang6;
      wxMenuItem* MenuItem2ndLang7;
      wxMenuItem* MenuItem3;
      wxMenuItem* MenuItem4;
      wxMenuItem* MenuItemConcealToggle;
      wxMenuItem* MenuItemCopy;
      wxMenuItem* MenuItemCzech;
      wxMenuItem* MenuItemCzechX28;
      wxMenuItem* MenuItemDeletePage;
      wxMenuItem* MenuItemEnglish;
      wxMenuItem* MenuItemEnglishX28;
      wxMenuItem* MenuItemExportTTX40;
      wxMenuItem* MenuItemFrench;
      wxMenuItem* MenuItemFrenchX28;
      wxMenuItem* MenuItemGerman;
      wxMenuItem* MenuItemGermanX28;
      wxMenuItem* MenuItemInsertSubpage;
      wxMenuItem* MenuItemItalian;
      wxMenuItem* MenuItemItalianX28;
      wxMenuItem* MenuItemPageNumber;
      wxMenuItem* MenuItemPalette;
      wxMenuItem* MenuItemPaste;
      wxMenuItem* MenuItemRegion0;
      wxMenuItem* MenuItemRegion10;
      wxMenuItem* MenuItemRegion1;
      wxMenuItem* MenuItemRegion2;
      wxMenuItem* MenuItemRegion3;
      wxMenuItem* MenuItemRegion4;
      wxMenuItem* MenuItemRegion6;
      wxMenuItem* MenuItemRegion8;
      wxMenuItem* MenuItemRegionB0;
      wxMenuItem* MenuItemRegionB10;
      wxMenuItem* MenuItemRegionB1;
      wxMenuItem* MenuItemRegionB2;
      wxMenuItem* MenuItemRegionB3;
      wxMenuItem* MenuItemRegionB4;
      wxMenuItem* MenuItemRegionB6;
      wxMenuItem* MenuItemRegionB8;
      wxMenuItem* MenuItemSave;
      wxMenuItem* MenuItemSaveAs;
      wxMenuItem* MenuItemSelectAll;
      wxMenuItem* MenuItemShowCodes;
      wxMenuItem* MenuItemShowHeader;
      wxMenuItem* MenuItemSpanish;
      wxMenuItem* MenuItemSpanishX28;
      wxMenuItem* MenuItemSpecialKeys;
      wxMenuItem* MenuItemSwedish;
      wxMenuItem* MenuItemSwedishX28;
      wxMenuItem* MenuItemTemplate;
      wxMenuItem* MenuItemUndo;
      wxMenuItem* MenuItemUnused;
      wxMenuItem* MenuItemUnusedX28;
      wxMenuItem* ModeBounce;
      wxMenuItem* ModeLoop;
      wxMenuItem* Preview12fps;
      wxMenuItem* Preview25fps;
      wxMenuItem* Preview2fps;
      wxMenuItem* Preview30fps;
      wxMenuItem* Preview6fps;
      wxMenuItem* PreviewNormal;
      wxMenuItem* PreviewRun;
      wxPanel* Panel1;
      wxStatusBar* StatusBar1;
      wxTimer m_Timer1;
      //*)

      DECLARE_EVENT_TABLE()

      wxMenuBar* MenuBar;
};

#ifdef __WXMSW__
#include <windows.h>
int send(LPCTSTR ftp, LPCTSTR user, LPCTSTR pass, LPCTSTR pathondisk, LPTSTR nameonftp);
#endif // __WXMSW__

#endif // WXTEDMAIN_H
