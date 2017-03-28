#ifndef THREAD_MANAGER
#define THREAD_MANAGER

#include <deque>
#include "logs.h"
#include "Sync.h"
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

#else

	std::deque <bool *> flags;

#endif

	const double showInterval;
	const double createNewThreadInterval;
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
};

#endif
