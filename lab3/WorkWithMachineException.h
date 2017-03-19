#ifndef WWM_EXCEPTION
#define WWM_EXCEPTION

#include "VA_Exception.h"

class WorkWithMachineException : public VA_Exception
{
public:
	WorkWithMachineException() : VA_Exception("Cannot work with machine")
	{
	}
};

#endif
