#ifndef VA_CONSTANTS
#define VA_CONSTANTS

#ifdef _WIN32
#include <Windows.h>
#endif

namespace VA
{
	namespace constants
	{
		static const char transferFile[] = "transfer.db";

#ifdef _WIN32

		static const LPCTSTR isMachineFree = TEXT("isMachineFree");
		static const LPCTSTR fromUser = TEXT("fromUser");
		static const LPCTSTR fromMachine = TEXT("fromMachine");
		static const LPCTSTR disconnectUser = TEXT("disconnectUser");

		static const LPCTSTR shmPersonName = TEXT("shmPersonName");


#elif (defined(__linux__) || defined(__unix__))

		static const char serverPIDfilename[] = "serverPID.db";
		static const int SIGF0 = 10;
		static const int SIGF1 = 11;
		static const int SIGF2 = 12;

		static const char shmPersonName[] = "//shmPersonName";
#endif
	}
}

#endif
