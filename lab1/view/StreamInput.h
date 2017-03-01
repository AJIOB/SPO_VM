#ifndef STREAMINPUT_HEADER
#define STREAMINPUT_HEADER

#include <iostream>
#include <string>

namespace Stream
{
	void Clear();

	template<typename InputType>
	InputType Input();
	
	template<typename InputType>
	void Input(InputType& elem);
}



#define AJIOB_END_OF_LINE '\n'


//cpp part 1. inline

inline void Stream::Clear()
{
	std::cin.clear();

	std::streambuf* tmp = std::cin.rdbuf();

	while ( tmp->in_avail() != 0 )
	{
		tmp->sbumpc();
    }
}

template<typename InputType>
InputType Stream::Input()
{
	InputType toReturn;

	while (true)
	{
		if (std::cin >> toReturn)
		{
			Clear();
			break;
		}
		std::cout << "Ошибка ввода. Пожалуйста, повторите ввод" << std::endl;
		Clear();
	}
	return toReturn;
}

template<typename InputType>
void Stream::Input(InputType& elem)
{
	elem = Input<InputType>();
}

//for std::string
template<>
inline std::string Stream::Input()
{
	std::string buffer;

	while (true)
	{
		char tmp = std::cin.get();

		if (tmp == AJIOB_END_OF_LINE)
		{
			break;
		}

		buffer.push_back(tmp);
	}

	return buffer;
}
//end for std::string

#undef AJIOB_END_OF_LINE

#endif