//
// Created by Alex on 07.04.2017.
//

#ifndef LAB5_CREATEPROCESSEXCEPTION_H
#define LAB5_CREATEPROCESSEXCEPTION_H


#include <cstring>
#include "VA_Exception.h"

class CreateProcessException : public VA_Exception
{
public:
    CreateProcessException(): VA_Exception("Ошибка создания нового процесса. Информация: " + std::string(strerror(errno)))
    {
    }
};


#endif //LAB5_CREATEPROCESSEXCEPTION_H
