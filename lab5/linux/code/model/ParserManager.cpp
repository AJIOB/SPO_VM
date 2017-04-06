//
// Created by alex on 02.04.17.
//

#include "ParserManager.h"
#include "../view/headers/view.h"

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

std::string (*readFile)(const std::string &fileWay);

void ParserManager::run() {
    //setSigAction(RWFinishedSignal, ignore_handler);

    findFilesRecursively(rootWay);

    auto dllDescriptor = dlopen(dllName, RTLD_LAZY);

    if (!dllDescriptor)
    {
        throw BadLoadingDLLException(dlerror());
    }

    readFile = (std::string (*)(const std::string &)) dlsym(dllDescriptor, "asyncReadAllFile");

    auto err = dlerror();
    if (err)
    {
        dlclose(dllDescriptor);
        throw BadLoadingDLLException(err);
    }

    PrintLine(readFile(fileQueue.front()));

    //todo


    dlclose(dllDescriptor);
}

void ParserManager::findFilesRecursively(const std::string &way)
{
    std::string goodWay = (way.back() == '/') ? way.substr(0, way.size() - 1) : way;

    dirent** listOfEntries;
    auto numDirEntries = scandir(goodWay.c_str(), &listOfEntries, onlyFolders, alphasort);
    for (auto i = 0; i < numDirEntries; i++)
    {
        findFilesRecursively(goodWay + "/" + listOfEntries[i]->d_name);
    }

    auto numFilesEntries = scandir(goodWay.c_str(), &listOfEntries, onlyTextFiles, alphasort);
    for (auto i = 0; i < numFilesEntries; i++)
    {
        fileQueue.push(goodWay + "/" + listOfEntries[i]->d_name);
    }
}
