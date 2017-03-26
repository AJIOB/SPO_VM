#ifndef MSM_EXCEPTION
#define MSM_EXCEPTION

#include "VA_Exception.h"

class MapSharedMemoryException : public VA_Exception
{
public:
	MapSharedMemoryException() : VA_Exception("Cannot reallocate shared memory")
	{
	}
};

#endif