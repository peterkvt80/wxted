#include "PaletteFrame.h"

//(*InternalHeaders(PaletteFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(PaletteFrame)
const wxWindowID PaletteFrame::ID_REMAP_CHOICE = wxNewId();
const wxWindowID PaletteFrame::ID_STATICTEXT0 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL1 = wxNewId();
const wxWindowID PaletteFrame::ID_STATICTEXT1 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL2 = wxNewId();
const wxWindowID PaletteFrame::ID_STATICTEXT2 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL3 = wxNewId();
const wxWindowID PaletteFrame::ID_STATICTEXT3 = wxNewId();
const wxWindowID PaletteFrame::ID_CLUTPANEL4 = wxNewId();
const wxWindowID PaletteFrame::ID_DEFAULT_BUTTON = wxNewId();
const wxWindowID PaletteFrame::ID_CHOICE1 = wxNewId();
const wxWindowID PaletteFrame::ID_ROW_COLOUR_PANEL = wxNewId();
const wxWindowID PaletteFrame::ID_PAGE_COLOUR_PANEL = wxNewId();
const wxWindowID PaletteFrame::ID_PAGE_COLOUR_CHOICE = wxNewId();
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
  PaletteRemapChoice = new wxChoice(this, ID_REMAP_CHOICE, wxPoint(0,0), wxDLG_UNIT(this,wxSize(90,12)), 0, 0, 0, wxDefaultValidator, _T("ID_REMAP_CHOICE"));
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
  StaticTextCLUT0 = new wxStaticText(ClutPanel1, ID_STATICTEXT0, _("CLUT 0: Foreground & Background"), wxPoint(0,16), wxSize(272,16), 0, _T("ID_STATICTEXT0"));
  StaticTextCLUT0->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
  ClutPanel2 = new wxPanel(this, ID_CLUTPANEL2, wxPoint(32,96), wxSize(472,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL2"));
  StaticTextCLUT1 = new wxStaticText(ClutPanel2, ID_STATICTEXT1, _("CLUT 0: Foreground & Background"), wxPoint(0,24), wxSize(272,16), 0, _T("ID_STATICTEXT1"));
  StaticTextCLUT1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
  ClutPanel3 = new wxPanel(this, ID_CLUTPANEL3, wxPoint(32,152), wxSize(496,40), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL3"));
  ClutPanel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
  StaticTextCLUT2 = new wxStaticText(ClutPanel3, ID_STATICTEXT2, _("CLUT 0: Foreground & Background"), wxPoint(0,24), wxSize(272,16), 0, _T("ID_STATICTEXT2"));
  StaticTextCLUT2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
  ClutPanel4 = new wxPanel(this, ID_CLUTPANEL4, wxPoint(24,200), wxSize(504,32), wxTAB_TRAVERSAL, _T("ID_CLUTPANEL4"));
  StaticTextCLUT3 = new wxStaticText(ClutPanel4, ID_STATICTEXT3, _("CLUT 0: Foreground & Background"), wxPoint(0,16), wxSize(272,16), 0, _T("ID_STATICTEXT3"));
  StaticTextCLUT3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
  DefaultsButton = new wxButton(this, ID_DEFAULT_BUTTON, _("Set defaults"), wxPoint(424,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_DEFAULT_BUTTON"));
  const wxString RowColourChoice_choices[] = {
  _T("0:0"),
  _T("0:1"),
  _T("0:2"),
  _T("0:3"),
  _T("0:4"),
  _T("0:5"),
  _T("0:6"),
  _T("0:7"),
  _T("1:0"),
  _T("1:1"),
  _T("1:2"),
  _T("1:3"),
  _T("1:4"),
  _T("1:5"),
  _T("1:6"),
  _T("1:7"),
  _T("2:0"),
  _T("2:1"),
  _T("2:2"),
  _T("2:3"),
  _T("2:4"),
  _T("2:5"),
  _T("2:6"),
  _T("2:7"),
  _T("3:0"),
  _T("3:1"),
  _T("3:2"),
  _T("3:3"),
  _T("3:4"),
  _T("3:5"),
  _T("3:6"),
  _T("3:7"),
  };
  RowColourChoice = new wxChoice(this, ID_CHOICE1, wxPoint(216,0), wxSize(64,23), 32, RowColourChoice_choices, 0, wxDefaultValidator, _T("ID_CHOICE1"));
  RowColourChoice->SetForegroundColour(wxColour(255,0,0));
  RowColourChoice->SetBackgroundColour(wxColour(0,255,0));
  RowColourPanel = new wxPanel(this, ID_ROW_COLOUR_PANEL, wxPoint(168,0), wxSize(40,20), wxFULL_REPAINT_ON_RESIZE, _T("ID_ROW_COLOUR_PANEL"));
  RowColourPanel->SetForegroundColour(wxColour(255,0,0));
  RowColourPanel->SetBackgroundColour(wxColour(0,255,0));
  PageColourPanel = new wxPanel(this, ID_PAGE_COLOUR_PANEL, wxPoint(288,0), wxSize(40,20), wxFULL_REPAINT_ON_RESIZE, _T("ID_PAGE_COLOUR_PANEL"));
  PageColourPanel->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
  PageColourPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
  PageColourChoice = new wxChoice(this, ID_PAGE_COLOUR_CHOICE, wxPoint(336,0), wxSize(72,23), 0, 0, 0, wxDefaultValidator, _T("ID_PAGE_COLOUR_CHOICE"));
  PageColourChoice->Append(_T("0:0"));
  PageColourChoice->Append(_T("0:1"));
  PageColourChoice->Append(_T("0:2"));
  PageColourChoice->Append(_T("0:3"));
  PageColourChoice->Append(_T("0:4"));
  PageColourChoice->Append(_T("0:5"));
  PageColourChoice->Append(_T("0:6"));
  PageColourChoice->Append(_T("0:7"));
  PageColourChoice->Append(_T("1:0"));
  PageColourChoice->Append(_T("1:1"));
  PageColourChoice->Append(_T("1:2"));
  PageColourChoice->Append(_T("1:3"));
  PageColourChoice->Append(_T("1:4"));
  PageColourChoice->Append(_T("1:5"));
  PageColourChoice->Append(_T("1:6"));
  PageColourChoice->Append(_T("1:7"));
  PageColourChoice->Append(_T("2:0"));
  PageColourChoice->Append(_T("2:1"));
  PageColourChoice->Append(_T("2:2"));
  PageColourChoice->Append(_T("2:3"));
  PageColourChoice->Append(_T("2:4"));
  PageColourChoice->Append(_T("2:5"));
  PageColourChoice->Append(_T("2:6"));
  PageColourChoice->Append(_T("2:7"));
  PageColourChoice->Append(_T("3:0"));
  PageColourChoice->Append(_T("3:1"));
  PageColourChoice->Append(_T("3:2"));
  PageColourChoice->Append(_T("3:3"));
  PageColourChoice->Append(_T("3:4"));
  PageColourChoice->Append(_T("3:5"));
  PageColourChoice->Append(_T("3:6"));
  PageColourChoice->Append(_T("3:7"));
  wxColourData __ColourData_1;
  __ColourData_1.SetColour(wxColour(128,0,255));
  ColourDialog1 = new wxColourDialog(this, &__ColourData_1);

  Connect(ID_REMAP_CHOICE, wxEVT_COMMAND_CHOICE_SELECTED, (wxObjectEventFunction)&PaletteFrame::OnChoiceRemapSelect);
  ClutPanel1->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseEnter, NULL, this);
  ClutPanel1->Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  ClutPanel2->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseEnter, NULL, this);
  ClutPanel3->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  ClutPanel4->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&PaletteFrame::OnClutPanel1MouseLeave, NULL, this);
  Connect(ID_DEFAULT_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&PaletteFrame::OnDefaultButtonClick);
  Connect(ID_CHOICE1, wxEVT_COMMAND_CHOICE_SELECTED, (wxObjectEventFunction)&PaletteFrame::OnRowColourChoiceSelect);
  Connect(ID_PAGE_COLOUR_CHOICE, wxEVT_COMMAND_CHOICE_SELECTED, (wxObjectEventFunction)&PaletteFrame::OnPageColourChoiceSelect);
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

  captions[0] = StaticTextCLUT0;
  captions[1] = StaticTextCLUT1;
  captions[2] = StaticTextCLUT2;
  captions[3] = StaticTextCLUT3;

  SetSizer(palSizer);

  // Colour array

  for (unsigned int clut = 0; clut < 4; ++clut)
  {
    // The eight colour swatches
    fgs[clut] = new wxBoxSizer(wxHORIZONTAL);
    for (int colour = 0; colour < 8; ++colour)
    {
      fgs[clut]->AddSpacer(10);
      wxButton* button = new wxButton(cluts[clut], wxID_ANY, wxString::Format("%d", colour), wxDefaultPosition, wxSize(28,28), wxBORDER_NONE);
      button->Enable(clut > 1);
      fgs[clut]->Add( colours[clut][colour] = button);
    }
    // Layout the swatches and the text
    clutSizer[clut] = new wxBoxSizer(wxVERTICAL);
    clutSizer[clut]-> Add(fgs[clut]);
    clutSizer[clut]-> Add(captions[clut]);
    // cluts[clut]->SetSizer(fgs[clut]);
    cluts[clut]-> SetSizer(clutSizer[clut]);
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
  x28row->SetRemap(choice); // Set the x28
  // Update the captions
  // Clear all the captions
  for (unsigned int i = 0; i<4; ++i)
  {
    captions[i]->SetLabel("");
    captions[i]->Show(false);
  }
  switch (choice)
  {
  case 0:
    captions[0]->Show();
    captions[0]->SetLabel("Foreground and background");
    break;
  case 1:
    captions[0]->SetLabel("Foreground");
    captions[0]->Show();
    captions[1]->SetLabel("Background");
    captions[1]->Show();
    break;
  case 2:
    captions[0]->SetLabel("Foreground");
    captions[0]->Show();
    captions[2]->SetLabel("Background");
    captions[2]->Show();
    break;
  case 3:
    captions[1]->Show();
    captions[1]->SetLabel("Foreground and background");
    break;
  case 4:
    captions[1]->SetLabel("Foreground");
    captions[1]->Show();
    captions[2]->SetLabel("Background");
    captions[2]->Show();
    break;
  case 5:
    captions[2]->Show();
    captions[2]->SetLabel("Foreground");
    captions[1]->Show();
    captions[1]->SetLabel("Background");
    break;
  case 6:
    captions[2]->Show();
    captions[2]->SetLabel("Foreground and background");
    break;
  case 7:
    captions[2]->SetLabel("Foreground");
    captions[2]->Show();
    captions[3]->SetLabel("Background");
    captions[3]->Show();
    break;
  }
}

void PaletteFrame::SetX28(TTXRow28* x28)
{
  x28row = x28;
  if (x28 == nullptr)
  {
    std::cout << "[PaletteFrame::SetX28] x28 is null :-(" << std::endl;
    return;
  }
  // Copy remap to the choice widget
  PaletteRemapChoice->SetSelection(x28row->GetRemap());

  UpdateDefaultRowColour();
  UpdateDefaultScreenColour();
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

  OnChoiceRemapSelect(*(new wxCommandEvent())); // Make sure the labels get updated
  this->Refresh();
}

template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(2)
         << std::hex << i;
  return stream.str();
}

void PaletteFrame::OnColourClick(wxCommandEvent& event)
{
  std::cout << "[PaletteFrame::OnColourClick] an event happened" << std::endl;
  // Which button did we click on?
  wxButton* button = static_cast<wxButton*>(event.GetEventObject());

  // No idea why the default button event comes here,
  // so redirect to the handler that we actually want.
  // Some mysterious way that wxID_ANY works?
  if (button == DefaultsButton)
  {
    OnDefaultButtonClick(event);
    return;
  }

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
    unsigned int colourVal = ((red & 0xf0) << 4) | ((green & 0xf0)) | (blue & 0xf0 >> 4);
    button->SetLabel(int_to_hex(colourVal));
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

void PaletteFrame::OnDefaultButtonClick(wxCommandEvent& event)
{
  x28row->defaultClut();
  x28row->SetRemap(0);
  // @todo black background substitution
  SetX28(x28row);
}

void PaletteFrame::OnRowColourChoiceSelect(wxCommandEvent& event)
{
  x28row->SetDefaultRowColour(event.GetInt());
  UpdateDefaultRowColour();
  this->Refresh();
}

void PaletteFrame::UpdateDefaultRowColour()   // Set up the row colour
{
  int x = x28row->GetDefaultRowColour();
  int clut = x >> 3;
  int colour = x & 0x07;
  unsigned int clr = x28row->GetColour(clut, colour);
  RowColourPanel->SetBackgroundColour(Pal2wxColour(clr));
}

void PaletteFrame::UpdateDefaultScreenColour()   // Set up the Screen colour
{
  int x = x28row->GetDefaultScreenColour();
  int clut = x >> 3;
  int colour = x & 0x07;
  unsigned int clr = x28row->GetColour(clut, colour);
  PageColourPanel->SetBackgroundColour(Pal2wxColour(clr));
}

void PaletteFrame::OnPageColourChoiceSelect(wxCommandEvent& event)
{
  x28row->SetDefaultScreenColour(event.GetInt());
  UpdateDefaultScreenColour();
  this->Refresh();
}
