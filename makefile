objects = main.o CoffeMachine.o Person.o Drink.o
params = -std=c++11 -c
way = lab1/

lab1.exe : $(objects)
	g++ -o lab1.exe $(objects)

main.o: $(way)main.cpp $(way)Person.h $(way)CoffeMachine.h
	g++ $(params) $(way)main.cpp
CoffeMachine.o : $(way)CoffeMachine.cpp $(way)CoffeMachine.h
	g++ $(params) $(way)CoffeMachine.cpp
Person.o : $(way)Person.cpp $(way)Person.h
	g++ $(params) $(way)Person.cpp
Drink.o : $(way)Drink.cpp $(way)Drink.h
	g++ $(params) $(way)Drink.cpp

max_clean:
	rm lab1.exe $(objects)

clean:
	rm $(objects)