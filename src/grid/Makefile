CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../include
LDFLAGS = -L ../../lib -lm -lgrid
SOURCES = $(wildcard *.c)
VPATH = ../../include
OUTFILES = test-grid

all: $(OUTFILES)
	$(MAKE) -C . install

test-grid: test-grid.o grid.o grid_utilities.o
	${CC} test-grid.o grid.o grid_utilities.o grid.h grid_utilities.h -lm -o test-grid

include files.txt
files.txt: $(SOURCES)
	gcc -MM $(CPPFLAGS) *.c > files.txt

.PHONY: clean
clean:
	rm -f *.o $(OUTFILES)
	rm files.txt

test:
	./test-grid

install:
	ar -r libgrid.a grid.o grid_utilities.o
	mkdir ../../lib -p
	mkdir ../../include -p
	cp grid.h ../../include/
	cp grid_utilities.h ../../include/
	mv libgrid.a ../../lib

