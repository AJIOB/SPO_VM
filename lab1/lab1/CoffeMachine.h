#ifndef COFFE_CLASS
#define COFFE_CLASS

#include"Drink.h"
#include <vector>

class CoffeMachine
{
    private:
        int money;
        std::vector<Drink> drinks;
    public:
	void showMoney() const;
        CoffeMachine(int argc, char* argv[]);
        ~CoffeMachine();
        void addMoney(int money);
        int buy (int drinkID);
        void showAvailable();
	void moneyBack();

        void init();
        
};

#endif