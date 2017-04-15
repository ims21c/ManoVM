ManoVM : main.o ManoComputer.o
	g++ main.o ManoComputer.o -o ManoVM
main.o : main.cpp
	g++ -c main.cpp
ManoComputer.o : ManoComputer.cpp
	g++ -c ManoComputer.cpp
