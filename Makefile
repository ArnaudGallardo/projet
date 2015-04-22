install:
	$(MAKE) -C src/grid
	$(MAKE) -C src/strategy
	$(MAKE) -C src install
	$(MAKE) -C src/sdl
	$(MAKE) -C src/sdl install

clean:
	rm -f bin/main
	rm -f bin/sdl
	rm -f lib/libgrid.a
	rm -f include/grid.h
	rm -rf include
	$(MAKE) -C src clean

test:
	$(MAKE) -C src test
