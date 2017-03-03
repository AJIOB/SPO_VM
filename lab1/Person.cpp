#ifdef _WIN32

#include <windows.h>

#elif (defined(__linux__) || defined(__unix__))

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#endif

#include "Person.h"

#if (defined(__linux__) || defined(__unix__))

namespace
{
	inline char** BreakString(const std::string& s, const char delim)
	{
		if (s.length() == 0)
		{
			return nullptr;
		}

		char** res = new char* [s.length() / 2 + 3];			//обязательно + 2, а то может быть краш на нечетной длине строки

		//для выравнивания количества параметров
		res[0] = new char[1];
		res[0][0] = '\0';

		int i = 1, j = 0;

		res[i] = new char[s.length() + 1];

		for (char sym : s)
		{
			if (sym == delim)
			{
				res[i][j] = '\0';
				i++;
				j = 0;

				res[i] = new char[s.length() + 1];
				continue;
			}

			res[i][j] = sym;
			j++;
		}

		res[i][j] = '\0';
		i++;
		res[i] = nullptr;

		return res;
	}

	inline void DualFree(char** a)
	{
		if (!a)
		{
			return;
		}

		int i = 0;

		while (a[i])
		{
			delete [] a[i];
			i++;
		}

		delete [] a;
	}
}

#endif

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
#ifdef _WIN32
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	ZeroMemory(&sInfo, sizeof sInfo);
	sInfo.cb = sizeof sInfo;
	ZeroMemory(&pInfo, sizeof pInfo);

	if (!CreateProcess(NULL, (LPSTR)(("lab1 " + params).c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo))
	{
		std::cout << "Не удается включить автомат" << std::endl;
		return;
	}

	WaitForSingleObject(pInfo.hProcess, INFINITE);

	CloseHandle(pInfo.hThread);
	CloseHandle(pInfo.hProcess);

#elif ((__linux__) || (__unix__))
	
	char** arrayOfParams = BreakString(params, ' ');

	pid_t pid = fork();

	if (pid < 0)
	{
		std::cout << "Не удается включить автомат" << std::endl;
		return;
	}
	else if (pid > 0)
	{
		int status = -1;

		//while (status != 0)
		//{
			if (waitpid(pid, &status, 0) != pid)
			{
				std::cout << "Что-то пошло не так. Процесс не завершился" << std::endl;
			}
		//}

		DualFree(arrayOfParams);
	}
	else
	{
		execve("lab1.exe", arrayOfParams, nullptr);
	}
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
			{
				return;
			}
			case '1':
			{
				params += " a " + std::to_string(inputMoney());
				
				break;
			}
			case '2':
			{
				params += " s";

				break;
			}
			case '3':
			{
				params += " sm";

				break;
			}
			case '4':
			{
				params += " b " + std::to_string(inputDrinkIndex());
				break;
			}
			case '5':
			{
				params += " m";
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
