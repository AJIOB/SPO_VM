ParserObjects = parser_main.o ParserManager.o handlers.o Threads.o Sync.o FindFuncs.o
ViewObjects = log.o StreamInput.o StreamOutput.o
dllObjects = AsyncReadWriteLib.o
mainObjects = main.o ProcessCreator.o FindFuncs.o

CFLAGS = -std=c++11
CXXFLAGS = $(CFLAGS)

destinationLinkFlags = 
parserLinkFlags = -lrt -ldl -pthread
dllLinkFlags = -lrt

sourceWay = code/
ViewWayHeaders = view/headers/
ViewWaySource = view/source/
modelWay = model/

destinationWay = bin/unix/
destinationName = lab5
dllDestName = libVA_ARW.so
parserDestName = parser

deps = VA_$(destinationName).log

objWay = $(destinationWay)obj/
objBackHome = ../../../

goObject = cd $(objWay) &&
compilerPrefix = $(goObject) $(CXX)
prefix = $(compilerPrefix) $(CXXFLAGS) -c $(objBackHome)$(sourceWay)

MKDIR = mkdir -p
RMDIR = -rm -r
COPY = cp


.PHONY: buildAll parser $(destinationName) clean max_clean baseInit copyDeps run runParams

buildAll : baseInit $(destinationName) $(parserDestName) $(dllDestName) copyDeps

$(destinationName) : $(mainObjects) $(ViewObjects)
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(destinationName) $(mainObjects) $(ViewObjects) $(destinationLinkFlags)

$(parserDestName) : $(ParserObjects) $(ViewObjects)
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(parserDestName) $(ParserObjects) $(ViewObjects) $(parserLinkFlags)

$(dllDestName) : $(dllObjects)
	$(compilerPrefix) -shared $(dllObjects) -o $(objBackHome)$(destinationWay)$(dllDestName) $(dllLinkFlags)

#------------------------------------main-----------------------------
main.o : $(sourceWay)main.cpp
	$(prefix)main.cpp
ProcessCreator.o : $(sourceWay)$(modelWay)ProcessCreator.cpp $(sourceWay)$(modelWay)ProcessCreator.h
	$(prefix)$(modelWay)ProcessCreator.cpp

#------------------------------------dll------------------------------
AsyncReadWriteLib.o : $(sourceWay)$(modelWay)AsyncReadWriteLib.cpp $(sourceWay)$(modelWay)AsyncReadWriteLib.h
	$(prefix)$(modelWay)AsyncReadWriteLib.cpp -fPIC

#------------------------------------parser---------------------------
parser_main.o : $(sourceWay)parser_main.cpp
	$(prefix)parser_main.cpp
	
ParserManager.o : $(sourceWay)$(modelWay)ParserManager.cpp $(sourceWay)$(modelWay)ParserManager.h
	$(prefix)$(modelWay)ParserManager.cpp

handlers.o : $(sourceWay)$(modelWay)handlers.cpp $(sourceWay)$(modelWay)handlers.h
	$(prefix)$(modelWay)handlers.cpp

Threads.o : $(sourceWay)$(modelWay)Threads.cpp $(sourceWay)$(modelWay)Threads.h
	$(prefix)$(modelWay)Threads.cpp

Sync.o : $(sourceWay)$(modelWay)Sync.cpp $(sourceWay)$(modelWay)Sync.h
	$(prefix)$(modelWay)Sync.cpp

FindFuncs.o : $(sourceWay)$(modelWay)FindFuncs.cpp $(sourceWay)$(modelWay)FindFuncs.h
	$(prefix)$(modelWay)FindFuncs.cpp

#------------------------------------view-----------------------------
log.o : $(sourceWay)$(ViewWaySource)log.cpp $(sourceWay)$(ViewWayHeaders)log.h
	$(prefix)$(ViewWaySource)log.cpp

StreamInput.o : $(sourceWay)$(ViewWaySource)StreamInput.cpp $(sourceWay)$(ViewWayHeaders)StreamInput.h
	$(prefix)$(ViewWaySource)StreamInput.cpp

StreamOutput.o : $(sourceWay)$(ViewWaySource)StreamOutput.cpp $(sourceWay)$(ViewWayHeaders)StreamOutput.h
	$(prefix)$(ViewWaySource)StreamOutput.cpp	
#------------------------------------logs-----------------------------


#------------------------------------other----------------------------
max_clean :
	$(MAKE) -i clean
	$(RMDIR) $(destinationWay)

clean :
	$(RMDIR) $(objWay)

baseInit :
	$(MKDIR) $(destinationWay)
	$(MKDIR) $(objWay)

copyDeps : $(deps)
	$(COPY) $(deps) $(destinationWay)

run :
	cd $(destinationWay) && ./$(destinationName)

runParams :
	cd $(destinationWay) && ./$(destinationName) /mnt/d/Alex/Documents/SourceTree/SPO/labs/lab5/testing_folder
