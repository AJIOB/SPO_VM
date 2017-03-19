#ifndef RSM_EXCEPTION
#define RSM_EXCEPTION

#include "VA_Exception.h"

class ReallocSharedMemoryException : public VA_Exception
{
public:
	ReallocSharedMemoryException() : VA_Exception("Cannot reallocate shared memory")
	{
	}
};

#endif