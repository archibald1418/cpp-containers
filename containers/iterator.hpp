#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>
# include <cstddef>
# include "type_traits.hpp"
# include "algorithm.hpp"

namespace ft{

// Iterator tags
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag : public input_iterator_tag{};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};


// NOTE: iterator can be output iterator if it's allowed to write to it!!!

	// Explicitly Parametric iterator
	template<
			class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
		struct iterator {
			// Type defenitions for addressing and manipulating allocated objects
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
		};

	// Copy iterator template
	template<class It> 
		struct iterator_traits {
			typedef typename It::iterator_category      iterator_category;
			typedef typename It::value_type             value_type;
			typedef typename It::difference_type		difference_type;
			typedef typename It::pointer                pointer;
			typedef typename It::reference              reference;
		};

	// Define iterator in terms of type
	template <class T>
		struct iterator_traits<T*>{
			typedef random_access_iterator_tag				iterator_category;
			typedef typename ft::remove_const<T>::type		value_type; // stl source removes const altogether - they create const_iterator later
			typedef std::ptrdiff_t						 	difference_type;
			typedef T* 										pointer;
			typedef T&										reference;
		};

	template <class T>
		struct iterator_traits<const T*>{
			typedef random_access_iterator_tag			iterator_category;
			typedef T									value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef const T*							pointer;
			typedef const T& 							reference;
		};

	template <class T>
		struct RAIterator : iterator<random_access_iterator_tag, T>
		{
			typedef typename iterator_traits<T>::iterator_category		iterator_category;
			typedef typename iterator_traits<T>::value_type				value_type;
			typedef typename iterator_traits<T>::difference_type		difference_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference				reference;
			// typedef typename const_pointer

			protected:
				pointer _it;
			
			public:
			// Ctors
				RAIterator(): _it(0){};
				RAIterator(pointer it) : _it(it){};
				// RAIterator(const pointer it) : _it(it){};
				RAIterator(const RAIterator &src) : _it(src._it){};
			// Dtor
				virtual ~RAIterator(){};
			// Operators
				// Arithmetic
				RAIterator& operator=(const RAIterator& other){
					if (this == &other)
						return *this;
					_it = other._it;
					return *this;
				}
				RAIterator operator+(difference_type diff)const{
					return RAIterator(_it + diff);
				}
				RAIterator operator-(difference_type diff)const{
					return RAIterator(_it - diff);
				} /* 
					+- return new object, so it can't be a constant reference
						Since returned object can't be const
							(because it  could be changed later)
						ret by ref won't work
					*/
				difference_type operator-(RAIterator& other) const{
					return _it - other._it;
				}
				/*
					'cls&', 'cls*' are covariant types for virtual functions, 'cls' is not
					overload: overwriting the parent method entirely
					override: choosing the child method instead of parent when constructing child (hence, virtual)
					NOTE: since c++11 'override' keyword is used explicitly 
				*/

				// Increment/Decrement
				virtual RAIterator& operator++(){
					_it++; return *this;
				}
				virtual RAIterator& operator--(){ 
					_it--; return *this;
				}
				RAIterator operator++(int){
					RAIterator tmp(*this);
					_it++; 
					return *tmp;
				}
				RAIterator operator--(int){
					RAIterator tmp(*this);
					_it--; return *tmp;
				}
				virtual RAIterator& operator+=(difference_type n){
					this->_it += n; return *this;
				}
				virtual RAIterator& operator-=(difference_type n){
					this->_it -= n; return *this;
				}
				// Comparisons
				bool operator==(const RAIterator& other) const{
					return _it == other._it;
				}
				bool operator!=(const RAIterator& other) const{
					return _it != other._it;
				}
				bool operator<(const RAIterator& other) const{
					return _it < other._it;
				}
				bool operator>(const RAIterator& other) const{
					return _it > other._it;
				}
				bool operator<=(const RAIterator& other) const{
					return _it <= other._it;
				}
				bool operator>=(const RAIterator& other) const{
					return _it >= other._it;
				}
				// Dereferencing
				reference operator[](difference_type diff) const{
					return *(_it + diff);
				}
				reference operator*() const{
					return *_it;
				}
				pointer operator->() const{
					return _it;
				}

				// pointer 
		};

		template <class Iter>
			struct reverse_iterator : public iterator<typename Iter::iterator_category, typename Iter::value_type> // Fixed inheritance
			{
				// typename reverse_iterator<Iter> reverse_iterator_t;

				typedef Iter iterator_type; // base iterator type
				typedef typename iterator_type::iterator_category	iterator_category;
				typedef typename iterator_type::value_type			value_type;
				typedef typename iterator_type::difference_type		difference_type;
				typedef typename iterator_type::pointer				pointer;
				typedef typename iterator_type::reference			reference;

			// Ctors
			private:
				iterator_type _it;

			public:
				reverse_iterator(): iterator_type(){};
				reverse_iterator(iterator_type it): _it(it){};
				reverse_iterator(const reverse_iterator &src) : _it(src._it){};
			// Dtor
				virtual ~reverse_iterator(){};

			// Arithmetic operators override
				reverse_iterator operator+(difference_type diff) const{
					return reverse_iterator(this->_it - diff);
				}
				reverse_iterator operator-(difference_type diff) const{
					return reverse_iterator(this->_it + diff);
				}
				difference_type operator-(reverse_iterator& other) const{
					return this->_it + other._it;
				}
				// Increment/Decrement
				reverse_iterator& operator++(){
					this->_it--; return *this;
				}
				reverse_iterator& operator--(){
					this->_it++; return *this;
				}
				reverse_iterator operator++(int){
					reverse_iterator tmp(*this);
					this->_it--; return *tmp; 
				}
				reverse_iterator operator--(int){
					reverse_iterator tmp(*this);
					this->_it++; return *tmp;
				}
				reverse_iterator& operator+=(difference_type n){
					this->_it -= n; return *this;
				}
				reverse_iterator& operator-=(difference_type n){
					this->_it += n; return *this;
				}
				reference operator[](difference_type diff) const{
					return *(this->_it - diff);
				}

				iterator_type base()const {
					return (this->_it);
				}
			};




// TODO: advance, distance, front_inserter, back_inserter, inserter
// TODO: iterators: back_insert_iterator, front_insert_iterator, insert_iterator
// 	template< class InputIt >
// typename ft::iterator_traits<InputIt>::difference_type
//     distance(InputIt first, InputIt last){

// 	}

};

#endif 
