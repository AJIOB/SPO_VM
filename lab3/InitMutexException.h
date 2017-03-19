#ifndef IM_EXCEPTION
#define IM_EXCEPTION

#include "VA_Exception.h"

class InitMutexException : public VA_Exception
{
public:
	InitMutexException() : VA_Exception("Cannot init mutex")
	{
	}
};

#endif
