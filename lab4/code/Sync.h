#ifndef SYNC
#define SYNC

#ifdef _WIN32

#include <windows.h>

struct Sync
{
	CONDITION_VARIABLE rw;
	CONDITION_VARIABLE stop;
	HANDLE h;

	Sync()
	{
		InitializeConditionVariable(&rw);
		InitializeConditionVariable(&stop);
		h = NULL;
	}
};

#else

struct Sync
{
	bool* rw;
	bool* stop;
};

#endif

#endif