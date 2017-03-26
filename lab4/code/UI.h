#ifndef UI_HEADER
#define UI_HEADER

#include <string>

#include "ThreadGenerator.h"

class UI
{
	ThreadGenerator model;

public:
	UI(char* showPeriod, char* generateNewThreadPeriod);
	void run();
};

#endif