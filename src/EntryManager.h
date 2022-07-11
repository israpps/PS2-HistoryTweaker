#ifndef ENTRYMANAGER_H
#define ENTRYMANAGER_H
#include "HistoryUtils.h"
//(*Headers(EntryManager)
#include <wx/button.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
//*)

#define EM_USER_CHOSE_TO_SAVE_MODIFICATIONS 99
class EntryManager: public wxDialog
{
	public:

		EntryManager(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EntryManager();
		void feed_premade_struct(HistoryEntry_t ENTRY);
		HistoryEntry_t Spit_struct(void);
		//(*Declarations(EntryManager)
		wxButton* Button1;
		wxButton* Save;
		wxDatePickerCtrl* DATEE;
		wxSpinCtrl* BITMASK;
		wxSpinCtrl* LAUNCH_COUNT;
		wxSpinCtrl* PADDING;
		wxSpinCtrl* SHIFT_AMMOUNT;
		wxTextCtrl* Name;
		//*)

	protected:

		//(*Identifiers(EntryManager)
		static const long ID_TEXTCTRL1;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL3;
		static const long ID_SPINCTRL4;
		static const long ID_DATEPICKERCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
		HistoryEntry_t ENTRY_CONTAINER;
		//(*Handlers(EntryManager)
		void OnSaveClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
