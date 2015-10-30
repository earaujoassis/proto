# Top-level Makefile

.PHONY: tests clean

tests:
	$(MAKE) -C tests build

clean:
	$(MAKE) -C tests clean
