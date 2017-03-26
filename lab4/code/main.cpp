#include <iostream>
#include <string>
#include <clocale>

#include "VA_Exception.h"
#include "UI.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	try
	{
		if (argc == 3)
		{
			//work
			UI ui(argv[1], argv[2]);
			ui.run();
		}
		else
		{
			//error
			throw VA_Exception("Bad parameters");
		}
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
