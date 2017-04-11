#pragma once
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
class FileHandler
{
private:

public:
	
	char subDirs[MAX_PATH][100];
	char* mainDir;
	
	FileHandler(char* mainDir);
	~FileHandler(void);
	bool getDirectories();
	bool getFiles();
	bool createFileThreads(char* directory,char*file, LARGE_INTEGER ilesize,char* rootDir);
	//static DWORD WINAPI runWriter(LPVOID lpParam);

	int subDirsCount;
};

