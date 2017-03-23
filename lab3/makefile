objects = main.o Client.o Server.o AJIOBlib.o
CXXFLAGS = -std=c++11
destWay = bin/
back = ../

.PHONY: test

test: $(objects)
	cd $(destWay) && $(CXX) -o test $(objects)

main.o : main.cpp
	cd $(destWay) && $(CXX) $(CXXFLAGS) -c $(back)main.cpp
Client.o : Client.h Client.cpp
	cd $(destWay) && $(CXX) $(CXXFLAGS) -c $(back)Client.cpp
Server.o : Server.h Server.cpp
	cd $(destWay) && $(CXX) $(CXXFLAGS) -c $(back)Server.cpp
AJIOBlib.o : AJIOBlib.cpp AJIOBlib.h
	cd $(destWay) && $(CXX) $(CXXFLAGS) -c $(back)AJIOBlib.cpp

run :
	cd $(destWay) && ./test
