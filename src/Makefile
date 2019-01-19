COMPILER  ?= g++
CPP_FLAGS ?= -std=c++1z -fconcepts
HEADERS   := $(wildcard *.hpp)
CPP_SRCS  := $(wildcard *.cpp)

doc ?= ../docs

all: ${CPP_SRCS:.cpp=.o} \
$(addprefix lib,${CPP_SRCS:.cpp=.a} ${CPP_SRCS:.cpp=.so}) \
$(addprefix fm2gp_,${CPP_SRCS:.cpp=}) \
docs

clean:
	${RM} *.a *.o *.so fm2gp_*

install:
	install -m755 -d ${prefix}/lib
	install -m644 *.a *.so ${prefix}/lib
	install -m755 -d ${prefix}/include
	install -m644 *.hpp ${prefix}/include
	install -m755 -d ${prefix}/bin
	install -m755 fm2gp_* ${prefix}/bin

%.o: %.cpp
	${COMPILER} ${CPP_FLAGS} -c $< -o $@

lib%.a: %.o
	ar rvs $@ $<

lib%.so: %.cpp
	${COMPILER} ${CPP_FLAGS} -shared -o $@ -fPIC $<

fm2gp_%: %.cpp
	${COMPILER} ${CPP_FLAGS} -o $@ $<


docs:
	doxygen
	@ ${MAKE} -C ${doc}/latex
