#ifndef THREAD_MANAGER
#define THREAD_MANAGER

#ifdef _WIN32

#include <deque>
#include <list>
#include "logs.h"
#include "Sync.h"
#include "ThreadFuncs.h"

#elif (defined(__linux__) || defined(__unix__))
#include "Thread.h"
#include <chrono>
#include <thread>
#include <mutex>
#include<pthread.h>

#endif


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
    void* thread_data;

    pthread_t printerThread;
    pthread_t generatorThread;

    pthread_mutex_t lock;

    bool printerAlive;
    bool generatorAlive;

    const double pinterInterval;
	const double generatorInterval;

    char threadName;
    std::list <Thread> runningThreads;

public:
	ThreadManager(const double& printerInterval_, const double& generatorInterval_);
	~ThreadManager();

	void generateNewThread();
	bool removeThread();			//kills first thread

	void runGenerator();
	void runPrinter();

	void runAll();
	void stopAll();

	int getNumOfThreads() const;

#endif
};

#endif