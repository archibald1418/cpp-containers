
#include <iostream>

struct an_object {
	int a;
	std::string b;
};

class Parent {
	public:
		an_object A;
		int b;
		int c;
};

class Child : public Parent {
	public:
		int A;
		int b;
		int c;
	
	Child(const int A = 78) : A(A), b(0){

	}
};
