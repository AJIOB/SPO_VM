#pragma once
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
class FileThreads
{
		
	HANDLE threadWriter;
	HANDLE threadReader;
public:

	bool isFirst;

	HANDLE writerCompleted;
	HANDLE readerCompleted;
	HANDLE readerStop;
	WIN32_FIND_DATA ffd;
	char directory[MAX_PATH];
	char file[MAX_PATH];
	LARGE_INTEGER filesize;
	HANDLE hFind;
	char rootDir[MAX_PATH];
	char* buffer;

	FileThreads(char* directory_, char* rootDir_, WIN32_FIND_DATA ffd_,HANDLE hFind_);
	~FileThreads(void);
};

