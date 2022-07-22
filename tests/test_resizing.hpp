#ifndef TEST_RESIZING_H
# define TEST_RESIZING_H

# include <iostream>

# include "pick_vector.hpp"
# include "type_traits.hpp"
# include "Test.hpp"
# include "utils.hpp"

using test::unique_ptr;
using test::VectorFactory;

template <typename V>
void test_vector_sizes(V &v)
{
  print_test_info<int>("TESTING VECTOR SIZES", BOLDMAGENTA);

  // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
  std::cout << BOLDBLUE;
  std::cout << "size"
            << "\t"
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  int elem = -10;
  std::cout << RESET << BLUE;
  for (; elem <= 0; ++elem)
  {
    v.push_back(elem);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << *v.rbegin() << std::endl;
  }

  std::cout << RESET << std::endl;

  test_vector_iterate(v);
  // std::cout << v.size();
  // std::cout << v.capacity(); // _cap *= 2, if newer elem.size overflows capacity

  delineate();
}

template <typename T>
void test_vector_reserve()
{

  print_test_info<T>("TESTING VECTOR RESERVE", BOLDRED);

  std::cout << WHITE
            << "Testing vector reserve: allocating extra memory"
            << std::endl;

  typedef vector<T> vector_of;
  typedef typename vector_of::size_type size_type;
  
  unique_ptr<vector_of> pt(VectorFactory<T>::factory::create());

  vector_of foo(*pt);

  foo.reserve(33);

  std::cout << BLUE << "FOO SIZES {" << std::endl;
  std::cout << BLUE << " size: " << foo.size() << "\n";
  std::cout << BLUE << " cap: " << foo.capacity() << "\n}\n";   

  size_type cap = foo.capacity();

  for (size_type i = 0; i < cap; i++){
    // std::cout << i << std::endl;
    foo.push_back(T());
  }
  foo.push_back(T());
  foo.push_back(T());

  std::cout << BLUE << "FOO SIZES {" << std::endl;
  std::cout << BLUE << " size: " << foo.size() << "\n";
  std::cout << BLUE << " cap: " << foo.capacity() << "\n}\n";   

  delineate();

  std::cout << YELLOW << std::endl
            << "RESERVE >MAX SIZE TEST" << RESET << std::endl;

  print_test_info<test::test>("TESTING VECTOR RESERVE", BOLDRED);
  

  vector<test::my_class> evil(10);
  evil.reserve(40);
  test_vector_iterate(evil);

  print_test_info<test::test>("RESERVING > max_size BYTES", BOLDRED);
  std::cout << "max size = " << evil.max_size() << std::endl;
  size_type max_size = evil.max_size();
   try
   {
    evil.reserve(max_size + 1);
  }
  catch (const std::exception &e)
  {
      std::cout << BOLDMAGENTA << "Size error is expected: " << e.what() << std::endl << RESET;
  }

  delineate();
}



template <typename T>
void test_vector_resize_with_default_value(const T &value = T())
{
  print_test_info<T>("RESIZING VECTOR WITH DEFAULT VALUE", YELLOW);
  
  std::cout << "value = " << '"' << value << '"' << std::endl;

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
  std::cout << WHITE << "Elements in vector after resize(5):" << std::endl;

  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;

// Extend to size 10 again and fill with value
  Vector.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vector back to resize(10) and value \'" <<\
      value << "'" << std::endl;
  
  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << std::endl;

// Resize to 10, should be idempotent
  Vector.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors after resize(10) again and value " << "'" << value << "'" << std::endl;


  for (vector<int>::size_type i = 0; i < Vector.size(); ++i){
    std::cout << BLUE << ' ' << Vector[i];
  };
  std::cout << RESET << std::endl;

  delineate();
}


#endif