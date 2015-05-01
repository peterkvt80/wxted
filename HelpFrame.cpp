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
	HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxPoint(24,40), wxSize(344,384), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetPage(_("<html>\n\n<style>\nbody {\n  font-family: Helvetica, Arial, Sans-Serif;\n}\n\n</style>\n\n<body>\n<div style=\"border:2px black solid; display: inline-block;\">\n\t<span style=\"display: inline-block;\">\n\t\t<table>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F1</td><td>Red text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F2</td><td>Green text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F3</td><td>Yellow text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F4</td><td>Blue text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F5</td><td>Magenta text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F6</td><td>Cyan text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>Shift-F7</td><td>White text</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-H</td><td>Flash</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-I</td><td>Steady</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-J</td><td>End Box</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-K</td><td>Start Box<td/>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-L</td><td>Normal height</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-M (enter)</td><td>Double height</td>\n\t\t\t</tr>\n\t\t\t<tr>\n\t\t\t\t<td>CTRL-R</td><td>Conceal display</td>\n\t\t\t</tr>\n\t\t</table>\n\t</span>\n</div>\n<div style=\"border:2px black solid; display: inline-block;\">\n\t<span style=\"display: inline-block; background-color:grey\">\n\t\tCtrl-F1<br/>\n\t\tCtrl-F2<br/>\n\t\tCtrl-F3<br/>\n\t\tCtrl-F4<br/>\n\t\tCtrl-F5<br/>\n\t\tCtrl-F6<br/>\n\t\tCtrl-F7<br/>\n\t\tCTRL-Y<br/>\n\t\tCTRL-T<br/>\n\t\tCTRL-U<br/>\n\t\tCTRL-B<br/>\n\t\tCTRL-W<br/>\n\t\tCTRL-X<br/>\n\t\t.\n\t</span>\n\t<span style=\"display: inline-block; background-color:yellow\">\n\t\tRed graphic<br/>\n\t\tGreen graphic<br/>\n\t\tYellow graphic<br/>\n\t\tBlue graphic<br/>\n\t\tMagenta graphic<br/>\n\t\tCyan graphic<br/>\n\t\tWhite graphic<br/>\n\t\tContiguous graphics<br/>\n\t\tSeparated graphics<br/>\n\t\tBlack background<br/>\n\t\tNew background<br/>\n\t\tHold graphics<br/>\n\t\tRelease graphics<br/>\n\t\t.<br/>\n\t</span>\n</div>\n\tWhen the small graphics cursor is displayed then pressing space will toggle the pixel on and off.\n\n</body>\n</html>"));
	//*)
}

HelpFrame::~HelpFrame()
{
	//(*Destroy(HelpFrame)
	//*)
}

