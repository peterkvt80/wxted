#ifndef PAGESETTINGSDIALOG_H
#define PAGESETTINGSDIALOG_H

//(*Headers(PageSettingsDialog)
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class PageSettingsDialog: public wxDialog
{
	public:

		PageSettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);

		void SetPageNumber(int page);

		virtual ~PageSettingsDialog();

		//(*Declarations(PageSettingsDialog)
		wxStaticText* StaticTextLabel1;
		wxCheckBox* CheckBoxC5Newsflash;
		wxRadioBox* RadioBoxCycleMode;
		wxStaticText* StaticText2;
		wxCheckBox* CheckBoxC7SuppressHeader;
		wxButton* ButtonOK;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrlDescription;
		wxButton* ButtonCancel;
		wxTextCtrl* TextCtrlPageNumber;
		wxCheckBox* CheckBoxC8Update;
		wxCheckBox* CheckBoxC4ErasePage;
		wxCheckBox* CheckBoxC6Subtitle;
		wxCheckBox* CheckBoxTransmitPage;
		wxTextCtrl* TextCtrlCycleTime;
		//*)

	protected:

		//(*Identifiers(PageSettingsDialog)
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
