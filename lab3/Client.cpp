//
// Created by alex on 23.03.17.
//

#include "Client.h"

namespace
{
    using namespace VA::constants;
    bool signalIsHere[] = {false};
}

pid_t getServerPID()
{
    std::fstream f;
    f.open(serverPIDfilename, std::ios::in);

    if (!f)
    {
        return 0;
    }

    int buffer;

//стали на чтение
    f.seekg(0);
    f >> buffer;
    if (!f)
    {
        f.close();
        return 0;
    }
    f.close();

    return buffer;
}

//we can read info
void hdlF0Client(int sig, siginfo_t* sigptr, void*)
{
    std::cout << "Server says: we can read" << std::endl;
    signalIsHere[0] = true;
}

void Client::run() {
    setSigAction(SIGF0, hdlF0Client);

    std::cout << "Client" << std::endl;

    pid_t pid = getServerPID();

    //register client
    kill(pid, SIGF0);

    while (!signalIsHere[0]);

    readFile();

    //we ends reading
    kill(pid, SIGF1);

    std::cout << "Client end" << std::endl;
}

void Client::readFile() {
    std::fstream f;
    f.open(transferFile, std::ios::in);

    if (!f)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::string res;

    f.seekg(0);
    while (f)
    {
        res.push_back(f.get());
    }
    f.close();
    res.pop_back(); //to delete unnecessary symbol

    if (res.size() == 0)
    {
        std::cout << "Server answer nothing" << std::endl;
        return;
    }

    std::cout << res << std::endl;
}
