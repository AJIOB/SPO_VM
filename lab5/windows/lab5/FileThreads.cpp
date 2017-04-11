#include "FileThreads.h"

DWORD WINAPI runWriter(LPVOID lpParam);
DWORD WINAPI runReader(LPVOID lpParam);

FileThreads::FileThreads(char* directory_,char* rootDir_, WIN32_FIND_DATA ffd_,HANDLE hFind_)
{
	ffd=ffd_;
	hFind=hFind_;
	strcpy(directory,directory_);
	strcpy(rootDir,rootDir_);
	isFirst = true;

	writerCompleted = CreateEvent(NULL, false, false, NULL);
	readerCompleted = CreateEvent(NULL, false, false, NULL);
	readerStop = CreateEvent(NULL, false, false, NULL);
	threadReader = CreateThread(NULL,0,runReader,this,0,NULL);
	threadWriter = CreateThread(NULL,0,runWriter,this,0,NULL);
	WaitForSingleObject(readerStop,INFINITE);

	std::cout<<"writing finished";
}

FileThreads::~FileThreads(void)
{
}

DWORD WINAPI runWriter(LPVOID lpParam)
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

DWORD WINAPI runReader(LPVOID lpParam)
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
