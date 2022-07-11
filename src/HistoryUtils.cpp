#include "HistoryUtils.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>
#include <iomanip>

int LoadHistoryFile(wxString path, std::vector<HistoryEntry_t> *HistoryEntries)
{
    int fd, counter = 0;
	HistoryEntry_t ENTRY;
	memset(&ENTRY, 0x00, sizeof(ENTRY));
    size_t result;
    if ((fd = open(path.mb_str(), O_RDONLY)) >= 0) {
		while(result = read(fd, &ENTRY, HISTORY_ENTRY_SIZE))
		{
			if (result != HISTORY_ENTRY_SIZE)
			{
				std::cerr << "ERROR: the chunk size is not equal to [" <<HISTORY_ENTRY_SIZE <<"] the file is not a ps2 history record or the file is corrupted\n";
				close(fd);
				return -EIO;
			}
			 std::cout << wxString::Format("Readed chunk number %.2d of %d bytes... DUMP: {%-*s, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.4x}\n",
											counter, result, 16, ENTRY.name, ENTRY.LaunchCount, ENTRY.bitmask, ENTRY.ShiftAmount, ENTRY.padding, ENTRY.DateStamp);
        	HistoryEntries->push_back(ENTRY);
        	memset(&ENTRY, 0x00, sizeof(ENTRY));
        	counter++;
		}
        close(fd);
    } else
        result = fd;

    return result;
}

long GetFileSize(wxString filename)
{
    struct stat stat_buf;
    int rc = stat(filename.mb_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
