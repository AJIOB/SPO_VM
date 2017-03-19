#ifndef CCSM_EXCEPTION
#define CCSM_EXCEPTION

#include "VA_Exception.h"

class CannotCreateSharedMemoryException : public VA_Exception
{
public:
	CannotCreateSharedMemoryException() : VA_Exception("Cannot create shared memory")
	{
	}
};

#endif
