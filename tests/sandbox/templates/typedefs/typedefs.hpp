#include <iterator>
#include <iostream>
#include <cstddef>

template<typename T>
struct template_class {
	T t;
	template_class (){
		std::cout << t << std::endl;
	}
};

template <typename T, class allocator = std::allocator<T>,
		 template<typename> class temp = template_class>
struct Container
{
    
        // Basic type definitions for allocator use
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef T           value_type;
		typedef allocator	allocator_type;

		// template template typedef


    
    // Rebind structure
    template <class U>
        struct rebind{
            /*
        Used when a class allocates memory 
        to some other custom object, not of type T.
        E.g. list content vs list Node, std::pair vs types in std::pair
        
        allocator<T>::rebind<Node_class>::other
            */
            typedef std::allocator<U> other;
        };

	class Inner {
		public:
			int i;
	};
    
};


struct Child : public Container<int>{

};

struct Grandchild : public Child{

};
