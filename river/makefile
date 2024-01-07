river: main.o river.o
	g++ -g -Wall main.o river.o -o river

main.o: main.cpp river.h
	g++ -c main.cpp

river.o: river.cpp river.h
	g++ -c river.cpp