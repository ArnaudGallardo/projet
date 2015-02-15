CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../../include
LDFLAGS = -L ../../../lib -lm -lncurses
SOURCES = $(wildcard *.c)
VPATH = ../../../include
OUTFILES = main test-grid

all: $(OUTFILES)

main: main.o grid.o
	${CC} main.o grid.o ${LDFLAGS} -o main

test-grid: grid.o
	${CC} grid.o ${LDFLAGS} -o test-grid

include files.txt
files.txt: $(SOURCES)
	gcc -MM $(CPPFLAGS) *.c > files.txt

.PHONY: clean
clean:
	-rm -f *.o $(OUTFILES)

test:
	./test-grid

run:
	./main
