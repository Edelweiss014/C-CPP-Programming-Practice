CC = g++
TARGETS = main
MEMCHECKARGS =

CFLAGS = -g -Wall -O2

all: test

test: test.o
	gcc -g -Wall -O2 -o test test.o

test.o: test.c
	gcc -g -Wall -O2 -c test.c

memcheck: test
	valgrind --leak-check=full ./test $(MEMCHECKARGS)

clean:
	rm -f main

.PHONY: all memcheck clean
