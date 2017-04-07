//
// Created by alex on 07.04.17.
//

#include <dirent.h>
#include "ProcessCreator.h"

ProcessCreator::ProcessCreator(const std::string &way) {
    parentWay = way;
}

void ProcessCreator::run() {

}

void ProcessCreator::findFolders(const std::string &way)
{
    dirent** listOfEntries;
    auto numDirEntries = scandir(way.c_str(), &listOfEntries, onlyFolders, alphasort);
    for (auto i = 0; i < numDirEntries; i++)
    {
        //todo:

    }

    auto numFilesEntries = scandir(way.c_str(), &listOfEntries, onlyTextFiles, alphasort);
    for (auto i = 0; i < numFilesEntries; i++)
    {
        fileQueue.push(way + "/" + listOfEntries[i]->d_name);
    }
}