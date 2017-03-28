#ifndef SYNC
#define SYNC

#ifdef _WIN32

#include <windows.h>

#define OPERATION_EXIT_THREAD 1
#define OPERATION_START_WRITING_NAME 2

struct Sync
{
	CONDITION_VARIABLE canWork;
	CONDITION_VARIABLE isEndWork;
	HANDLE threadHandle;		//handle to thread
	int operation;				//operation type: 1 - exit, 2 - start writing name
	int index;					//thread index

	Sync()
	{
		InitializeConditionVariable(&canWork);
		InitializeConditionVariable(&isEndWork);
		threadHandle = NULL;
		operation = 0;
		index = -1;
	}

	~Sync()
	{
		if (threadHandle)
		{
			CloseHandle(threadHandle);
		}
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