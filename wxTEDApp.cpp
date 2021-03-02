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
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxTEDFrame* Frame;
        if (wxApp::argc>1)
            Frame = new wxTEDFrame(0,-1,wxApp::argv[1]);
        else
            Frame = new wxTEDFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
