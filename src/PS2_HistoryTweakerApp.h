/***************************************************************
 * Name:      PS2_HistoryTweakerApp.h
 * Purpose:   Defines Application Class
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-04-26
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#ifndef PS2_HISTORYTWEAKERAPP_H
#define PS2_HISTORYTWEAKERAPP_H

#include <wx/app.h>
#include "LNGTable.h"
class PS2_HistoryTweakerApp : public wxApp
{
    public:
        virtual bool OnInit();
    protected:
        wxLanguage m_lang = wxLANGUAGE_UNKNOWN;  // language specified by user
        wxLocale m_locale;  // locale we'll be using
};

#endif // PS2_HISTORYTWEAKERAPP_H
