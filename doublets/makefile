doublets: main.o doublets.o
	g++ -O3 -g -Wall main.o doublets.o -o doublets

main.o: main.cpp doublets.h
	g++ -O3 -c main.cpp

doublets.o: doublets.cpp doublets.h dictionary.h
	g++ -O3 -c doublets.cpp