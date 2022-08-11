#ifndef MAP_H
# define MAP_H

# include "functional.hpp"
# include "utility.hpp"
# include "node.hpp"
# include "tree.hpp"
# include <memory>

namespace ft
{
    
    template <
        typename Key,
        typename Value,
        class Predicate, // DEBUG: This should be ft::less<Key>, but will it access the pair's first element????
        class Alloc,
        bool MultiFlag,
        template<typename> class NodeType
    >
    struct map_traits
    {
        typedef Key                                                                 key_type;
        typedef pair<const Key, Value>                                              value_type;
        typedef Predicate                                                           key_compare;
        // NOTE: there will be key_comp() function that applies key_compare to ft::pair<T, U>::first_argument_type
        typedef Alloc                                                               allocator_type; 
        typedef typename allocator_type::template rebind<value_type>::other         allocator_node;

        typedef NodeType<value_type>                                                node_t;
        // typedef ft::tree_traits<node_t, key_compare>                                tree_traits;

        Predicate comp;

        map_traits() : comp(){};
        map_traits(Predicate Parg) : comp(Parg){};
    };
    

    
    template <
        typename Key,
        typename T,
        typename Compare = less<Key>,
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


}


#endif
