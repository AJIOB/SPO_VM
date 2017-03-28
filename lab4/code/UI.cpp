#include "UI.h"

UI::UI(char* showPeriod, char* generateNewThreadPeriod)
	: model(std::stod(showPeriod), std::stod(generateNewThreadPeriod))
{
}

void UI::run()
{
	model.runAll();

	do
	{
		std::cout << "Выберите, пожалуйста, ваше действие:" << std::endl;
		std::cout << "1) Добавить новый поток" << std::endl;
		std::cout << "2) Просмотреть количество потоков" << std::endl;
		std::cout << "3) Удалить случайный поток" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;

		auto k = std::cin.get();
		Stream::Clear();

		switch (k)
		{
		case '0':
			{
				std::cout << std::endl << "Программа завершается. Пожалуйста, подождите..." << std::endl;
				return;
			}
		case '1':
			{
				model.generateNewThread();
				break;
			}
		case '2':
			{
				std::cout << model.getNumOfThreads() << std::endl;
				break;
			}
		case '3':
			{
				model.removeThread();
				break;
			}
		default:
			{
				std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
			}
		}
	}
	while (true);
}
