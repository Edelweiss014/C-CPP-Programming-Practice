CC = g++
TARGETS = main
MEMCHECKARGS =

CFLAGS = -g -Wall -O2

all: main

main: maxSeq.o test-subseq.o
	gcc -g -Wall -O2 -o main maxSeq.o test-subseq.o

maxSeq.o: maxSeq.c
	gcc -g -Wall -O2 -c maxSeq.c

test-subseq.o: test-subseq.c
	gcc -g -Wall -O2 -c test-subseq.c

memcheck: main
	valgrind --leak-check=full ./main $(MEMCHECKARGS)

clean:
	rm -f *.o

.PHONY: all memcheck clean
