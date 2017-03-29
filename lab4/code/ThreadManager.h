#ifndef THREAD_MANAGER
#define THREAD_MANAGER

#ifdef _WIN32

#include <deque>
#include "logs.h"
#include "Sync.h"


#elif (defined(__linux__) || defined(__unix__))

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <list>
#include "Thread.h"

#else
#error Bad operation system. Please, recompile me to Linux, Unix or Windows
#endif

#include "ThreadFuncs.h"

class ThreadManager
{
#ifdef _WIN32

	std::deque <Sync *> flags;
	CRITICAL_SECTION workWithFlags;

	friend DWORD WINAPI threadGenerator(LPVOID);
	friend DWORD WINAPI threadPrinter(LPVOID);

	HANDLE printerThread;
	HANDLE generatorThread;

    std::deque <bool *> flags;
	const double showInterval;                  //interval between printing names
	const double createNewThreadInterval;       //interval between creating threads
	bool isStopGeneration;
	bool isStopPrinting;

    public:
	ThreadManager(const double& showInterval, const double& createNewThreadInterval);
	~ThreadManager();

	void generateNewThread();
	bool removeThread();			//kill random thread
	bool removeThread(int index);

	void runGeneration();
	void stopGeneration();

	void runPrinting();
	void stopPrinting();

	void runAll();
	void stopAll();

	int getNumOfThreads() const;

#elif (defined(__linux__) || defined(__unix__))

    pthread_t printerThread;
    pthread_t generatorThread;

    pthread_mutex_t lock;

public:

	bool printerAlive;
	bool generatorAlive;

	double printerInterval;
	double generatorInterval;

	char threadName;
	std::list <Thread *> runningThreads;


	ThreadManager(const double& printerInterval_, const double& generatorInterval_);
	~ThreadManager();

	void generateNewThread();
	void removeThread();			//kills first thread

	void runAll();
	void stopAll();

	int getNumOfThreads();
#endif

};

#endif