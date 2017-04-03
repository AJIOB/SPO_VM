//
// Created by alex on 02.04.17.
//

#include "ParserManager.h"

ParserManager::ParserManager(const std::string &rootWay) {
    this->rootWay = rootWay;

    onlyFolders = [](const struct dirent* d)->int
    {
        //non-zero return => selected

        if (!d)
        {
            return 0;
        }

        return (d->d_type != DT_DIR);
    };

    onlyTextFiles = [](const struct dirent* d)->int
    {
        //non-zero return => selected
        if (!d)
        {
            return 0;
        }

        std::string fName = d->d_name;
        std::string requiredExtension[] = {".txt", ".TXT"};
        if (fName.size() < requiredExtension[0].size())
        {
            return 0;
        }

        auto fExtension = fName.substr(fName.size() - requiredExtension[0].size(), requiredExtension[0].size());

        bool isTXT = (fExtension == requiredExtension[0]) || (fExtension == requiredExtension[1]);

        return !((d->d_type == DT_UNKNOWN) && (isTXT));
    };
}

void ParserManager::run() {
    findFilesRecursively(rootWay);

    //todo
}

void ParserManager::findFilesRecursively(const std::string &way)
{
    dirent** listOfEntries;
    auto numDirEntries = scandir(rootWay.c_str(), &listOfEntries, onlyFolders, alphasort);
    for (auto i = 0; i < numDirEntries; i++)
    {
        findFilesRecursively(way + "//" + listOfEntries[i]->d_name);
    }

    auto numFilesEntries = scandir(rootWay.c_str(), &listOfEntries, onlyTextFiles, alphasort);
    for (auto i = 0; i < numFilesEntries; i++)
    {
        fileQueue.push(way + "//" + listOfEntries[i]->d_name);
    }
}
