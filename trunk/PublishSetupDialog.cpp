#include "PublishSetupDialog.h"

//(*InternalHeaders(PublishSetupDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PublishSetupDialog)
const long PublishSetupDialog::ID_CHOICE1 = wxNewId();
const long PublishSetupDialog::ID_STATICTEXT2 = wxNewId();
const long PublishSetupDialog::ID_STATICTEXT3 = wxNewId();
const long PublishSetupDialog::ID_STATICTEXT1 = wxNewId();
const long PublishSetupDialog::ID_TEXTCTRL1 = wxNewId();
const long PublishSetupDialog::ID_TEXTCTRLFTPSERVER = wxNewId();
const long PublishSetupDialog::ID_TEXTCTRLUSERNAME = wxNewId();
const long PublishSetupDialog::ID_STATICTEXT4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PublishSetupDialog,wxDialog)
	//(*EventTable(PublishSetupDialog)
	//*)
END_EVENT_TABLE()

PublishSetupDialog::PublishSetupDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PublishSetupDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(289,238));
	Move(wxDefaultPosition);
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(24,40), wxSize(168,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->SetSelection( Choice1->Append(_("FTP")) );
	Choice1->Append(_("TED Scheduler"));
	Choice1->Append(_("VBIT "));
	Choice1->Append(_("Local folder"));
	Choice1->Append(_("MRG Serial"));
	Choice1->Append(_("MRG Network"));
	Choice1->Append(_("Astet serial"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("FTP server"), wxPoint(24,72), wxSize(64,13), 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Password"), wxPoint(24,152), wxSize(64,13), 0, _T("ID_STATICTEXT3"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Username"), wxPoint(24,112), wxSize(64,13), 0, _T("ID_STATICTEXT1"));
	TextCtrlFTPPassword = new wxTextCtrl(this, ID_TEXTCTRL1, _("<password>"), wxPoint(88,152), wxSize(168,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrlFTPServer = new wxTextCtrl(this, ID_TEXTCTRLFTPSERVER, _("<server>"), wxPoint(88,72), wxSize(168,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFTPSERVER"));
	TextCtrlFTPUsername = new wxTextCtrl(this, ID_TEXTCTRLUSERNAME, _("<username>"), wxPoint(88,112), wxSize(168,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLUSERNAME"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Publish to..."), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxPoint(96,192), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(192,192), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&PublishSetupDialog::OnChoice1Select);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PublishSetupDialog::OnButtonOKClick);
	Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PublishSetupDialog::OnButtonCancelClick);
	//*)
}

PublishSetupDialog::~PublishSetupDialog()
{
	//(*Destroy(PublishSetupDialog)
	//*)
}


void PublishSetupDialog::OnChoice1Select(wxCommandEvent& event)
{
    // Perhaps we should put each method on a panel and just hide those? Don't know.
}

void PublishSetupDialog::OnButtonOKClick(wxCommandEvent& event)
{
    AcceptAndClose();
}

void PublishSetupDialog::OnButtonCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
