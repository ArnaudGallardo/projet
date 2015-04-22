install:
	$(MAKE) -C src/grid
	$(MAKE) -C src/strategy
	$(MAKE) -C src install

clean:
	rm -f bin/main
	rm -f lib/libgrid.a
	rm -f include/grid.h
	$(MAKE) -C src clean

test:
	$(MAKE) -C src test

run-sdl:
	$(MAKE) -C src run-sdl
