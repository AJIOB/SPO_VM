#ifndef VA_CONSTANTS
#define VA_CONSTANTS

namespace VA_const
{
#ifdef __CYGWIN__
    static const char dllName[] = "./cygVA_ARW.dll";
#else
    static const char dllName[] = "./libVA_ARW.so";
#endif

    static const int readFinished = 1;
    static const int writeFinished = 2;

    static const int RWFinishedSignal = 12;

    static const char extension[] = ".txt";
}

#endif
