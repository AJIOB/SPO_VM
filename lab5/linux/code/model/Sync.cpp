//
// Created by Alex on 06.04.2017.
//

#include "Sync.h"

void Sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
