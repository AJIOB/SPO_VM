#include "FileThreads.h"

#include "IOfuncs.h"

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
	threadReader = CreateThread(NULL,0,IOfuncs::Functions::runReader,this,0,NULL);
	threadWriter = CreateThread(NULL,0,IOfuncs::Functions::runWriter,this,0,NULL);
	WaitForSingleObject(readerStop,INFINITE);

	std::cout<<"writing finished";
}

FileThreads::~FileThreads(void)
{
}
