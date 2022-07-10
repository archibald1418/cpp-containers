#ifndef TEST_ASSIGNING_H
# define TEST_ASSIGNING_H
# include "pick_vector.hpp"
# include "test_iteration.hpp"


void  test_vector_assign_count()
{
    std::cout << "TESTING ASSIGN COUNT" << std::endl;
    vector<int> v1(5, 0);
    vector<int> v2(10, 42);

    test_vector_iterate(v1);
try {
    v1.assign(2, -1);
} catch (const std::exception& e){
  std::cout << "Error: e" << e.what() << std::endl;
}
    // entirely replaces the vector contents, regardless of size, + deletes redundant if any
    // v1.assign(v1.begin(), v2.begin());
    // std::cout << diff << std::endl;
    test_vector_iterate(v1);
}

#endif