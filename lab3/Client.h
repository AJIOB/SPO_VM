//
// Created by alex on 23.03.17.
//

#ifndef TEST_LINUX_CLIENT_H
#define TEST_LINUX_CLIENT_H

#include <iostream>
#include <fstream>

#include "Person.h"
#include "AJIOBlib.h"
#include "Constants.h"

class Client {
    Person person;

    void readFile();
public:
    Client();

    void run();
};


#endif //TEST_LINUX_CLIENT_H
