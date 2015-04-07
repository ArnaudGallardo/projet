CC = gcc
CFLAGS = -g -std=c99 -Wall
CPPFLAGS = -I ../../include
LDFLAGS = -L ../../lib -lm -lgrid
VPATH = ../../include

all:
	gcc -c $(CFLAGS) $(CPPFLAGS) -fPIC fast.c
	gcc -shared -o libstrat.so fast.o 

.PHONY: clean
clean:
	-rm -f *.o $(OUTFILES)
	-rm -f ../../lib/libstrat.so


install:
	mkdir ../../lib -p
	mkdir ../../include -p
	cp strategy.h ../../include/
	mv libstrat.so ../../lib


