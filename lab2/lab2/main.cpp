#include <string>
#include <clocale>

#include "Person.h"
#include "CoffeMachine.h"

void SelectMode();

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
			Person tmp;
		}
		else if (argc == 1 && std::string("-m") == argv[1])
		{
			//new Machine
			CoffeMachine tmp;
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


void SelectMode()
{
	std::cout << "Выберите, пожалуйста, режим работы:" << std::endl;
	std::cout << "1) Пользователь" << std::endl;
	std::cout << "2) Автомат" << std::endl;
	std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
	auto k = std::cin.get();
	Stream::Clear();

	switch (k)
	{
	case '1':
		{
			Person tmp;
				
			break;
		}
	case '2':
		{
			CoffeMachine tmp;

			break;
		}
	default:
		{
			std::cout << "Извините, такого ватианта не существует. Выходим..." << std::endl;
			break;
		}
	}
}