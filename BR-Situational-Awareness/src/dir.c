#include "common.h"

//Not if anyone else adopts or looks at this
//Its not threadsafe
typedef struct _item{
    void * elem;
    struct _item * next;
}item, *Pitem;

typedef struct _queue{\
    Pitem head;
    Pitem tail;
    void (*push)(struct _queue *, void *);
    void * (*pop)(struct _queue *);
    void (*free)(struct _queue *);
}queue, *Pqueue;

void _push(Pqueue q, void * v)
{
    Pitem i = (Pitem)intAlloc(sizeof(item));
    i->elem = v;
    if(q->head == NULL && q->tail == NULL) // empty
    {
        q->head = i;
        q->tail = i;
        i->next = NULL;
    }else // not empty
    {
        q->tail->next = i;
        q->tail = i;
    }
}
void * _pop(Pqueue q)
{
    void * retval = NULL;
    Pitem i = NULL;
    if(q->head == NULL && q->tail == NULL) // empty
    {
        return NULL;
    }
    retval = q->head->elem; //scanbuild false positive
    if(q->head == q->tail) //last elem
    {
        intFree(q->head);
        q->head = NULL;
        q->tail = NULL;
    }
    else // not the last item
    {
        i = q->head;
        q->head = q->head->next;
        intFree(i);
    }
    return retval;

}

void _free(Pqueue q)
{
    intFree(q);
}

Pqueue queueInit()
{
    Pqueue q = (Pqueue)intAlloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->push = _push;
    q->pop = _pop;
    q->free = _free;
    return q;
}

void usage() {
    PRINT("[+] Usage:\n    dir <DIRECTORY> </s>\n\n");
    PRINT("[+] Descruptions:\n    List files in a directory. Supports wildcards (e.g. \"C:\\Windows\\S*\") unlike the BRC4 ls command.\n    The `/s` flag if set, prints all contents recursively\n");
}

void listDir(char *path, BOOL subdirs) {
    WIN32_FIND_DATA fd = {0};
	HANDLE hand = NULL;
	LARGE_INTEGER fileSize;
	LONGLONG totalFileSize = 0;
	int nFiles = 0;
	int nDirs = 0;
	Pqueue dirQueue = queueInit();
	char * uncIndex;
	char * curitem;
	char * nextPath;
    size_t pathlen = strlen(path);

    // Per MSDN: "On network shares ... you cannot use an lpFileName that points to the share itself; for example, "\\Server\Share" is not valid."
    // Workaround: If we're using a UNC Path, there'd better be at least 4 backslashes
    // This breaks the convention, but a `cmd /c dir \\hostname\admin$` will work, so let's replicate that functionality.
    if (_strnicmp(path, "\\\\", 2) == 0) {
        uncIndex = strstr(path + 2, "\\");
        if (uncIndex != NULL && strstr(uncIndex + 1, "\\") == NULL) {
            strcat(path, "\\");
            pathlen = pathlen + 1;
        }
    }

	// If the file ends in \ or is a drive (C:), throw a * on there
	if (BadgerStrcmp(path + pathlen - 1, "\\") == 0) {
		strcat(path, "*");
	} else if (BadgerStrcmp(path + pathlen - 1, ":") == 0) {
		strcat(path, "\\*");
	}

    // Query the first file
	hand = FindFirstFileA(path, &fd);
	if (hand == INVALID_HANDLE_VALUE) {
		ERR_PRINT("FindFirstFileA");
		FindClose(hand);
		return;
	}

    // If it's a single directory without a wildcard, re-run it with a \*
	if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strstr(path, "*") == NULL) {
		strcat(path, "\\*");
		listDir(path, subdirs);
		FindClose(hand);
		return;
	}

    PRINT("[+] Contents of %s: \n", path);

    do {
        // Get file write time
		SYSTEMTIME stUTC, stLocal;
		FileTimeToSystemTime(&(fd.ftLastWriteTime), &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        PRINT("\t%02d/%02d/%02d %02d:%02d",
				stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, stLocal.wMinute);

        // File size (or ujust print dir)
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
				PRINT("%16s %s\n", "<junction>", fd.cFileName);
			} else {
				PRINT("%16s %s\n", "<dir>", fd.cFileName);
			}
			nDirs++;
			// ignore . and ..
			if (BadgerStrcmp(fd.cFileName, ".") == 0 || BadgerStrcmp(fd.cFileName, "..") == 0) {
				continue;
			}
			// Queue subdirectory for recursion
			if (subdirs) {
				nextPath = intAlloc((BadgerStrlen(path) + BadgerStrlen(fd.cFileName) + 3)*2);
				strncat(nextPath, path, BadgerStrlen(path)-1);
				strcat(nextPath, fd.cFileName);
				dirQueue->push(dirQueue, nextPath);
			}
		} else {
			fileSize.LowPart = (DWORD)fd.nFileSizeLow;
			fileSize.HighPart = (LONG)fd.nFileSizeHigh;
			PRINT("%16lld %s\n", fileSize.QuadPart, fd.cFileName);

			nFiles++;
			totalFileSize += fileSize.QuadPart;
		}

    } while(FindNextFileA(hand, &fd));

    PRINT("\t%32lld Total File Size for %d File(s)\n", totalFileSize, nFiles);
	PRINT("\t%55d Dir(s)\n\n", nDirs);

    // A single error (ERROR_NO_MORE_FILES) is normal
	DWORD err = GetLastError();
	if (err != ERROR_NO_MORE_FILES) {
		EPRINT("[-] Error fetching files: 0x%lx\n", err);
		FindClose(hand);
		return;
	}

	FindClose(hand);
	while((curitem = dirQueue->pop(dirQueue)) != NULL) {
		listDir(curitem, subdirs);
		intFree(curitem);
	}
	dirQueue->free(dirQueue);

}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

    char * path = NULL;
    BOOL s_flag = FALSE;

    // Nasty work around I had to improvise while porting
    // If no other input is provided, enumerate the current dir
    if (argc == 0 ) {
        path = "*";
    }

    // Check for help flag
    if (argc == 1) {
      if (
            (BadgerStrcmp(argv[0], "-h") == 0) ||
            (BadgerStrcmp(argv[0], "--help") == 0) ||
            (BadgerStrcmp(argv[0], "/?") == 0)
        ) {
        usage();
        return;
        }
    }

    if (argc >= 1) {
        path = argv[0];
    }

    if (argc == 2) {
        if ( BadgerStrcmp(argv[1], "/s") == 0 ) {
            s_flag = TRUE;
        }
        else {
            usage();
            return;
        }
    }

    if (argc > 2) {
        usage();
        return;
    }

    // Not positive how long path is, let's be safe
	// At worst, we will append \* so give it four bytes (= 2 wchar_t)
    char realPath[1024] = {0};
    // intZeroMemory(realPath, 1024);
    strncat(realPath, path, 1023);

    listDir(realPath, s_flag);
    // intFree(realPath);
}
