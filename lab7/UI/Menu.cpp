#include "Menu.h"
#include <algorithm>
#include <iostream>

std::string Menu::inputString()
{
	std::string res;
	std::cin >> res;
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
	std::cout << "¬ведите путь источника (с именем)" << std::endl;
	auto source = inputString();
	std::cout << "¬ведите путь приемника (с именем)" << std::endl;
	auto destination = inputString();
	if (!fs->copy(source, destination))
	{
		std::cout << "ќшибка копировани€" << std::endl;
	}
}

void Menu::Move()
{
	std::cout << "¬ведите путь источника (с именем)" << std::endl;
	auto source = inputString();
	std::cout << "¬ведите путь приемника (с именем)" << std::endl;
	auto destination = inputString();
	if (!fs->move(source, destination))
	{
		std::cout << "ќшибка перемещени€" << std::endl;
	}
}

void Menu::Delete()
{
	std::cout << "¬ведите путь источника (с именем)" << std::endl;
	auto source = inputString();
	if (!fs->deleteF(source))
	{
		std::cout << "ќшибка удалени€" << std::endl;
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
