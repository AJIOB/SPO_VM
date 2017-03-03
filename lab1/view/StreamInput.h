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


	//cpp part 1. inline
#define AJIOB_END_OF_LINE '\n'

	inline void Clear()
	{
		std::cin.clear();

#ifdef _WIN32
		std::streambuf* tmp = std::cin.rdbuf();

		while ( tmp->in_avail() > 0 )
		{
			tmp->sbumpc();
		}
#else
		char c = std::cin.get();
		while (c != AJIOB_END_OF_LINE && c != EOF)
		{
			c = std::cin.get();
		}
#endif
	}

	template<typename InputType>
	InputType Input()
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
	void Input(InputType& elem)
	{
		elem = Input<InputType>();
	}

	//for std::string
	template<>
	inline std::string Input()
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
}

#endif