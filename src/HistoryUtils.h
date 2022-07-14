#ifndef HISTORYUTILS_H_INCLUDED
#define HISTORYUTILS_H_INCLUDED

#include <wx/string.h>
#include <vector>
#include <unistd.h>
#define MAX_HISTORY_ENTRIES 21
struct HistoryEntry_t
{
    char name[16];
    unsigned char LaunchCount;
    unsigned char bitmask;
    unsigned char ShiftAmount;
    unsigned char padding;
    unsigned short int DateStamp;
};

enum HISTORY_VALIDATION_RET
{
	SUCCESS = 0,
	CANT_OPEN_HISTORY,
	PROPER_HISTORY_SIZE,
	SMALLER_THAN_HISTORY_SIZE,
	BIGGER_THAN_HISTORY_BUT_ACCEPTABLE,
	BIGGER_THAN_HISTORY_AND_UNNACEPTABLE,
	UNHANDLED_ERR,

	HISTORY_VALIDATION_RET_COUNT
};

#define HISTORY_SIZE (MAX_HISTORY_ENTRIES * sizeof(struct HistoryEntry_t))
#define HISTORY_ENTRY_SIZE sizeof(struct HistoryEntry_t)

#define OSD_HISTORY_GET_YEAR(datestamp)         ((datestamp) >> 9 & 0x7F)
#define OSD_HISTORY_GET_MONTH(datestamp)        ((datestamp) >> 5 & 0xF)
#define OSD_HISTORY_GET_DATE(datestamp)         ((datestamp)&0x1F)

#define OSD_HISTORY_SET_DATE(year, month, date) (((unsigned short int)(year)) << 9 | ((unsigned short int)(month)&0xF) << 5 | ((date)&0x1F))

int LoadHistoryFile(wxString path, std::vector<HistoryEntry_t> *HistoryEntries);
long GetFileSize(wxString filename);
int ValidateHistorysize(wxString filename);
#endif // HISTORYUTILS_H_INCLUDED
