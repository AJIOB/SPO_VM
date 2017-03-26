#ifndef VA_LOGS
#define VA_LOGS

#include <string>
#include <fstream>
#include <iostream>

namespace Stream
{
	inline void log(const std::string& s)
	{
		std::fstream f;
		f.open("VA_lab4.log", std::ios::out | std::ios::app);
		if (!f)
		{
			std::cout << "Error writing logs" << std::endl;
			return;
		}

		f << std::endl << s;
		f.close();
	}
}

#endif
