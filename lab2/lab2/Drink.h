#ifndef DRINK_CLASS
#define DRINK_CLASS


#include<string>
class Drink
{
private:
    std::string name;
    int amountLeft;
    int price;
public:
    Drink(std::string name_,int amountLeft_,int price_);
    void addDrink(int count);
    void deleteDrink();
    void show();   
    
    std::string getName();
    int getPrice();
    int getAmount();
};


#endif 