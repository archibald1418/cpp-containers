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
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(i);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
  }
  v.size();
  v.capacity(); // _cap *= 2, if newer elem.size overflows capacity
}

template <typename V>
void test_create_vector_custom_type(V &v)
{

  test::my_class my_obj;

  int i = 0;
  std::cout << "size"
            << "\t"
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(my_obj);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;

    my_obj++;
  }
}

// template <typename T>
void  test_vector_reserve(){
  std::cout << WHITE \
    << "Changing of capacity during adding 100 new elements" \
    << std::endl;

  typedef vector<int>::size_type size_type;

  int amount = 33;

  vector<int> foo;
  size_type sizefoo = foo.size();

  std::cout << "SIZES OF FOO" << std::endl;
  for (int i = 0; i < amount; ++i){
    foo.push_back(i);
    std::cout << BLUE << " " << sizefoo;
    sizefoo = foo.capacity();
  }

  std::cout << "\n";
  std::cout << WHITE \
    << "Changing of capacity during adding 100 new elements (100 were reserved)" \
    << std::endl;

  vector<int> bar;
  size_type sizebar = bar.size();

  bar.reserve(static_cast<size_type>(amount) - 2);
  
  std::cout << "SIZES OF BAR" << std::endl;
  for (int i = 0; i < amount; ++i){
    bar.push_back(i);
    std::cout << BLUE << " " << sizebar;
    sizebar = bar.capacity();
  }
  std::cout << std::endl;
  std::cout << "------------------" << std::endl;  
  test_iterate_vector(bar);
  std::cout << "------------------" << std::endl;  
  test_iterate_vector(foo);  
  
  
  std::cout << std::endl << "RESERVE >MAX SIZE TEST" << std::endl;
  
  typedef vector<char>::size_type stype;
  vector<char> evil;
  std::cout << "max size = " << evil.max_size() << std::endl;
  stype max_size = evil.max_size();
  try
  {
    evil.reserve(max_size + 1);
  } catch (const std::exception& e){
    std::cout << "Error: " << e.what() << std::endl;
  }

  
  
}

int main()
{
  std::cout << "TESTING " << vector_types[MY] << std::endl;

  // vector<int> vzero; //
  // test::my_class my_object;

  // vector<int> vnonzero(5);
  // vector<test::my_class> vmyclass(5);

  // vector<int> v;

  // test_vector(vzero);
  // test_vector(vnonzero);
  // test_create_vector_custom_type(vmyclass);
  // test_iterate_vector(vmyclass);
  test_vector_reserve();
};
