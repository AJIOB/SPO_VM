//
// Created by Alex on 06.04.2017.
//

#ifndef LAB5_CREATINGNEWTHREADEXCEPTION_H
#define LAB5_CREATINGNEWTHREADEXCEPTION_H


#include "VA_Exception.h"

class CreatingNewThreadException : public VA_Exception
{
public:
    CreatingNewThreadException(): VA_Exception("Ошибка создания нового потока")
    {
    }
};


#endif //LAB5_CREATINGNEWTHREADEXCEPTION_H
