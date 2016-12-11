all:
	${MAKE} -C src $@

clean:
	${MAKE} -C src $@

install:
	${MAKE} -C src $@

docs: src/*.cpp src/*.hpp
	cd src; doxygen
	${MAKE} -C docs/latex
