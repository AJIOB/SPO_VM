#include "Thread.h"
#ifdef _WIN32

#elif (defined(__linux__) || defined(__unix__))

    Thread::Thread(char name_, const double showInterval)
    {
        this -> writeName = false;
        this -> alive = true;
        this -> name = name_;

        void* thread_data = NULL;
        pthread_create(&thread, NULL, run, thread_data);
    }

    Thread::~Thread()
    {
        free(thread);
    }

    void* Thread::run(void* thread_data)
    {
        while(alive)
        {
            if(writeName)
            {
                writeName = false;
                std::cout<<" "<<name<<" ";
            }
            std::this_thread::sleep_for(0,1s);
        }
        pthread_exit(0);
    }

    void Thread::stopThread()
    {
        this -> alive = false;
    }

     void Thread::askToWriteName()
    {
        this -> writeName = true;
    }

#endif