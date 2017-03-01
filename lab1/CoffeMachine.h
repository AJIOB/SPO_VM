#include"Drink.h"
class CoffeMachine
{
    private:
//        int moneyCount;
        int money;
        std::vector<Drink> drinks;
    public:
        CoffeMachine(int argc, char* argv[]);
        ~CoffeMachine();
        void addMoney(int money);
        int buy (int drinkID);
        void showAvailable();
        void moneyBack(int money);
        void init();
        
};
