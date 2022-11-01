SHELL:=/bin/zsh

CC		=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -pedantic

CONTAINERS=../../containers
TESTS=../
TESTFILE=test
DO_TESTFILE=-o ${TESTFILE}

DIFF=diff

ifeq ($(mode),debug)
	CFLAGS := -g -Wall -Wextra -std=c++98
endif

# Containers

DO_INCLUDE	=	-I${CONTAINERS} -I. -I${TESTS}
TESTSRC		=	vector_main.cpp ../utils.cpp

TESTS_F		=	pick_vector.hpp Test.hpp types.hpp utils.hpp VectorFactory.hpp colors.hpp
TESTS_H		=	$(addprefix $(TESTS), $(TESTS_F))

all: vector_compare

vector_my: ${TESTS_H}
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=1 ${DO_TESTFILE}my -fsanitize=address;

vector_sys:
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=0 ${DO_TESTFILE}sys -fsanitize=address;
	@# -fsanitize=leak; export ASAN_OPTIONS=detect_leak=1

vector_compare: vector_my vector_sys
	-${DIFF} <(./testmy | tee my.log) <(./testsys | tee sys.log)
	@#ignore diff writing to stderr
	@#TODO: replace this for sh

clean:
	-rm -rf *.o
	-rm -rf test testmy testsys
	-rm -rf *.dSYM
	-rm -rf .*.swp
	-rm -rf a.out
	-rm -rf *.log

re-test: clean
