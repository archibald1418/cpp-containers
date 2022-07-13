#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <stack>
#include <iterator>
#include <random>
#include "ft_containers.hpp"
#include "pick_vector.hpp"
#include "VectorFactory.hpp"
#include "Test.hpp"
#include "utils.hpp"
#include "type_traits.hpp"
#include "test_iteration.hpp"
#include "test_constructing.hpp"
#include "test_assigning.hpp"
#include "test_modifying.hpp"
#include "test_resizing.hpp"
#include "test_iterator_non_members.hpp"

using test::VectorFactory;
using test::factory_type;
using test::unique_ptr;

int main()
{
  std::cout << RED << "\nTESTING " << vector_types[MY] << "\n\n" << RESET;

  // test_vector_erase<int>();
  // test_vector_erase<std::string>();
  // test_vector_erase<char>();
  // test_vector_reserve<int>();
  // test_vector_resize_with_default_value<std::string>("spam");
  
  // test_vector_sizes(*unique_ptr< vector<int> >(VectorFactory<int>::factory::create()));

  
  // vector<int> v1;
  // vector<int> dummy;
  // (void)dummy;
  // create_vector_of_ints(v1, 10);
  // v1[0] = -1;

  // test_vector_iterate(v1);
  // vector<int>::const_iterator last = v.cend() - 1;
  // // vector<int>::iterator it = v.erase(dummy.end() - 1);
  // // (void)it;
  // vector<int>::iterator range_it = v.erase(v.begin(), v.begin());
  // // (void)range_it;



  // std::cout << *range_it << std::endl;
  // std::cout << v.empty() << std::endl;
  
  // test_vector_iterate(*unique_ptr< const vector<int> >(VectorFactory<int>::factory::create()));
  // test_vector_erase<int>();
  // test_vector_assign_count();

  // v.erase(v.begin(), v.end());
  // // test_iterators(v);
  // test_vector_iterate(v);

  // test_vector_assign_range();
  // test_assignment_operator();
  
  // test_default_constructor();
  // test_size_value_constructor();
  // test_range_constructor();
  // test_vector_erase_range<int>();
  // test_vector_erase<int>();
  // test_vector_erase<int>();
  
  // vector<int> v(5, 5);
  // vector<int>::reverse_iterator it(v.rbegin());
  test_advance();

  // *it = 5;
};
