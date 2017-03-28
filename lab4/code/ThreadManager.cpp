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

	s->h = CreateThread(NULL, 0, threadChild, s, /*run immediately*/ 0, NULL);
	if (s->h != NULL)
	{
		EnterCriticalSection(&workWithFlags);
		flags.push_back(s);
		LeaveCriticalSection(&workWithFlags);
	}
	else
	{
		Stream::log("Error creating new thread");
		delete s;
	}
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
	s->stop = true;
	WakeConditionVariable(&s->rw);

	WaitForSingleObject(s->h, INFINITE);

	//CloseThread();
	CloseHandle(s->h);

	delete s;

	flags.erase(flags.begin() + index);
	LeaveCriticalSection(&workWithFlags);

	return false;
}

void ThreadManager::runGeneration()
{
	isStopGeneration = false;

	generatorThread = CreateThread(NULL, 0, threadGenerator, this, /*run immediately*/ 0, NULL);
	if (generatorThread == NULL)
	{
		Stream::log("Error creating generation thread");
		isStopGeneration = true;
	}
}

void ThreadManager::stopGeneration()
{
	isStopGeneration = true;
	
	WaitForSingleObject(generatorThread, INFINITE);

	CloseHandle(printerThread);
	
	printerThread = NULL;
}

void ThreadManager::runPrinting()
{
	isStopPrinting = false;

	printerThread = CreateThread(NULL, 0, threadPrinter, this, /*run immediately*/ 0, NULL);
	if (printerThread == NULL)
	{
		Stream::log("Error creating printer thread");
		isStopPrinting = true;
	}
}

void ThreadManager::stopPrinting()
{
	isStopPrinting = true;

	WaitForSingleObject(printerThread, INFINITE);

	CloseHandle(printerThread);

	printerThread = NULL;
}

bool ThreadManager::removeThread()
{
	return removeThread(rand() % flags.size());
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

