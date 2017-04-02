#include "../headers/StreamInput.h"

char Stream::GetOnlyYN(const std::string& infoText)
{
	char result;

	while (true)
	{
        PrintLine(infoText + " (Y - да, N - нет)");
		result = Stream::Get();

		if (result == 'y' || (result == 'n'))
		{
			result += 'A' - 'a';
			break;
		}

		if (result == 'Y' || (result == 'N'))
		{
			break;
		}

        PrintLine("Извините, данный вариант ответа не поддерживается. Пожалуйста, повторите ввод");
	}

	return result;
}

#ifdef _WIN32
std::string Stream::Getpass(const char* prompt, bool show_asterisk)
{
	const char BACKSPACE=8;
	const char RETURN=13;

	std::string password;
	unsigned char ch=0;

	std::cout <<prompt<< std::endl;

	do
	{
		ch = _getch();
		if (ch == RETURN)
		{
			break;
		}

		if (ch == BACKSPACE)
		{
			if ((password.length() == 0))
			{
				continue;
			}

			password.pop_back();

			//�������� ����� *
			if (show_asterisk)
			{
				std::cout << "\r";
				//��������� ������� �������
				for (auto i = 0; i <= password.size(); i++)
				{
					std::cout << " ";
				}

				std::cout << "\r";
				for (auto i = 0; i < password.size(); i++)
				{
					std::cout << "*";
				}
			}

			continue;
		}

		password.push_back(ch);
		if (show_asterisk)
		{
			std::cout << "*";
		}

	} while (true);

	std::cout << std::endl;
	return password;
}
#endif
