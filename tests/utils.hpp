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


namespace test{
  
    template <bool B>
    struct signal_const {
      static void prnt(){}
    };
    template <>
    struct signal_const<true>{
      static void prnt(){std::cout << "CONST!" << std::endl;}
    };

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
    pointer operator->()const{
      return _ptr;
    }
  };

  template <typename T>
  class IsDereferenceable{
    private:
        typedef char YesType[1];
        typedef char NoType[2];
        

        template <typename U> static YesType& test(void* = &U::operator*);
        template <typename U> static NoType& test(...);
    public:
        static const bool value = (
            ft::is_pointer<T>::value || (sizeof(test<T>(0)) == sizeof(YesType))
        );
}; 
};

// Useful functions
void prnt(std::string s);
template <typename T>
void prnt(
    T ptr, 
    typename ft::enable_if<test::IsDereferenceable<T>::value, T>::type* = 0)
{
  std::cout << GREEN << *ptr << "\n\n" << RESET;
}

#endif

