#ifndef PALETTEFRAME_H
#define PALETTEFRAME_H

//(*Headers(PaletteFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/colordlg.h>
#include <wx/frame.h>
#include <wx/panel.h>
//*)
#include <wx/sizer.h>
#include <wx/button.h>
#include "ttxrow28.h"


class PaletteFrame: public wxFrame
{
  public:

    PaletteFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~PaletteFrame();

    //(*Declarations(PaletteFrame)
    wxButton* Button1;
    wxButton* Button2;
    wxChoice* PaletteRemapChoice;
    wxColourDialog* ColourDialog1;
    wxPanel* ClutPanel1;
    wxPanel* ClutPanel2;
    wxPanel* ClutPanel3;
    wxPanel* ClutPanel4;
    //*)
    void SetX28(TTXRow28* x28); /// Save a pointer to Packet 28

  protected:

    //(*Identifiers(PaletteFrame)
    static const wxWindowID ID_CHOICE1;
    static const wxWindowID ID_COLOUR;
    static const wxWindowID ID_CLUTPANEL1;
    static const wxWindowID ID_CLUTPANEL2;
    static const wxWindowID ID_CLUTPANEL3;
    static const wxWindowID ID_CLUTPANEL4;
    static const wxWindowID ID_BUTTON1;
    //*)
    // static const wxWindowID ID_COLOUR;

  private:

    //(*Handlers(PaletteFrame)
    void OnClosePalette(wxCloseEvent& event);
    void OnChoice1Select(wxCommandEvent& event);
    void OnColourClick(wxCommandEvent& event);
    void OnClutPanel1MouseEnter(wxMouseEvent& event);
    void OnClutPanel1MouseLeave(wxMouseEvent& event);
    //*)
    wxBoxSizer* palSizer; // CLUT Layout
    wxBoxSizer* fgs[4]; // Colours Layout
    wxPanel* cluts[4];  // Pointers to each clut panel
    wxButton* colours[4][8]; // Four CLUTs with eight colours each
    TTXRow28* x28row;
    DECLARE_EVENT_TABLE()
};

wxColour Pal2wxColour(unsigned int pal);
unsigned int wxColour2Pal(wxColour wxc);

#endif
