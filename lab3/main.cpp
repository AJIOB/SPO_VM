#include <iostream>
#include <string>
#include <clocale>

#include "Controller.h"
#include "VA_Exception.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	try
	{
		if (argc <= 1)
		{
			SelectMode();
		}
		else if (argc == 2 && std::string("-p") == argv[1])
		{
			//new Person
			WorkAsPerson();
		}
		else if (argc == 2 && std::string("-m") == argv[1])
		{
			//new Machine
			WorkAsCoffeeMachine();
		}
		else
		{
			throw BadCommandLineArgumentsException();
		}
	}
	catch (const int& eCode)
	{
		return eCode;
	}
	catch (VA_Exception& e)
	{
		std::cout << "Ошибка. " << e.what() << ". Для выхода введите любой символ" << std::endl;
		std::cin.get();
		return 2;
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}
