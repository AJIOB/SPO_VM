#include "handlers.h"

int setSigAction(int sig, void (*handleFun) (int))
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));	//clear all struct
	act.sa_handler = handleFun;       //todo: fix (not sigaction)
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	act.sa_mask = set;
	return sigaction(sig, &act, NULL);
}

void ignore_handler(int sig)
{
    
}