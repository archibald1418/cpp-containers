#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <assert.h>
#include <stack>
#include <iterator>
#include "ft_containers.hpp"
#include "pick_vector.hpp"
#include "VectorFactory.hpp"
#include "Test.hpp"
#include "utils.hpp"
#include "type_traits.hpp"

using test::VectorFactory;


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

template <bool B>
struct signal_const {
  static void prnt(){}
};
template <>
struct signal_const<true>{
  static void prnt(){std::cout << "CONST!" << std::endl;}
};

template <typename V>
void test_iterate_vector(V &v)
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

  std::cout << "Iterating through vector" << std::endl;
  for (; begin != end; ++begin)
  {
    std::cout << *begin << " ";
  }
  std::cout << "\n";
  std::cout << "Iterating through vector using const iterator" << std::endl;
  for (; cbegin != cend; ++cbegin)
  {
    std::cout << *cbegin << " ";
    // *cbegin = 5
    // compile error
  }
  std::cout << "\n";

  std::cout << std::string(20, '>') << std::endl;

  std::cout << "Iterating through vector backwards" << std::endl;
  for (; rbegin != rend; ++rbegin)
  {
    std::cout << *rbegin << " ";
  }
  std::cout << "\n";

  std::cout << "Iterating through vector backwards using const reverse iterator" << std::endl;
  for (; crbegin != crend; ++crbegin)
  {
    std::cout << *crbegin << " ";
  }
    // *crbegin = 5
    // compile error
  std::cout << "\n";
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
void test_vector_reserve()
{
  std::cout << WHITE
            << "Changing of capacity during adding 100 new elements"
            << std::endl;

  typedef vector<int>::size_type size_type;

  int amount = 33;

  vector<int> foo;
  size_type sizefoo = foo.size();

  std::cout << "SIZES OF FOO" << std::endl;
  for (int i = 0; i < amount; ++i)
  {
    foo.push_back(i);
    std::cout << BLUE << " " << sizefoo;
    sizefoo = foo.capacity();
  }

  std::cout << "\n";
  std::cout << WHITE
            << "Changing of capacity during adding 100 new elements (100 were reserved)"
            << std::endl;

  vector<int> bar;
  size_type sizebar = bar.size();

  bar.reserve(static_cast<size_type>(amount) - 2);

  std::cout << "SIZES OF BAR" << std::endl;
  for (int i = 0; i < amount; ++i)
  {
    bar.push_back(i);
    std::cout << BLUE << " " << sizebar;
    sizebar = bar.capacity();
  }
  std::cout << std::endl;
  std::cout << "------------------" << std::endl;
  test_iterate_vector(bar);
  std::cout << "------------------" << std::endl;
  test_iterate_vector(foo);

  std::cout << std::endl
            << "RESERVE >MAX SIZE TEST" << std::endl;

  typedef vector<test::my_class>::size_type stype;
  vector<test::my_class> evil(10);
  evil.reserve(40);
  test_iterate_vector(evil);
  std::cout << "max size = " << evil.max_size() << std::endl;
  stype max_size = evil.max_size();
  try
  {
    evil.reserve(max_size + 1);
  }
  catch (const std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

template <typename T>
void test_vector_resize_with_default_value(const T &value = T())
{
  vector<T> vints;

// Create size 10
  ::create_vector_of_ints(vints, 10);
  std::cout << WHITE << "Elements in vector 10" << std::endl;
  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Truncate to size 5
  vints.resize(5);
  std::cout << WHITE << "Elements in vectors after resize(5):" << std::endl;

  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Extend to size 10 again and fill with value
  vints.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors back to resize(10) and value " <<\
      value << std::endl;
  
  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Resize to 10, should be idempotent
  vints.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors after resize(10) again and value " << value << std::endl;


  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

}


void  test_erase_vector(){
  vector<int> vints;

  create_vector_of_ints(vints, 10);
  test_iterate_vector(vints);  

  std::cout << "Delete start" << std::endl;
  vints.erase(vints.begin());
  test_iterate_vector(vints);  
  std::cout << "Delete end" << std::endl;
  vints.erase(vints.end() - 1);
  test_iterate_vector(vints);  

  std::cout << "Delete middle element" << std::endl;
  vints.erase(vints.begin() + (vints.size() / 2));
  test_iterate_vector(vints);
}

int main()
{
  std::cout << "TESTING " << vector_types[MY] << std::endl;

  typedef 
          int type;

  typedef VectorFactory<type> VF;

  VF::pointer pt = VF::factory::create();
  const VF::Container const_vector = *pt;

  // test_iterate_vector(*pt);
  test_iterate_vector(const_vector);

  // test_iterate_vector(*VectorFactory<char>().create());
  // test_iterate_vector(*VectorFactory<std::string>().create());

  // test_erase_vector();
  
  // vector<int> v;
  
  // create_vector_of_ints(v, 10);
  // test_erase_vector();

  
  // system("leaks testmy");

};
