#include <iostream>
#include "ThreadManager.h"


#ifdef _WIN32
	InitializeCriticalSection(&workWithFlags);

	printerThread = NULL;
	generatorThread = NULL;

    DeleteCriticalSection(&workWithFlags);
#elif (defined(__linux__) || defined(__unix__))

    //todo:
#endif

#ifdef _WIN32

int ThreadManager::getNumOfThreads() const
{
	return flags.size();
}

ThreadManager::ThreadManager(const double& showInterval, const double& createNewThreadInterval) :
	showInterval(showInterval), createNewThreadInterval(createNewThreadInterval), isStopGeneration(true), isStopPrinting(true)

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


void ThreadManager::generateNewThread()
{
	Sync* s = new Sync();
	InitializeConditionVariable(&s->rw);
	InitializeConditionVariable(&s->stop);

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
	WakeConditionVariable(&s->stop);
	WakeConditionVariable(&s->rw);

	WaitForSingleObject(s->h, INFINITE);

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
}

bool ThreadManager::removeThread()
{
	bool res = removeThread(rand() % flags.size());

	return res;
}

#elif (defined(__linux__) || defined(__unix__))

void* runPrinter(void* thread_data);
void* runGenerator(void* thread_data);

ThreadManager::ThreadManager(const double& printerInterval_, const double& generatorInterval_)
{
    this -> printerInterval = printerInterval_;
	this -> generatorInterval = generatorInterval_;
	this -> printerAlive = true;
	this -> generatorAlive = true;
	this -> threadName = 'a';

	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return;
    }

}
ThreadManager::~ThreadManager()
{
    // finishing all running threads
    for(std::list<Thread>::iterator it=runningThreads.begin(); it != runningThreads.end(); ++it)
        it -> stopThread();
}

void ThreadManager::runAll()
{

    //pthread_create(&printerThread, NULL, runPrinter, this);
    //pthread_create(&generatorThread, NULL, runGenerator, this);
}

void ThreadManager::stopAll()
{
    this -> printerAlive = false;
	this -> generatorAlive = false;

	this -> ~ThreadManager();
}

int ThreadManager::getNumOfThreads()
{
    pthread_mutex_lock(&lock);

	int count = runningThreads.size();

	pthread_mutex_unlock(&lock);
    return  count;
}

void* runPrinter(void* thread_data)
{
    ThreadManager &threadManager = *reinterpret_cast<ThreadManager*>(thread_data);
    while(threadManager.printerAlive)
    {
        for(std::list<Thread>::iterator it=threadManager.runningThreads.begin(); it != threadManager.runningThreads.end(); ++it)
        {
            if(!threadManager.printerAlive) break;
            it -> askToWriteName();
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

void ThreadManager::removeThread()
{
    pthread_mutex_lock(&lock);
    if(runningThreads.size() != 0)
    {
        Thread &t = runningThreads.front();
        t.stopThread();
        runningThreads.pop_front();
    } else
    {
        std::cout<<"Очередь потоков пустая"<<std::endl;
    }
    pthread_mutex_unlock(&lock);
}

void ThreadManager::generateNewThread()
{
     pthread_mutex_lock(&lock);                     //mutex, to bу sure, that only one operation is making on list

	Thread newThread(threadName);
	threadName++;
    runningThreads.push_back(newThread);

     pthread_mutex_unlock(&lock);
}

#endif
