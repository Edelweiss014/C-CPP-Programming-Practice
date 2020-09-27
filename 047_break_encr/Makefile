CC = g++
TARGETS = breaker
MEMCHECKARGS =

CFLAGS = -g -Wall -O2

all: breaker

breaker: HW47.o
	g++ -g -Wall -O2 -o breaker HW47.o

HW47.o: HW47.c
	g++ -g -Wall -O2 -c HW47.c

memcheck: breaker
	valgrind --leak-check=full ./main $(MEMCHECKARGS)

clean:
	rm -f *.o main

.PHONY: all memcheck clean

