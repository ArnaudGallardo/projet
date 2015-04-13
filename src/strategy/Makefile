CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../include
LDFLAGS = -L ../../lib -lm -lgrid
VPATH = ../../include

all:
	gcc -c $(CFLAGS) $(CPPFLAGS) -fPIC fast.c
	gcc -shared -o libstrat.so fast.o 
	gcc -c $(CFLAGS) $(CPPFLAGS) strategy.h -fPIC efficient.c
	gcc -shared -o libA2_bifert_daubasse_gallardo_efficient.so efficient.o 

.PHONY: clean
clean:
	-rm -f *.o $(OUTFILES)
	-rm -f ../../lib/libstrat.so
	-rm -f ../../lib/libA2_bifert_daubasse_gallardo_efficient.so


install:
	mkdir ../../lib -p
	mkdir ../../include -p
	cp strategy.h ../../include/
	mv libstrat.so ../../lib
	mv libA2_bifert_daubasse_gallardo_efficient.so ../../lib


