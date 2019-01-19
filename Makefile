.PHONY: all docs

all:
	nix-build

docs: $(wildcard src/*.cpp) $(wildcard src/*.hpp)
	nix-shell --run 'make -C src docs doc=$(CURDIR)/docs'

