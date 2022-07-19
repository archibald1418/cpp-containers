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

  std::cout << "Delete from vector slice [0:3] :" << std::endl;
  vector<T> slice(ptr->begin(), ptr->begin() + 2);
  test_vector_iterate(slice);
  slice.erase(slice.begin());
  test_vector_iterate(slice);
  slice.erase(slice.begin());
  test_vector_iterate(slice);
}

template <typename T>
void test_vector_equality(){

  std::cout << "Equality tests" << std::endl;

  typedef vector<T> vint;
  typedef typename VectorFactory<T>::factory factory;

  vint a = *unique_ptr<vint>(factory::create());
  vint b(a);

  int value = 42;

  assert (a == b);

  a.push_back(value);
  assert (a != b); assert (a > b); assert (b <= a);


  // test_vector_iterate(a);
 
  // typename vint::const_iterator cit = a.begin();

  a.erase(a.begin());
  // a.erase(a.rbegin());
  
  // test_vector_iterate(a);

  // assert (a != b); assert (a < b);
  // assert (b != a); assert (b >= a);
}

template <typename T>
void test_vector_erase_range(){
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

void test_vector_insert(){
  vector<int> v = *unique_ptr<vector<int> >(VectorFactory<int>::factory::create());
  vector<int> v2(v);

  // vector<int> v1; v1.push_back(42);

// One element insert
  // v.insert(v.end() - 1, v[0]); // Tricky case! 
  // v.insert(v.begin() + 1, 666);

  // test_vector_iterate(v);
  // // v.insert(v.end() + 1, 666); UB - causes heap-buffer overflow 
  // v.insert(v.end(), 666);
  // v.insert(v.end() - 1, -42);

// Size insert
  // v.insert(v.end(), 7, 42);
  // test_vector_iterate(v);
  // std::cout << v.size() << " " << v.capacity() << std::endl;
  // v2.insert(v2.begin(), -42);
  // v.insert(v.begin(), 1, -42);

  // assert (v == v2);

  // v2.insert(v2.begin() + 1, -42);
  // v2.insert(v2.begin() + 1, -42);
  // v.insert(v.begin() + 1, 2, -42);

  // assert (v == v2);

  // std::cout << v.size() << " " << v.capacity() << std::endl;
  // std::cout << v.size() << " " << v.capacity() << std::endl;

// Range insert
  
  vector<int> to_insert(8, -8);
  // v.insert(v.end(), to_insert.begin(), to_insert.end() - 2);
  v.insert(v.end(), to_insert.end() - 2, to_insert.begin()); // first > last is UB
  
  test_vector_iterate(v);
}

#endif