#include <iostream>
#include "Menu.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	Menu m;

	do
	{
		std::cout << "��������, ����������, ��������:" << std::endl;
		std::cout << "1) �������� ���� ������ � ��" << std::endl;
		std::cout << "2) ��������������� ��" << std::endl;
		std::cout << "3) ����������� ����" << std::endl;
		std::cout << "4) ����������� ����" << std::endl;
		std::cout << "5) ������� ����" << std::endl;
		std::cout << "0) �����" << std::endl;
		std::cout << "����������, �������� ���� �����" << std::endl;

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
			std::cout << ("��������, ������ �������� �� ����������. ����������, ��������� �����");
		}

		system("pause");
		system("cls");
	}
	while (true);
}
