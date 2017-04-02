#pragma once

#include <string>
#include <iostream>
#include <vector>

//#include "../../external/headers/ExternalLib.h"
#include "log.h"

void PrintLine(const std::string &);
void PrintWarning(const std::string &);
void PrintError(const std::string &);
void OutputLog(const std::string&, const bool isCloseFile = false);

std::string OutputEnum(const std::vector<std::string>& texts, const int& enumToShow);

inline void ClearConsole()
{
	system("cls");
}

inline void PauseConsole()
{
	system("pause");
}