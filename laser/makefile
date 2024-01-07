laser: main.o laser.o
	g++ -g -Wall main.o laser.o -o laser

main.o: main.cpp laser.h
	g++ -c main.cpp

laser.o: laser.cpp laser.h
	g++ -c laser.cpp