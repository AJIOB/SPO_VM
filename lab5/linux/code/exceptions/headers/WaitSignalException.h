//
// Created by alex on 04.04.17.
//

#ifndef LAB5_WAITEXCEPTION_H
#define LAB5_WAITEXCEPTION_H


class WaitSignalException : public VA_Exception
{
public:
    WaitSignalException(): VA_Exception("Ошибка ожидания сигнала")
    {
    }
};


#endif //LAB5_WAITEXCEPTION_H
