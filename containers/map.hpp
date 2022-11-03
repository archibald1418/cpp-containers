#ifndef MAP_H
# define MAP_H

# include "functional.hpp"
# include "utility.hpp"
# include "node.hpp"
# include "tree.hpp"
# include "type_traits.hpp"
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
		typedef IsMulti																is_multi<MultiFlag>;
        // NOTE: there will be key_comp() function that applies key_compare to ft::pair<T, U>::first_argument_type
		// TODO: these should be obtained from the tree's typedefs
        /* typedef Alloc                                                               allocator_type; */ 
        /* typedef typename allocator_type::template rebind<value_type>::other         allocator_node; */

        /* typedef NodeType<value_type>                                                node_t; */
        // typedef ft::tree_traits<node_t, key_compare>                                tree_traits;

        Predicate comp;

        map_traits() : comp(){};
        map_traits(Predicate Parg) : comp(Parg){};
    };
   

    
    template <
        typename Key,
        typename T,
        typename Compare = less<Key>,
	    typename Alloc = std::allocator<pair<const Key, T> > 
    >
    class map
    {
		/* TODO: ready for writing map 
		 * - make tree accessible for map (via inheritance)
		 *- AVLTree<value_type> as private member on stack memory
		 *- AVLTree<value_type> knows its Compare, its Alloc => its node allocators
		 *- map methods call tree's methods
		 *- iterator is dereferenced by calling Get() method from pointer to tree (calls node's Get())
		 *- if found key that's already present, throws error
		 * 
		 * - CAUTION: Iterators are based on Lmost and Rmost tracking! TEST THIS CAREFULLY
		 * */
        public:
            typedef Key										key_type;
            typedef T										mapped_type;
            typedef pair<const Key, T>						value_type;
            typedef Compare									key_compare;
            typedef Alloc									allocator_type;

			typedef size_type								std::size_t;
			typedef difference_type							std::ptrdiff_t;

			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;

			// TODO: create iterators
			
    };


}


#endif // MAP_H

