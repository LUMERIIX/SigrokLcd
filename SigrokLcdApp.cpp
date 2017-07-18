/***************************************************************
 * Name:      SigrokLcdApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2017-05-31
 * Copyright:  ()
 * License:
 **************************************************************/

#include "SigrokLcdApp.h"

//(*AppHeaders
#include "SigrokLcdMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SigrokLcdApp);

bool SigrokLcdApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SigrokLcdFrame* Frame = new SigrokLcdFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
