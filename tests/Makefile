SHELL:=/bin/bash

CONTAINERS=../containers
TESTFILE=test
DO_TESTFILE=-o ${TESTFILE}
DO_DSYM=-g
TESTSRC=vector_main.cpp utils.cpp


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
	c++ $(TESTSRC) -g -I ${CONTAINERS} -I./ -D MY=1 ${DO_TESTFILE}my -fsanitize=address
	./testmy;
vector_sys:
	c++ $(TESTSRC) -g -I ${CONTAINERS} -I./ -D MY=0 ${DO_TESTFILE}sys -fsanitize=address
	./testsys;
vector_compare: testmy testsys
	@#ignore diff writing to stderr
	-diff <(./testmy) <(./testsys)

clean:
	rm -rf *.o
	rm -rf test testmy testsys
	rm -rf *.dSYM
	rm -rf .*.swp
re-test: clean test
