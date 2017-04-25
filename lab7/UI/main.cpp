#include <iostream>
#include "Menu.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	Menu m;

	do
	{
		std::cout << "Выберите, пожалуйста, операцию:" << std::endl;
		std::cout << "1) Просмотр всех файлов в ФС" << std::endl;
		std::cout << "2) Отформатировать ФС" << std::endl;
		std::cout << "3) Скопировать файл" << std::endl;
		std::cout << "4) Переместить файл" << std::endl;
		std::cout << "5) Удалить файл" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;

		auto k = std::cin.get();
		std::cin.get(); //for '\n'

		switch (k)
		{
		case '0':
			return 0;
		case '1':
			m.ShowFS();
			break;
		case '2':
			m.FormatFS();
			break;
		case '3':
			m.Copy();
			break;
		case '4':
			m.Move();
			break;
		case '5':
			m.Delete();
			break;
		default:
			std::cout << ("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		system("pause");
		system("cls");
	}
	while (true);
}
