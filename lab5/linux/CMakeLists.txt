cmake_minimum_required(VERSION 3.7)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

set(consoleIO_files
        code/view/headers/view.h

        code/view/headers/log.h
        code/view/headers/StreamInput.h
        code/view/headers/StreamOutput.h

        code/view/source/log.cpp
        code/view/source/StreamInput.cpp
        code/view/source/StreamOutput.cpp
        )

set(VA_exceptions
        code/exceptions/AllExceptions.h
        code/exceptions/headers/VA_Exception.h
        code/exceptions/headers/RangeException.h
        code/exceptions/headers/OpenFileException.h
        code/exceptions/headers/FileLengthException.h
        code/exceptions/headers/WaitSignalException.h
        code/exceptions/headers/BadLoadingDLLException.h
        code/exceptions/headers/CreatingNewThreadException.h)

set(SOURCE_FILES code/main.cpp)

set(parser_files
        code/parser_main.cpp
        code/model/ParserManager.cpp
        code/model/ParserManager.h
        code/model/handlers.h
        code/model/handlers.cpp
        code/model/Threads.cpp code/model/Threads.h code/model/Sync.h code/model/Sync.cpp)

set(dynamicLib_Files
        code/model/AsyncReadWriteLib.h
        code/model/AsyncReadWriteLib.cpp
        )

add_library(VA_ARW SHARED ${dynamicLib_Files} ${VA_exceptions} code/model/Constants.h)

add_executable(lab5 ${SOURCE_FILES} ${consoleIO_files} ${VA_exceptions})
add_executable(oneFolderParser ${parser_files} ${consoleIO_files} ${VA_exceptions} code/model/Constants.h)

target_link_libraries(oneFolderParser ${CMAKE_DL_LIBS})
target_link_libraries(VA_ARW -lrt)
