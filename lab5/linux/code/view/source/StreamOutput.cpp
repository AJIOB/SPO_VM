#include "../headers/view.h"

void PrintLine(const std::string &s)
{
	std::cout << s << std::endl;
}

void PrintWarning(const std::string &s)
{
	std::cout << "Warning: " << s << std::endl;
	//OutputLog("Warning: " + s);
}

void PrintError(const std::string &s)
{
	std::cout << "Error: " << s << std::endl;
	OutputLog("Error: " + s);
}

void OutputLog(const std::string& s, const bool isCloseFile)
{
	AJIOB::ProgramLog(s, isCloseFile);
}

std::string OutputEnum(const std::vector<std::string>& texts, const int& enumToShow)
{
	std::string result;
	int i = 0;
	for ( ; i < static_cast<long int>(texts.size()); ++i)
	{
		if (enumToShow == i)
		{
			result = texts[i];
			break;
		}
	}

	if (i >= static_cast<long int>(texts.size()))
	{
		result = "Другое";
	}

	return result;
}
