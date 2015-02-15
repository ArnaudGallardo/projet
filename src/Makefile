CC= gcc

CFLAGS= -g -Wall -std=c99
CPPFLAGS= -I ../include
LDFLAGS= -lm -L ../lib -lgrid -lncurses
VPATH = ../include
OBJ= main.o

main : $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

main.o: main.c grid.h

clean :
	$(MAKE) -C grid clean
	rm -f main.o main

install:
	$(MAKE) -C grid install
	mkdir ../bin/ -p
	cp main ../bin/

test:
	$(MAKE) -C grid test



