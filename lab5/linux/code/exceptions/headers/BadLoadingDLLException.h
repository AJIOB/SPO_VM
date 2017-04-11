//
// Created by Alex on 04.04.2017.
//

#ifndef LAB5_ERRORLOADINGDLLEXCEPTION_H
#define LAB5_ERRORLOADINGDLLEXCEPTION_H

#include "VA_Exception.h"

class BadLoadingDLLException: public VA_Exception
{
public:
    BadLoadingDLLException(const std::string& s): VA_Exception("Ошибка загрузки динамического модуля: " + s)
    {
    }
};


#endif //LAB5_ERRORLOADINGDLLEXCEPTION_H
