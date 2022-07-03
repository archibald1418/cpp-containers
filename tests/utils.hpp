#ifndef UTILS_H
# define UTILS_H

#include "type_traits.hpp"
#include "Test.hpp"

template <typename Container>
void create_vector_of_ints(Container &vector, int elems)
{

  for (int i = 0; i < elems; i++)
  {
    vector.push_back(i);
  };
}

void prnt(std::string s){
  std::cout << RED << s << "\n\n" << RESET;
}

namespace test{

  template <typename T>
  struct unique_ptr{
    typedef T* pointer;
    typedef T element_type;
    typedef element_type& reference;
    
    pointer _ptr;
    
    unique_ptr(T* ptr) : _ptr(ptr){};
    ~unique_ptr(){
      if (_ptr) delete _ptr;
    }
    reference operator*()const{
      return *_ptr;
    }
  };
};

#endif

