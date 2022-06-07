#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include "tests.hpp"

#ifdef MY
# define MY 1
# include "ft_containers.hpp"
  using ft::vector;
#endif

#ifndef MY
# define MY 0
  using std::vector;
#endif


const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")
};


template <typename V>
void  test_vector(V &v){
    int i = 0;
    // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
    std::cout << "size" << "\t" << "cap" << "\t" << "elem" << std::endl;
    for (; i < 10; ++i)
    {
        v.push_back(i);
        std::cout <<  v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
    }
    v.size();
    v.capacity(); // cap *= 2, if newer elem.size overflows capacity
}



template <typename V>
void test_vector_custom_type(V &v){

  test::my_class my_obj;

  int i = 0;
  std::cout << "size" << "\t" << "cap" << "\t" << "elem" << std::endl;
  for (; i < 10; ++i){
    v.push_back(my_obj);
    std::cout <<  v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
    my_obj++;
  }
}

int main(){
    std::cout << "TESTING " << vector_types[MY] << std::endl;

    // vector<int> vzero; //
    test::my_class my_object;

    vector<int> vnonzero(5);
    vector<test::my_class> vmyclass(5);

    // test_vector(vzero);
    // test_vector(vnonzero);
    test_vector_custom_type(vmyclass);


};
