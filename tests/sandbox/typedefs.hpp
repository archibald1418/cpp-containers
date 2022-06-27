#include <iterator>
#include <iostream>

template <typename T, class allocator = std::allocator<T> >
class Container
{
    
        // Basic type definitions for allocator use
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef T           value_type;
    
    // Rebind structure
    template <class U>
        struct rebind{
            /*
        Used when a class allocates memory 
        to some other custom object, not of type T.
        E.g. list content vs list Node, std::pair vs types in std::pair
        
        allocator<T>::rebind<Node_class>::other
            */
            typedef allocator<U> other;
        };
    
};

