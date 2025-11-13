#include "HelpFrame.h"

//(*InternalHeaders(HelpFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HelpFrame)
const wxWindowID HelpFrame::ID_HTMLWINDOW1 = wxNewId();
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
	HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxPoint(8,40), wxSize(344,384), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetPage(_("<html>\n\n<body>\n  <h1>Guide to Keyboard commands</h1>\n  <p>\n  These are the special keys that you can use for editing teletext pages. In many cases\n  you can also use edit.tf escapes.\n  </p>\n  \n<h2>Special keys</h2>\n\n<table>\n<tr><th>Key</th><th>Action</th></tr>\n<tr><td><b>Page Up</b></td><td>Show next page of carousel</td></tr>\n<tr><td><b>Page Down</b></td><td>Show previous page of carousel</td></tr>\n<tr><td><b>F11</b></td><td>Hide/Reveal</td></tr>\n<tr><td><b>ctrl-z</b></td><td>Undo</td></tr>\n<tr><td><b>esc q</b></td><td>Toggle show control codes (or Alt-Gr)</td></tr>\n</table>\n\n<h2>Text colours</h2>\n<table>\n<tr><th>Key</th><th>Action</th></tr>\n<tr><td><b>Shift-F1</b> or...<br/>esc r<br/>esc 1</td><td>Red text</td></tr>\n<tr><td><b>Shift-F2</b> or...<br/>esc g<br/>esc 2</td><td>Green text</td></tr>\n<tr><td><b>Shift-F3</b> or...<br/>esc y<br/>esc 3<td>Yellow text</td></tr>\n<tr><td><b>Shift-F4</b> or...<br/>esc b<br/>esc 4<td>Blue text</td></tr>\n<tr><td><b>Shift-F5</b> or...<br/>esc m<br/>esc 5<td>Magenta text</td></tr>\n<tr><td><b>Shift-F6</b> or...<br/>esc c<br/>esc 6<td>Cyan text</td></tr>\n<tr><td><b>Shift-F7</b> or...<br/>esc w<br/>esc 7<td>White text</td></tr>\n<tr><td><b>Shift-F8</b> or...<br/>esc k<br/>esc 0<td>Black text (Level 2.5)</td></tr>\n</table>\n\n<h2>Graphic colours</h2>\n<p>When the small graphics cursor is displayed then pressing space will toggle the pixel on and off.\nAlso, the keys q,w,a,s,z,x toggle individual bits within a mosaic character</p>\n<table>\n<tr><th>Key</th><th>Action</th></tr>\n<tr><td><b>Ctrl-F1</b> or...<br/>esc R<br/>esc !</td><td>Graphics Red</td></tr>\n<tr><td><b>Ctrl-F2</b> or...<br/>esc G<br/>esc \"</td><td>Graphics Green</td></tr>\n<tr><td><b>Ctrl-F3</b> or...<br/>esc Y<br/>esc £<td>Graphics Yellow</td></tr>\n<tr><td><b>Ctrl-F4</b> or...<br/>esc B<br/>esc $<td>Graphics Blue</td></tr>\n<tr><td><b>Ctrl-F5</b> or...<br/>esc M<br/>esc %<td>Graphics Magenta</td></tr>\n<tr><td><b>Ctrl-F6</b> or...<br/>esc C<br/>esc ^<td>Graphics Cyan</td></tr>\n<tr><td><b>Ctrl-F7</b> or...<br/>esc W<br/>esc &<td>Graphics White</td></tr>\n<tr><td><b>Ctrl-F8</b> or...<br/>esc K<br/>esc 0<td>Graphics Black (Level 2.5)</td></tr>\n</table>\n\n<h2>Effects</h2>\n<table>\n<tr><th>Key</th><th>Action</th></tr>\n<tr><td><b>CTRL-H</b> or...<br/>esc F</td><td>Flash</td></tr>\n<tr><td><b>CTRL-I</b> or...<br/>esc f</td><td>Steady</td></tr>\n<tr><td><b>CTRL-J</b></td><td>End Box</td></tr>\n<tr><td><b>CTRL-K</b></td><td>Start Box</td></tr>\n<tr><td><b>CTRL-L</b> or...<br/>esc d</td><td>Normal height</td></tr>\n<tr><td><b>CTRL-M (enter)</b> or...<br/>esc D</td><td>Double height</td></tr>\n<tr><td><b>CTRL-R</b> or...<br/>esc O</td><td>Conceal display</td></tr>\n<tr><td><b>CTRL-E</b> or...<br/>esc s</td><td>Contiguous graphics</td></tr>\n<tr><td><b>CTRL-T</b> or...<br/>esc S</td><td>Separated graphics</td></tr>\n<tr><td><b>CTRL-U</b> or...<br/>esc n</td><td>Black background</td></tr>\n<tr><td><b>CTRL-B</b> or...<br/>esc N</td><td>New background</td></tr>\n<tr><td><b>CTRL-W</b> or...<br/>esc H</td><td>Hold graphics</td></tr>\n<tr><td><b>CTRL-X</b> or...<br/>esc h</td><td>Release graphics</td></tr>\n<tr><td><b>esc ctrl-s</b></td><td>Toggle G0G2 languages</td></tr>\n</table>\n\n<h2>Rows</h2>\n<table>\n<tr><th>Key</th><th>Action</th></tr>\n<tr><td><b>Shift-F9</b> or...<br/>esc i</td><td>Insert row below</td></tr>\n<tr><td><b>Ctrl-F9</b> or...<br/>esc I</td><td>Delete row</td></tr>\n</table>\n\n</body>\n</html>"));

	Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&HelpFrame::OnClose);
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
