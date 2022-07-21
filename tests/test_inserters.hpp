#ifndef TEST_INSERTERS_H
# define TEST_INSERTERS_H


#include "test_iteration.hpp"
#include "test_modifying.hpp"
#include "test_constructing.hpp"
#include "Test.hpp"
#include "VectorFactory.hpp"
#include "utility.hpp"
#include "pick_vector.hpp"

// #include <deque>
// #include <memory>
// #include <algorithm>
// #include <iterator>
// #include <iostream>


using test::unique_ptr;
using test::VectorFactory;

void test_front_inserter()
{
    vector<int> v(*unique_ptr<vector<int> >(VectorFactory<int>::factory::create()));

    std::deque<int> d;
    vector<int> v2;
    v2.reserve(20);
    ft::copy(v.begin(), v.end(), ft::inserter(d, d.begin()));
    // ft::copy(&v.begin()[0], &v.end()[-1], &v2.begin()[0]);

    // typedef std::deque<int>::iterator iterator;

    for (auto it = v2.begin(); it != v2.end(); ++it)
        std::cout << *it << ' ';
}

void test_copy(){
    int a[30];

    std::memset(a, 42, 30 * sizeof(int));

    for (int i = 0; i < 30; i++)
        std::cout << a[i] << " ";

    for (int i = 0; i < 10; i++){
        a[i] = i + 1;
    }

    std::cout << std::endl;

    for (int i = 0; i < 30; i++)
        std::cout << a[i] << " ";

    std::cout << std::endl;

    ft::copy(&a[0], &a[10], &a[15]);

    for (int i = 0; i < 30; i++)
        std::cout << a[i] << " ";
}

#endif