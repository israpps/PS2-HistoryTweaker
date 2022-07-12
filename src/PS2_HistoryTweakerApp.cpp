/***************************************************************
 * Name:      PS2_HistoryTweakerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-04-26
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#include "PS2_HistoryTweakerApp.h"
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/intl.h>
//(*AppHeaders
#include "PS2_HistoryTweakerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PS2_HistoryTweakerApp);
extern int LNGID;
bool PS2_HistoryTweakerApp::OnInit()
{

    wxFileName fname( wxTheApp->argv[0] );
    wxString ARGV_0 = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);

    wxString config_file = ARGV_0 + "PS2-HistoryTweaker.INI";
    wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, config_file);
    if ( m_lang == wxLANGUAGE_UNKNOWN )
    {
        main_config->Read("PS2-HistoryTweaker/LANGUAGE", &LNGID, 0);
        m_lang = LNGID == 0 ? wxLANGUAGE_DEFAULT : langIds[LNGID];
        std::cout <<"Loading lang ID ["<< LNGID <<"]\n";
    }

    if ( !m_locale.Init(m_lang, wxLOCALE_DONT_LOAD_DEFAULT) )
        wxLogWarning(_("This language is not supported by the system."));

    wxLocale::AddCatalogLookupPathPrefix("./Lang");
    const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_lang);
    if (!m_locale.AddCatalog("PS2-HistoryTweaker"))///add program specific catalog
    {
        wxLogError(_("Couldn't find/load the 'PS2-HistoryTweaker' catalog for locale '%s'.\nThe translation file must be placed here: \"Lang\\%s\\PS2-HistoryTweaker.mo\""),
                   pInfo ? pInfo->GetLocaleName() : "unknown",
                   m_locale.GetCanonicalName());
    }
    if (!m_locale.AddCatalog("wxstd"))///add wxwidgets standard catalog
    {
        std::cerr << "can't find wxstd.mo\n";
    }




    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    PS2_HistoryTweakerFrame* Frame = new PS2_HistoryTweakerFrame(0, m_locale);
    Frame->Show();
    SetTopWindow(Frame);
    }

    return wxsOK;

}
