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

	while (!manager->isStopPrinting)
	{
		EnterCriticalSection(&manager->workWithFlags);

		for (auto it = manager->flags.begin(); it != manager->flags.end(); ++it)
		{
			WakeConditionVariable(&((*it)->rw));

			SleepConditionVariableCS(&((*it)->rw), NULL, INFINITE);
		}
		
		LeaveCriticalSection(&manager->workWithFlags);

		Sleep(manager->showInterval * 1000);
	}

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

DWORD __stdcall threadChild(LPVOID ptr)
{
	std::string name = std::to_string(static_cast<long long>(rand() % 10000));
	Sync* s = reinterpret_cast<Sync*> (ptr);

	if (s == NULL)
	{
		return 1;
	}

	while (true)
	{		
		SleepConditionVariableCS(&(s->rw), NULL, INFINITE);

		if (SleepConditionVariableCS(&(s->stop), NULL, 0))
		{
			break;
		}

		std::cout << name << " ";

		WakeConditionVariable(&(s->rw));
	}

	return 0;
}

#endif
