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
	std::cout << "������� ���� ��������� (� ������)" << std::endl;
	auto source = inputString();
	std::cout << "������� ���� ��������� (� ������)" << std::endl;
	auto destination = inputString();
	if (!fs->copy(source, destination))
	{
		std::cout << "������ �����������" << std::endl;
	}
}

void Menu::Move()
{
	std::cout << "������� ���� ��������� (� ������)" << std::endl;
	auto source = inputString();
	std::cout << "������� ���� ��������� (� ������)" << std::endl;
	auto destination = inputString();
	if (!fs->move(source, destination))
	{
		std::cout << "������ �����������" << std::endl;
	}
}

void Menu::Delete()
{
	std::cout << "������� ���� ��������� (� ������)" << std::endl;
	auto source = inputString();
	if (!fs->deleteF(source))
	{
		std::cout << "������ ��������" << std::endl;
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
