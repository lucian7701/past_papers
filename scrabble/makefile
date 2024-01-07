scrabble: main.o scrabble.o
	g++ -g -Wall main.o scrabble.o -o scrabble

main.o: main.cpp scrabble.h
	g++ -g -c main.cpp

scrabble.o: scrabble.cpp scrabble.h
	g++ -g -c scrabble.cpp