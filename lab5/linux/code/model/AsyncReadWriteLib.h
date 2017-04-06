//
// Created by alex on 02.04.17.
//

#ifndef LAB5_ASYNCREADWRITELIB_H
#define LAB5_ASYNCREADWRITELIB_H

#include <string>
#include <aio.h>
#include <signal.h>
#include <unistd.h>

#include "Constants.h"

std::string asyncReadAllFile(const std::string &fileWay);
void asyncWriteToFileEnd(const std::string &fileWay, const std::string &toWrite);

long filelength(const char* fileName);

aiocb Make_aiocb(const int& fileDescriptor, void* bufferToRead, const long& sizeOfBuffer, int signal, int sigval_int);

#endif //LAB5_ASYNCREADWRITELIB_H
