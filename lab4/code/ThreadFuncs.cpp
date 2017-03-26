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
		//todo: add critical section
		for (auto it = manager->flags.begin(); it != manager->flags.end(); ++it)
		{
			WakeConditionVariable(&((*it)->rw));

			SleepConditionVariableCS(&((*it)->rw), NULL, INFINITE);
		}
		
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
		Sync* s = new Sync();
		s->h = CreateThread(NULL, 0, threadChild, s, /*run immediately*/ 0, NULL);
		if (s->h != NULL)
		{
			//todo: add critical section

			manager->flags.push_back(s);
		}
		else
		{
			Stream::log("Error creating new thread");
		}

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
