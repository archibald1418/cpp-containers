SHELL:=/bin/zsh

CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -pedantic

CONTAINERS=		../../containers
TESTS=			../
TESTFILE=		test
DO_TESTFILE=	-o ${TESTFILE}

DIFF	=	diff

# Flags for debug mode. Invoke with make mode=debug
ifeq ($(mode),debug)
	CFLAGS := -g -Wall -Wextra
endif

# Containers

DO_INCLUDE	=	-I${CONTAINERS} -I. -I${TESTS}
TESTSRC		=	map_main.cpp ../utils.cpp

TESTS_F		=	pick_map.hpp Test.hpp types.hpp utils.hpp colors.hpp
TESTS_H		=	$(addprefix $(TESTS), $(TESTS_F))

all: map_compare

map_my: ${TESTS_H}
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=1 ${DO_TESTFILE}my -fsanitize=address;

map_sys:
	${CC} ${CFLAGS} $(TESTSRC) ${DO_INCLUDE} -D MY=0 ${DO_TESTFILE}sys -fsanitize=address;
	@# -fsanitize=leak; export ASAN_OPTIONS=detect_leak=1

map_compare: map_my map_sys
	-${DIFF} <(./testmy | tee my.log) <(./testsys | tee sys.log)
	@#ignore diff writing to stderr

tree_test:
	${CC} -g -I${TESTS} -I${CONTAINERS} map_main.cpp -o tree

clean:
	-rm -rf *.o
	-rm -rf test testmy testsys
	-rm -rf *.dSYM
	-rm -rf .*.swp
	-rm -rf a.out
	-rm -rf *.log
	-rm -rf tree

re-test: clean
