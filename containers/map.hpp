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
        class Predicate, // DEBUG: This should be ft::less<Key> - when comparing pair it will compare 'first' - if equals - should throw error!
        class Alloc,
        bool MultiFlag,
        template<typename> class NodeType = AVLNode
    >
    struct map_traits
    {
        typedef Key						key_type;
        typedef pair<const Key, Value>	value_type;
        typedef Predicate				key_compare;
		typedef is_multi<MultiFlag>		isMulti;
        /* typedef Alloc                                                               allocator_type; */ 
        /* typedef typename allocator_type::template rebind<value_type>::other         allocator_node; */

        /* typedef NodeType<value_type>                                                node_t; */

        typedef tree_traits<
				value_type,
				NodeType,
				Alloc,
				Predicate>								tree_traits;
		typedef BaseNode<value_type, NodeType>			__base_node;
		typedef BaseTree<tree_traits>					tree_t;

		typedef typename tree_traits::node_t			node_t;
		typedef typename tree_traits::nodeptr			nodeptr;
		typedef typename tree_traits::pointer			pointer;
		typedef typename tree_traits::allocator_type	allocator_type;

		typedef typename
			allocator_type::template rebind<node_t>::other	allocator_node;
		typedef typename
			allocator_type::template rebind<node_t*>::other	allocator_node_pointer;


        key_compare comp;

        map_traits() : comp(){};
        map_traits(key_compare comparator) : comp(comparator){};
		// TODO: maybe try throw error in comp if keys are equal?..

	
		class value_compare : public binary_function<value_type, value_type, bool>
		{
			protected:
				key_compare comp;
			public:
				bool operator()(const value_type& X, const value_type& Y)const{
					// All extra logic goes here
					return comp(X.first, Y.first);
				}

				value_compare(key_compare comp) : comp(comp){};
		};

		protected:
			const key_type& getKeyByVal(const value_type& pairxy) const{
				return pairxy.first;
			}
    };
   
    template <
        typename Key,
        typename T,
        typename Compare = less<Key>,
	    typename Alloc = std::allocator<pair<const Key, T> > 
    >
    class map : protected BaseTree<map_traits<Key, T, Compare, Alloc, false> >
    {
		// protected - for stopping access from the outside
		/* TODO: ready for writing map 
		 *- AVLTree<value_type> as private member on stack memory
		 *- AVLTree<value_type> knows its Compare, its Alloc => its node allocators
		 *- map methods call tree's methods
		 *- iterator is dereferenced by calling Get() method from pointer to tree (calls node's Get())
		 *- if found key that's already present, throws error
		 * 
		 * - CAUTION: Iterators are based on Lmost and Rmost tracking! TEST THIS CAREFULLY
		 * */

		private:
			typedef map_traits<Key, T, Compare, Alloc, false>	traits;
			typedef BaseTree<traits>							tree;
			typedef typename tree::traits						tree_traits;
			typedef tree										__base;
        public:
            typedef Key										key_type;
            typedef T										mapped_type;
            typedef pair<const Key, T>						value_type;
            typedef Compare									key_compare;
            typedef Alloc									allocator_type;

			typedef std::size_t 							size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;

			// Node stuff
			typedef typename traits::node_t				node_t;
			typedef typename traits::nodeptr			nodeptr;

			typedef typename traits::allocator_node			allocator_node;
			typedef typename traits::allocator_node_pointer allocator_node_pointer;
			typedef node_t								node_type; // member type since c++17
			
			map() : __base(key_compare()){

			}
			~map(){

			}
			
			const nodeptr& getRoot()const{
				return this->Root();
			}
    };


}


#endif // MAP_H

