#ifndef THREAD_FUNCS
#define THREAD_FUNCS

#ifdef _WIN32

#include <windows.h>
#include "logs.h"

#include "Sync.h"

DWORD WINAPI threadPrinter(LPVOID);
DWORD WINAPI threadGenerator(LPVOID);
DWORD WINAPI threadChild(LPVOID);

#elif (defined(__linux__) || defined(__unix__))

void* runPrinter(void* thread_data);
void* runGenerator(void* thread_data);

#endif

#endif
