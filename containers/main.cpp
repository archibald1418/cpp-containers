/*
*
 *
*
**  This main is for testing the headers syntax. The tests are in tests/ folder
*
 *
*/ 

#include "stack.hpp"

int main(){
	
	ft::stack<int> s;
	ft::stack<int>s2(s);
	s = s2;
}
