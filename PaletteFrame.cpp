#include "PaletteFrame.h"

//(*InternalHeaders(PaletteFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(PaletteFrame)
const wxWindowID PaletteFrame::ID_REMAP_CHOICE = wxNewId();
const wxWindowID PaletteFrame::ID_COLOUR = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL1 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL2 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL3 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL4 = wxNewId();
const wxWindowID PaletteFrame::ID_BUTTON1 = wxNewId();
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
  PaletteRemapChoice = new wxChoice(this, ID_REMAP_CHOICE, wxPoint(10,10), wxDLG_UNIT(this,wxSize(90,12)), 0, 0, 0, wxDefaultValidator, _T("ID_REMAP_CHOICE"));
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
  Button2 = new wxButton(ClutPanel1, ID_COLOUR, _("F0F"), wxPoint(56,8), wxSize(28,28), 0, wxDefaultValidator, _T("ID_COLOUR"));
  Button2->Disable();
  Button2->Hide();
  ClutPanel2 = new wxPanel(this, ID_CLUTPANEL2, wxPoint(32,96), wxSize(472,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL2"));
  ClutPanel3 = new wxPanel(this, ID_CLUTPANEL3, wxPoint(32,152), wxSize(496,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL3"));
  ClutPanel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
  ClutPanel4 = new wxPanel(this, ID_CLUTPANEL4, wxPoint(24,200), wxSize(504,32), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL4"));
  Button1 = new wxButton(this, ID_BUTTON1, _("Label"), wxPoint(232,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
  wxColourData __ColourData_1;
  __ColourData_1.SetColour(wxColour(128,0,255));
  ColourDialog1 = new wxColourDialog(this, &__ColourData_1);

  Connect(ID_REMAP_CHOICE, wxEVT_COMMAND_CHOICE_SELECTED, (wxObjectEventFunction)&PaletteFrame::OnChoiceRemapSelect);
  Connect(ID_COLOUR, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&PaletteFrame::OnColourClick);
  ClutPanel1->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseEnter, NULL, this);
  ClutPanel1->Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  ClutPanel2->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseEnter, NULL, this);
  ClutPanel3->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  ClutPanel4->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClosePalette);
  Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave);
  //*)
  Connect(wxID_ANY, wxEVT_BUTTON, (wxObjectEventFunction)&PaletteFrame::OnColourClick);
  palSizer->Add(PaletteRemapChoice, 0);
  palSizer->AddSpacer(10);
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
      wxButton* button = new wxButton(cluts[clut], wxID_ANY, wxString::Format("%d", colour), wxDefaultPosition, wxSize(28,28), wxBORDER_NONE);
      button->Enable(clut > 1);
      fgs[clut]->Add( colours[clut][colour] = button);
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

void PaletteFrame::OnChoiceRemapSelect(wxCommandEvent& event)
{
  // Get the remap number 0..7
  unsigned int choice = PaletteRemapChoice->GetSelection();
  x28row->SetRemap(choice);
  // Set the x28
}

void PaletteFrame::SetX28(TTXRow28* x28)
{
  x28row = x28;
  if (x28 == nullptr)
  {
    return;
  }
  // Copy remap to the choice widget
  PaletteRemapChoice->SetSelection(x28row->GetRemap());

  // Copy clut colours to the GUI
  for (unsigned int clut = 0; clut < 4; ++clut)
  {
    for (unsigned int colour = 0; colour < 8; ++colour)
    {
      unsigned int clr = x28row->GetColour(clut, colour);
      wxColour wxc = Pal2wxColour(clr);
      colours[clut][colour]->SetBackgroundColour(wxc);
    }
  }
  this->Refresh();
}


void PaletteFrame::OnColourClick(wxCommandEvent& event)
{
  std::cout << "[PaletteFrame::OnColourClick] an event happened" << std::endl;
  // Which button did we click on?
  wxButton* button = static_cast<wxButton*>(event.GetEventObject());
  // What colour is it?
  auto clr = button->GetBackgroundColour();

  wxColourData wxcd;
  wxcd.SetColour(clr);
  wxColourDialog* ColourDialog = new wxColourDialog(this, &wxcd);
  if (ColourDialog->ShowModal() == wxID_OK)
  {
    wxColour clr2 = ColourDialog->GetColourData().GetColour();
    unsigned int red = static_cast<unsigned char>(clr2.Red());
    unsigned int green = static_cast<unsigned char>(clr2.Green());
    unsigned int blue = static_cast<unsigned char>(clr2.Blue());
    std::cout << "red = " << red << " green = " << green << " blue = " << blue << std::endl;
    // Put this colour back into the CLUT GUI
    button->SetBackgroundColour(clr2);
    // Put this colour into the X28 CLUT
    // Get the clut and colour of the button
    unsigned int clut;
    unsigned int colour;
    for (clut = 0; clut < 4; ++clut)
    {
      for (colour = 0; colour < 8; ++colour)
      {
          if (colours[clut][colour] == button)
          {
            break;
          }
      }
      if (colours[clut][colour] == button)
      {
        break;
      }
    }
    std::cout << "Found button, clut = " << clut << " colour = " << colour << std::endl;
    unsigned int colourVal = ((red & 0x0f) << 8) | ((green & 0x0f) << 4) | (blue & 0x0f);
    x28row->SetColour(colourVal, clut, colour);
  }
}

wxColour Pal2wxColour(unsigned int pal)
{
  unsigned int b = pal & 0x0f;
  unsigned int g = pal >> 4 & 0x0f;
  unsigned int r = pal >> 8 & 0x0f;
  // Stretch values
  r = r | r << 4;
  g = g | g << 4;
  b = b | b << 4;
  return wxColour(r, g, b);
}

unsigned int wxColour2Pal(wxColour wxc)
{
  return 0; // @todo
}

void PaletteFrame::OnClutPanel1MouseEnter(wxMouseEvent& event)
{
  // Set the cursor to unclickable
  SetCursor(wxCURSOR_NO_ENTRY );
}

void PaletteFrame::OnClutPanel1MouseLeave(wxMouseEvent& event)
{
  // Set the cursor to normal
  SetCursor(*wxSTANDARD_CURSOR);
}
