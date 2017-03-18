#ifndef VA_EXCEPTION
#define VA_EXCEPTION

#include <exception>
#include <string>

class VA_Exception : public std::exception
{
public:
	VA_Exception() : exception()
	{
		
	}

	explicit VA_Exception(std::string s) : exception(s.c_str())
	{
		
	}
};

#endif
