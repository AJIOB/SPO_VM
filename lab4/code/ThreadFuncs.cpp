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
	std::string name = std::to_string(static_cast<long long>(rand() % 10000));
	Sync* s = reinterpret_cast<Sync*> (ptr);

	if (s == NULL)
	{
		return 1;
	}

	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);

	while (true)
	{		
		SleepConditionVariableCS(&(s->rw), &cs, INFINITE);

		if (SleepConditionVariableCS(&(s->stop), &cs, 0))
		{
			break;
		}

		std::cout << name << " ";

		WakeConditionVariable(&(s->rw));
	}

	LeaveCriticalSection(&cs);

	return 0;
}

#elif (defined(__linux__) || defined(__unix__))

void* runPrinter(void* thread_data)
{
    ThreadManager &threadManager = *reinterpret_cast<ThreadManager*>(thread_data);
    while(threadManager.printerAlive)
    {
        for(auto it=threadManager.runningThreads.begin(); it != threadManager.runningThreads.end(); ++it)
        {
            if(!threadManager.printerAlive) break;
            (*it) -> askToWriteName();
            while(!(*it) -> isStoppedWriting);
            (*it)->isStoppedWriting = false;
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(threadManager.printerInterval * 1000)));   //sleps printerInterval seconds!!!
        }
    }
    pthread_exit(0);
}

void* runGenerator(void* thread_data)
{
    ThreadManager &threadManager = *reinterpret_cast<ThreadManager*>(thread_data);
    while(threadManager.generatorAlive)
    {
        threadManager.generateNewThread();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(threadManager.generatorInterval * 1000)));   //sleps printerInterval seconds!!!
        //std::this_thread::sleep_for(std::chrono::seconds(2));   //sleps printerInterval seconds!!!
    }
    pthread_exit(0);
}

#endif
