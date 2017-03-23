#include "Person.h"

namespace
{
	using namespace VA::constants;
}

Person::Person()
{
}

Person::~Person()
{
}

void Person::sendRequest() const
{
	std::fstream f;
	f.open(transferFile, std::ios::out | std::ios::trunc);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return;
	}

	f << query.str();
	f.close();
}

void Person::getResponse() const
{
	std::fstream f;
	f.open(transferFile, std::ios::in);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return;
	}

	std::string res;

	//стали на чтение
	f.seekg(0);
	while (f)
	{
		res.push_back(f.get());
	}
	f.close();
	res.pop_back(); //лишний символ

	if (res.size() == 0)
	{
		std::cout << "Автомат ничего не ответил" << std::endl;
		return;
	}

	std::cout << res << std::endl;
}

unsigned long long Person::inputDrinkIndex() const
{
	unsigned long long res = 0;
	std::cout << "Введите индекс напитка для покупки" << std::endl;
	Stream::Input(res);
	return res;
}


void Person::runConsole()
{
	do
	{
		std::cout << "Выберите, пожалуйста, ваше действие:" << std::endl;
		std::cout << "1) Положить денег" << std::endl;
		std::cout << "2) Просмотреть список доступных напитков" << std::endl;
		std::cout << "3) Просмотреть доступную сумму" << std::endl;
		std::cout << "4) Купить напиток" << std::endl;
		std::cout << "5) Вернуть деньги" << std::endl;
		std::cout << "0) Отойти от автомата" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;

		auto k = std::cin.get();
		Stream::Clear();

		bool isSelectGood = true;

		std::string params;

		switch (k)
		{
		case '0':
			{
				throw 0;
			}
		case '1':
			{
				params += "a " + std::to_string(inputMoney());

				break;
			}
		case '2':
			{
				params += "s";

				break;
			}
		case '3':
			{
				params += "sm";

				break;
			}
		case '4':
			{
				params += "b " + std::to_string(inputDrinkIndex());
				break;
			}
		case '5':
			{
				params += "m";
				break;
			}
		default:
			{
				std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
				isSelectGood = false;
			}
		}

		if (isSelectGood)
		{
			query.str(params);
			return;
		}
	}
	while (true);
}

unsigned long long Person::inputMoney() const
{
	unsigned long long res = 0;
	std::cout << "Введите сумму, которую вы хотите положить в автомат. ВНИМАНИЕ! Автомат принимает только целые значению рубля" << std::endl;
	Stream::Input(res);
	return res;
}
