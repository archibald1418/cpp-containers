CONTAINERS=../containers
TESTFILE=test
DO_TESTFILE=-o ${TESTFILE}
DO_DSYM=-g

all:
	c++ *.cpp

test:
	c++ *sandbox.cpp -o test

overload:
	c++ *overload*.cpp -o test
spec:
	c++ *spec*.cpp -o test
non-type:
	c++ *non_type*.cpp -o test

compile:
	c++ *.cpp -c
typedefs:
	c++ -Itypedefs.hpp *typedefs*.cpp ${DO_TESTFILE}

# Containers

vector_my:
	c++ vector_main.cpp -g -I ${CONTAINERS} -D MY=1 ${DO_TESTFILE}
vector_sys:
	c++ vector_main.cpp -g ${DO_TESTFILE}

clean:
	rm -rf *.o
	rm -rf test
re-test: clean test
