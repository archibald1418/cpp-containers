SHELL:=/bin/zsh

CC=clang++
CFLAGS=-Wall -Wextra #-Werror
CONTAINERS=../containers
TESTFILE=test
DO_TESTFILE=-o ${TESTFILE}
DO_DSYM=-g
TESTSRC=vector_main.cpp utils.cpp

DIFF=diff


all: 
	make -C vector 
	@# TODO: add map and stack rules
sandbox: 
	make -C sandbox
test:
	make test -C sandbox
overload:
	make overload -C sandbox
spec:
	make spec -C sandbox
non-type:
	make non-type -C sandbox
compile:
	make compile -C sandbox
typedefs:
	make typedefs -C sandbox


# Containers

vector:
	make -C vector

vector_my:
	make vector_my -C vector; 
	./vector/testmy
vector_sys:
	make vector_sys -C vector; 
	./vector/testsys
vector_compare: vector_my vector_sys
	make vector_compare -C vector;

clean:
	-rm -rf *.o
	-rm -rf test testmy testsys
	-rm -rf *.dSYM
	-rm -rf .*.swp
	-rm -rf a.out
	-rm -rf *.log

re-test: clean test
