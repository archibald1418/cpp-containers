#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include "tests.hpp"
#include <assert.h>

#ifdef MY
#define MY 1
#include "ft_containers.hpp"
using ft::vector;
#endif

#ifndef MY
#define MY 0
using std::vector;
#endif


const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")};

template <typename V>
void test_iterators(V &v)
{
  typename V::iterator start = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rstart = v.rbegin();
  typename V::reverse_iterator rend = v.rend();

  std::cout << "First elem of vector V:\t" << *start << "\n";
  std::cout << "Last elem of vector V:\t" << *(end - 1) << std::endl;
  std::cout << "First elem of vector V[::-1]:\t" << *rstart << std::endl;    // will take the last item of array
  std::cout << "Last elem of vector V[::-1]:\t" << *(rend - 1) << std::endl; // will move reverse iterator to first position in array
}

template <typename Container>
void create_vector_of_ints(Container *vector, int elems)
{

  for (int i = 0; i < elems; i++)
  {
    vector->push_back(i);
  };
}

template <typename V>
void test_iterate_vector(V &v)
{
  typename V::iterator start = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rstart = v.rbegin();
  typename V::reverse_iterator rend = v.rend();

  std::cout << "Iterating through vector" << std::endl;
  for (; start != end; ++start)
  {
    std::cout << *start << "\n";
  }

  std::cout << std::string(20, '>') << std::endl;

  std::cout << "Iterating through vector backwards" << std::endl;
  for (; rstart != rend; ++rstart)
  {
    std::cout << *rstart << "\n";
  }
}

template <typename V>
void test_vector_sizes(V &v)
{
  int i = 0;
  // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
  std::cout << "size"
            << "\t"
            << "cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(i);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
  }
  v.size();
  v.capacity(); // cap *= 2, if newer elem.size overflows capacity
}

template <typename V>
void test_create_vector_custom_type(V &v)
{

  test::my_class my_obj;

  int i = 0;
  std::cout << "size"
            << "\t"
            << "cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(my_obj);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;

    my_obj++;
  }
}

int main()
{
  std::cout << "TESTING " << vector_types[MY] << std::endl;

  // vector<int> vzero; //
  // test::my_class my_object;

  // vector<int> vnonzero(5);
  vector<test::my_class> vmyclass(5);

  // vector<int> v;

  // test_vector(vzero);
  // test_vector(vnonzero);
  test_create_vector_custom_type(vmyclass);
  test_iterate_vector(vmyclass);
};
