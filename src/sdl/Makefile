CC= gcc

CFLAGS= -g -Wall -std=c99
CPPFLAGS= -I ../../include
LDFLAGS= -lm -L ../../lib -lgrid -lSDL2 -lncurses
VPATH = ../../include
OBJ= display.o

display: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

display.o: display.c grid.h grid_utilities.h

.PHONY: clean
clean:
	rm -f display display.o

test: display
	./display