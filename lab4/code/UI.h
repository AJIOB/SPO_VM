#ifndef UI_HEADER
#define UI_HEADER

#include <string>
#include <iostream>

#include "ThreadManager.h"
#include "StreamInput.h"

class UI
{
	ThreadManager model;

public:
	UI(char* showPeriod, char* generateNewThreadPeriod);
	void run();
};

#endif
