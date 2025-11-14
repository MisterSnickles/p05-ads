all: p05
p05: removal main.o
	g++ -o p05 main.o
main.o: main.cpp
	g++ -c -g main.cpp
removal: # change "del" to "rm -f" if not on Windows
	del *.o