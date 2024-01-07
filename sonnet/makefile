sonnet: main.o sonnet.o
	g++ -g -Wall main.o sonnet.o -o sonnet

main.o: main.cpp sonnet.h
	g++ -c main.cpp

sonnet.o: sonnet.cpp sonnet.h
	g++ -c sonnet.cpp