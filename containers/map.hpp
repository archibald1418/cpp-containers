#ifndef MAP_H
# define MAP_H

# include "functional.hpp"
# include "utility.hpp"
# include <memory>

namespace ft{
    template <
        typename Key,
        typename T,
        typename Compare = ft::less<Key>,
	    typename Alloc = std::allocator<ft::pair<const Key, T> > 
    >
    class map
    {
        public:
            typedef Key					        key_type;
            typedef T					        mapped_type;
            typedef ft::pair<const Key, T>		value_type;
            typedef Compare					    keycompare;
            typedef Alloc					    allocator_type;
    };

#endif
