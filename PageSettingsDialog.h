#ifndef PAGESETTINGSDIALOG_H
#define PAGESETTINGSDIALOG_H

//(*Headers(PageSettingsDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class PageSettingsDialog: public wxDialog
{
	public:

		PageSettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);

		void SetPageNumber(int page);

		virtual ~PageSettingsDialog();

		//(*Declarations(PageSettingsDialog)
		wxButton* ButtonCancel;
		wxButton* ButtonOK;
		wxCheckBox* CheckBoxC4ErasePage;
		wxCheckBox* CheckBoxC5Newsflash;
		wxCheckBox* CheckBoxC6Subtitle;
		wxCheckBox* CheckBoxC7SuppressHeader;
		wxCheckBox* CheckBoxC8Update;
		wxCheckBox* CheckBoxTransmitPage;
		wxRadioBox* RadioBoxCycleMode;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticTextLabel1;
		wxTextCtrl* TextCtrlCycleTime;
		wxTextCtrl* TextCtrlDescription;
		wxTextCtrl* TextCtrlFastext1;
		wxTextCtrl* TextCtrlFastext2;
		wxTextCtrl* TextCtrlFastext3;
		wxTextCtrl* TextCtrlFastext4;
		wxTextCtrl* TextCtrlFastextIndex;
		wxTextCtrl* TextCtrlPageNumber;
		//*)

	protected:

		//(*Identifiers(PageSettingsDialog)
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRLPAGENUMBER;
		static const long ID_TEXTCTRLDESCRIPTION;
		static const long ID_TEXTCTRLCYCLETIME;
		static const long ID_RADIOBOXCYCLE;
		static const long ID_CHECKBOXC4ERASEPAGE;
		static const long ID_CHECKBOXC5Newsflash;
		static const long ID_CHECKBOXTransmitPage;
		static const long ID_CHECKBOXC8UPDATE;
		static const long ID_CHECKBOXC7SuppressHeader;
		static const long ID_CHECKBOXC6Subtitle;
		static const long ID_TEXTCTRLFASTEXTLINK1;
		static const long ID_TEXTCTRLFASTEXTINDEX;
		static const long ID_TEXTCTRLFASTEXTLINK4;
		static const long ID_TEXTCTRLFASTEXTLINK3;
		static const long ID_TEXTCTRLFASTEXTLINK2;
		//*)

	private:

		//(*Handlers(PageSettingsDialog)
		void OnButtonOKClick(wxCommandEvent& event);
		void OnButtonCancelClick(wxCommandEvent& event);
		void OnRadioButtonTimedSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
