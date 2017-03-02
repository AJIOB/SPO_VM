#ifdef _WIN32
#include <windows.h>
#elif ((__linux__) || (__unix__))

#endif

#include "Person.h"

Person::Person()
{
	runMenu();
}

Person::~Person()
{
}

unsigned long long Person::inputDrinkIndex() const
{
	unsigned long long res = 0;
	std::cout << "Введите индекс напитка для покупки" << std::endl;
	Stream::Input(res);
	return res;
}

void Person::RunChild(const std::string& params) const
{
	//create process with parametres
	//TODO
#ifdef _WIN32
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	ZeroMemory(&sInfo, sizeof sInfo);
	sInfo.cb = sizeof sInfo;
	ZeroMemory(&pInfo, sizeof pInfo);

	//auto tmp = params.c_str();
	//LPTSTR s = (LPTSTR) std::wstring(tmp, tmp + params.length()).c_str();

	//bool isCreated = CreateProcess("C:\Windows\System32\cmd.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo);

	if (!CreateProcess(NULL, (LPSTR)(("lab1 " + params).c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo))
	{
		std::cout << "Не удается включить автомат" << std::endl;
		return;
	}

	WaitForSingleObject(pInfo.hProcess, INFINITE);

	CloseHandle(pInfo.hThread);
	CloseHandle(pInfo.hProcess);
#elif ((__linux__) || (__unix__))

#else
	std::cout << "Bad operation system. Please, recompile me to Linux, Unix or Windows" << std::endl;
#endif
}

void Person::runMenu() const
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

		std::string params = "-m";

		switch (k)
		{
		case '0':
			return;
		case '1':
			params += " a " + std::to_string(inputMoney());
			
			break;
		case '2':
			params += " s";

			break;
		case '3':
			params += " sm";

			break;
		case '4':
			params += " b " + std::to_string(inputDrinkIndex());
			break;
		case '5':
			params += " m";
			break;
		default:
			std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
			isSelectGood = false;
		}

		if (isSelectGood)
		{
			RunChild(params);
		}
	} while (true);
}

unsigned long long Person::inputMoney() const
{
	unsigned long long res = 0;
	std::cout << "Введите сумму, которую вы хотите положить в автомат. ВНИМАНИЕ! Автомат принимает только целые значению рубля" << std::endl;
	Stream::Input(res);
	return res;
}
