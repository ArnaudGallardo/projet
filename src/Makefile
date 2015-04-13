CC= gcc

CFLAGS= -g -Wall -std=c99
CPPFLAGS= -I ../include
LDFLAGS= -Wl,-rpath=../lib -L ../lib -lgrid -lncurses -lA2_bifert_daubasse_gallardo_fast.so -lA2_bifert_daubasse_gallardo_efficient.so -lm 
VPATH = ../include
OBJ= main.o

main: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

main.o: main.c grid.h

clean:
	$(MAKE) -C grid clean
	$(MAKE) -C sdl clean
	$(MAKE) -C strategy clean
	rm -f main.o main

install:
	$(MAKE) -C grid install
	$(MAKE) -C strategy install
	$(MAKE) -C . main
	mkdir ../bin/ -p
	mv main ../bin/

test:
	$(MAKE) -C grid test

test-sdl:
	$(MAKE) -C sdl test
