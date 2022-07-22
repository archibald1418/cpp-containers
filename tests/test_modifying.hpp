#ifndef TEST_MODIFIYING_H
# define TEST_MODIFIYING_H

# include <iostream>

# include "pick_vector.hpp"
# include "Test.hpp"
# include "utils.hpp"
# include "test_iteration.hpp"
# include "test_assigning.hpp"
# include "VectorFactory.hpp"

using test::unique_ptr;
using test::VectorFactory;


template <typename T>
void  test_vector_erase(){

  ::print_test_info<T>("ERASING VECTOR TEST", RED);

  unique_ptr<vector<T> > ptr = unique_ptr<vector<T> >(VectorFactory<T>::factory::create());
  vector<T> Vector = *ptr;

  test_vector_iterate(Vector);

  delineate();

  std::cout << GREEN << "Delete start" << RESET << std::endl;
  Vector.erase(Vector.begin());
  test_vector_iterate(Vector);

  delineate();

  std::cout << GREEN << "Delete end" << RESET << std::endl;
  Vector.erase(Vector.end() - 1);
  test_vector_iterate(Vector);  

  delineate();

  std::cout << GREEN << "Delete middle element" << RESET << std::endl;
  Vector.erase(Vector.begin() + (Vector.size() / 2));
  test_vector_iterate(Vector);

  delineate();

  std::cout << GREEN << "Delete from vector slice [0:3)" << RESET << std::endl;
  vector<T> slice(ptr->begin(), ptr->begin() + 3);
  test_vector_iterate(slice);
  slice.erase(slice.begin());
  test_vector_iterate(slice);
  slice.erase(slice.begin());
  test_vector_iterate(slice);

  delineate();
}


void test_vector_equality(){

  print_test_info<int>("EQUALITY TESTS");

  typedef vector<int> vint;
  typedef typename VectorFactory<int>::factory factory;

  vint a = *unique_ptr<vint>(factory::create());
  vint b(a);

  int value = 42;

  assert (a == b);

  a.push_back(value);

  assert (a != b); 
  assert (a > b); 
  assert (b <= a);


  // test_vector_iterate(a);
 
  // typename vint::const_iterator cit = a.begin();

  a.erase(a.end() - 1);

  assert (a == b);
  
  // test_vector_iterate(a);

  b.push_back(value);

  assert (a != b); assert (a < b);
  assert (b != a); assert (b >= a);

  std::cout << "Assertions passed" << std::endl;

  delineate();
}

template <typename T>
void test_vector_erase_range(){

  print_test_info<T>("ERASING RANGE FROM VECTOR", YELLOW);

  typedef vector<T> vector_of;
  typedef typename vector_of::iterator iterator;
  // typedef typename vector_of::difference_type size_type;

  vector_of v(
    *unique_ptr<vector_of>(VectorFactory<T>::factory::create())
  ); // 0,1,2,3,4,5,6,7,8,9

  iterator last;
  iterator out;
  
  test_vector_iterate(v);

  // erase whole
  v.erase(v.begin(), v.end()); // empty
  assert (v.empty());
  test_vector_iterate(v);

  create_vector_of_ints(v, 5); // 0,1,2,3,4
  //erase from right
  v.erase(v.begin() + 2, v.end()); // 0,1
  test_vector_iterate(v);

  v.clear();


  create_vector_of_ints(v, 5); // 0,1,2,3,4
  // erase from left
  last = v.end() - 2;
  out = v.erase(v.begin(), last); // 3,4
  test_vector_iterate(v); assert(out == (v.end() - 2));

  v.clear();

  // size_type loffset = 1; size_type roffset = 1;
  // erase from middle
  // last = v.end() - roffset;
  // iterator old_end = v.end();
  // out = v.erase(v.begin() + loffset, v.end() - roffset);  // 0,4
  create_vector_of_ints(v, 5); // 0,1,2,3,4
  test_vector_iterate(v);
  out = v.erase(v.begin() + 1, v.end() - 2);  // 0,4
  assert ((out - v.begin()) == 1);
  test_vector_iterate(v); 

  vector_of empty;
  empty.push_back(1);

  test_vector_iterate(empty);

  empty.erase(empty.begin(), empty.end());

  test_vector_iterate(empty);
  
}

template <>
void test_vector_erase_range<char>(){
  
  typedef vector<char> vector_of;

  vector_of vchar;

  ::print_test_info<char>("ERASING RANGE FROM VECTOR", BLUE);

  create_vector_of_chars(vchar);

  std::cout << YELLOW;
  test_vector_iterate(vchar);

  cut_vector_of_chars(vchar);
  std::cout << RESET << RED;
  
  test_vector_iterate(vchar);
  std::cout << RESET;
}


void test_vector_insert(){

  print_test_info<int>("TEST VECTOR INSERTION", CYAN);

  vector<int> v = *unique_ptr<vector<int> >(VectorFactory<int>::factory::create());
  vector<int> v2(v);

  vector<int> v1; v1.push_back(42);

// One element insert
  v.insert(v.end() - 1, v[0]); // Tricky case! 
  v.insert(v.begin() + 1, 666);

  test_vector_iterate(v);
  // v.insert(v.end() + 1, 666); UB - causes heap-buffer overflow 
  v.insert(v.end(), 666);
  v.insert(v.end() - 1, -42);

// Size insert
  v.insert(v.end(), 7, 42);
  test_vector_iterate(v);
  // std::cout << v.size() << " " << v.capacity() << std::endl;
  v2.insert(v2.begin(), -42);
  v.insert(v.begin(), 1, -42);

  // assert (v == v2);

  v2.insert(v2.begin() + 1, -42);
  v2.insert(v2.begin() + 1, -42);
  v.insert(v.begin() + 1, 2, -42);

  // assert (v == v2);

  // std::cout << v.size() << " " << v.capacity() << std::endl;
  // std::cout << v.size() << " " << v.capacity() << std::endl;

// Range insert
  
  vector<int> to_insert(8, -8);
  typedef vector<int>::reverse_iterator revit;
  to_insert.push_back(42);
  v.insert(v.end(), revit(to_insert.begin()), revit(to_insert.end()));
  // v.insert(v.end(), to_insert.end() - 2, to_insert.begin()); // first > last is UB
  
  test_vector_iterate(v);
}

#endif