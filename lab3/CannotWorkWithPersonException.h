#ifndef CWWP_EXCEPTION
#define CWWP_EXCEPTION

#include "VA_Exception.h"

class CannotWorkWithPersonException : public VA_Exception
{
public:
	CannotWorkWithPersonException() : VA_Exception("Cannot work with person")
	{
	}
};

#endif
