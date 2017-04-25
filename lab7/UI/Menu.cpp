#include "Menu.h"
#include <algorithm>
#include <iostream>

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
}

void Menu::Move()
{
}

void Menu::Delete()
{
}

Menu::Menu()
{
	fs = new VA_FileSystem;
}

Menu::~Menu()
{
	delete fs;
}
