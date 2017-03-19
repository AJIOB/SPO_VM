#ifndef CRSM_EXCEPTION
#define CRSM_EXCEPTION

#include "VA_Exception.h"

class CannotReallocSharedMemoryException : public VA_Exception
{
public:
	CannotReallocSharedMemoryException() : VA_Exception("Cannot reallocate shared memory")
	{
	}
};

#endif