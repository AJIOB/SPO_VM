#include "ThreadManager.h"

#ifdef _WIN32

ThreadManager::ThreadManager(const double& showInterval, const double& createNewThreadInterval) :
	printerThread(nullptr), generatorThread(nullptr), showInterval(showInterval), createNewThreadInterval(createNewThreadInterval), isStopGeneration(true), isStopPrinting(true)
{
	InitializeCriticalSection(&workWithFlags);
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

	while (!flags.empty())
	{
		removeThread(flags.size() - 1);
	}

	DeleteCriticalSection(&workWithFlags);
}

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
	if (!generatorThread)
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
	if (!printerThread)
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

#elif (defined(__linux__) || defined(__unix__))

ThreadManager::ThreadManager(const double& printerInterval_, const double& generatorInterval_)
{
	this -> printerInterval = printerInterval_;
	this -> generatorInterval = generatorInterval_;
	this -> printerAlive = true;
	this -> generatorAlive = true;
	this -> threadName = 'a';

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		std::cout<<" mutex init failed";
		return;
	}

}

ThreadManager::~ThreadManager()
{
// finishing all running threads
	for(auto it=runningThreads.begin(); it != runningThreads.end(); ++it)
		delete (*it);
}

void ThreadManager::runAll()
{
	pthread_create(&printerThread, NULL, runPrinter, this);
	pthread_create(&generatorThread, NULL, runGenerator, this);
}

void ThreadManager::stopAll()
{
	this -> printerAlive = false;
	this -> generatorAlive = false;
}

int ThreadManager::getNumOfThreads()
{
	pthread_mutex_lock(&lock);

	int count = runningThreads.size();

	pthread_mutex_unlock(&lock);
	return count;
}

void ThreadManager::removeThread()
{
	pthread_mutex_lock(&lock);
	if(runningThreads.size() != 0)
	{
		Thread* t = runningThreads.front();
		delete t;
		runningThreads.pop_front();
	}
	else
	{
		std::cout<<"Очередь потоков пустая"<<std::endl;
	}
	pthread_mutex_unlock(&lock);
}

void ThreadManager::generateNewThread()
{
	pthread_mutex_lock(&lock);                     //mutex, to bу sure, that only one operation is making on list

	Thread* newThread = new Thread(threadName);
	threadName++;
	runningThreads.push_back(newThread);

	pthread_mutex_unlock(&lock);
}

#endif

