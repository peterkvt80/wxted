/***************************************************************
 * Name:      wxTEDMain.h
 * Purpose:   Defines Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan (http://www.teastop.co.uk)
 * License:
 *
 * Copyright (C) 2014-2016, Peter Kwan
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

#ifndef WXTEDMAIN_H
#define WXTEDMAIN_H

//(*Headers(wxTEDFrame)
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
//*)
#include <wx/clipbrd.h>
#include <wx/config.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
/*
<wx/confbase.h> - Base config class.
<wx/fileconf.h> - wxFileConfig class.
<wx/msw/regconf.h> - wxRegConfig class, see also wxRegKey.
*/

#include "HelpFrame.h"
#include <sstream>
#include "ttxpage.h"
#include "PageSettingsDialog.h"
#include "mapchar.h"

// Version number
#define VERSION_STRING   wxT("1.24")

// ftp
#include <wininet.h>
#pragma comment(lib, "wininet")

// Publish setup
#include "PublishSetupDialog.h"

// Export to teletext40
#include "teletext40.h"

class wxTEDFrame: public wxFrame
{
    public:

        wxTEDFrame(wxWindow* parent,wxWindowID id = -1, wxString initialPage="BBC100.tti");
        virtual ~wxTEDFrame();
        inline TTXPage* Page(){return m_rootPage;};

    private:

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

        wxClipboard *m_clip;

        // Page
        TTXPage* m_rootPage; /// This is the root page used for load/save
        TTXPage* m_currentPage; /// This may point to a sub-page and is the page currently viewed and edited
        void m_resize(wxSize event);
        wchar_t mapTextChar(wchar_t ch);  /// Maps a teletext character to a teletext2 font if they aren't the same

        int iPageCount;     // How many pages in this set?
        int iPage;          // Which page are we looking at?

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
        //*)
        /* Manually added handlers */
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        void OnChar(wxKeyEvent& event);
        void OnTimer(wxTimerEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        /* Manually added menu handlers */
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);

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
        static const long ID_NOTEBOOK1;
        static const long idNewPage;
        static const long idOpenPage;
        static const long idSavePage;
        static const long isSavePageAs;
        static const long idPublish;
        static const long idPublishSettings;
        static const long idExportTTX40;
        static const long idMenuQuit;
        static const long idNewWindow;
        static const long idUndo;
        static const long idCut;
        static const long idCopy;
        static const long idPaste;
        static const long idSelectAll;
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
        //*)

        //(*Declarations(wxTEDFrame)
        wxMenu* MenuPresentation;
        wxMenu* MenuItem2;
        wxMenuItem* MenuItemSpanish;
        wxMenuItem* MenuItemExportTTX40;
        wxMenuItem* MenuItemRegion0;
        wxMenuItem* MenuItemItalian;
        wxMenuItem* MenuItemSave;
        wxMenuItem* MenuItemCzech;
        wxNotebook* Notebook1;
        wxMenuItem* MenuItemSaveAs;
        wxMenuItem* MenuItemPublishSettings;
        wxMenuItem* MenuItemSpecialKeys;
        wxMenu* Menu3;
        wxMenu* MenuItemLanguage;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItemDeletePage;
        wxMenuItem* MenuItemRegion6;
        wxMenuItem* MenuItemGerman;
        wxPanel* Panel1;
        wxMenuItem* MenuItemRegion10;
        wxMenuItem* MenuItemPageNumber;
        wxMenuItem* MenuItemRegion2;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItemConcealToggle;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItemSelectAll;
        wxMenuItem* MenuItemSwedish;
        wxFileDialog* LoadPageFileDialog;
        wxMenuItem* MenuItemCopy;
        wxMenuItem* MenuItemRegion1;
        wxMenuItem* MenuItemPublish;
        wxMenuItem* MenuItemInsertSubpage;
        wxMenuItem* MenuItemRegion4;
        wxMenuItem* MenuItemRegion8;
        wxMenuItem* MenuItemFrench;
        wxMenuItem* MenuItemRegion3;
        wxMenuItem* MenuItemShowHeader;
        wxMenuItem* MenuItemUnused;
        wxMenuItem* MenuItemPaste;
        wxTimer m_Timer1;
        wxMenuItem* MenuItemEnglish;
        wxMenuItem* MenuItemUndo;
        wxFileDialog* FileDialogSaveAs;
        //*)

        DECLARE_EVENT_TABLE()
};

int send(LPCTSTR ftp, LPCTSTR user, LPCTSTR pass, LPCTSTR pathondisk, LPTSTR nameonftp);

#endif // WXTEDMAIN_H
