//
// Created by Alex on 06.04.2017.
//

#include <unistd.h>
#include "Threads.h"
#include "Sync.h"

void *ReadThread(void *ptr)
{
    Sync *s = reinterpret_cast<Sync*> (ptr);

    if (!s)
    {
        pthread_exit(nullptr);
    }

    while (!s->readWays.empty())
    {
        while (!s->WeCanRead && !s->ThatIsAll)
        {
            Sleep(250);
        }

        if (s->ThatIsAll)
        {
            break;
        }

        s->WeCanRead = false;

        s->transfer = s->readFileFun(s->readWays.front());
        s->readWays.pop();

        s->WeCanWrite = true;
    }

    s->ThisIsLast = true;

    pthread_exit(nullptr);
}

void *WriteThread(void *ptr)
{
    Sync *s = reinterpret_cast<Sync*> (ptr);

    if (!s)
    {
        pthread_exit(nullptr);
    }

    unlink(s->writeWay.c_str());

    while (true)
    {
        while (!s->WeCanWrite && !s->ThatIsAll)
        {
            Sleep(250);
        }

        if (s->ThatIsAll)
        {
            break;
        }

        s->WeCanWrite = false;

        s->writeFileFun(s->writeWay, s->transfer);

        if (s->ThisIsLast)
        {
            break;
        }

        s->WeCanRead = true;
    }

    s->ThatIsAll = true;

    pthread_exit(nullptr);
}
