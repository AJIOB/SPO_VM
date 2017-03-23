//
// Created by alex on 23.03.17.
//

#ifndef TEST_LINUX_SERVER_H
#define TEST_LINUX_SERVER_H

#include <iostream>
#include <queue>
#include <fstream>
#include <signal.h>
#include <unistd.h>

#include "AJIOBlib.h"
#include "Constants.h"


class Server {

    pid_t currPID;
    void writePID();

public:
    Server();

    void run();

    void writeFile();
};


#endif //TEST_LINUX_SERVER_H
