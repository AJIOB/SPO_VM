#ifndef HANDLERS_H
#define HANDLERS_H

#include <signal.h>
#include <cstring>

int setSigAction(int sig, void (*handleFun) (int));
void ignore_handler(int sig);

#endif
