//
// Created by alex on 02.04.17.
//

#ifndef LAB5_READER_H
#define LAB5_READER_H

#include <string>
#include <queue>

#include <dirent.h>

class ParserManager {
    std::string rootWay;
    std::queue<std::string> fileQueue;

public:
    ParserManager(const std::string& rootWay);

    void run();
};


#endif //LAB5_READER_H
