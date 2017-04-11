//
// Created by alex on 07.04.17.
//

#ifndef LAB5_PROCESSCREATOR_H
#define LAB5_PROCESSCREATOR_H

#include <string>
#include <deque>

class ProcessCreator
{
    std::string parentWay;
    std::deque<pid_t> childPIDs;
    std::deque<char**> arguments;

    std::deque<std::string> findFolders(const std::string &way);

    void createProcess(const std::string& CMDParameter);
    char **GenerateCallingParams(const std::string &CMDParam);

public:
    ProcessCreator(const std::string& way);
    ~ProcessCreator();

    void run();
};


#endif //LAB5_PROCESSCREATOR_H
