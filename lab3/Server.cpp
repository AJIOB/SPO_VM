//
// Created by alex on 23.03.17.
//


#include "Server.h"

namespace
{
    using namespace VA::constants;
    std::queue<pid_t> PIDq;
    bool signalIsHere[] = {false, false};
    bool isStopServer = false;
}

//save pid to queue
void hdlF0Server(int sig, siginfo_t *sigptr, void *)
{
    std::cout << "Client want to add itself" << std::endl;

    if (!sigptr)
    {
        return;
    }

    PIDq.push(sigptr -> si_pid);

    signalIsHere[0] = true;
}

//нужно обработать результаты
void hdlF1Server(int sig, siginfo_t *sigptr, void *)
{
    std::cout << "Client is answer. His pid is ";

    if (!sigptr)
    {
        return;
    }

    std::cout << sigptr -> si_pid << std::endl;

    signalIsHere[1] = true;
}

//нужно выключить сервер
void hdlINTServer(int sig)
{
    std::cout << "Close server..." << std::endl;

    isStopServer = true;
}

//нужно выключить сервер
void hdlINTServer2(int sig, siginfo_t *sigptr, void *)
{
    std::cout << "Close server..." << std::endl;

    isStopServer = true;
}


void Server::writePID() {
    std::fstream f;
    f.open(serverPIDfilename, std::ios::out | std::ios::trunc);

    if (!f) {
        std::cout << "Error reading file" << std::endl;
        return;
    }

    f << (int)getpid();
    f.close();
}

void Server::writeFile() {
    std::fstream f;
    f.open(transferFile, std::ios::out | std::ios::trunc);

    if (!f) {
        std::cout << "Error reading file" << std::endl;
        return;
    }

    f << "Hello from server";
    f.close();
}

void Server::run() {
    std::cout << "Server" << std::endl;

    writeFile();

    while (true) {
        if (isStopServer)
        {
            break;
        }

        while (PIDq.empty());

        pid_t pid = PIDq.front();
        PIDq.pop();

        kill(pid, SIGF0);

        while (!signalIsHere[1]);

        signalIsHere[1] = false;

        std::cout << "All is good" << std::endl;
        std::cout << "isStopServer = " << isStopServer << std::endl;
    }
}

Server::Server() {
    setSigAction(SIGF0, hdlF0Server);
    setSigAction(SIGF1, hdlF1Server);
    setSigAction(SIGINT, hdlINTServer2);

    writePID();

    currPID = 0;
}

Server::~Server() {
    unlink(serverPIDfilename);
}
