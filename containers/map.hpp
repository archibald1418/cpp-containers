#ifndef MAP_H
# define MAP_H

# include "functional.hpp"
# include "utility.hpp"
# include "node.hpp"
# include "tree.hpp"
# include "type_traits.hpp"
# include "tree_iterator.hpp"
# include <memory>
# include <limits>

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
    /* class map : protected BaseTree<map_traits<Key, T, Compare, Alloc, false> > */
    class map : public BaseTree<map_traits<Key, T, Compare, Alloc, false> >
    {
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
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			typedef pair<iterator, bool>				pair_ib;
			typedef pair<iterator, iterator>			pair_ii;
			typedef pair<const_iterator, bool>			pair_cb;
			typedef pair<const_iterator, const_iterator>		pair_cc;

		private:
			const Key& getKeyByVal(const value_type& node)const{
				return node.first;
			}


		public:
			explicit map(const key_compare& comp = key_compare())
			:
			__base(comp){}

			template< class InputIt >
			map(InputIt first, InputIt last,
				const Compare& comp = Compare(),
				const Alloc& alloc = Alloc() )
			: __base(comp, alloc){
				for (; first != last; ++first)
				{
					this->insert(*first);
				}
			}

			map(const map& other) : __base(other.comp, other._alloc){
				this->insert(other.begin(), other.end());
			}
			map& operator=(const map& other){
				if (*this == &other)
					return *this;
				clear();
				this->insert(other.begin(), other.end());
				return *this;
			}

			virtual ~map(){
				//std::cout << "Destroying map" << std::endl;
			}

			void	clear(){
				if (!empty())
					erase(begin(), end());
			}

			allocator_type get_allocator(){
				return allocator_type();
			}

			iterator begin(){
				return iterator(this->Lmost());
			} const_iterator begin()const{
				return const_iterator(this->lmost);
			}

			reverse_iterator rbegin(){
				return reverse_iterator(this->Rbegin()); // operator-- gives rmost
			} const_reverse_iterator rbegin()const{
				return const_reverse_iterator(this->Rbegin()); 
			}

			iterator end(){
				return iterator(this->End());
			} const_iterator end()const{
				return const_iterator(this->n_rbegin);
			}

			// DEBUG: Rend node symmetric to End
			reverse_iterator rend(){
				return reverse_iterator(begin());
			} const_reverse_iterator rend()const{
				return const_reverse_iterator(begin());
			}

			bool empty()const{
				return this->empty();
			}

			size_type size()const{
				return this->_size;
			}
			size_type max_size()const{
			return	ft::min<size_type>(
				this->_alloc.max_size(),
				std::numeric_limits<difference_type>::max());
			}

			// Find & count search values by key
			// Insert & Delete search by node, it's ok
			iterator find(const Key& key)
			{
				nodeptr begin = getRoot(); // starting from root gives logN complexity
				while (!IsPhony(begin)){
					const key_type& other = getKeyByVal(begin->Get());
					if (other == key)
						return iterator(begin);
					if (other > key)
						begin = begin->Left();
					else
						begin = begin->Right();
				}
				return end();
			}
			const_iterator find(const Key& key)const{
				nodeptr begin = getRoot();
				while (!IsPhony(begin)){
					const key_type& other = getKeyByVal(begin->Get());
					if (other == key)
						return const_iterator(begin);
					if (other > key)
						begin = begin->Left();
					else
						begin = begin->Right();
				}
				return end();
			}

			size_type count(const Key& key){
				if (find(key) != end())
						return 1;
				return 0;
			}

			pair<iterator, bool> insert(const value_type& value){
				
				iterator found = find(value.first);
				if (found != end())
					return pair<iterator, bool>(iterator(found), false);
				return pair<iterator, bool>(this->Insert(value), true);
			}
			template<typename InputIt>
			void	insert(InputIt first, InputIt last){
				for (; first != last; ++first){
					insert(*first);
				}
			}

			iterator erase(iterator pos){
				this->Delete(*pos);
				return iterator(pos); // compare outputs
			}
			size_type erase(const Key& key){
				iterator found = find(key);
				bool flag = (found != end());
				if (flag)
					erase(found);
				return static_cast<size_type>(flag);
				// returns 0 or 1
			}
			iterator erase(iterator first, iterator last){
				for(; first != last; ++first){
					erase(first);
				}
				return last;
			}
			

			nodeptr getRoot()const{
				return this->root;
			}

			/*
			 *TODO: lower bound, upper bound, swap
			 * */
			pair_ii equal_range(const Key& key)
			{
				iterator tmp = this->find(key);
				if (tmp == end())
					return pair_ii(end(), end());
				iterator found(tmp++);
				if (tmp == end())
					return pair_ii(found, end());
				if (found == begin())
					return pair_ii(end(), found);
				return pair_ii(found, tmp);
			}

			pair_cc equal_range(const Key& key)const
			{
				const_iterator found = this->find(key);
				const const_iterator& cend = const_iterator(end());
				const const_iterator& cbegin = const_iterator(begin());

				if (found == cend)
					return pair_cc(cend, cend);
				const const_iterator& next = ++found;
				if (next == cend)
					return pair_cc(found, cend);
				if (found == const_iterator(cbegin))
					return pair_cc(cend, found);
			}

			iterator lower_bound(const Key& key){
				return find(key);
			}

			const_iterator lower_bound(const Key& key)const{
				return const_iterator(find(key));
			}

			iterator upper_bound(const Key& key){
				return equal_range(key).second;
			}

			const_iterator upper_bound(const Key& key)const{
				return const_iterator(equal_range(key).second);		
			}

			T& at(const Key& key){
				iterator found = find(key);
				if (found == end())
					throw std::out_of_range(
							std::string("map::at")
							);
				return found->second;
			}
			const T& at(const Key& key)const{
				const_iterator found = find(key);
				if (found == end())
					throw std::out_of_range(
							std::string("map::at")
							);
				return found->second;
			}

			T& operator[](const Key& key){
				iterator found = find(key);
				if (found == end())
					return insert(make_pair(key, T())).first->second;
				return found->second;
			}

			void swap(map& other){

				this->swap_tree(other);
				size_type tmp = size();
				this->_size = other._size;
				other._size = tmp;
			}
    };

				
    // Non-member comparison operators

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(
			const map<Key, T, Compare, Alloc> &lhs,
			const map<Key, T, Compare, Alloc> &rhs)
    {
        if (rhs.size() != lhs.size())
            return false;

		typedef typename map<Key, T, Compare, Alloc>::const_iterator It;
		
		It lhs_it = lhs.begin();
		It rhs_it = rhs.begin();
		while (lhs_it != lhs.end())
		{
			if (lhs_it->first != rhs_it->first)
				return false;
			++lhs_it;
			++rhs_it;
		}
        return true;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(
			const map<Key, T, Compare, Alloc>& lhs,
			const map<Key, T, Compare, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(
			const map<Key, T, Compare, Alloc> &lhs,
			const map<Key, T, Compare, Alloc> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(
			const map<Key, T, Compare, Alloc> &lhs,
			const map<Key, T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(
			const map<Key, T, Compare, Alloc> &lhs,
			const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(
			const map<Key, T, Compare, Alloc> &lhs,
			const map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }


}


#endif // MAP_H

