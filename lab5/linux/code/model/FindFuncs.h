//
// Created by Alex on 07.04.2017.
//

#ifndef LAB5_FILES_H
#define LAB5_FILES_H


#include <dirent.h>

namespace FindFuncs
{
    int onlyFolders(const dirent *);
    int onlyTextFiles(const dirent *);
};


#endif //LAB5_FILES_H
