#ifndef TEST_MODIFIYING_H
# define TEST_MODIFIYING_H

# include "pick_vector.hpp"
# include "Test.hpp"
# include "utils.hpp"
# include <iostream>
# include "test_iteration.hpp"
# include "test_assigning.hpp"
# include "VectorFactory.hpp"

using test::unique_ptr;
using test::VectorFactory;


template <typename T>
void  test_vector_erase(){

  std::cout << "ERASING VECTOR TEST" << std::endl;
  unique_ptr<vector<T> > ptr = unique_ptr<vector<T> >(VectorFactory<T>::factory::create());
  vector<T> Vector = *ptr;

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

template <typename T>
void test_vector_equality(){

  std::cout << "Equality tests" << std::endl;

  typedef vector<T> vint;
  typedef typename VectorFactory<T>::factory factory;

  const vint a = *unique_ptr<vint>(factory::create());
  (void)a;

  // int value = 42;

  // assert (a == b);

  // a.push_back(value);
  // assert (a != b); assert (a > b); assert (b <= a);


  // test_vector_iterate(a);
 
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

  test_vector_iterate(v);
  v.erase(v.begin(), v.end());
  test_vector_iterate(v);
}

#endif