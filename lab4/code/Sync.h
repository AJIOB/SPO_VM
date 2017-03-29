#ifndef SYNC
#define SYNC

#ifdef _WIN32

#include <windows.h>

#define OPERATION_EXIT_THREAD 1
#define OPERATION_START_WRITING_NAME 2

struct Sync
{
	HANDLE canWork;				//event that said that thread can work (print name)
	HANDLE isEndWork;			//event that said that thread is stopped working
	HANDLE threadHandle;		//handle to thread
	int operation;				//operation type: 1 - exit, 2 - start writing name
	int index;					//thread index

	Sync()
	{
		canWork = nullptr;
		isEndWork = nullptr;
		threadHandle = nullptr;
		operation = 0;
		index = -1;
	}

	~Sync()
	{
		if (canWork)
		{
			CloseHandle(canWork);
		}

		if (isEndWork)
		{
			CloseHandle(isEndWork);
		}

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