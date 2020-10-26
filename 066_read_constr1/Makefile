all: main

main: code.o
	g++ -g -Wall -O3 -o main code.o

code.o: code.cpp
	g++ -g -Wall -O3 -c code.cpp

clean:
	rm -f *.o main

.PHONY: all memcheck clean
