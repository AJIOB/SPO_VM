#ifndef CSM_EXCEPTION
#define CSM_EXCEPTION

#include "VA_Exception.h"

class CreateSharedMemoryException : public VA_Exception
{
public:
	CreateSharedMemoryException() : VA_Exception("Cannot create shared memory")
	{
	}
};

#endif
