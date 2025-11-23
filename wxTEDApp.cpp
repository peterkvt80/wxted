/***************************************************************
 * Name:      wxTEDApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-10-30
 * Copyright: Peter Kwan
 * License:
 **************************************************************/

#include "wxTEDApp.h"

//(*AppHeaders
#include "wxTEDMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxTEDApp);

bool wxTEDApp::OnInit()
{
    std::string str("wxtedsplash.tti");
    if (argc > 1)
    {
      if (argv[1].Len() > 0)
      {
        str = argv[1].ToStdString();
      }
      std::cerr << "[wxTEDApp::wxTEDApp] arg = " << str << std::endl;
    }
    // [!] Special note. The command line argument can be a tti file.
    // However, the instancing of wxTEDFrame is managed by wxSmith
    // so it is liable to break it by removing the str parameter.
    // wxSmith has been locked out by adding spaces to the AppInitialize markers
    // If wxTED launch by clicking on a .tti file isn't working
    // then make sure that the wxTEDFrame launch line looks like this:
    //  wxTEDFrame* Frame = new wxTEDFrame(nullptr, -1, str);

    // ( * AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
      wxTEDFrame* Frame = new wxTEDFrame(nullptr, -1, str);
      Frame->Show();
      SetTopWindow(Frame);
    }
    // * )

    return wxsOK;
}
