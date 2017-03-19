#ifndef STRUCTS
#define STRUCTS

#include <string>

struct Command{
	bool isAdd;	//true = add;  fasle == delete
	std::string name;
};
#endif