install:
	$(MAKE) -C src/grid
	$(MAKE) -C src
	$(MAKE) -C src install
clean:
	rm -f bin/main
	$(MAKE) -C src clean
test:
	$(MAKE) -C src test
run:
	bin/main
