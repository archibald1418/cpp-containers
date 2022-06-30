#include <vector>
using std::vector;
#include <iostream>

int main(){

	typedef const vector<int> const_vector;
	const_vector v;

	const int i = 5;
	
	v.push_back(i);

	const_vector::const_iterator it = v.begin();

	std::cout << v.at(0) << std::endl;
	std::cout << &(*v.begin()) << std::endl;
	std::cout << &i << std::endl;
	
	v[0] = 6;

	std::cout << *v.begin() << std::endl;
	std::cout << i << std::endl;
}
