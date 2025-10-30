#ifndef PUBLISHSETUPDIALOG_H
#define PUBLISHSETUPDIALOG_H

//(*Headers(PublishSetupDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class PublishSetupDialog: public wxDialog
{
	public:

		PublishSetupDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PublishSetupDialog();

		//(*Declarations(PublishSetupDialog)
		wxButton* ButtonCancel;
		wxButton* ButtonOK;
		wxChoice* Choice1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxTextCtrl* TextCtrlFTPPassword;
		wxTextCtrl* TextCtrlFTPRemote;
		wxTextCtrl* TextCtrlFTPServer;
		wxTextCtrl* TextCtrlFTPUsername;
		//*)

	protected:

		//(*Identifiers(PublishSetupDialog)
		static const wxWindowID ID_CHOICE1;
		static const wxWindowID ID_STATICTEXT2;
		static const wxWindowID ID_STATICTEXT5;
		static const wxWindowID ID_STATICTEXT3;
		static const wxWindowID ID_STATICTEXT1;
		static const wxWindowID ID_TEXTCTRLFTPPASSWORD;
		static const wxWindowID ID_TEXTCTRLFTPREMOTE;
		static const wxWindowID ID_TEXTCTRLFTPSERVER;
		static const wxWindowID ID_TEXTCTRLUSERNAME;
		static const wxWindowID ID_STATICTEXT4;
		//*)

	private:

		//(*Handlers(PublishSetupDialog)
		void OnChoice1Select(wxCommandEvent& event);
		void OnButtonOKClick(wxCommandEvent& event);
		void OnButtonCancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
