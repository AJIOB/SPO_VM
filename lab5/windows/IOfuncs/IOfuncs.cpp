// IOfuncs.cpp : Defines the exported functions for the DLL application.  
// Compile by using: cl /EHsc /DIOfuncs_EXPORTS /LD IOfuncs.cpp  

#include "stdafx.h"  
#include "IOfuncs.h"  

#include "../lab5/FileThreads.h"

namespace IOfuncs  
{
	DWORD Functions::runWriter(LPVOID lpParam)
	{
		FileThreads* p = reinterpret_cast<FileThreads*>(lpParam);
	
		HANDLE destinationFile;
	
		if(p -> isFirst)
		{
			destinationFile = CreateFile(p -> rootDir,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			p -> isFirst = false;
		}
		else
		{
			destinationFile = CreateFile(p -> rootDir,FILE_APPEND_DATA,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		}
		do
		{
			WaitForSingleObject(p->readerCompleted,INFINITE);
			DWORD nWritten;
			WriteFile(destinationFile, p->buffer, p -> filesize.QuadPart, &nWritten, NULL);
			if (!SetEvent(p->writerCompleted))
			{
				std::cout << "error in setting event"; //error. Event is not pulsed
				return -1;
			}
		} while(true);	

		return 0;
	}

	DWORD Functions::runReader(LPVOID lpParam)
	{
		FileThreads* p = reinterpret_cast<FileThreads*>(lpParam);

		do
			{
				if (!(p->ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					p->filesize.LowPart = p->ffd.nFileSizeLow;
					p->filesize.HighPart = p->ffd.nFileSizeHigh;
					char fileToCopy[MAX_PATH];
					strcpy(fileToCopy,p -> directory);
					strcat(fileToCopy,"\\");
					strcat(fileToCopy,p -> ffd.cFileName);

					std::cout<<p->ffd.cFileName<<"  "<<p->filesize.QuadPart<<" bytes\n";

					HANDLE sourceFile;
				
					p->buffer = new char[p -> filesize.QuadPart];
	
					sourceFile = CreateFile(fileToCopy,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE ,
						NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

					DWORD nRead;
					ReadFile(sourceFile, p->buffer, p -> filesize.QuadPart, &nRead, NULL);
					CloseHandle(sourceFile);
					//setEvent witer yo write
					if (!SetEvent(p->readerCompleted))
					{
						std::cout << "Error working with events"; //error. Event is not pulsed
						return -1;
					}

					WaitForSingleObject(p->writerCompleted,INFINITE);
				}
			}
			while (FindNextFile(p->hFind, &p->ffd) != 0);

			if (!SetEvent(p->readerStop))
			{
				std::cout << "Error working with events"; //error. Event is not pulsed
				return -1;
			}
	
		return 0;
	}
}  