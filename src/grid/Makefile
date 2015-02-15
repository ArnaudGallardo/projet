CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../include
LDFLAGS = -L ../../lib -lm -lgrid
SOURCES = $(wildcard *.c)
VPATH = ../../include
OUTFILES = test-grid

all: $(OUTFILES)

test-grid: test-grid.o grid.o
	${CC} test-grid.o grid.o ${LDFLAGS} -o test-grid

include files.txt
files.txt: $(SOURCES)
	gcc -MM $(CPPFLAGS) *.c > files.txt

.PHONY: clean
clean:
	-rm -f *.o $(OUTFILES)

test:
	./test-grid

install:
	ar -r libgrid.a grid.o
	mkdir ../../lib -p
	mkdir ../../include -p
	cp grid.h ../../include/
	mv libgrid.a ../../lib

