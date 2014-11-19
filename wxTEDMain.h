/***************************************************************
 * Name:      wxTEDMain.h
 * Purpose:   Defines Application Frame
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
#include <sstream>
#include "ttxpage.h"
#include "PageSettingsDialog.h"

// ftp
#include <wininet.h>
#pragma comment(lib, "wininet")

#include "c:\users\Peter\Documents\My Projects\ftplogin\ftplogin.h"

#ifndef _FTPLOGIN.H_
#define _FTPLOGIN.H_
// Obviously you move this section into your own ftplogin.h at the moment
// Longer term you put it in the persistent settings
#define FTP_SERVER   _T("your.ftp.server")
#define FTP_USER     _T("username")
#define FTP_PASSWORD _T("password")

#endif

class wxTEDFrame: public wxFrame
{
    public:

        wxTEDFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxTEDFrame();

    private:
        // Cursor
        wxPoint m_cursorPoint; /// Cursor location (in character coordinates)
        wxPoint m_subPixelPoint; /// Sub-pixel location when in graphics mode
        bool m_blinkToggle;  /// Blink state
        bool m_cursorIsAlpha; /// Selects graphics or alpha
        void m_SetStatus(); /// Shows cursor location and character info


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


        unsigned int m_ttxW; /// Font width
        unsigned int m_ttxH; /// Font height
        wxSize m_fontSize[100];

        wxWindow* m_parentWindow;

        //(*Identifiers(wxTEDFrame)
        static const long ID_PANEL1;
        static const long ID_NOTEBOOK1;
        static const long idNewPage;
        static const long idOpenPage;
        static const long idSavePage;
        static const long isSavePageAs;
        static const long idProperties;
        static const long idPublish;
        static const long idMenuQuit;
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
        static const long ID_MENUITEM1;
        static const long idPageNumber;
        static const long ID_MENUITEMSHOWHEADER;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(wxTEDFrame)
        wxMenu* MenuPresentation;
        wxMenuItem* MenuItemSpanish;
        wxMenuItem* MenuItemItalian;
        wxMenuItem* MenuItemCzech;
        wxNotebook* Notebook1;
        wxMenuItem* MenuItemSaveAs;
        wxMenu* Menu3;
        wxMenu* MenuItemLanguage;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItemDeletePage;
        wxMenuItem* MenuItemGerman;
        wxPanel* Panel1;
        wxMenuItem* MenuItemPageNumber;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItemSwedish;
        wxFileDialog* LoadPageFileDialog;
        wxMenuItem* MenuItemPublish;
        wxMenuItem* MenuItemInsertSubpage;
        wxMenuItem* MenuItemFrench;
        wxMenuItem* MenuItemShowHeader;
        wxMenuItem* MenuItemProperties;
        wxTimer m_Timer1;
        wxMenuItem* MenuItemEnglish;
        wxMenuItem* MenuItemUndo;
        wxFileDialog* FileDialogSaveAs;
        //*)

        DECLARE_EVENT_TABLE()
};

int send(LPCTSTR ftp, LPCTSTR user, LPCTSTR pass, LPCTSTR pathondisk, LPTSTR nameonftp);

#endif // WXTEDMAIN_H
