#include "HelpFrame.h"

//(*InternalHeaders(HelpFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HelpFrame)
const long HelpFrame::ID_HTMLWINDOW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HelpFrame,wxFrame)
	//(*EventTable(HelpFrame)
	//*)
END_EVENT_TABLE()

HelpFrame::HelpFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(HelpFrame)
	Create(parent, id, _("Special Keys"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxPoint(0,72), wxSize(344,384), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetPage(_("<html>\n\n<style>\nbody {\n  font-family: Helvetica, Arial, Sans-Serif;\n}\n\n</style>\n\n<body>\n<div style=\"border:2px black solid; display: inline-block;\">\n\t<span style=\"display: inline-block; background-color:#FFFFBB\">\n\t\t<b>Special keys</b><br/>\n\t\tPage Up - Show next page of carousel<br/>\n\t\tPage Down - Show previous page of carousel<br/>\n\t\tF11 - Hide/Reveal<br/>\n\t\tCTRL-Z - Undo<br/>\n\t\tAlt-Gr - Show control codes<br/>\n\t</span>\n</div>\n<div style=\"border:2px black solid; display: inline-block;\">\n\t<b>Text colours</b><br/>\n\t<span style=\"display: inline-block;\">\n\t\tShift-F1 - Red text<br/>\n\t\tShift-F2 - Green text<br/>\n\t\tShift-F3 - Yellow text<br/>\n\t\tShift-F4 - Blue text<br/>\n\t\tShift-F5 - Magenta text<br/>\n\t\tShift-F6 - Cyan text<br/>\n\t\tShift-F7 - White text<br/>\n\t\tShift-F8 - Black text (Level 2.5)<br/>\n\t</span>\n\t<b>Graphic colours</b>\tWhen the small graphics cursor is displayed then pressing space will toggle the pixel on and off. Also, the keys q,w,a,s,z,x toggle individual bits within a mosaic character<br/>\n\t<span style=\"display: inline-block; background-color:#BBBBBB\">\n\t\tCtrl-F1 - Graphics red<br/>\n\t\tCtrl-F2 - Graphics green<br/>\n\t\tCtrl-F3 - Graphics yellow<br/>\n\t\tCtrl-F4 - Graphics blue<br/>\n\t\tCtrl-F5 - Graphics magenta<br/>\n\t\tCtrl-F6 - Graphics cyan<br/>\n\t\tCtrl-F7 - Graphics white<br/>\n\t\tCtrl-F8 - Graphics black (Level 2.5)<br/>\n\t</span>\n</div>\n<div style=\"border:2px black solid; display: inline-block;\">\n\t<b>Effects</b><br/>\n\t<span style=\"display: inline-block; background-color:#BBBBBB\">\n\t\tCTRL-H - Flash<br/>\n\t\tCTRL-I - Steady<br/>\n\t\tCTRL-J - End Box<br/>\n\t\tCTRL-K - Start Box<br/>\n\t\tCTRL-L - Normal height<br/>\n\t\tCTRL-M (enter) - Double height<br/>\n\t\tCTRL-R - Conceal display<br/>\n\t\tCTRL-D - Contiguous graphics<br/>\n\t\tCTRL-T - Separated graphics<br/>\n\t\tCTRL-U - Black background<br/>\n\t\tCTRL-B - New background<br/>\n\t\tCTRL-W - Hold graphics<br/>\n\t\tCTRL-X - Release graphics<br/>\n                               <br/>\n                               CTRL-BACKSPACE - Delete Row<br/>\n\t</span>\n</div>\n\n</body>\n</html>"));

	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&HelpFrame::OnClose);
	//*)
}

HelpFrame::~HelpFrame()
{
	//(*Destroy(HelpFrame)
	//*)
}


void HelpFrame::OnClose(wxCloseEvent& event)
{
  Show(false);
}
