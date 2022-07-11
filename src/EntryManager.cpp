#include "EntryManager.h"
#include <wx/datetime.h>
#include <wx/datectrl.h>
//(*InternalHeaders(EntryManager)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EntryManager)
const long EntryManager::ID_TEXTCTRL1 = wxNewId();
const long EntryManager::ID_SPINCTRL1 = wxNewId();
const long EntryManager::ID_SPINCTRL2 = wxNewId();
const long EntryManager::ID_SPINCTRL3 = wxNewId();
const long EntryManager::ID_SPINCTRL4 = wxNewId();
const long EntryManager::ID_DATEPICKERCTRL1 = wxNewId();
const long EntryManager::ID_BUTTON1 = wxNewId();
const long EntryManager::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EntryManager,wxDialog)
	//(*EventTable(EntryManager)
	//*)
END_EVENT_TABLE()

EntryManager::EntryManager(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EntryManager)
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxStaticBoxSizer* StaticBoxSizer6;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 6, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Entry name"));
	Name = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(226,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	Name->SetMaxLength(16);
	StaticBoxSizer1->Add(Name, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Launch count"));
	LAUNCH_COUNT = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL1"));
	LAUNCH_COUNT->SetValue(_T("0"));
	StaticBoxSizer2->Add(LAUNCH_COUNT, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bitmask"));
	BITMASK = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL2"));
	BITMASK->SetValue(_T("0"));
	StaticBoxSizer3->Add(BITMASK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Shift Ammount"));
	SHIFT_AMMOUNT = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL3"));
	SHIFT_AMMOUNT->SetValue(_T("0"));
	StaticBoxSizer4->Add(SHIFT_AMMOUNT, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Padding"));
	PADDING = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL4"));
	PADDING->SetValue(_T("0"));
	StaticBoxSizer5->Add(PADDING, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Date"));
	DATEE = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
	StaticBoxSizer6->Add(DATEE, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Save = new wxButton(this, ID_BUTTON1, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(Save, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON2, _("Simulate Game execution"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button1->SetToolTip(_("The information is modified just like the console does when the game is loaded\n"));
	FlexGridSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EntryManager::OnSaveClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EntryManager::OnButton1Click);
	//*)


	wxDateTime MIN(1,wxDateTime::Jan, 2000), MAX(31,wxDateTime::Dec, 2099);
	//MIN.SetDay(wxDateTime::Sat);
	//MIN.SetMonth(wxDateTime::Jan);
	//MIN.SetYear(2000);

	//MAX.SetDay(wxDateTime::Thu);
	//MAX.SetMonth(wxDateTime::Dec);
	//MAX.SetYear(2099);
	DATEE->SetRange(MIN, MAX);
}

EntryManager::~EntryManager()
{
	//(*Destroy(EntryManager)
	//*)
}


void EntryManager::OnSaveClick(wxCommandEvent& event)
{
	char TMPBUF[16];
	memset(TMPBUF, 0x00, 16);
	strncpy(TMPBUF, (const char*)Name->GetValue().mb_str(), 16);
	wxDateTime _DATEE = DATEE->GetValue();
	std::cout << "day=" << _DATEE.GetDay() << " month=" << _DATEE.GetMonth() << " year=" <<_DATEE.GetYear() << "\n";
	ENTRY_CONTAINER.DateStamp = OSD_HISTORY_SET_DATE((_DATEE.GetYear()-2000), (_DATEE.GetMonth()+1), _DATEE.GetDay());
	ENTRY_CONTAINER.LaunchCount = (unsigned char) LAUNCH_COUNT->GetValue();
	ENTRY_CONTAINER.bitmask = (unsigned char) BITMASK->GetValue();
	ENTRY_CONTAINER.ShiftAmount = (unsigned char) SHIFT_AMMOUNT->GetValue();
	ENTRY_CONTAINER.padding = (unsigned char) PADDING->GetValue();
	strncpy(ENTRY_CONTAINER.name, TMPBUF, 16);
	EndModal(EM_USER_CHOSE_TO_SAVE_MODIFICATIONS);
}

void EntryManager::feed_premade_struct(HistoryEntry_t ENTRY)
{
	memset(&ENTRY_CONTAINER, 0x00, sizeof(ENTRY_CONTAINER));
	ENTRY_CONTAINER = ENTRY;
}

HistoryEntry_t EntryManager::Spit_struct(void)
{
	return ENTRY_CONTAINER;
}

void EntryManager::OnButton1Click(wxCommandEvent& event)
{
	int NewLaunchCount, value;
	if ((ENTRY_CONTAINER.bitmask & 0x3F) != 0x3F)
	{
		NewLaunchCount = ENTRY_CONTAINER.LaunchCount + 1;
		if (NewLaunchCount >= 0x80) {
			NewLaunchCount = 0x7F;
		}

		if (NewLaunchCount >= 14)
		{
			if ((NewLaunchCount - 14) % 10 == 0)
			{
				while ((ENTRY_CONTAINER.bitmask >> (value = rand() % 6)) & 1) {
				};
				ENTRY_CONTAINER.ShiftAmount = value;
				ENTRY_CONTAINER.bitmask |= 1 << value;
			}
		}

			ENTRY_CONTAINER.LaunchCount = NewLaunchCount;
	}
	else
	{
		if (ENTRY_CONTAINER.LaunchCount < 0x3F)
		{
			ENTRY_CONTAINER.LaunchCount++;
		}
		else
		{
			ENTRY_CONTAINER.LaunchCount = ENTRY_CONTAINER.bitmask & 0x3F;
			ENTRY_CONTAINER.ShiftAmount = 7;
		}
	}
	LAUNCH_COUNT->SetValue(ENTRY_CONTAINER.LaunchCount);
	SHIFT_AMMOUNT->SetValue(ENTRY_CONTAINER.ShiftAmount);
	BITMASK->SetValue(ENTRY_CONTAINER.bitmask);

}
