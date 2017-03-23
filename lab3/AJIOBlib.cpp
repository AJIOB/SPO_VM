#include "AJIOBlib.h"

#if (defined(__linux__) || defined(__unix__))

int setSigAction(int sig, void (*handleFun) (int, siginfo_t*, void*))
{
	struct sigaction act;
	memset(&act, NULL, sizeof(act));	//clear all struct
	act.sa_sigaction = handleFun;
	act.sa_flags = SA_SIGINFO;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	act.sa_mask = set;
	return sigaction(sig, &act, NULL);
}

#endif