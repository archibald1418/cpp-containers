#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <assert.h>
#include <stack>
#include <iterator>
#include <random>
#include "ft_containers.hpp"
#include "pick_vector.hpp"
#include "VectorFactory.hpp"
#include "Test.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

using test::VectorFactory;
using test::factory_type;
using test::unique_ptr;


template <typename V>
void test_iterators(V &v)
{
  typename V::iterator begin = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rbegin = v.rbegin();
  typename V::reverse_iterator rend = v.rend();
  typename V::const_iterator cbegin = v.cbegin();
  typename V::const_iterator cend = v.cend();
  typename V::const_reverse_iterator crbegin = v.crbegin();
  typename V::const_reverse_iterator crend = v.crend();

  // Mutable elems
  std::cout << GREEN << "Iterators to mutable elements\n" << RESET;
  
  std::cout << "First elem of vector V:\t"              << *begin << "\n";
  std::cout << "Last elem of vector V:\t"               << *(end - 1) << std::endl;
  std::cout << "First elem of vector V[::-1]:\t"        << *rbegin << std::endl;    // will take the last item of array
  std::cout << "Last elem of vector V[::-1]:\t"         << *(rend - 1) << std::endl; // will move reverse iterator to first position in array

  std::cout << std::endl;
  // Constant elems
  // Assigning to these leads to CE
  std::cout << RED << "Iterators to constant elements\n" << RESET;

  std::cout << "First const elem of vector V:\t"        << *cbegin << "\n";
  std::cout << "Last const elem of vector V:\t"         << *(cend - 1) << std::endl;
  std::cout << "First const elem of vector V[::-1]:\t"  << *crbegin << std::endl;    // will take the last item of array
  std::cout << "Last const elem of vector V[::-1]:\t"   << *(crend - 1) << std::endl; // will move reverse iterator to first position in array
}



template <typename V>
void test_vector_iterate(V &v)
{
  signal_const<ft::is_const<V>::value>::prnt();
  
  typedef typename ft::conditional<
    ft::is_const<V>::value,
    typename V::const_iterator,
    typename V::iterator>::type
  iterator_type;

  typedef typename ft::conditional<
    ft::is_const<V>::value,
    typename V::const_reverse_iterator,
    typename V::reverse_iterator>::type
  reverse_iterator_type;

  iterator_type begin = v.begin(); // implicitly requiring an iterator based on vector constness
  iterator_type end = v.end();
  typename V::const_iterator cend = v.cend(); // explicitly requiring a const iterator
  typename V::const_iterator cbegin = v.cbegin();
  reverse_iterator_type rbegin = v.rbegin();
  reverse_iterator_type rend = v.rend();
  typename V::const_reverse_iterator crbegin = v.crbegin();
  typename V::const_reverse_iterator crend = v.crend();
  
  (void)cend;
  (void)cbegin;
  (void)crbegin;
  (void)crend;

  std::cout << "Iterating through vector" << std::endl;
  for (; begin != end; ++begin)
  {
    std::cout << *begin << " ";
  }
  // std::cout << "\n";
  // std::cout << "Iterating through vector using const iterator" << std::endl;
  // for (; cbegin != cend; ++cbegin)
  // {
  //   std::cout << *cbegin << " ";
  //   // *cbegin = 5
  //   // compile error
  // }
  std::cout << "\n";

  std::cout << std::string(20, '>') << std::endl;

  std::cout << "Iterating through vector backwards" << std::endl;
  for (; rbegin != rend; ++rbegin)
  {
    std::cout << *rbegin << " ";
  }
  std::cout << "\n";

  // std::cout << "Iterating through vector backwards using const reverse iterator" << std::endl;
  // for (; crbegin != crend; ++crbegin)
  // {
  //   std::cout << *crbegin << " ";
  // }
  //   // *crbegin = 5
  //   // compile error
  std::cout << "\n\n";
}

template <typename V>
void test_vector_sizes(V &v)
{

  // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
  std::cout << "size"
            << "\t"
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  int elem = -10;
  for (; elem <= 0; ++elem)
  {
    v.push_back(elem);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << *v.rbegin() << std::endl;
  }
  test_vector_iterate(v);
  v.size();
  v.capacity(); // _cap *= 2, if newer elem.size overflows capacity
}

template <typename T>
void test_vector_reserve()
{

  std::cout << WHITE
            << "Testing vector reserve: allocating extra memory"
            << std::endl;

  typedef vector<T> vector_of;
  typedef typename vector_of::size_type size_type;
  
  unique_ptr<vector_of> pt(VectorFactory<T>::factory::create());

  vector_of foo(*pt);

  foo.reserve(33);

  std::cout << "FOO SIZES" << std::endl;
  std::cout << BLUE << " size " << foo.size() << "\n";
  std::cout << BLUE << " cap " << foo.capacity() << "\n";   

  size_type cap = foo.capacity();

  for (size_type i = 0; i < cap; i++){
    // std::cout << i << std::endl;
    foo.push_back(T());
  }
  foo.push_back(T());
  foo.push_back(T());

  std::cout << "FOO SIZES" << std::endl;
  std::cout << BLUE << " size " << foo.size() << "\n";
  std::cout << BLUE << " cap " << foo.capacity() << "\n";   

  std::cout << std::endl
            << "RESERVE >MAX SIZE TEST" << std::endl;

  vector<test::my_class> evil(10);
  evil.reserve(40);
  test_vector_iterate(evil);
  std::cout << "max size = " << evil.max_size() << std::endl;
  size_type max_size = evil.max_size();
   try
   {
    evil.reserve(max_size + 1);
  }
  catch (const std::exception &e)
  {
      std::cout << "Size error is expected: " << e.what() << std::endl;
  }
}



template <typename T>
void test_vector_resize_with_default_value(const T &value = T())
{
  ::prnt("Resizing vector with default value");
  std::cout << "value = " << value << std::endl;

  typedef vector<T> vector_of;

  unique_ptr<vector_of> pt(VectorFactory<T>::factory::create());
  vector_of Vector(*pt);

  std::cout << WHITE << "Elements in vector: " << Vector.size() << std::endl;
  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;

// Truncate to size 5
  Vector.resize(5);
  std::cout << WHITE << "Elements in vectors after resize(5):" << std::endl;

  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;

// Extend to size 10 again and fill with value
  Vector.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors back to resize(10) and value " <<\
      value << std::endl;
  
  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;

// Resize to 10, should be idempotent
  Vector.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors after resize(10) again and value " << value << std::endl;


  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;
}

template <typename T>
void  test_vector_erase(){

  const vector<T> Vector(*unique_ptr<vector<T>>(VectorFactory<T>::factory::create()));

  test_vector_iterate(Vector);

  std::cout << "Delete start" << std::endl;
  Vector.erase(Vector.begin());
  test_vector_iterate(Vector);

  std::cout << "Delete end" << std::endl;
  Vector.erase(Vector.end() - 1);
  test_vector_iterate(Vector);  

  std::cout << "Delete middle element" << std::endl;
  Vector.erase(Vector.begin() + (Vector.size() / 2));
  test_vector_iterate(Vector);
}

void test_vector_equality(){

  std::cout << "Equality tests" << std::endl;

  typedef vector<int> vint;
  typedef typename VectorFactory<int>::factory factory;

  const vint a = *unique_ptr<vint>(factory::create());
  (void)a;

  // int value = 42;

  // assert (a == b);

  // a.push_back(value);
  // assert (a != b); assert (a > b); assert (b <= a);


  // test_vector_iterate(a);

// TODO: vector.erase should work with both iterators (const_iter and iter)  
  // vint::iterator cit = a.begin(); //NOTE: iterators should be convertible from and to const

  // a.erase(a.cbegin());
  // a.erase(a.crbegin());
  
  // test_vector_iterate(a);

  // assert (a != b); assert (a < b); (
  // assert (b != a); assert (b >= a);
}

template <typename T>
void test_vector_erase_range(){
  typedef vector<T> vector_of;

  vector_of v = *unique_ptr<T>(VectorFactory<T>::factory::create());
  
}

int main()
{
  std::cout << RED << "\nTESTING " << vector_types[MY] << "\n\n" << RESET;

  // test_vector_erase<int>();
  // test_vector_erase<std::string>();
  // test_vector_erase<char>();
  // test_vector_reserve<int>();
  // test_vector_resize_with_default_value<std::string>("spam");
  
  // test_vector_sizes(*unique_ptr< vector<int> >(VectorFactory<int>::factory::create()));

  
  // vector<int> v;
  // vector<int> dummy;
  // create_vector_of_ints(v, 10);
  // v[0] = -1;

  // test_vector_iterate(v);
  // vector<int>::const_iterator last = v.cend() - 1;
  // // vector<int>::iterator it = v.erase(dummy.end() - 1);
  // // (void)it;
  // vector<int>::iterator range_it = v.erase(v.begin(), v.begin());
  // // (void)range_it;


  // test_vector_iterate(v);

  // std::cout << *range_it << std::endl;
  // std::cout << v.empty() << std::endl;
  
  test_vector_iterate(*unique_ptr< const vector<int> >(VectorFactory<int>::factory::create()));
};
