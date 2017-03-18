#ifndef BCLA_EXCEPTION
#define BCLA_EXCEPTION

#include "VA_Exception.h"

class BadCommandLineArgumentsException : public VA_Exception
{
public:
	BadCommandLineArgumentsException() : VA_Exception("Bad command-line arguments")
	{
	}
};

#endif
