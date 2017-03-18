#ifndef NRM_EXCEPTION
#define NRM_EXCEPTION

#include "VA_Exception.h"

class NoRunningMachineException : public VA_Exception
{
public:
	NoRunningMachineException() : VA_Exception("Machine is not running")
	{
		
	}
};

#endif
