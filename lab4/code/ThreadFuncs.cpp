#include "ThreadManager.h"

#include "ThreadFuncs.h"

#ifdef _WIN32

int calculateCurrentPrintIndex(ThreadManager* manager, int prevIndex)
{
	if (prevIndex < 0)
	{
		return 0;

	}
	
	auto findRes = std::find_if(manager->flags.begin(), manager->flags.end(), 
		[prevIndex](Sync* s) -> bool
		{
			if(!s)
			{
				return false;
			}

			return (s->index > prevIndex);
		});

	int currIndex;

	if (findRes == manager->flags.end())
	{
		currIndex = 0;
	}
	else
	{
		currIndex = findRes - manager->flags.begin();
	}

	return currIndex;
}

DWORD WINAPI threadPrinter(LPVOID ptr)
{
	ThreadManager* manager = reinterpret_cast<ThreadManager*>(ptr);
	if (!manager)
	{
		return 1;
	}

	int prevIndex = -1;

	while (!manager->isStopPrinting)
	{
		EnterCriticalSection(&manager->workWithFlags);

		if (manager->flags.size() == 0)
		{
			prevIndex = -1;
			LeaveCriticalSection(&manager->workWithFlags);

			Sleep(100);

			continue;
		}

		auto currIndex = calculateCurrentPrintIndex(manager, prevIndex);
		auto curr = manager->flags[currIndex];
		curr->operation = OPERATION_START_WRITING_NAME;
		SetEvent(curr->canWork);

		while(WaitForSingleObject(curr->isEndWork, INFINITE) != WAIT_OBJECT_0);

		auto numOfElements = manager->flags.size();
		prevIndex = curr->index;

		LeaveCriticalSection(&manager->workWithFlags);

		Sleep(manager->showInterval * 1000 / numOfElements);
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

DWORD WINAPI threadChild(LPVOID ptr)
{
	Sync* s = reinterpret_cast<Sync*> (ptr);
	if (s == NULL)
	{
		return 1;
	}

	std::string name = "Th_" + std::to_string(static_cast<long long>(s->index));

	while (true)
	{		
		WaitForSingleObject(s->canWork, INFINITE);

		if (s->operation == OPERATION_EXIT_THREAD)
		{
			break;
		}

		if (s->operation == OPERATION_START_WRITING_NAME)
		{
			std::cout << name << " ";
			SetEvent(s->isEndWork);
			continue;
		}

		SetEvent(s->isEndWork);
	}

	return 0;
}

#endif
