#include <iostream>
#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>

int& f(int x){
	int &y = *(new int(x));
	return y;
	// битая ссылка, не надо так
};

int main()
{
	
	// for (int i = 0; i < 20; ++i)
	// {
	// 	int a = 5;
	// 	std::cout << &f(a) << std::endl;
	// }

	delete &f(4);

	std::map<int, int> map;

	map[0] = 0;
	map[1] = 1;
	map[2] = 2;
	
	std::map<int, int>::iterator it = map.begin();

	while (it != map.end()){
		std::cout << it->first << "\n";
		++it;
	}


  std::istringstream str("0.1 0.2 0.3 0.4");
    std::partial_sum(std::istream_iterator<double>(str),
                      std::istream_iterator<double>(),
                      std::ostream_iterator<double>(std::cout, ","));
	
	std::istream_operator<double> it(str);

	whil

	

	

	// int x = 5;
	// const int& y = x;

	// int& z = const_cast<int&> (x);

	// z++;

	// std::cout << y << std::endl;
	// std::cout << z << std::endl;

	return (0);
}

