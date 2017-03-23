#ifndef STRUCTS
#define STRUCTS

#include <string>

struct Command
{
	bool isAdd;	//true = add;  fasle == delete
	std::string name;

	Command()
	{
		isAdd = false;
	}

	Command(bool isAdd, std::string name) {
		this->isAdd = isAdd;
		this->name = name;
	}
};
#endif