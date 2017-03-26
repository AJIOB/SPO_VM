#ifndef AJIOB_LIB
#define AJIOB_LIB


#if (defined(__linux__) || defined(__unix__))

#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int setSigAction(int sig, void (*handleFun) (int, siginfo_t*, void*));

#endif

#endif