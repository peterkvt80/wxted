/***************************************************************
 * Name:      wxTEDMain.h
 * Purpose:   Defines Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan (c) 2014-2020
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
#include <wx/richtext/richtextsymboldlg.h>
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
#include <sstream>
#include "ttxpage.h"
#include "PageSettingsDialog.h"
#include "mapchar.h"

// Version number
#define VERSION_STRING   wxT("1.47")

// ftp
#if defined(__WXMSW__)
#include <wininet.h>
#pragma comment(lib, "wininet")
#endif // __WXMSW__

// Publish setup
#include "PublishSetupDialog.h"

// Export to teletext40
#include "teletext40.h"

class wxTEDFrame: public wxFrame
{
    public:

        wxTEDFrame(wxWindow* parent,wxWindowID id = -1, wxString initialPage="wxtedsplash.tti");
        virtual ~wxTEDFrame();
        inline TTXPage* Page(){return m_rootPage;};

    private:
        bool m_escapeMode; /// True if the last key pressed was Escape
        int m_menuCount;      // How many menus are open
        bool m_inhibitStatus; // Inhibit the status bar while menus are up

        bool m_ShowMarkup; // If true, we show ttx markup
        bool m_Released;   // If true, m_ShowMarkup can be toggled

        // Language menu
        void SetRegionMenu(int region);

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
        TTXPage* m_rootPage; /// This is the root page used for load/save
        TTXPage* m_currentPage; /// This may point to a sub-page and is the page currently viewed and edited
        void m_resize(wxSize event);
        wchar_t mapTextChar(wchar_t ch);  /// Maps a teletext character to a teletext2 font if they aren't the same

        int iPageCount;     // How many pages in this set?
        int iPage;          // Which page are we looking at?
        wxPoint m_offset;   // The offset of the current page

        wxPoint m_slideOrigin;  // Origin of a slide
        bool m_slidePages;      // True if we are sliding the page with the right mouse key

        // Frame
        bool m_focused;

        // Properties Dialog
        PageSettingsDialog* m_propertiesDlg;

        // Config
        wxConfig *m_config;

        // Help
        HelpFrame* helpFrame;


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
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnMenuOpen(wxMenuEvent& event); // On opening the menu
        void OnMenuClose(wxMenuEvent& event); // On closing the menu
        void OnPanel1Char(wxKeyEvent& event);
        void OnPanelTEMPORARYPaint(wxPaintEvent& event);
        void OnPanel1LeftDClick(wxMouseEvent& event);
        void OnMenuOpenPage(wxCommandEvent& event);
        //*)

        /* Set the language menu radio option */
        void m_setLanguage();

        /**
         * \return true if the character is in the range of mosaics, not including A-Z.
         */
        bool isMosaic(char ch);


        wxSize m_fontSize[100];

        wxWindow* m_parentWindow;

        //(*Identifiers(wxTEDFrame)
        static const long ID_PANEL1;
        static const long idNewPage;
        static const long idNewFromTemplate;
        static const long idOpenPage;
        static const long idSavePage;
        static const long isSavePageAs;
        static const long idPublish;
        static const long idPublishSettings;
        static const long idExportTTX40;
        static const long isExportZxnet;
        static const long idMenuQuit;
        static const long idNewWindow;
        static const long idUndo;
        static const long idCut;
        static const long idCopy;
        static const long idPaste;
        static const long idSelectAll;
        static const long isInsertLine;
        static const long isDeleteLine;
        static const long idInsertPage;
        static const long idDeleteSubPage;
        static const long idLanguageEnglish;
        static const long idLanguageFrench;
        static const long idLanguageSwedish;
        static const long idLanguageCzechSlovak;
        static const long idLanguageGerman;
        static const long idLanguageSpanish;
        static const long idLanguageItalian;
        static const long idLanguageUnused;
        static const long ID_MENUITEM1;
        static const long ID_REGION0;
        static const long ID_REGION1;
        static const long ID_REGION2;
        static const long ID_REGION3;
        static const long ID_REGION4;
        static const long ID_REGION6;
        static const long ID_REGION8;
        static const long ID_REGION10;
        static const long ID_REGION;
        static const long idPageNumber;
        static const long ID_MENUITEMSHOWHEADER;
        static const long ID_HIDECONCEAL;
        static const long idSpecialKeys;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        static const long ID_SYMBOLPICKERDIALOG1;
        //*)

        static const long idMenuOpen;
        static const long idMenuClose;

        //(*Declarations(wxTEDFrame)
        wxFileDialog* FileDialogSaveAs;
        wxFileDialog* LoadPageFileDialog;
        wxMenu* Menu3;
        wxMenu* MenuItem2;
        wxMenu* MenuItemLanguage;
        wxMenu* MenuPresentation;
        wxMenuItem* MenuDeleteLine;
        wxMenuItem* MenuExportZxnet;
        wxMenuItem* MenuInsertLine;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItemConcealToggle;
        wxMenuItem* MenuItemCopy;
        wxMenuItem* MenuItemCzech;
        wxMenuItem* MenuItemDeletePage;
        wxMenuItem* MenuItemEnglish;
        wxMenuItem* MenuItemExportTTX40;
        wxMenuItem* MenuItemFrench;
        wxMenuItem* MenuItemGerman;
        wxMenuItem* MenuItemInsertSubpage;
        wxMenuItem* MenuItemItalian;
        wxMenuItem* MenuItemPageNumber;
        wxMenuItem* MenuItemPaste;
        wxMenuItem* MenuItemPublish;
        wxMenuItem* MenuItemPublishSettings;
        wxMenuItem* MenuItemRegion0;
        wxMenuItem* MenuItemRegion10;
        wxMenuItem* MenuItemRegion1;
        wxMenuItem* MenuItemRegion2;
        wxMenuItem* MenuItemRegion3;
        wxMenuItem* MenuItemRegion4;
        wxMenuItem* MenuItemRegion6;
        wxMenuItem* MenuItemRegion8;
        wxMenuItem* MenuItemSave;
        wxMenuItem* MenuItemSaveAs;
        wxMenuItem* MenuItemSelectAll;
        wxMenuItem* MenuItemShowHeader;
        wxMenuItem* MenuItemSpanish;
        wxMenuItem* MenuItemSpecialKeys;
        wxMenuItem* MenuItemSwedish;
        wxMenuItem* MenuItemTemplate;
        wxMenuItem* MenuItemUndo;
        wxMenuItem* MenuItemUnused;
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxSymbolPickerDialog* SymbolPickerDialog1;
        wxTimer m_Timer1;
        //*)

        DECLARE_EVENT_TABLE()
};

#ifdef __WXMSW__
int send(LPCTSTR ftp, LPCTSTR user, LPCTSTR pass, LPCTSTR pathondisk, LPTSTR nameonftp);
#endif // __WXMSW__

#endif // WXTEDMAIN_H
