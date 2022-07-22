#ifndef TEST_ASSIGNING_H
# define TEST_ASSIGNING_H

# include <cassert>

# include "pick_vector.hpp"
# include "test_iteration.hpp"
# include "test_modifying.hpp"
# include "utils.hpp"


void  test_vector_assign_count()
{   
    print_test_info<int>("TESTING ASSIGN COUNT");
    

    vector<int> v1(5, 0);
    vector<int> v2(10, 42);

    test_vector_iterate(v1);
try {
    v1.assign(2, -1);
} catch (const std::exception& e){
  std::cout << "Error: e" << e.what() << std::endl;
}
    test_vector_iterate(v1);

    delineate();
}

void test_vector_assign_range(){

    print_test_info<int>("TESTING ASSIGN RANGE");

    vector<int> v(5, 0);

    vector<int> v2(10, 42);

    for (vector<int>::iterator it = v.begin(); it < v.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << "\n";

    try 
    {   
        std::cout << v2.end() - v2.begin() << std::endl;
        v.assign(v2.rbegin(), v2.rbegin());
        // If it1 > it2, throws length_error
        // If it1 == it2, does one replacement
    }
    catch (const std::exception& e){
        std::cout << "ERROR:"<<e.what() << std::endl;
    }

    for (vector<int>::iterator it = v.begin(); it < v.end(); ++it){
        std::cout << *it << ' ';
    }

  delineate();
}

void test_assignment_operator(){

    print_test_info<int>("TESTING ASSIGNMENT OPERATOR");

    vector<int> v;

    create_vector_of_ints(v, 10);

    assert (v == v);

    test_vector_iterate(v);

    vector<int> vcopy = v;
    
    assert (vcopy == v);

    test_vector_equality<int>();    

  delineate();
}

#endif