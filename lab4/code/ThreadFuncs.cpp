#include "ThreadManager.h"

#include "ThreadFuncs.h"

#ifdef _WIN32

DWORD WINAPI threadPrinter(LPVOID ptr)
{
	ThreadManager* manager = reinterpret_cast<ThreadManager*>(ptr);
	if (!manager)
	{
		return 1;
	}

	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);

	while (!manager->isStopPrinting)
	{
		EnterCriticalSection(&manager->workWithFlags);

		for (auto it = manager->flags.begin(); it != manager->flags.end(); ++it)
		{
			WakeConditionVariable(&((*it)->rw));

			SleepConditionVariableCS(&((*it)->rw), &cs, INFINITE);
		}
		
		LeaveCriticalSection(&manager->workWithFlags);

		Sleep(manager->showInterval * 1000);
	}

	LeaveCriticalSection(&cs);

	return 0;
}

DWORD WINAPI threadGenerator(LPVOID ptr)
{
	ThreadManager* manager = reinterpret_cast<ThreadManager*>(ptr);
	if (!manager)
	{
		return 1;
	}

	while (!manager->isStopGeneration)
	{
		manager->generateNewThread();

		Sleep(manager->createNewThreadInterval * 1000);
	}

	return 0;
}

DWORD WINAPI threadChild(LPVOID ptr)
{
	Sync* s = reinterpret_cast<Sync*> (ptr);
	if (s == NULL)
	{
		return 1;
	}

	std::string name = "Th_" + std::to_string(static_cast<long long>(s->index));

	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);

	while (true)
	{		
		SleepConditionVariableCS(&(s->rw), &cs, INFINITE);

		if (s->stop)
		{
			break;
		}

		std::cout << name << " ";

		WakeConditionVariable(&(s->rw));
	}

	LeaveCriticalSection(&cs);

	return 0;
}

#endif
