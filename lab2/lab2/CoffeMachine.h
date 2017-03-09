#ifndef COFFE_CLASS
#define COFFE_CLASS

#include"Drink.h"
#include <vector>

class CoffeMachine
{
    private:
        int money;
        std::vector<Drink> drinks;
		void setCommand();
		void getCommand();
		void addMoney(int money);
        int buy (int drinkID);
        void showAvailable();
		void moneyBack();
    public:
	void showMoney() const;
        CoffeMachine();
        ~CoffeMachine();
        void proceed();
		void writeToFile();
};

#endif