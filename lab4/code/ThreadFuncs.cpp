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
			(*it)->operation = OPERATION_START_WRITING_NAME;
			WakeConditionVariable(&(*it)->canWork);

			SleepConditionVariableCS(&(*it)->isEndWork, &cs, INFINITE);
		}
		
		LeaveCriticalSection(&manager->workWithFlags);

		Sleep(manager->showInterval * 1000);
	}

	LeaveCriticalSection(&cs);
	DeleteCriticalSection(&cs);

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
		SleepConditionVariableCS(&s->canWork, &cs, INFINITE);

		if (s->operation == OPERATION_EXIT_THREAD)
		{
			break;
		}

		if (s->operation == OPERATION_START_WRITING_NAME)
		{
			std::cout << name << " ";
			WakeConditionVariable(&s->isEndWork);
			continue;
		}

		WakeConditionVariable(&s->isEndWork);
	}

	LeaveCriticalSection(&cs);
	DeleteCriticalSection(&cs);

	return 0;
}

#endif
