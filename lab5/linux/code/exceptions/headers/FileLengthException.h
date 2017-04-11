//
// Created by alex on 04.04.17.
//

#ifndef LAB5_FILELENGTHEXCEPTION_H
#define LAB5_FILELENGTHEXCEPTION_H


#include "VA_Exception.h"

class FileLengthException : public VA_Exception
{
public:
    FileLengthException(): VA_Exception("Ошибка расчета длины файла")
    {
    }
};


#endif //LAB5_FILELENGTHEXCEPTION_H
