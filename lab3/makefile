objects = main.o Controller.o Server.o Client.o AJIOBlib.o
CFLAGS = -std=c++11
CXXFLAGS = $(CFLAGS)
sourceWay =
deps = $(sourceWay)info.db
destinationWay = bin/unix/
destinationName = lab3

objWay = $(destinationWay)obj/
objBackHome = ../../../

goObject = cd $(objWay) &&
compilerPrefix = $(goObject) $(CXX)
prefix = $(compilerPrefix) $(CXXFLAGS) -c $(objBackHome)$(sourceWay)

MKDIR = mkdir -p
RMDIR = -rm -r
COPY = cp


.PHONY: $(destinationName) clean max_clean baseInit copyDeps run runPerson runMachine


$(destinationName) : baseInit $(objects) copyDeps
	$(compilerPrefix) -lrt -lpthread -o $(objBackHome)$(destinationWay)$(destinationName) $(objects)

main.o : $(sourceWay)main.cpp $(sourceWay)Controller.h
	$(prefix)main.cpp
Server.o : $(sourceWay)Server.cpp $(sourceWay)Server.h
	$(prefix)Server.cpp
Client.o : $(sourceWay)Client.cpp $(sourceWay)Client.h
	$(prefix)Client.cpp
Controller.o : $(sourceWay)Controller.cpp $(sourceWay)Controller.h
	$(prefix)Controller.cpp
AJIOBlib.o : $(sourceWay)AJIOBlib.cpp $(sourceWay)AJIOBlib.h
	$(prefix)AJIOBlib.cpp

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

runPerson :
	cd $(destinationWay) && ./$(destinationName) -p

runMachine :
	cd $(destinationWay) && ./$(destinationName) -m