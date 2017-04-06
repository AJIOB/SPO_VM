//
// Created by Alex on 06.04.2017.
//

#include "Threads.h"
#include "Sync.h"

void *ReadThread(void *ptr)
{
    Sync &s = *reinterpret_cast<Sync*> (ptr);

    while (!s.readWays.empty())
    {
        while (!s.WeCanRead && !s.ThatIsAll)
        {
            Sleep(250);
        }

        if (s.ThatIsAll)
        {
            break;
        }

        s.WeCanRead = false;

        s.transfer = s.readFileFun(s.readWays.front());
        s.readWays.pop();

        s.WeCanWrite = true;
    }

    pthread_exit(nullptr);
}

void *WriteThread(void *ptr)
{
    Sync &s = *reinterpret_cast<Sync*> (ptr);

    while (true)
    {
        while (!s.WeCanWrite && !s.ThatIsAll)
        {
            Sleep(250);
        }

        if (s.ThatIsAll)
        {
            break;
        }

        s.WeCanWrite = false;

        s.writeFileFun(s.writeWay, s.transfer);

        s.WeCanRead = true;
    }

    pthread_exit(nullptr);
}
