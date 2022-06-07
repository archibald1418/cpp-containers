CONTAINERS=../containers

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
	c++ -Itypedefs.hpp *typedefs*.cpp -o test

# Containers

vector_my:
	c++ vector_main.cpp -I ${CONTAINERS} -D MY=1
vector_sys:
	c++ vector_main.cpp

clean:
	rm -rf *.o
	rm -rf test
re-test: clean test
