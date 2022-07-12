/***************************************************************
 * Name:      PS2_HistoryTweakerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matias Israelson (El_isra) (israelson-matias@hotmail.com)
 * Created:   2022-04-26
 * Copyright: Matias Israelson (El_isra) (www.github.com/israpps)
 * License:
 **************************************************************/

int LNGID;
#include "PS2_HistoryTweakerMain.h"
#include <wx/msgdlg.h>
#include <errno.h>
#include <vector>
#include <cstdio>
#include <iomanip>

#include "EntryManager.h"

//(*InternalHeaders(PS2_HistoryTweakerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "HistoryUtils.h"

enum STATE
{
	NO_HISTORY_OPENED = 0,
	HISTORY_OPENED,

	STATE_COUNT
};

enum COLUMNS
{
	COL_ENTRYNUMBER = 0,
	COL_ENTRY,
	COL_COUNT,
	COL_MASK,
	COL_SHIFT,
	COL_PADDING,
	COL_DATE,

	TOTAL_COLUMNS
};

#define BITSHIFT(x) (1 << x)
enum CTXMNSTATE
{
	FORBID_PASTING = BITSHIFT(1),
};


static int globstate = NO_HISTORY_OPENED;
static int CTXMenuglobstate = FORBID_PASTING;


std::vector<HistoryEntry_t> GLOBAL_HISTORY;
static HistoryEntry_t HISTORY_ENTRY_CLIPBOARD;
const HistoryEntry_t BLANK_HISTORY_ENTRY = {"", 0x00, 0x00, 0x00, 0x00, 0x0000};

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PS2_HistoryTweakerFrame)
const long PS2_HistoryTweakerFrame::ID_LISTCTRL1 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM1 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM2 = wxNewId();
const long PS2_HistoryTweakerFrame::idMenuQuit = wxNewId();
const long PS2_HistoryTweakerFrame::idMenuAbout = wxNewId();
const long PS2_HistoryTweakerFrame::ID_STATUSBAR1 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM3 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM7 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM4 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM5 = wxNewId();
const long PS2_HistoryTweakerFrame::ID_MENUITEM6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PS2_HistoryTweakerFrame,wxFrame)
    //(*EventTable(PS2_HistoryTweakerFrame)
    //*)
END_EVENT_TABLE()

PS2_HistoryTweakerFrame::PS2_HistoryTweakerFrame(wxWindow* parent, wxLocale& locale, wxWindowID id)
{
    //(*Initialize(PS2_HistoryTweakerFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("PlayStation 2 History Tweaker"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    EntryList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(872,436), wxLC_REPORT|wxLC_ALIGN_LEFT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES, wxDefaultValidator, _T("ID_LISTCTRL1"));
    wxListItem col6;
    col6.SetId(COL_ENTRYNUMBER);
    col6.SetText( _("Entry number") );
    col6.SetWidth(110);
    EntryList->InsertColumn(COL_ENTRYNUMBER, col6);

    wxListItem col0;
    col0.SetId(COL_ENTRY);
    col0.SetText( _("Entry") );
    col0.SetWidth(180);//180
    EntryList->InsertColumn(COL_ENTRY, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(COL_COUNT);
    col1.SetText( _("Launch count") );
    col1.SetWidth(100);
    EntryList->InsertColumn(COL_COUNT, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(COL_MASK);
    col2.SetText( _("BitMask") );
    col2.SetWidth(100);
    EntryList->InsertColumn(COL_MASK, col2);

    // Add 4th column
    wxListItem col3;
    col3.SetId(COL_SHIFT);
    col3.SetText( _("ShiftAmount") );
    col3.SetWidth(100);
    EntryList->InsertColumn(COL_SHIFT, col3);

    wxListItem col4;
    col4.SetId(COL_PADDING);
    col4.SetText( _("padding") );
    col4.SetWidth(100);
    EntryList->InsertColumn(COL_PADDING, col4);

    wxListItem col5;
    col5.SetId(COL_DATE);
    col5.SetText( _("Date") );
    col5.SetWidth(110);
    EntryList->InsertColumn(COL_DATE, col5);

    BoxSizer3->Add(EntryList, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Open\tF2"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, ID_MENUITEM2, _("Save\tF3"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[2] = { -100, -10 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(2,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    MenuItem5 = new wxMenuItem((&EntryListMenu), ID_MENUITEM3, _("Clear"), wxEmptyString, wxITEM_NORMAL);
    EntryListMenu.Append(MenuItem5);
    MenuItem9 = new wxMenuItem((&EntryListMenu), ID_MENUITEM7, _("Remove"), wxEmptyString, wxITEM_NORMAL);
    EntryListMenu.Append(MenuItem9);
    MenuItem6 = new wxMenuItem((&EntryListMenu), ID_MENUITEM4, _("Edit"), wxEmptyString, wxITEM_NORMAL);
    EntryListMenu.Append(MenuItem6);
    MenuItem7 = new wxMenuItem((&EntryListMenu), ID_MENUITEM5, _("Copy"), wxEmptyString, wxITEM_NORMAL);
    EntryListMenu.Append(MenuItem7);
    CTXMenPaste = new wxMenuItem((&EntryListMenu), ID_MENUITEM6, _("Paste"), wxEmptyString, wxITEM_NORMAL);
    EntryListMenu.Append(CTXMenPaste);
    CTXMenPaste->Enable(false);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnEntryListBeginDrag);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_DELETE_ITEM,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnRefreshCounter);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnRefreshCounter);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnEntryListItemRightClick);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_INSERT_ITEM,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnRefreshCounter);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnOpenHistoryFileRequest);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnSaveHistoryRequest);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnAbout);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnClearEntryRequest);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnRemoveEntryRequest);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnentryEditRequest);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnItemCopy);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PS2_HistoryTweakerFrame::OnItemPaste);
    //*)
}

PS2_HistoryTweakerFrame::~PS2_HistoryTweakerFrame()
{
    //(*Destroy(PS2_HistoryTweakerFrame)
    //*)
}

void PS2_HistoryTweakerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PS2_HistoryTweakerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("PS2 History Tweaker.\nCreated by Matias israelson (AKA: El_isra)\nThis software is free to use and open source:\nhttps://github.com/israpps/PS2-HistoryTweaker");
    wxMessageBox(msg, _("Welcome to..."));
}

void PS2_HistoryTweakerFrame::OnEntryListBeginDrag(wxListEvent& event)
{
}

void PS2_HistoryTweakerFrame::RepopulateList(void)
{
	EntryList->DeleteAllItems();
	//for (int x = 0; x < GLOBAL_HISTORY.size(); x++)
	for (int x = GLOBAL_HISTORY.size() - 1; x >= 0 ; x--)
	{

		std::cout << wxString::Format("Entry %.2d... DUMP: {%-*s, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.4x}\n",
									x, 16, GLOBAL_HISTORY[x].name, GLOBAL_HISTORY[x].LaunchCount, GLOBAL_HISTORY[x].bitmask, GLOBAL_HISTORY[x].ShiftAmount, GLOBAL_HISTORY[x].padding, GLOBAL_HISTORY[x].DateStamp);


		long z =
		EntryList->InsertItem(COLUMNS::COL_ENTRYNUMBER, wxString::Format("%i",x));
		EntryList->SetItem(z, COLUMNS::COL_ENTRY, 								wxString(GLOBAL_HISTORY[x].name));
		EntryList->SetItem(z, COLUMNS::COL_COUNT, 	wxString::Format("%d", 		GLOBAL_HISTORY[x].LaunchCount));
		EntryList->SetItem(z, COLUMNS::COL_MASK, 	wxString::Format("0x%x",	GLOBAL_HISTORY[x].bitmask));
		EntryList->SetItem(z, COLUMNS::COL_SHIFT, 	wxString::Format("0x%x",	GLOBAL_HISTORY[x].ShiftAmount));
		EntryList->SetItem(z, COLUMNS::COL_PADDING,	wxString::Format("0x%x",	GLOBAL_HISTORY[x].padding));
		EntryList->SetItem(z, COLUMNS::COL_DATE,	wxString::Format("%i-%i-%i",
																				OSD_HISTORY_GET_DATE(GLOBAL_HISTORY[x].DateStamp),
																				OSD_HISTORY_GET_MONTH(GLOBAL_HISTORY[x].DateStamp),
																				2000+OSD_HISTORY_GET_YEAR(GLOBAL_HISTORY[x].DateStamp)
																	));
		if (
				(wxString(GLOBAL_HISTORY[x].name) == "") &&
				(GLOBAL_HISTORY[x].LaunchCount == 0) &&
				(GLOBAL_HISTORY[x].bitmask == 0) &&
				(GLOBAL_HISTORY[x].DateStamp == 0x0000)
				)
			EntryList->SetItemTextColour(z, wxColour(*wxBLACK));
		else
			EntryList->SetItemTextColour(z, wxColour(*wxRED));
	}
}

void PS2_HistoryTweakerFrame::OnOpenHistoryFileRequest(wxCommandEvent& event)
{

	if (EntryList->GetItemCount() != 0)
	{
		if (wxMessageBox(_("There is a history record already opened\nClear data and load new one?"),"",wxICON_WARNING|wxYES_NO)==wxYES)
			EntryList->DeleteAllItems();
		else
			return;
		globstate = NO_HISTORY_OPENED;
	}
	wxFileDialog HistoyQuery(this,_("Choose history file"),wxEmptyString,"history", _("All Histoy files") + "|history;history.old|" + _("Any file") + "|*.*",wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (HistoyQuery.ShowModal() == wxID_OK)
	{
		wxString collected_path = HistoyQuery.GetPath();
		int ERR;
		ERR = LoadHistoryFile(collected_path, &GLOBAL_HISTORY);

		if (GLOBAL_HISTORY.size() != MAX_HISTORY_ENTRIES)
			wxMessageBox(wxString::Format(_("The loaded history file doesn't have 21 entries (ie: %d bytes in length)\n Therefore, it can't be used as a 'history' file, only as a 'history.old'"), HISTORY_SIZE), _("not a proper size"), wxICON_WARNING);

		if (ERR == -EIO)
		{
			wxMessageBox(_("There was an error reading the file, or it's size is smaller than expected"),_("IO error"),wxICON_WARNING);
		}
		else
		{
			RepopulateList();
		}
	}
}

void PS2_HistoryTweakerFrame::OnEntryListItemRightClick(wxListEvent& event)
{
	PopupMenu(&EntryListMenu);
}

void PS2_HistoryTweakerFrame::OnClearEntryRequest(wxCommandEvent& event)
{
	long itemIndex = -1;
	if ((itemIndex = EntryList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
	{
		std::cout << "> Cleaning entry ["<<itemIndex<<"]\n";
		//GLOBAL_HISTORY.at(itemIndex) = BLANK_HISTORY_ENTRY;
		memset(&GLOBAL_HISTORY[itemIndex], 0, sizeof GLOBAL_HISTORY[itemIndex]);
		RepopulateList();
	} else std::cerr << "ERROR Deleting entry\n";
}

void PS2_HistoryTweakerFrame::OnRefreshCounter(wxListEvent& event)
{
	SetStatusText(
				wxString::Format(_("Registered entries: %d"),GLOBAL_HISTORY.size())
				);

}

void PS2_HistoryTweakerFrame::OnRemoveEntryRequest(wxCommandEvent& event)
{
	int itemIndex = -1;
	if ((itemIndex = EntryList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
	{
		std::cout << "removing entry ["<<itemIndex<<"]\n";
		std::cout << "Vecsize="<<GLOBAL_HISTORY.size()<<"\n";
		//GLOBAL_HISTORY.remove(itemIndex); //GLOBAL_HISTORY.begin() + itemIndex
		GLOBAL_HISTORY.erase((GLOBAL_HISTORY.begin() + itemIndex));
		EntryList->DeleteItem(itemIndex);
		RepopulateList();
		std::cout << "Vecsize="<<GLOBAL_HISTORY.size()<<"\n";
	} else std::cerr << "Failed to remove element\n";
}

void PS2_HistoryTweakerFrame::OnItemCopy(wxCommandEvent& event)
{
	int itemIndex = -1;
	if ((itemIndex = EntryList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
	{
		std::cout << "copying entry number ["<<itemIndex<<"] to clipboard\n";
		HISTORY_ENTRY_CLIPBOARD = GLOBAL_HISTORY[itemIndex];
		CTXMenPaste->Enable();
	}
}

void PS2_HistoryTweakerFrame::OnItemPaste(wxCommandEvent& event)
{
	int itemIndex = -1;
	if ((itemIndex = EntryList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
	{
		std::cout << "pasting clipboard into entry ["<<itemIndex<<"]\n";
		GLOBAL_HISTORY[itemIndex] = HISTORY_ENTRY_CLIPBOARD;
		RepopulateList();
	}
}

void PS2_HistoryTweakerFrame::OnentryEditRequest(wxCommandEvent& event)
{
	int itemIndex = -1;
	if ((itemIndex = EntryList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
	{
		EntryManager* ENT = new EntryManager(this);
		ENT->feed_premade_struct(GLOBAL_HISTORY[itemIndex]);
		if (ENT->ShowModal() == EM_USER_CHOSE_TO_SAVE_MODIFICATIONS)
		{
			memset(&GLOBAL_HISTORY[itemIndex], 0, sizeof GLOBAL_HISTORY[itemIndex]);
			GLOBAL_HISTORY[itemIndex] = ENT->Spit_struct();
		}

		RepopulateList();
	}
}

void PS2_HistoryTweakerFrame::OnSaveHistoryRequest(wxCommandEvent& event)
{
	wxFileDialog* DLG = new wxFileDialog(this,
										_("Choose where to save the history file"),
										wxEmptyString,
										((GLOBAL_HISTORY.size() == MAX_HISTORY_ENTRIES) ? "history" : "history.old"),
										((GLOBAL_HISTORY.size() == MAX_HISTORY_ENTRIES) ? "history|history" : "history.old|history.old"),
										wxFD_SAVE
										);
	if (DLG->ShowModal() == wxID_OK)
	{
		wxString PATH = DLG->GetPath();
		std::cout << "Saving to \""<<PATH <<"\"\n";
    	int fd, result, SIZEWRITTEN;
    	if ((fd = open(PATH.mb_str(), O_WRONLY | O_CREAT | O_TRUNC)) >= 0)
		{
#ifdef LOOPWRITE
    		for (int x=0; x < GLOBAL_HISTORY.size(); x++)
    		{
    			SIZEWRITTEN = write(fd, &GLOBAL_HISTORY[x], HISTORY_ENTRY_SIZE);
    			result = (SIZEWRITTEN == HISTORY_ENTRY_SIZE ? 0 : -EIO);
    			if (result != 0)
				{
					wxMessageBox(_("An error ocurred while saving the new file"),_("FATAL ERROR"),wxICON_ERROR);
					close(fd);
					return;
				}
    		}
#else

			SIZEWRITTEN = write(fd, GLOBAL_HISTORY.data(), (HISTORY_ENTRY_SIZE * GLOBAL_HISTORY.size()) );
			result = (SIZEWRITTEN == (HISTORY_ENTRY_SIZE * GLOBAL_HISTORY.size())) ? 0 : -EIO;
			if (result != 0)
			{
				wxMessageBox(_("An error ocurred while saving the new file"),_("FATAL ERROR"),wxICON_ERROR);
				close(fd);
				return;
			} else {
			std::cout << "successfully written \""<<PATH<<"\" with a size of ["<<SIZEWRITTEN<<"] bytes\n";
			}
#endif
    		close(fd);
    	} else {result = fd;}

    	std::cout << "return="<<result<<"\n";
	}
}
