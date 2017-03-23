#ifndef CWWP_EXCEPTION
#define CWWP_EXCEPTION

#include "VA_Exception.h"

class WorkWithPersonException : public VA_Exception
{
public:
	WorkWithPersonException() : VA_Exception("Cannot work with person")
	{
	}
};

#endif
