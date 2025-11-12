#ifndef PALETTEFRAME_H
#define PALETTEFRAME_H

//(*Headers(PaletteFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/colordlg.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
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
    wxButton* DefaultsButton;
    wxCheckBox* BlackBGSubCheckBox;
    wxChoice* PageColourChoice;
    wxChoice* PaletteRemapChoice;
    wxChoice* RowColourChoice;
    wxColourDialog* ColourDialog1;
    wxPanel* ClutPanel1;
    wxPanel* ClutPanel2;
    wxPanel* ClutPanel3;
    wxPanel* ClutPanel4;
    wxPanel* PageColourPanel;
    wxPanel* RowColourPanel;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticTextCLUT0;
    wxStaticText* StaticTextCLUT1;
    wxStaticText* StaticTextCLUT2;
    wxStaticText* StaticTextCLUT3;
    //*)
    void SetX28(TTXRow28* x28); /// Save a pointer to Packet 28

    void UpdateDefaultRowColour();   /// Draw the row colour
    void UpdateDefaultScreenColour();   /// Draw the screen colour

  protected:

    //(*Identifiers(PaletteFrame)
    static const wxWindowID ID_REMAP_CHOICE;
    static const wxWindowID ID_STATICTEXT0;
    static const wxWindowID ID_CLUTPANEL1;
    static const wxWindowID ID_STATICTEXT1;
    static const wxWindowID ID_CLUTPANEL2;
    static const wxWindowID ID_STATICTEXT2;
    static const wxWindowID ID_CLUTPANEL3;
    static const wxWindowID ID_STATICTEXT3;
    static const wxWindowID ID_CLUTPANEL4;
    static const wxWindowID ID_DEFAULT_BUTTON;
    static const wxWindowID ID_CHOICE1;
    static const wxWindowID ID_ROW_COLOUR_PANEL;
    static const wxWindowID ID_PAGE_COLOUR_PANEL;
    static const wxWindowID ID_PAGE_COLOUR_CHOICE;
    static const wxWindowID ID_BLACKBGCHECKBOX;
    static const wxWindowID ID_STATICTEXT4;
    static const wxWindowID ID_STATICTEXT5;
    //*)
    // static const wxWindowID ID_COLOUR;

  private:

    //(*Handlers(PaletteFrame)
    void OnClosePalette(wxCloseEvent& event);
    void OnChoiceRemapSelect(wxCommandEvent& event);
    void OnColourClick(wxCommandEvent& event);
    void OnClutPanel1MouseEnter(wxMouseEvent& event);
    void OnClutPanel1MouseLeave(wxMouseEvent& event);
    void OnDefaultButtonClick(wxCommandEvent& event);
    void OnPaletteRemapChoiceSelect(wxCommandEvent& event);
    void OnRowColourChoiceSelect(wxCommandEvent& event);
    void OnPageColourChoiceSelect(wxCommandEvent& event);
    void OnBlackBGSubCheckBoxClick(wxCommandEvent& event);
    //*)
    wxBoxSizer* palSizer; // CLUT Layout
    wxBoxSizer* clutSizer[4]; // fgs Colours and caption text
    wxBoxSizer* fgs[4]; // Colours Layout
    wxPanel* cluts[4];  // Pointers to each clut panel
    wxStaticText* captions[4]; // One caption per clut
    wxButton* colours[4][8]; // Four CLUTs with eight colours each
    TTXRow28* x28row;
    DECLARE_EVENT_TABLE()
};

wxColour Pal2wxColour(unsigned int pal);
unsigned int wxColour2Pal(wxColour wxc);

#endif
