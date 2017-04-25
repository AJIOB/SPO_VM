#include "Menu.h"
#include <algorithm>
#include <iostream>

std::string Menu::inputString()
{
	std::string res;
	std::cin >> res;
	std::cin.ignore(512,'\n');
	return res;
}

void Menu::ShowFS()
{
	auto list = fs->getListOfFiles();

	std::for_each(list.begin(), list.end(), [](const std::string& s)
	              {
		              std::cout << s << std::endl;
	              });
}

void Menu::FormatFS()
{
	fs->format();
}

void Menu::Copy()
{
	std::cout << "Введите путь источника (с именем)" << std::endl;
	auto source = inputString();
	std::cout << "Введите путь приемника (с именем)" << std::endl;
	auto destination = inputString();
	if (!fs->copy(source, destination))
	{
		std::cout << "Ошибка копирования" << std::endl;
	}
}

void Menu::Move()
{
	std::cout << "Введите путь источника (с именем)" << std::endl;
	auto source = inputString();
	std::cout << "Введите путь приемника (с именем)" << std::endl;
	auto destination = inputString();
	if (!fs->move(source, destination))
	{
		std::cout << "Ошибка перемещения" << std::endl;
	}
}

void Menu::Delete()
{
	std::cout << "Введите путь источника (с именем)" << std::endl;
	auto source = inputString();
	if (!fs->deleteF(source))
	{
		std::cout << "Ошибка удаления" << std::endl;
	}
}

Menu::Menu()
{
	fs = new VA_FileSystem;
}

Menu::~Menu()
{
	delete fs;
}
