all: code

code: code.o
	g++ -g -Wall -O3 -o code code.o

code.o: code.cpp
	g++ -g -Wall -O3 -c code.cpp

clean:
	rm -f *.o main

.PHONY: all memcheck clean
