CPP_FLAGS  = -stdlib=libc++ -std=c++11
HEADERS   := $(wildcard *.hpp)
CPP_SRCS  := $(wildcard *.cpp)

all: ${CPP_SRCS:.cpp=.o} \
$(addprefix lib,${CPP_SRCS:.cpp=.a} ${CPP_SRCS:.cpp=.so}) \
$(addprefix ../bin/fm2gp_,${CPP_SRCS:.cpp=})

clean:
	${RM} *.a *.o *.so ../bin/fm2gp_*

install:
	install -m755 -d ${prefix}/lib
	install -m644 *.a *.so ${prefix}/lib
	install -m755 -d ${prefix}/include
	install -m644 *.hpp ${prefix}/include
	install -m755 -d ${prefix}/bin
	install -m755 fm2gp* ${prefix}/bin

%.o: %.cpp
	c++ ${CPP_FLAGS} -c $< -o $@

lib%.a: %.o
	ar rvs $@ $<

lib%.so: %.cpp
	c++ ${CPP_FLAGS} -shared -o $@ -fPIC $<

../bin/fm2gp_%: %.cpp
	c++ ${CPP_FLAGS} -o $@ $<
