//
// Created by alex on 07.04.17.
//

#ifndef LAB5_BADCMDAGRSEXCEPTION_H
#define LAB5_BADCMDAGRSEXCEPTION_H


#include "VA_Exception.h"

class BadCMDAgrsException : public VA_Exception
{
public:
    BadCMDAgrsException(const int& num): VA_Exception("Неожиданные параметры командной строки. Ожидался " + std::to_string(num) + " параметр(-ов)")
    {
    }
};


#endif //LAB5_BADCMDAGRSEXCEPTION_H
