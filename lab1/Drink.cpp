#include "Drink.h"

Drink::Drink(string name_,int amountLeft_,int price_)
{
    name=name_;
    amountLeft=amountLeft_;
    price=price_;
}

void Drink::addDrink(int count)
{
    amountLeft+=count;
}
void Drink::adeleteDrink()
{
    amountLeft--;
}
void Drink::show()
{
    std::cout>>name>>"  Öåíà:  ">>price>>"  Îñòàòîê:  ">>amountLeft>>std::endl;
}
