CC = g++
TARGETS = main
MEMCHECKARGS =

CFLAGS = -g -Wall -O2

all: main

main: power.o test-power.o
	gcc -g -Wall -O2 -o main power.o test-power.o

power.o: power.c
	gcc -g -Wall -O2 -c power.c

test-power.o: test-power.c
	gcc -g -Wall -O2 -c test-power.c

memcheck: main
	valgrind --leak-check=full ./main $(MEMCHECKARGS)

clean:
	rm -f main

.PHONY: all memcheck clean
