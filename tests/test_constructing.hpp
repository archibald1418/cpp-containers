#ifndef TEST_CONSTRUCTING_H
# define TEST_CONSTRUCTING_H

# include <cassert>
# include <memory>
# include <string>

# include "utils.hpp"
# include "pick_vector.hpp"
# include "test_iteration.hpp"
# include "test_resizing.hpp"

void test_default_constructor(){

    print_test_info<int>("TESTING DEFAULT CONSTRUCTOR\n");

    vector<int> v1;
    vector<int> v2 = vector<int>();
    vector<int> v3(v1);

    assert((v1 == v2) && (v1.size() == v2.size()));
    assert (v1.empty() && v2.empty() && v3.empty());
    assert (v1.end() == v2.begin()); // If the vector is empty, the returned iterator will be equal to end().

  delineate();
}

void test_size_value_constructor(){

    print_test_info<int>("Testing (size, value) constructor\n");
    
    vector<int> v1(0); assert (v1.empty());
    vector<int> v2(0, 0); assert(v2.empty());

    test_vector_iterate(v2);
    
    v2.assign(42, 42);
    v1 = v2; assert (v1 == v2);

    test_vector_iterate(v2);    

    // try {
    //     vector<int> evil(4570298750498759487, 0); RE - bad alloc
    // } catch (const std::exception& e){
    //     std::cout << "Error:" << e.what() << std::endl;
    // }

  delineate();
}

void test_range_constructor(){

    print_test_info<int>("Testing (iterator, iterator) constructor\n");

    vector<int> v1;
    create_vector_of_ints(v1, 11);
    v1[0] = -1;
    *v1.rbegin() = -10;

    // vector<int>v2(v1.begin() - 6, v1.end() - 8); heap-buffer overflow
    vector<int>vr(v1.rbegin(), v1.rend());

    test_vector_iterate(v1);    
    // test_vector_iterate(v2);
    test_vector_iterate(vr);

  delineate();
}

#endif