#ifndef TEST_ITERATION_H
# define TEST_ITERATION_H

# include <iostream>
# include <iomanip>

# include "pick_vector.hpp"
# include "Test.hpp"
# include "type_traits.hpp"
# include "utils.hpp"
# include "colors.hpp"
# include "test_iteration.hpp"

using test::signal_const;

template <typename V>
void test_vector_iterate(V &v);


template <typename V>
void test_iterators(V &v)
{
  
  print_test_info<int>("TEST ITERATOR COMPARISON", GREEN);
  print("Look test_iterators function for assertions. \n \
  Assertion throws an error if the expression is not correct", MAGENTA);

  typename V::iterator begin = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rbegin = v.rbegin();
  typename V::reverse_iterator rend = v.rend();
  /* typename V::const_iterator cbegin = v.cbegin(); */
  /* typename V::const_iterator cend = v.cend(); */
  /* typename V::const_reverse_iterator crbegin = v.crbegin(); */
  /* typename V::const_reverse_iterator crend = v.crend(); */

  vector<char> vchar(5, 'h');

  // vector<std::string> vstring(5, "Hello!111");

  // Comparison
  /* assert (crbegin != crend); */
  /* assert (end == cend); */
  assert (end > begin);
  /* assert (begin == cbegin); */
  /* assert (cbegin == begin); */
  /* assert (crbegin <= rend); */
  assert (begin < end);
  assert (begin != end);
  /* assert (rbegin == crbegin); */
  
  assert ((rend - rbegin) == static_cast<typename V::difference_type>(v.size()));
  assert ((end - begin) == static_cast<typename V::difference_type>(v.size()));
  /* assert ((cend - begin) == static_cast<typename V::difference_type>(v.size())); */
  /* assert ((crend - rbegin) == static_cast<typename V::difference_type>(v.size())); */

  /* assert ((begin + 1) == (cbegin + 1)); */
  /* assert ((end - 1) == (cend - 1)); */
  // assert ((rbegin + 1) == (end - 1));  // CE - iterators are different
  // assert (rbegin > end); CE - can't compare iterator with adaptor
  // end[0]; rend[0];   //UB + possible heap-buffer-overflow ('ends' are invalid iterators)
  assert (begin[v.size() - 1] == end[-1]);
  assert (begin[v.size() - 1] == rbegin[0]);
  assert (rbegin[0] == end[-1]);
  assert (&rbegin[-1] == end.base()); 

  // Wrong type comparison
  // std::cout << (begin > vstring.begin()) << std::endl; CE

  // Arithmetic
  assert (end > (end - 1));
  assert (rend > (rend - 1));
  // vchar.insert;
  

  test_vector_iterate(v);

  // Mutable elems
  std::cout << GREEN << "Iterators to mutable elements\n" << RESET;
  
  std::cout << std::left << std::setw(35) << "First elem of vector V:"             << "\t" << *begin << "\n";
  std::cout << std::left << std::setw(35) << "Last elem of vector V:"              << "\t" << *(end - 1) << std::endl;
  std::cout << std::left << std::setw(35) << "First elem of vector V[::-1]:"       << "\t" << *rbegin << std::endl;    // will take the last item of array
  std::cout << std::left << std::setw(35) << "Last elem of vector V[::-1]:"        << "\t" << *(rend - 1) << std::endl; // will move reverse iterator to first position in array


  std::cout << std::endl;
  
  // Constant elems
    // Assigning to these leads to CE
  /* std::cout << RED << "Iterators to constant elements\n" << RESET; */

  /* std::cout << std::left << std::setw(35) << "First const elem of vector V:"       << "\t" << *cbegin << "\n"; */
  /* std::cout << std::left << std::setw(35) << "Last const elem of vector V:"        << "\t" << *(cend - 1) << std::endl; */
  /* std::cout << std::left << std::setw(35) << "First const elem of vector V[::-1]:" << "\t" << *crbegin << std::endl;    // will take the last item of array */
  /* std::cout << std::left << std::setw(35) << "Last const elem of vector V[::-1]:"  << "\t" << *(crend - 1) << std::endl; // will move reverse iterator to first position in array */

  // *cbegin = 5; // CE 

  delineate();
}



template <typename V>
void test_vector_iterate(V &v)
{
  signal_const<ft::is_const<V>::value>::print();
  
  typedef typename ft::conditional<
    ft::is_const<V>::value,
    typename V::const_iterator,
    typename V::iterator>::type
  iterator_type;

  // static_assert (
  //   ft::is_same<
  //     typename ft::conditional<
  //       ft::is_const<V>::value,
  //       typename V::const_iterator,
  //       typename V::iterator
  //     >::type, 
  //     iterator_type
  //   >::value,
  //   "Const vector must yield const_iterator"
  //   );


  // static_assert (
  //   ft::is_same<
  //     typename ft::conditional<
  //       !ft::is_const<V>::value,
  //       typename V::iterator,
  //       typename V::const_iterator
  //     >::type,
  //     iterator_type
  //   >::value,
  //   "Non-const vector must yield iterator"
  //   );

  typedef typename ft::conditional<
    ft::is_const<V>::value,
    typename V::const_reverse_iterator,
    typename V::reverse_iterator>::type
  reverse_iterator_type;


  iterator_type begin = v.begin(); // implicitly requiring an iterator based on vector constness
  iterator_type end = v.end();
  
  /* typename V::const_iterator cend = v.cend(); // explicitly requiring a const iterator */
  /* typename V::const_iterator cbegin = v.cbegin(); */
  reverse_iterator_type rbegin = v.rbegin();
  reverse_iterator_type rend = v.rend();
  /* typename V::const_reverse_iterator crbegin = v.crbegin(); */
  /* typename V::const_reverse_iterator crend = v.crend(); */
  
  /* (void)cend; */
  /* (void)cbegin; */
  /* (void)crbegin; */
  /* (void)crend; */

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
  std::cout << std::endl;

  std::cout << std::string(20, '>') << std::endl;

  std::cout << "Iterating through vector backwards" << std::endl;
  for (; rbegin != rend; ++rbegin)
  {
    std::cout << *rbegin << " ";
  }
  std::cout << std::endl;

  // std::cout << "Iterating through vector backwards using const reverse iterator" << std::endl;
  // for (; crbegin != crend; ++crbegin)
  // {
  //   std::cout << *crbegin << " ";
  // }
  //   // *crbegin = 5
  //   // compile error
  std::cout << "\n\n";

}

#endif
