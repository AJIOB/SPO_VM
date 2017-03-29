#include <iostream>

#include "Thread.h"

#ifdef _WIN32

#elif (defined(__linux__) || defined(__unix__))

void* run(void* thread_data);

Thread::Thread(char name_)
{
    this -> writeName = false;
    this -> alive = true;
    this -> name = name_;

    pthread_create(&thread, NULL, run, this);
}



Thread::~Thread()
{
    
}

void* run(void* thread_data)
{
    if (!thread_data)
    {
        std::cout<<"проблемы с потоком";
        pthread_exit(NULL);
    }

    Thread *thread = reinterpret_cast<Thread*>(thread_data);
    while(thread->alive)
    {
        if(thread->writeName)
        {
            thread->writeName = false;
            std::cout<<" "<<thread->name<<" ";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    pthread_exit(NULL);
}

void Thread::stopThread()
{
    this -> alive = false;
}

 void Thread::askToWriteName()
{
    this -> writeName = true;
}

Thread::Thread(const Thread& t) : thread(t.thread), name(t.name), writeName(t.writeName), alive(t.alive)
{}

#endif