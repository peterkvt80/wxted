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
	HtmlWindow1->SetPage(_("<!DOCTYPE html>\n<html>\n<header>\n<meta charset=\"UTF-8\">\n</header>\n\n<style>\nbody {\n  font-family: Teletext2, Helvetica, Arial, Sans-Serif;\n  background-color: black;\n  color: white;\n}\n.black {color:black;background-color:white;}\n.red {color:red;background-color:white}\n.green {color:#00ff00;}\n.yellow {color:yellow;}\n.blue {color:blue;background-color:white;}\n.magenta {color:magenta;}\n.cyan {color:cyan;}\n.white {color:white;}\n.panel {\n  display: inline-block;\n  background-color:#666666\"\n}\n\n</style>\n\n<body>\n<div>\n\t<span class=\"panel\" >\n\t\t<b style=\"color:yellow;\">SPECIAL KEYS</b><br/>\n\t\tPage Up - Show next page of carousel<br/>\n\t\tPage Down - Show previous page of carousel<br/>\n\t\tF11 - Hide/Reveal<br/>\n\t\tCTRL-Z - Undo<br/>\n\t\tAlt-Gr - Show control codes<br/>\n\t</span>\n</div>\n<div>\n\t<b style=\"color:yellow;\">TEXT COLOURS</b><br/>\n\t<span class=\"panel\">\n\t\t<span class=\"red\">A</span> Shift-F1 - Red text<br/>\n\t\t<span class=\"green\">A</span> Shift-F2 - Green text<br/>\n\t\t<span class=\"yellow\">A</span> Shift-F3 - Yellow text<br/>\n\t\t<span class=\"blue\">A</span> Shift-F4 - Blue text<br/>\n\t\t<span class=\"magenta\">A</span> Shift-F5 - Magenta text<br/>\n\t\t<span class=\"cyan\">A</span> Shift-F6 - Cyan text<br/>\n\t\t<span class=\"white\">A</span> Shift-F7 - White text<br/>\n\t\t<span class=\"black\">A</span> Shift-F8 - Black text<br/>\n\t</span><br/>\n\t<b style=\"color:yellow;\">GRAPHIC COLOURS</b><br/>\n\tWhen the small graphics cursor is displayed then pressing space will toggle the pixel on and off.<br/>\n\t<span class=\"panel\" >\n\t\t<span class=\"red\">&#xe69b;</span> Ctrl-F1 - Graphics red<br/>\n\t\t<span class=\"green\">&#xe69b;</span> Ctrl-F2 - Graphics green<br/>\n\t\t<span class=\"yellow\">&#xe69b;</span> Ctrl-F3 - Graphics yellow<br/>\n\t\t<span class=\"blue\">&#xe69b;</span> Ctrl-F4 - Graphics blue<br/>\n\t\t<span class=\"magenta\">&#xe69b;</span> Ctrl-F5 - Graphics magenta<br/>\n\t\t<span class=\"cyan\">&#xe69b;</span> Ctrl-F6 - Graphics cyan<br/>\n\t\t<span class=\"white\">&#xe69b;</span> Ctrl-F7 - Graphics white<br/>\n\t\t<span class=\"black\">&#xe69b;</span> Ctrl-F8 - Graphics black<br/>\n\t</span>\n</div>\n<div class=\"panel\">\n\t<b style=\"color:yellow;\">EFFECTS</b><br/>\n\t<span>\n\t\tCTRL-H - Flash<br/>\n\t\tCTRL-I - Steady<br/>\n\t\tCTRL-J - End Box<br/>\n\t\tCTRL-K - Start Box<br/>\n\t\tCTRL-L - Normal height<br/>\n\t\tCTRL-M (enter) - Double height<br/>\n\t\tCTRL-R - Conceal display<br/>\n\t\tCTRL-Y - Contiguous graphics<br/>\n\t\tCTRL-T - Separated graphics<br/>\n\t\tCTRL-U - Black background<br/>\n\t\tCTRL-B - New background<br/>\n\t\tCTRL-W - Hold graphics<br/>\n\t\tCTRL-X - Release graphics<br/>\n\t</span>\n</div>\n\n</body>\n</html>"));
	//*)
}

HelpFrame::~HelpFrame()
{
	//(*Destroy(HelpFrame)
	//*)
}

