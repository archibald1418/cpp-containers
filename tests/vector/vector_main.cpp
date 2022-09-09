#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <stack>
#include <iterator>


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
#include "test_inserters.hpp"
#include "colors.hpp"
#include "utility.hpp"


using test::VectorFactory;
using test::factory_type;
using test::unique_ptr;



int main(){
  std::cout << YELLOW << "\nTESTING " << vector_types[MY] << "\n\n" << RESET;

// Erasure
  test_vector_erase<int>();
  test_vector_erase<std::string>();
  test_vector_erase<char>();

// Reserving memory
  test_vector_reserve<int>();

// Resizin vector
  test_vector_resize_with_default_value<std::string>("spam");

// Size, capacity
  test_vector_sizes(*unique_ptr< vector<int> >(VectorFactory<int>::factory::create()));

  
  vector<int> v1;
  vector<int> dummy;
  (void)dummy;
  create_vector_of_ints(v1, 10);
  v1[0] = -1;

// Iterators 
  test_iterators(v1);
  test_vector_iterate(
    *unique_ptr< const vector<int> >(VectorFactory<int>::factory::create())
  );

// Erasure
  test_vector_erase<int>();
  test_vector_erase_range<int>();
  test_vector_erase_range<char>();

// Assignment
  test_vector_assign_count();
  test_vector_assign_range();
  test_assignment_operator();
  
// Constructors
  test_default_constructor();
  test_size_value_constructor();
  test_range_constructor();
  test_copy_constructor();

// Comparison operators
  test_vector_equality();
  
// Iterator non-members
  test_advance();
  test_distance();

// Swap
  test_swap<int>();
}
