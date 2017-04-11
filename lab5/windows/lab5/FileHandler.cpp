#include "FileHandler.h"
#include"FileThreads.h"

FileHandler::FileHandler(char* mainDir_)
{
	this -> subDirsCount = -2;
	this -> mainDir = mainDir_;
}

FileHandler::~FileHandler(void)
{
	
}

bool FileHandler::getDirectories()
{
	WIN32_FIND_DATA ffd;
	size_t length_of_arg;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	//ѕроверка длинны директории
	StringCchLength((TCHAR*)mainDir, MAX_PATH, &length_of_arg);
	if (length_of_arg > (MAX_PATH - 3))
	{
		std::cout<<"\nDirectory path is too long.\n";
		return false;
	}
	
	std::cout<<"\nTarget directory is \n"<< mainDir;
	
	//подготовка к работе с findFile. 
	StringCchCopy(szDir, MAX_PATH, (TCHAR*)mainDir);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	
	// нахождение первого файла в директории
	hFind = FindFirstFile(szDir, &ffd);
	
	if (INVALID_HANDLE_VALUE == hFind) 
	{
		std::cout<<" Error finding first file.\n The program would be terminated";
		return false;
	} 
   
	//отображение найденных директорий

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(subDirsCount>=0)
			{
				std::cout<<"\n	"<<ffd.cFileName;
				strcat(strcpy(this -> subDirs[subDirsCount],this->mainDir),ffd.cFileName);
			}
			this->subDirsCount++;
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
 
	//выделение пам€ти под массив имен директорий

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{
		std::cout<<" Error finding first file.\n The program would be terminated";
		return false;
	}

	FindClose(hFind);
	return true;
}

bool FileHandler::getFiles()
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	size_t length_of_arg;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	

	for(int i = 0; i < subDirsCount; i++)
	{
		//ѕроверка длинны директории
		StringCchLength((TCHAR*)subDirs[i], MAX_PATH, &length_of_arg);
		if (length_of_arg > (MAX_PATH - 3))
		{
			std::cout<<"\nDirectory path is too long.\n";
			return false;
		}
	
		std::cout<<"\nTarget directory is \n"<< subDirs[i]<<std::endl;
		
		//подготовка к работе с findFile. 
		StringCchCopy(szDir, MAX_PATH, (TCHAR*)subDirs[i]);
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	
		// нахождение первого файла в директории
		hFind = FindFirstFile(szDir, &ffd);

		if (INVALID_HANDLE_VALUE == hFind) 
		{
			return false;
		} 
   
		// List all the files in the directory with some info about them.
		char rootDir[MAX_PATH];
		strcpy(rootDir,subDirs[i]);
		strcat(rootDir,".txt");
		
		FileThreads ft(subDirs[i],rootDir,ffd, hFind);
		
		/*if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
			return false;
		}*/
	}
		FindClose(hFind);
		return true;
}
