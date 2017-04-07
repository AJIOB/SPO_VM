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
    std::deque<std::string> childPIDs;

    void findFolders(const std::string &way);

public:
    ProcessCreator(const std::string& way);

    void run();
};


#endif //LAB5_PROCESSCREATOR_H
