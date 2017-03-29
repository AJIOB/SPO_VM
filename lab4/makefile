objects = main.o Thread.o ThreadManager.o UI.o
CFLAGS = -std=c++11
CXXFLAGS = $(CFLAGS)
linkFlags = -lrt -lpthread
sourceWay = code/
deps = VA_lab4.log
destinationWay = bin/unix/
destinationName = lab4

objWay = $(destinationWay)obj/
objBackHome = ../../../

goObject = cd $(objWay) &&
compilerPrefix = $(goObject) $(CXX)
prefix = $(compilerPrefix) $(CXXFLAGS) -c $(objBackHome)$(sourceWay)

MKDIR = mkdir -p
RMDIR = -rm -r
COPY = cp


.PHONY: $(destinationName) clean max_clean baseInit copyDeps run runParams


$(destinationName) : baseInit $(objects) copyDeps
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(destinationName) $(objects) $(linkFlags)

main.o : $(sourceWay)main.cpp
	$(prefix)main.cpp
	
Thread.o : $(sourceWay)Thread.cpp $(sourceWay)Thread.h
	$(prefix)Thread.cpp
	
ThreadFuncs.o : $(sourceWay)ThreadFuncs.cpp $(sourceWay)ThreadFuncs.h
#	$(prefix)ThreadFuncs.cpp
	
ThreadManager.o : $(sourceWay)ThreadManager.cpp $(sourceWay)ThreadManager.h
	$(prefix)ThreadManager.cpp
	
UI.o : $(sourceWay)UI.cpp $(sourceWay)UI.h
	$(prefix)UI.cpp

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
	cd $(destinationWay) && ./$(destinationName) 2 3