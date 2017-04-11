//
// Created by alex on 07.04.17.
//

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <wait.h>
#include "ProcessCreator.h"
#include "FindFuncs.h"
#include "../exceptions/AllExceptions.h"
#include "Constants.h"
#include "../view/headers/view.h"

ProcessCreator::ProcessCreator(const std::string &way) {
    parentWay = way;
}

void ProcessCreator::run() {
    auto folders = findFolders(parentWay);
    for (auto it = folders.begin(); it != folders.end(); ++it)
    {
        createProcess(*it);
    }

    for (auto it = childPIDs.begin(); it != childPIDs.end(); ++it)
    {
        pid_t wpid = waitpid(*it, nullptr, 0);
        if (wpid < 0)
        {
            PrintError("Ошибка ожидания процесса с PID " + std::to_string(wpid) + ". Ошибка: " + strerror(errno));
        }
    }
}

std::deque<std::string> ProcessCreator::findFolders(const std::string &way)
{
    using namespace FindFuncs;
    dirent** listOfEntries;
    auto numDirEntries = scandir(way.c_str(), &listOfEntries, onlyFolders, alphasort);
    std::deque<std::string> res;

    for (auto i = 0; i < numDirEntries; i++)
    {
        res.push_back(way + "/" + listOfEntries[i]->d_name);
    }

    return res;
}

void ProcessCreator::createProcess(const std::string& CMDLine)
{
    using namespace VA_const;

    pid_t pid = fork();
    if (pid < 0)
    {
        throw CreateProcessException();
    }

    if (!pid)
    {
        //child
        if (execve(childCallName, GenerateCallingParams(CMDLine), nullptr))
        {
            throw CreateProcessException();
        }
    }

    //parent
    childPIDs.push_back(pid);
}

char **ProcessCreator::GenerateCallingParams(const std::string &CMDParam)
{
    using namespace VA_const;

    char** arr = new char*[3];
    arr[0] = new char[sizeof(childCallName) + 1];
    arr[1] = new char[CMDParam.size() + 1];
    arr[2] = nullptr;

    strcpy(arr[0], childCallName);
    strcpy(arr[1], CMDParam.c_str());

    return arr;
}

ProcessCreator::~ProcessCreator()
{
    for (auto it = arguments.begin(); it != arguments.end(); ++it)
    {
        char **ptr = *it;
        while(*ptr)
        {
            delete [] *ptr;
            ptr++;
        }

        delete [] *it;
    }
}
