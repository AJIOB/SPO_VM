#ifndef THREAD_GENERATOR
#define THREAD_GENERATOR
#include <deque>

class ThreadGenerator
{
	std::deque<bool *> flags;
	double showInterval;
	double createNewThreadInterval;
	bool isStopGeneration;

public:
	ThreadGenerator(const double& showInterval, const double& createNewThreadInterval);

	void generateNewThread();
	bool removeThread();

	void runGeneration();
	void stopGeneration();
};

#endif
