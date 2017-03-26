#include "UI.h"

UI::UI(char* showPeriod, char* generateNewThreadPeriod) 
	: model(std::stod(showPeriod), std::stod(generateNewThreadPeriod))
{
}

void UI::run()
{
	//todo: menu
}
