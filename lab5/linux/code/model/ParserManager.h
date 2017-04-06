//
// Created by alex on 02.04.17.
//

#ifndef LAB5_READER_H
#define LAB5_READER_H

#include <string>
#include <queue>

#include <dirent.h>
#include <dlfcn.h>
#include <thread>

#include "../exceptions/AllExceptions.h"
#include "Sync.h"
#include "Threads.h"
#include "handlers.h"
#include "Constants.h"


class ParserManager {
    std::string rootWay;
    std::queue<std::string> fileQueue;

    void findFilesRecursively(const std::string& way);

    int (*onlyFolders)(const dirent *);
    int (*onlyTextFiles)(const dirent *);

public:
    ParserManager(const std::string& rootWay);

    void run();
};


#endif //LAB5_READER_H
