#include "PaletteFrame.h"

//(*InternalHeaders(PaletteFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(PaletteFrame)
const wxWindowID PaletteFrame::ID_CHOICE1 = wxNewId();
const wxWindowID PaletteFrame::ID_PANEL1 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL1 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL2 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL3 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PaletteFrame,wxFrame)
  //(*EventTable(PaletteFrame)
  //*)
END_EVENT_TABLE()

PaletteFrame::PaletteFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
  wxBoxSizer* palSizer = new wxBoxSizer(wxVERTICAL);
  //(*Initialize(PaletteFrame)
  Create(0, wxID_ANY, _("Colour lookup tables"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(554,240));
  PaletteRemapChoice = new wxChoice(this, ID_CHOICE1, wxPoint(10,10), wxDLG_UNIT(this,wxSize(90,12)), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
  PaletteRemapChoice->SetSelection( PaletteRemapChoice->Append(_("Fore 0 Back 0")) );
  PaletteRemapChoice->Append(_("Fore 0 Back 1"));
  PaletteRemapChoice->Append(_("Fore 0 Back 2"));
  PaletteRemapChoice->Append(_("Fore 1 Back 1"));
  PaletteRemapChoice->Append(_("Fore 1 Back 2"));
  PaletteRemapChoice->Append(_("Fore 2 Back 1"));
  PaletteRemapChoice->Append(_("Fore 2 Back 2"));
  PaletteRemapChoice->Append(_("Fore 2 Back 3"));
  PaletteRemapChoice->SetMaxSize(wxSize(200,100));
  PaletteRemapChoice->SetToolTip(_("Choose the foreground and background colour look up tables"));
  ClutPanel1 = new wxPanel(this, ID_CLUTPANEL1, wxPoint(32,56), wxSize(496,32), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL1"));
  ClutPanel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
  Panel1 = new wxPanel(ClutPanel1, ID_PANEL1, wxPoint(24,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
  ClutPanel2 = new wxPanel(this, ID_CLUTPANEL2, wxPoint(32,96), wxSize(472,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL2"));
  ClutPanel3 = new wxPanel(this, ID_CLUTPANEL3, wxPoint(32,152), wxSize(496,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL3"));
  ClutPanel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
  ClutPanel4 = new wxPanel(this, ID_CLUTPANEL4, wxPoint(24,200), wxSize(504,32), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL4"));
  ColourDialog1 = new wxColourDialog(this);

  Connect(ID_CHOICE1, wxEVT_COMMAND_CHOICE_SELECTED, (wxObjectEventFunction)&PaletteFrame::OnChoice1Select);
  Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClosePalette);
  //*)
  palSizer->Add(PaletteRemapChoice, 0);
  palSizer->Add(ClutPanel1, 1, wxEXPAND);
  palSizer->Add(ClutPanel2, 1, wxEXPAND);
  palSizer->Add(ClutPanel3, 1, wxEXPAND);
  palSizer->Add(ClutPanel4, 1, wxEXPAND);

  cluts[0] = ClutPanel1;
  cluts[1] = ClutPanel2;
  cluts[2] = ClutPanel3;
  cluts[3] = ClutPanel4;

  SetSizer(palSizer);

  // Colour array

  for (unsigned int clut = 0; clut < 4; ++clut)
  {
    fgs[clut] = new wxBoxSizer(wxHORIZONTAL);
    for (int colour = 0; colour < 8; ++colour)
    {
      fgs[clut]->AddSpacer(10);
      fgs[clut]->Add( colours[clut][colour] = new wxButton(cluts[clut], wxID_ANY, wxString::Format("%d", colour)) );
    }
    cluts[clut]->SetSizer(fgs[clut]);
  }
}

PaletteFrame::~PaletteFrame()
{
  //(*Destroy(PaletteFrame)
  ColourDialog1->Destroy();
  //*)
}


void PaletteFrame::OnClosePalette(wxCloseEvent& event)
{
  Show(false);
}

void PaletteFrame::OnChoice1Select(wxCommandEvent& event)
{
}

void PaletteFrame::SetX28(TTXRow28* x28)
{
  x28row = x28;
  if (x28 == nullptr)
  {
    return;
  }
  // Copy clut colours to the GUI
  for (unsigned int clut = 0; clut < 4; ++clut)
  {
    for (unsigned int colour = 0; colour < 8; ++colour)
    {
      unsigned int clr = x28row->GetColour(clut, colour);
      unsigned int b = clr & 0x0f;
      unsigned int g = clr >> 4 & 0x0f;
      unsigned int r = clr >> 8 & 0x0f;
      // Stretch values
      r = r | r << 4;
      g = g | g << 4;
      b = b | b << 4;
      colours[clut][colour]->SetBackgroundColour(wxColour(r, g, b));
    }
  }
  this->Refresh();
}

