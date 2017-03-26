#ifndef SAE_EXCEPTION
#define SAE_EXCEPTION

#include "VA_Exception.h"

class ServerAlreadyExistException : public VA_Exception
{
public:
	ServerAlreadyExistException() : VA_Exception("Server already exist")
	{
	}
};

#endif