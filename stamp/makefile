stamp: main.o stamp.o
	g++ -g -Wall main.o stamp.o -o stamp -lcrypto

main.o: main.cpp stamp.h
	g++ -c main.cpp

stamp.o: stamp.cpp stamp.h
	g++ -c stamp.cpp