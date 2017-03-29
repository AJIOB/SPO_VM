cmake_minimum_required(VERSION 3.6)
project(lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        code/logs.h
        code/main.cpp
        code/StreamInput.h
        code/Sync.h
        code/Thread.cpp
        code/Thread.h
        code/ThreadFuncs.cpp
        code/ThreadFuncs.h
        code/ThreadManager.cpp
        code/ThreadManager.h
        code/UI.cpp
        code/UI.h
        code/VA_Exception.h)

add_executable(lab4 ${SOURCE_FILES})