//
// Created by alex on 02.04.17.
//

#include "ParserManager.h"

ParserManager::ParserManager(const std::string &rootWay) {
    this->rootWay = rootWay;

    onlyFolders = [](const dirent* d)->int
    {
        //non-zero return => selected

        if (!d)
        {
            return 0;
        }

        if (d->d_type != DT_DIR)
        {
            return 0;
        }

        if (d->d_name == std::string(".") || (d->d_name == std::string("..")))
        {
            return 0;
        }

        return 1;
    };

    onlyTextFiles = [](const dirent* d)->int
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

        if ((d->d_type != DT_DIR) && (isTXT))
        {
            return 1;
        }

        return 0;
    };
}

void ParserManager::run() {
    findFilesRecursively(rootWay);

    //todo
}

void ParserManager::findFilesRecursively(const std::string &way)
{
    dirent** listOfEntries;
    auto numDirEntries = scandir(way.c_str(), &listOfEntries, onlyFolders, alphasort);
    for (auto i = 0; i < numDirEntries; i++)
    {
        findFilesRecursively(way + "/" + listOfEntries[i]->d_name);
    }

    auto numFilesEntries = scandir(way.c_str(), &listOfEntries, onlyTextFiles, alphasort);
    for (auto i = 0; i < numFilesEntries; i++)
    {
        fileQueue.push(way + "/" + listOfEntries[i]->d_name);
    }
}
