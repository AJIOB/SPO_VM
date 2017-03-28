#ifndef LAB4_THREAD_H
#define LAB4_THREAD_H


#ifdef _WIN32

#elif (defined(__linux__) || defined(__unix__))
#include <chrono>
#include <thread>

class Thread
{
    char name;
    bool writeName;
    bool alive;
    pthread_t thread;

public:
    Thread(char name_, const double showInterval);
    ~Thread();
    void run();
    void stopThread();
    void askToWriteName();
};

#endif
#endif