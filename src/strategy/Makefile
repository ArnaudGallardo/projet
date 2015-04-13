CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../include
LDFLAGS = -L ../../lib -lm -lgrid
VPATH = ../../include

all:
	gcc -c $(CFLAGS) $(CPPFLAGS) -fPIC fast.c
	gcc -shared -o libA2_bifert_daubasse_gallardo_fast.so fast.o 
	gcc -c $(CFLAGS) $(CPPFLAGS) strategy.h -fPIC efficient.c
	gcc -shared -o libA2_bifert_daubasse_gallardo_efficient.so efficient.o 

.PHONY: clean
clean:
	-rm -f *.o $(OUTFILES)
	-rm -f ../../lib/libA2_bifert_daubasse_gallardo_fast.so
	-rm -f ../../lib/libA2_bifert_daubasse_gallardo_efficient.so


install:
	mkdir ../../lib -p
	mkdir ../../include -p
	cp strategy.h ../../include/
	mv libA2_bifert_daubasse_gallardo_fast.so ../../lib
	mv libA2_bifert_daubasse_gallardo_efficient.so ../../lib


