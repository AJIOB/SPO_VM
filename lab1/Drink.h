#include<string>
class Drink
{
private:
    std::string name;
    int amountLeft;
    int price;
public:
    Drink(string name_,int amountLeft_,int price_);
    void addDrink(int count);
    void deleteDrink();
    void show();   
    
    std::string getName();
    int getPrice();
    int getAmount();
};
