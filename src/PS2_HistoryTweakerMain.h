/***************************************************************
 * Name:      PS2_HistoryTweakerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-04-26
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

#ifndef PS2_HISTORYTWEAKERMAIN_H
#define PS2_HISTORYTWEAKERMAIN_H

//(*Headers(PS2_HistoryTweakerFrame)
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)
#include <wx/filedlg.h>

class PS2_HistoryTweakerFrame: public wxFrame
{
    public:

        PS2_HistoryTweakerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PS2_HistoryTweakerFrame();
		void RepopulateList(void);
    private:

        //(*Handlers(PS2_HistoryTweakerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnEntryListBeginDrag(wxListEvent& event);
        void OnOpenHistoryFileRequest(wxCommandEvent& event);
        void OnEntryListItemRightClick(wxListEvent& event);
        void OnClearEntryRequest(wxCommandEvent& event);
        void OnRefreshCounter(wxListEvent& event);
        void OnRemoveEntryRequest(wxCommandEvent& event);
        void OnItemCopy(wxCommandEvent& event);
        void OnItemPaste(wxCommandEvent& event);
        void OnentryEditRequest(wxCommandEvent& event);
        void OnSaveHistoryRequest(wxCommandEvent& event);
        //*)

        //(*Identifiers(PS2_HistoryTweakerFrame)
        static const long ID_LISTCTRL1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM7;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM6;
        //*)

        //(*Declarations(PS2_HistoryTweakerFrame)
        wxListCtrl* EntryList;
        wxMenu EntryListMenu;
        wxMenuItem* CTXMenPaste;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem9;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PS2_HISTORYTWEAKERMAIN_H
