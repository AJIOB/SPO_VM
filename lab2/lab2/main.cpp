#include <string>
#include <clocale>

#include "Controller.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	try
	{
		if (argc <= 1)
		{
			SelectMode();
		}
		else if (argc == 1 && std::string("-p") == argv[1])
		{
			//new Person
			WorkAsPerson();
		}
		else if (argc == 1 && std::string("-m") == argv[1])
		{
			//new Machine
			WorkAsCoffeeMachine();
		}
		else
		{
			std::cout << "Неожиданные параметры запуска. Программа аварийно завершена" << std::endl;
		}
	}
	catch (const int& eCode)
	{
		return eCode;
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}
