#include <stack>
#include <deque>
#include <vector>
#include <list>
#include "stack.hpp"
#include "pick_stack.hpp"

#include <cassert>
#include <iostream>

int main(){

	std::cout << "Stack assertions..." << std::endl;

	stack<int, std::list<int> > S;

	assert (S.empty());
	assert (S.size() == 0);
	
	S.push(42);

	assert(S.size() == 1);

	assert (S.top() == 42);

	S.pop();

	assert (S.empty() == true);

	stack<int, std::list<int> > copy_S(S);

	assert (S.empty());

	S.push(21);
	copy_S.push(21);

	assert (S == copy_S);
	
}
