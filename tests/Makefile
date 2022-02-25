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

clean:
	rm -rf *.o
	rm -rf test
re-test: clean test
