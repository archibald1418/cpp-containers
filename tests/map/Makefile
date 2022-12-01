SHELL:=/bin/zsh # NOTE: VMs don't have built-in zsh installed

CC			=	clang++
C++98		=	-std=c++98
CFLAGS		=	-Wall -Wextra -Werror $(C++98) -pedantic

CONTAINERS=		../../containers
TESTS=			../
TESTFILE=		test
DO_TESTFILE=	-o ${TESTFILE}
PIPE=			diff_pipe.fifo

DIFF	=	diff
COLOR	= 	--color=always --palette='ad=1;3;38;5;154:de=1;3;38;5;9' # added text color; deleted text color

DEBUG = -fstandalone-debug -fno-limit-debug-info

.PHONY: map clean re all

mode=

# Flags for debug mode. Invoke with make mode=debug
ifeq ($(mode),debug)
	CFLAGS := -g $(DEBUG) -Wall -Wextra $(C++98)
endif

# Checking for leaks
ifeq ($(mode),leak)
	CFLAGS := -g -Wall -Wextra -fsanitize=leak $(C++98)
endif

# Checking for mangled memory
ifeq ($(mode),memory)
	CFLAGS := -g -Wall -Wextra -fsanitize=address $(C++98)
endif
ifeq ($(mode),address)
	CFLAGS := -g -Wall -Wextra -fsanitize=address $(C++98)
endif

# Checking for linux compatibility
# ifeq ($(mode),linux)
	# REVIEW:: set up docker-linux -> compile_test -> print logs here
# endif

# Containers

DO_INCLUDE	=	-I${CONTAINERS} -I. -I${TESTS}
TESTSRC		=	map_main.cpp ../utils.cpp
TESTTREESRC =	tree_main.cpp ../utils.cpp

TESTS_F		=	pick_map.hpp Test.hpp types.hpp utils.hpp colors.hpp
TESTS_H		=	$(addprefix $(TESTS), $(TESTS_F))

all: map_compare

map_my: ${TESTS_H}
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=1 ${DO_TESTFILE}my;

map_sys:
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=0 ${DO_TESTFILE}sys;
	@# -fsanitize=leak; export ASAN_OPTIONS=detect_leak=1

map_compare: map_my map_sys
	-${DIFF}  <(./testmy | tee my.log) <(./testsys | tee sys.log)
	@#ignore diff writing to stderr

${TESTFILE}my: map_my
${TESTFILE}sys: map_sys

diff: ${TESTFILE}my ${TESTFILE}sys
	-${DIFF} =(./testmy | tee my.log) =(./testsys | tee sys.log)

diff_bash: ${TESTFILE}my ${TESTFILE}sys
	mkfifo ${PIPE}
	-./${TESTFILE}my | tee my.log  > ${PIPE} &
		@#redirect to pipe and suspend pipe process
	-./${TESTFILE}sys | tee sys.log | ${DIFF} - ${PIPE} | tee
		@#pass output to diff as a second argument and compare with what's in the pipe
	rm -rf ${PIPE}

tree_test:
	${CC} ${CFLAGS} -I${TESTS} -I${CONTAINERS} ${TESTTREESRC} -o tree
map_test:
	${CC} ${CFLAGS} -I${TESTS} -I${CONTAINERS} ${TESTSRC} -o map


clean:
	-rm -rf *.o
	-rm -rf test testmy testsys
	-rm -rf *.dSYM
	-rm -rf .*.swp
	-rm -rf a.out
	-rm -rf *.log
	-rm -rf tree map

re-test: clean
