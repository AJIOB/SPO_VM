#ifndef THREAD_MANAGER
#define THREAD_MANAGER

#include <deque>

#include "Sync.h"

class ThreadManager
{
#ifdef _WIN32

	std::deque <Sync *> flags;
	CRITICAL_SECTION workWithFlags;

	friend DWORD WINAPI threadGenerator(LPVOID);
	friend DWORD WINAPI threadPrinter(LPVOID);

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
	bool removeThread();
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
