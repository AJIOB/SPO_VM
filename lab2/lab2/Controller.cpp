#include "Controller.h"

void SelectMode()
{
	std::cout << "��������, ����������, ����� ������:" << std::endl;
	std::cout << "1) ������������" << std::endl;
	std::cout << "2) �������" << std::endl;
	std::cout << "����������, �������� ���� �����" << std::endl;
	
	auto k = std::cin.get();
	Stream::Clear();

	switch (k)
	{
	case '1':
		{
			WorkAsPerson();				
			break;
		}
	case '2':
		{
			WorkAsCoffeeMachine();
			break;
		}
	default:
		{
			std::cout << "��������, ������ �������� �� ����������. �������..." << std::endl;
			break;
		}
	}
}

void WorkAsPerson()
{
	//TODO
	Person person;
}

void WorkAsCoffeeMachine()
{
	//TODO
}
