//
// Created by alex on 04.04.17.
//

#ifndef LAB5_OPENFILEEXCEPTION_H
#define LAB5_OPENFILEEXCEPTION_H


#include "VA_Exception.h"

class OpenFileException : public VA_Exception
{
public:
    OpenFileException(): VA_Exception("Ошибка открытия файла")
    {
    }
};


#endif //LAB5_OPENFILEEXCEPTION_H
