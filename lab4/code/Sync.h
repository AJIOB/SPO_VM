#ifndef SYNC
#define SYNC

#ifdef _WIN32

#include <windows.h>

struct Sync
{
	CONDITION_VARIABLE rw;		//flag to write thread's name or stop
	bool stop;					//flag to stop
	HANDLE h;					//handle to thread

	Sync()
	{
		InitializeConditionVariable(&rw);
		stop  = false;
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