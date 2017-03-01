#include <string>
#include <clocale>

#include "Person.h"
#include "CoffeMachine.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	if (argc <= 1)
	{
		//new Person
		Person tmp;
	}
	else if (std::string("-m") == argv[1])
	{
		//new Machine
		CoffeMachine tmp(argc - 2, argv + 2);
	}

	return 0;
}
