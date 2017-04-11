//
// Created by alex on 02.04.17.
//

#include "ParserManager.h"
#include "FindFuncs.h"

ParserManager::ParserManager(const std::string &rootWay_) {
    this->rootWay = rootWay_;
    while (rootWay.back() == '/')
    {
        rootWay = rootWay.substr(0, rootWay.size() - 1);
    }
}

void ParserManager::run() {
    using namespace VA_const;

    //setSigAction(RWFinishedSignal, ignore_handler);
    findFilesRecursively(rootWay);

    auto dllDescriptor = dlopen(dllName, RTLD_LAZY);

    if (!dllDescriptor)
    {
        throw BadLoadingDLLException(dlerror());
    }

    Sync* sync = new Sync;

    sync->readFileFun = (std::string (*)(const std::string &)) dlsym(dllDescriptor, "asyncReadAllFile");
    auto err = dlerror();
    if (err)
    {
        dlclose(dllDescriptor);
        throw BadLoadingDLLException(err);
    }

    sync->writeFileFun = (void (*)(const std::string &, const std::string &)) dlsym(dllDescriptor, "asyncWriteToFileEnd");
    err = dlerror();
    if (err)
    {
        dlclose(dllDescriptor);
        throw BadLoadingDLLException(err);
    }

    sync->readWays = fileQueue;
    sync->writeWay = rootWay + extension;

    pthread_t reader, writer;
    if (pthread_create(&reader, nullptr, ReadThread, sync) || pthread_create(&writer, nullptr, WriteThread, sync))
    {
        throw CreatingNewThreadException();
    }
    
    sync->WeCanRead = true;

    while (!sync->ThatIsAll)
    {
        Sleep(250);
    }

    pthread_join(reader, nullptr);
    pthread_join(writer, nullptr);

    delete sync;
    dlclose(dllDescriptor);

}

void ParserManager::findFilesRecursively(const std::string &way)
{
    using namespace FindFuncs;

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
