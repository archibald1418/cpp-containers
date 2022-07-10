#ifndef TEST_RESIZING_H
# define TEST_RESIZING_H

# include "pick_vector.hpp"
# include "type_traits.hpp"
# include "Test.hpp"
# include "utils.hpp"
# include <iostream>

using test::unique_ptr;
using test::VectorFactory;

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


#endif