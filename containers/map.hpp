#ifndef MAP_H
# define MAP_H

# include "functional.hpp"
# include "utility.hpp"
# include "node.hpp"
# include "tree.hpp"
# include "type_traits.hpp"
# include "tree_iterator.hpp"
# include <memory>

# include <iostream>

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
	// NOTE: ft::less<Key> is for comparing key_type-s directly
    struct map_traits
    {
        typedef Key						key_type;
        typedef pair<const Key, Value>	value_type;
		typedef is_multi<MultiFlag>		isMulti; // flag for non-strict total order

        typedef Predicate				key_compare;
		
		class value_compare : public binary_function<value_type, value_type, bool>
		{
			protected:
				key_compare comp;
			public:
				bool operator()(const value_type& X, const value_type& Y)const{
					// All extra logic goes here - TODO: throw error ifeq and not multi
					return comp(X.first, Y.first);
				}

				value_compare(key_compare comp) : comp(comp){};
		};

		// Tree
		typedef tree_traits<
				value_type,
				NodeType,
				Alloc,
				value_compare>							tree_traits;
				// NOTE: value_compare compares compairs pairs by comparing keys
		typedef BaseNode<value_type, NodeType>			__base_node;
		typedef BaseTree<tree_traits>					tree_t;

		// nodes
		typedef typename tree_traits::node_t			node_t;
		typedef typename tree_traits::nodeptr			nodeptr;

		typedef typename tree_traits::pointer			pointer;

		// Allocation
		typedef typename tree_traits::allocator_type			allocator_type;
		typedef typename tree_traits::allocator_node			allocator_node;
		typedef typename tree_traits::allocator_node_pointer	allocator_node_pointer;

		// TODO: node info comes from trees, type info goes here


        key_compare comp;

        map_traits() : comp(){};
        map_traits(Predicate c) : comp(c){};

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
			
			typedef tree_iterator<value_type, node_t>			iterator;
			typedef const_tree_iterator<value_type, node_t>		const_iterator;
			/* typedef reverse_iterator<iterator>					reverse_iterator; */
			/* typedef reverse_iterator<const_iterator>			const_reverse_iterator; */

			/* template< class InputIt > */
			/* map( InputIt first, InputIt last, */
			/* 	 const Compare& comp = Compare(), */
			/* 	 const Alloc& alloc = Allocator()){ */

				
			/* } */

		private:
			const nodeptr& getRoot(){
				return this->Root();
			}

		public:
			explicit map(const key_compare& comp = key_compare())
			:
			__base(comp){}

			virtual ~map(){
				std::cout << "Destroying map" << std::endl;
			}

			allocator_type get_allocator(){
				return allocator_type();
			}
			

			iterator begin(){
				return iterator(this->Lmost());
			}

			iterator end(){
				return iterator(this->Rmost());
			}

			bool empty(){
				return this->empty();
			}

			iterator find(const Key& key){
				return iterator(this->search(getRoot(), key));
			}
			const_iterator find(const Key& key)const{
				return const_iterator(this->search(getRoot(), key));
			}

			size_type count(const Key& key){
				// if found key returns 1, else 0
				// uses IsPhony
				(void)key;
				return 0;
			}
			
    };


}


#endif // MAP_H

