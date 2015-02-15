install:
	$(MAKE) -C src
	$(MAKE) -C grid install
clean:
	$(MAKE) -C grid clean
test:
	$(MAKE) -C grid test
