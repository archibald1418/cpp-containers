#include <vector>
using std::vector;
#include <iostream>

int main(){
	vector<int> v;

	const int i = 5;
	
	v.push_back(i);

	std::cout << v.at(0) << std::endl;
	std::cout << &(*v.begin()) << std::endl;
	std::cout << &i << std::endl;
	
	v[0] = 6;

	std::cout << *v.begin() << std::endl;
	std::cout << i << std::endl;
}
