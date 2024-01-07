playfair: main.o playfair.o 
	g++ -Wall main.o playfair.o -o playfair

main.o: main.cpp playfair.h
	g++ -c main.cpp

playfair.o: playfair.cpp playfair.h
	g++ -c playfair.cpp