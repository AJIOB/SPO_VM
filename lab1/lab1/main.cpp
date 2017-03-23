#include <string>
#include <clocale>

#include "Person.h"
#include "CoffeMachine.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	try
	{
		if (argc <= 1)
		{
			//new Person
			Person tmp;
		}
		else if (std::string("-m") == argv[1])
		{
			//new Machine
			CoffeMachine tmp(argc - 2, argv + 2);
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
