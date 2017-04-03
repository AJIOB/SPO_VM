ParserObjects = parser_main.o ParserManager.o
ViewObjects = log.o StreamInput.o StreamOutput.o
CFLAGS = -std=c++11
CXXFLAGS = $(CFLAGS)
linkFlags = -lrt -lpthread
sourceWay = code/
ViewWayHeaders = view/headers/
ViewWaySource = view/source/
destinationWay = bin/unix/
destinationName = parser
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

buildAll : baseInit $(destinationName)

$(destinationName) : $(ParserObjects) $(ViewObjects) copyDeps
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(destinationName) $(ParserObjects) $(ViewObjects) $(linkFlags)

#------------------------------------parser---------------------------
parser_main.o : $(sourceWay)parser_main.cpp
	$(prefix)parser_main.cpp
	
ParserManager.o : $(sourceWay)model/ParserManager.cpp $(sourceWay)model/ParserManager.h
	$(prefix)model/ParserManager.cpp

#------------------------------------view-----------------------------
log.o : $(sourceWay)$(ViewWaySource)log.cpp $(sourceWay)$(ViewWayHeaders)log.h
	$(prefix)$(ViewWaySource)log.cpp

StreamInput.o : $(sourceWay)$(ViewWaySource)StreamInput.cpp $(sourceWay)$(ViewWayHeaders)StreamInput.h
	$(prefix)$(ViewWaySource)StreamInput.cpp

StreamOutput.o : $(sourceWay)$(ViewWaySource)StreamOutput.cpp $(sourceWay)$(ViewWayHeaders)StreamOutput.h
	$(prefix)$(ViewWaySource)StreamOutput.cpp	

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