#ifndef SYNC
#define SYNC

#ifdef _WIN32

#include <windows.h>

struct Sync
{
	CONDITION_VARIABLE rw;		//flag to write thread's name or stop
	CONDITION_VARIABLE stop;	//flag to stop
	HANDLE h;					//handle to thread

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