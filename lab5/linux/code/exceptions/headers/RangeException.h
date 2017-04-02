//
// Created by alex on 02.04.17.
//

#ifndef LAB5_RANGEEXCEPTION_H
#define LAB5_RANGEEXCEPTION_H


#include "VA_Exception.h"

class RangeException : public VA_Exception
{
public:
    RangeException(): VA_Exception("Ошибка промежутка. Возможно, вы перепутали местами минимальное и максимальное значение")
    {
    }
};

#endif //LAB5_RANGEEXCEPTION_H
