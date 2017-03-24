#ifndef WP_EXCEPTION
#define WP_EXCEPTION

#include "VA_Exception.h"

class WritePIDException : public VA_Exception
{
public:
	WritePIDException() : VA_Exception("Server already exist")
	{
	}
};

#endif