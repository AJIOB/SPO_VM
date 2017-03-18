#ifndef MAR_EXCEPTION
#define MAR_EXCEPTION

#include "VA_Exception.h"

class MachineAlreadyRunningException : public VA_Exception
{
public:
	MachineAlreadyRunningException() : VA_Exception("Machine already running")
	{
	}
};

#endif
