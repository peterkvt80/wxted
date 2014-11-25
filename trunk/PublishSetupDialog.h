#ifndef PUBLISHSETUPDIALOG_H
#define PUBLISHSETUPDIALOG_H

//(*Headers(PublishSetupDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class PublishSetupDialog: public wxDialog
{
	public:

		PublishSetupDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PublishSetupDialog();

		//(*Declarations(PublishSetupDialog)
		wxTextCtrl* TextCtrlFTPRemote;
		wxStaticText* StaticText2;
		wxTextCtrl* TextCtrlFTPUsername;
		wxButton* ButtonOK;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* ButtonCancel;
		wxTextCtrl* TextCtrlFTPServer;
		wxStaticText* StaticText5;
		wxTextCtrl* TextCtrlFTPPassword;
		wxStaticText* StaticText4;
		wxChoice* Choice1;
		//*)

	protected:

		//(*Identifiers(PublishSetupDialog)
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRLFTPPASSWORD;
		static const long ID_TEXTCTRLFTPREMOTE;
		static const long ID_TEXTCTRLFTPSERVER;
		static const long ID_TEXTCTRLUSERNAME;
		static const long ID_STATICTEXT4;
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
