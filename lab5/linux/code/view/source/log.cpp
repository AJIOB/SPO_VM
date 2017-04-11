#include "../headers/log.h"

void AJIOB::ProgramLog(const std::string putToLogFile, const bool isCloseFile)
{
	//����� ���������� � �������� ������ ������ ���� �����
	static std::ofstream file;

	if (!file.is_open())
	{
		file.open(logfileWay, std::ios::out | std::ios::app);

		if (!file.is_open())
		{
			std::cout << errorText << std::endl;
			return;
		}
	}
#ifdef _WIN32
	time_t currentTime;

	//�������� ������� �����
	time(&currentTime);
	//�������������� ��� � ������
	char timeInChar[strSize];

	ctime_s(timeInChar, strSize, &currentTime);
	//������� \n � ����� ������
	timeInChar [strlen(timeInChar) - 1] = '\0';

	file << timeInChar << ": " ;
#endif

	file << putToLogFile << std::endl;

	if (isCloseFile)
	{
		file.close();
	}
}
