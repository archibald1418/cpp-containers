#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

#ifdef MY
# define MY 1
# include "ft_containers.hpp"
  using ft::vector;
#else
# define MY 0
  using std::vector;
#endif

const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")
};

int main(){
    std::cout << "TESTING " << vector_types[MY] << std::endl;

    vector<int> v; //
    
    int i = 0;
    // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
    for (; i < 10; ++i)
    {
        v.push_back(i);
        std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
    }

    v.size();
    v.capacity(); // cap *= 2, if newer elem.size overflows capacity
};
