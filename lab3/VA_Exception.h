#ifndef VA_EXCEPTION
#define VA_EXCEPTION

#include <exception>
#include <string>

class VA_Exception : public std::exception
{
	std::string errorText;
public:
	VA_Exception() : exception()
	{
		
	}

	explicit VA_Exception(std::string s) : errorText(s)
	{
		
	}

#ifdef _WIN32
	const char* what() const override
	{
		return errorText.c_str();
	}
#elif (defined(__linux__) || defined(__unix__))
	const char* what() const noexcept
	{
		return errorText.c_str();
	}
#endif

};

#endif
