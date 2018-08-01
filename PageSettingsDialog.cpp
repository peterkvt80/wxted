#include "PageSettingsDialog.h"

//(*InternalHeaders(PageSettingsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PageSettingsDialog)
const long PageSettingsDialog::ID_STATICTEXT4 = wxNewId();
const long PageSettingsDialog::ID_STATICTEXT5 = wxNewId();
const long PageSettingsDialog::ID_STATICTEXT2 = wxNewId();
const long PageSettingsDialog::ID_STATICTEXT3 = wxNewId();
const long PageSettingsDialog::ID_STATICTEXT1 = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLPAGENUMBER = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLDESCRIPTION = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLCYCLETIME = wxNewId();
const long PageSettingsDialog::ID_RADIOBOXCYCLE = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXC4ERASEPAGE = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXC5Newsflash = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXTransmitPage = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXC8UPDATE = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXC7SuppressHeader = wxNewId();
const long PageSettingsDialog::ID_CHECKBOXC6Subtitle = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLFASTEXTLINK1 = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLFASTEXTLINK2 = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLFASTEXTLINK3 = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLFASTEXTLINK4 = wxNewId();
const long PageSettingsDialog::ID_TEXTCTRLFASTEXTINDEX = wxNewId();
//*)

BEGIN_EVENT_TABLE(PageSettingsDialog,wxDialog)
	//(*EventTable(PageSettingsDialog)
	//*)
END_EVENT_TABLE()

PageSettingsDialog::PageSettingsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PageSettingsDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(397,278));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Page number"), wxPoint(8,16), wxSize(72,16), 0, _T("ID_STATICTEXT4"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Links:"), wxPoint(8,184), wxSize(32,16), 0, _T("ID_STATICTEXT5"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Index"), wxPoint(8,240), wxSize(32,16), 0, _T("ID_STATICTEXT2"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Description"), wxPoint(8,48), wxSize(72,16), 0, _T("ID_STATICTEXT3"));
	StaticTextLabel1 = new wxStaticText(this, ID_STATICTEXT1, _("Cycle time"), wxPoint(8,88), wxSize(72,16), 0, _T("ID_STATICTEXT1"));
	TextCtrlPageNumber = new wxTextCtrl(this, ID_TEXTCTRLPAGENUMBER, _("10000"), wxPoint(88,16), wxSize(56,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLPAGENUMBER"));
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxPoint(184,240), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonOK->SetHelpText(_("Keep the current settings"));
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(272,240), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	TextCtrlDescription = new wxTextCtrl(this, ID_TEXTCTRLDESCRIPTION, _("Text"), wxPoint(88,48), wxSize(304,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLDESCRIPTION"));
	TextCtrlCycleTime = new wxTextCtrl(this, ID_TEXTCTRLCYCLETIME, _("8"), wxPoint(88,88), wxSize(72,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLCYCLETIME"));
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Cycled"),
		_("Timed")
	};
	RadioBoxCycleMode = new wxRadioBox(this, ID_RADIOBOXCYCLE, _("Mode"), wxPoint(0,120), wxSize(88,56), 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOXCYCLE"));
	RadioBoxCycleMode->SetSelection(1);
	CheckBoxC4ErasePage = new wxCheckBox(this, ID_CHECKBOXC4ERASEPAGE, _("C4 Erase Page"), wxPoint(192,88), wxSize(150,13), 0, wxDefaultValidator, _T("ID_CHECKBOXC4ERASEPAGE"));
	CheckBoxC4ErasePage->SetValue(false);
	CheckBoxC5Newsflash = new wxCheckBox(this, ID_CHECKBOXC5Newsflash, _("C5 Newsflash"), wxPoint(192,112), wxSize(150,13), 0, wxDefaultValidator, _T("ID_CHECKBOXC5Newsflash"));
	CheckBoxC5Newsflash->SetValue(false);
	CheckBoxC6Subtitle = new wxCheckBox(this, ID_CHECKBOXC6Subtitle, _("C6 Subtitle"), wxPoint(192,136), wxSize(150,13), 0, wxDefaultValidator, _T("ID_CHECKBOXC6Subtitle"));
	CheckBoxC6Subtitle->SetValue(false);
	CheckBoxC7SuppressHeader = new wxCheckBox(this, ID_CHECKBOXC7SuppressHeader, _("C7 Suppress Header"), wxPoint(192,160), wxSize(150,13), 0, wxDefaultValidator, _T("ID_CHECKBOXC7SuppressHeader"));
	CheckBoxC7SuppressHeader->SetValue(false);
	CheckBoxC8Update = new wxCheckBox(this, ID_CHECKBOXC8UPDATE, _("C8 Update"), wxPoint(192,184), wxSize(150,13), 0, wxDefaultValidator, _T("ID_CHECKBOXC8UPDATE"));
	CheckBoxC8Update->SetValue(false);
	CheckBoxTransmitPage = new wxCheckBox(this, ID_CHECKBOXTransmitPage, _("Transmit Page"), wxPoint(192,208), wxSize(104,13), 0, wxDefaultValidator, _T("ID_CHECKBOXTransmitPage"));
	CheckBoxTransmitPage->SetValue(false);
	TextCtrlFastext1 = new wxTextCtrl(this, ID_TEXTCTRLFASTEXTLINK1, _("100"), wxPoint(8,208), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFASTEXTLINK1"));
	TextCtrlFastext1->SetBackgroundColour(wxColour(255,174,174));
	TextCtrlFastext2 = new wxTextCtrl(this, ID_TEXTCTRLFASTEXTLINK2, _("100"), wxPoint(48,208), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFASTEXTLINK2"));
	TextCtrlFastext2->SetBackgroundColour(wxColour(184,249,181));
	TextCtrlFastext3 = new wxTextCtrl(this, ID_TEXTCTRLFASTEXTLINK3, _("100"), wxPoint(88,208), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFASTEXTLINK3"));
	TextCtrlFastext3->SetBackgroundColour(wxColour(249,253,176));
	TextCtrlFastext4 = new wxTextCtrl(this, ID_TEXTCTRLFASTEXTLINK4, _("100"), wxPoint(128,208), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFASTEXTLINK4"));
	TextCtrlFastext4->SetBackgroundColour(wxColour(177,249,252));
  TextCtrlFastextIndex = new wxTextCtrl(this, ID_TEXTCTRLFASTEXTINDEX, _("100"), wxPoint(48,240), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLFASTEXTINDEX"));

	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PageSettingsDialog::OnButtonOKClick);
	Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PageSettingsDialog::OnButtonCancelClick);
	//*)
}

PageSettingsDialog::~PageSettingsDialog()
{
    std::cout << "PageSettingsDialog ~ Bye bye dialog...." << std::endl;
	//(*Destroy(PageSettingsDialog)
	//*)
}

void PageSettingsDialog::OnButtonOKClick(wxCommandEvent& event)
{
    AcceptAndClose();
}

void PageSettingsDialog::OnButtonCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
