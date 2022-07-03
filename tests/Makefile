SHELL:=/bin/zsh

CC=clang++
CFLAGS=-Wall -Wextra -Werror
CONTAINERS=../containers
TESTFILE=test
DO_TESTFILE=-o ${TESTFILE}
DO_DSYM=-g
TESTSRC=vector_main.cpp utils.cpp


all:
	${CC} ${CFLAGS} *.cpp

test:
	${CC} ${CFLAGS} sandbox/*sandbox.cpp -o test

overload:
	${CC} ${CFLAGS} sandbox/*overload*.cpp -o test
spec:
	${CC} ${CFLAGS} sandbox/*spec*.cpp -o test
non-type:
	${CC} ${CFLAGS} sandbox/*non_type*.cpp -o test

compile:
	${CC} ${CFLAGS} *.cpp -c
typedefs:
	${CC} ${CFLAGS} -Itypedefs.hpp *typedefs*.cpp ${DO_TESTFILE}

# Containers

vector_my:
	${CC} ${CFLAGS} $(TESTSRC) -g -I ${CONTAINERS} -I./ -D MY=1 ${DO_TESTFILE}my -fsanitize=leak;
vector_sys:
	${CC} ${CFLAGS} $(TESTSRC) -g -I ${CONTAINERS} -I./ -D MY=0 ${DO_TESTFILE}sys -fsanitize=leak;
vector_compare: vector_my vector_sys
	-diff <(./testmy) <(./testsys)
	@#ignore diff writing to stderr

clean:
	rm -rf *.o
	rm -rf test testmy testsys
	rm -rf *.dSYM
	rm -rf .*.swp
re-test: clean test
