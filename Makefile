install:
	$(MAKE) -C src/grid
	$(MAKE) -C src
	$(MAKE) -C src install
clean:
	$(MAKE) -C src clean
test:
	$(MAKE) -C src test
