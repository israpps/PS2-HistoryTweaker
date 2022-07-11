/***************************************************************
 * Name:      PS2_HistoryTweakerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-04-26
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#include "PS2_HistoryTweakerApp.h"

//(*AppHeaders
#include "PS2_HistoryTweakerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PS2_HistoryTweakerApp);

bool PS2_HistoryTweakerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    PS2_HistoryTweakerFrame* Frame = new PS2_HistoryTweakerFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
