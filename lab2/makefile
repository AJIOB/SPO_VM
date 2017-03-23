objects = main.o Controller.o CoffeMachine.o Person.o Drink.o 
CFLAGS = -std=c++11
CXXFLAGS = $(CFLAGS)
sourceWay = lab2/
deps = $(sourceWay)info.db
destinationWay = bin/unix/
destinationName = lab2

objWay = $(destinationWay)obj/
objBackHome = ../../../

goObject = cd $(objWay) &&
compilerPrefix = $(goObject) $(CXX)
prefix = $(compilerPrefix) $(CXXFLAGS) -c $(objBackHome)$(sourceWay)

MKDIR = mkdir -p
RMDIR = -rm -r
COPY = cp


.PHONY: $(destinationName) clean max_clean baseInit run copyDeps


$(destinationName) : baseInit copyDeps $(objects)
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(destinationName) $(objects)

main.o : $(sourceWay)main.cpp $(sourceWay)Controller.h
	$(prefix)main.cpp
CoffeMachine.o : $(sourceWay)CoffeMachine.cpp $(sourceWay)CoffeMachine.h
	$(prefix)CoffeMachine.cpp
Person.o : $(sourceWay)Person.cpp $(sourceWay)Person.h
	$(prefix)Person.cpp
Drink.o : $(sourceWay)Drink.cpp $(sourceWay)Drink.h
	$(prefix)Drink.cpp
Controller.o : $(sourceWay)Controller.cpp $(sourceWay)Controller.h
	$(prefix)Controller.cpp

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
