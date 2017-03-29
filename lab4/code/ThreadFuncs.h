#ifndef THREAD_FUNCS
#define THREAD_FUNCS

#ifdef _WIN32

#include <windows.h>
#include <algorithm>
#include "logs.h"

#include "Sync.h"

DWORD WINAPI threadPrinter(LPVOID);
DWORD WINAPI threadGenerator(LPVOID);
DWORD WINAPI threadChild(LPVOID);

#endif

#endif
