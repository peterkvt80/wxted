#ifndef HELPFRAME_H
#define HELPFRAME_H

//(*Headers(HelpFrame)
#include <wx/frame.h>
#include <wx/html/htmlwin.h>
//*)

class HelpFrame: public wxFrame
{
	public:

		HelpFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HelpFrame();

		//(*Declarations(HelpFrame)
		wxHtmlWindow* HtmlWindow1;
		//*)

	protected:

		//(*Identifiers(HelpFrame)
		static const long ID_HTMLWINDOW1;
		//*)

	private:

		//(*Handlers(HelpFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
