//
// Created by Alex on 06.04.2017.
//

#ifndef LAB5_SYNC_H
#define LAB5_SYNC_H

#include <string>
#include <queue>

#include <thread>
#include <chrono>

struct Sync
{
    bool WeCanRead = false;
    bool WeCanWrite = false;
    bool ThatIsAll = false;

    std::queue<std::string> readWays;
    std::string writeWay;

    std::string (*readFileFun)(const std::string &fileWay);
    void (*writeFileFun)(const std::string &fileWay, const std::string &toWrite);

    std::string transfer;
};

void Sleep(int ms);

#endif //LAB5_SYNC_H
