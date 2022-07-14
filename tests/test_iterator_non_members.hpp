#ifndef TEST_ITERATOR_NON_MEMBERS_H
# define TEST_ITERATOR_NON_MEMBERS_H

#include "pick_vector.hpp"
#include "iterator.hpp"
#include "utils.hpp"
#include "test_iteration.hpp"
#include "VectorFactory.hpp"
#include <iostream>
#include <iterator>

using test::unique_ptr;
using test::VectorFactory;

typedef int type;


# ifdef MY
#  if MY == 1
    using ft::advance;
    using ft::distance;
#  else
    using std::advance;
    using std::distance;
#  endif
# endif

#ifndef MY
# define MY 0
    using std::advance;
    using std::distance;
# endif




void test_advance(){
    typedef vector<type> vector;
    typedef vector::value_type type;
    
    typedef vector::iterator iterator;
    // typedef typename vector::const_iterator const_iterator;
    // typedef typename vector::reverse_iterator reverse_iterator;
    // typedef typename vector::const_reverse_iterator const_reverse_iterator;

    vector v = *unique_ptr<vector>(VectorFactory<type>::factory::create());

    iterator it1 = v.begin();
    iterator it1_copy = it1;
    test_vector_iterate(v);
    advance(it1, 3);
    ::prnt(it1);
    advance(it1, -3);
    assert (it1_copy == it1);
    ::prnt(it1);
    // ::prnt(std::string("PSYCH"));    
}

void test_distance(){
    typedef vector<type> vector;
    typedef vector::value_type type;
    
    typedef vector::iterator iterator;
    typedef iterator::difference_type difference_type;

    vector v = *unique_ptr<vector>(VectorFactory<type>::factory::create());

    iterator begin = v.begin();
    iterator end = v.end();

    assert (
        -static_cast<difference_type>(v.size()) == distance(end, begin)
    ); // distance -> -10
    assert (
        static_cast<difference_type>(v.size()) == distance(begin, end)
    ); // distance -> 10
    // assert (
    //     static_cast<difference_type>(v.size()) == distance(cbegin, end)
    // ); CE - works only with same-class iterators

    // assert (v.size() == distance(end, begin));
}

#endif