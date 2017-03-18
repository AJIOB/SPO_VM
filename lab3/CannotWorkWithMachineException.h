#ifndef CWWM_EXCEPTION
#define CWWM_EXCEPTION

#include "VA_Exception.h"

class CannotWorkWithMachineException : public VA_Exception
{
public:
	CannotWorkWithMachineException() : VA_Exception("Cannot work with machine")
	{
	}
};

#endif
