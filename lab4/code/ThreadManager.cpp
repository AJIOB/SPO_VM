#include "ThreadManager.h"

ThreadManager::ThreadManager(const double& showInterval, const double& createNewThreadInterval) :
	showInterval(showInterval), createNewThreadInterval(createNewThreadInterval), isStopGeneration(true), isStopPrinting(true)
{
#ifdef _WIN32
	InitializeCriticalSection(&workWithFlags);

	printerThread = NULL;
	generatorThread = NULL;
#endif
}

int ThreadManager::getNumOfThreads() const
{
	return flags.size();
}

void ThreadManager::runAll()
{
	runGeneration();
	runPrinting();
}

void ThreadManager::stopAll()
{
	stopGeneration();
	stopPrinting();
}

ThreadManager::~ThreadManager()
{
	stopAll();

#ifdef _WIN32

	while (!flags.empty())
	{
		removeThread(flags.size() - 1);
	}

	DeleteCriticalSection(&workWithFlags);

#endif
}

#ifdef _WIN32

void ThreadManager::generateNewThread()
{
	static int newIndex = 0;
	Sync* s = new Sync();

	s->index = newIndex;
	newIndex++;

	s->threadHandle = CreateThread(NULL, 0, threadChild, s, /*run immediately*/ 0, NULL);
	if (!s->threadHandle)
	{
		Stream::log("Error creating new thread");
		delete s;
		return;
	}
	if (!(s->canWork = CreateEvent(NULL, FALSE, FALSE, NULL)))
	{
		Stream::log("Error creating new thread event \"can Work\"");
		delete s;
		return;
	}
	if (!(s->isEndWork = CreateEvent(NULL, FALSE, FALSE, NULL)))
	{
		Stream::log("Error creating new thread event \"is End Work\"");
		delete s;
		return;
	}

	EnterCriticalSection(&workWithFlags);
	flags.push_back(s);
	LeaveCriticalSection(&workWithFlags);
}

bool ThreadManager::removeThread(int index)
{
	EnterCriticalSection(&workWithFlags);

	if (flags.size() <= index || index < 0)
	{
		LeaveCriticalSection(&workWithFlags);
		return false;
	}

	Sync* s = flags[index];
	flags.erase(flags.begin() + index);

	s->operation = OPERATION_EXIT_THREAD;
	SetEvent(s->canWork);

	WaitForSingleObject(s->threadHandle, INFINITE);

	delete s;
	
	LeaveCriticalSection(&workWithFlags);

	return true;
}

void ThreadManager::runGeneration()
{
	isStopGeneration = false;

	if (generatorThread != NULL)
	{
		return;
	}

	generatorThread = CreateThread(NULL, 0, threadGenerator, this, /*run immediately*/ 0, NULL);
	if (generatorThread == NULL)
	{
		Stream::log("Error creating generation thread");
		isStopGeneration = true;
	}
}

void ThreadManager::stopGeneration()
{
	if (!generatorThread)
	{
		return;
	}

	isStopGeneration = true;
	
	WaitForSingleObject(generatorThread, INFINITE);

	CloseHandle(generatorThread);
	
	generatorThread = NULL;
}

void ThreadManager::runPrinting()
{
	isStopPrinting = false;

	if (printerThread != NULL)
	{
		return;
	}

	printerThread = CreateThread(NULL, 0, threadPrinter, this, /*run immediately*/ 0, NULL);
	if (printerThread == NULL)
	{
		Stream::log("Error creating printer thread");
		isStopPrinting = true;
	}
}

void ThreadManager::stopPrinting()
{
	if (!printerThread)
	{
		return;
	}

	isStopPrinting = true;

	WaitForSingleObject(printerThread, INFINITE);

	CloseHandle(printerThread);

	printerThread = NULL;
}

bool ThreadManager::removeThread()
{
	EnterCriticalSection(&workWithFlags);
	int size = flags.size();
	LeaveCriticalSection(&workWithFlags);
	
	if (!size)
	{
		return false;
	}

	return removeThread(rand() % size);
}

#else

void ThreadManager::generateNewThread()
{
	//todo: platform-dependent
}

void ThreadManager::runPrinting()
{
	//todo: platform-dependent
}

void ThreadManager::stopPrinting()
{
	//todo: platform-dependent
}

void ThreadManager::runGeneration()
{
	//todo: platform-dependent
}

void ThreadManager::stopGeneration()
{
	isStopGeneration = true;
	//todo: platform-dependent
}

bool ThreadManager::removeThread(int index)
{
	//todo: platform-dependent
	return false;
}

#endif

