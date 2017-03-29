#ifndef LAB4_THREAD_H
#define LAB4_THREAD_H


#ifdef _WIN32

#elif (defined(__linux__) || defined(__unix__))
#include <chrono>
#include <thread>
#include <iostream>

class Thread
{
    pthread_t* thread;

public:
    char name;
    bool writeName;
    bool alive;
    bool isStoppedWriting;

    Thread(char name_);
    Thread(const Thread &t);
    ~Thread();

    void stopThread();
    void askToWriteName();
};

#endif
#endif