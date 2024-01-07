gogen: main.o gogen.o
	g++ -g -Wall main.o gogen.o -o gogen

main.o: main.cpp common.h mask.h gogen.h
	g++ -c main.cpp

gogen.o: gogen.cpp gogen.h mask.h common.h
	g++ -c gogen.cpp