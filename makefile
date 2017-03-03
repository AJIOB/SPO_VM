objects = main.o CoffeMachine.o Person.o Drink.o
deps = lab1/info.db
params = -std=c++11 -c
sourceWay = lab1/
destinationWay = bin/unix/
destinationName = lab1.exe

objWay = $(destinationWay)obj/
objBackHome = ../../../

goObject = cd $(objWay) &&
compilerPrefix = $(goObject) $(CXX)
prefix = $(compilerPrefix) $(params) $(objBackHome)$(sourceWay)

MKDIR = mkdir -p
RMDIR = -rm -r
COPY = cp


.PHONY: $(destinationName) clean max_clean baseInit run copyDeps


$(destinationName) : baseInit copyDeps $(objects)
	$(compilerPrefix) -o $(objBackHome)$(destinationWay)$(destinationName) $(objects)

main.o : $(sourceWay)main.cpp $(sourceWay)Person.h $(sourceWay)CoffeMachine.h
	$(prefix)main.cpp
CoffeMachine.o : $(sourceWay)CoffeMachine.cpp $(sourceWay)CoffeMachine.h
	$(prefix)CoffeMachine.cpp
Person.o : $(sourceWay)Person.cpp $(sourceWay)Person.h
	$(prefix)Person.cpp
Drink.o : $(sourceWay)Drink.cpp $(sourceWay)Drink.h
	$(prefix)Drink.cpp

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
