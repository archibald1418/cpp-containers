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
	template<class T,
			class C = std::random_access_iterator_tag,
			class Dist = std::ptrdiff_t,
			class Pt = T*,
			class Rt = T&>
		struct iterator {
			// Type defenitions for addressing and manipulating allocated objects
			typedef C iterator_category;
			typedef T value_type;
			typedef Dist difference_type;
			typedef Pt pointer;
			typedef Rt reference;
		};

	// Copy iterator template
	template<class It> 
		struct iterator_traits {
			typedef typename It::iterator_category      iterator_category;
			typedef typename It::value_type             value_type;
			typedef typename It::difference_type		difference_type;
			typedef typename It::pointer                pointer;
			typedef typename It::reference              reference;
			typedef typename iterator_concept			It::iterator_category;
		};

	// Define iterator in terms of type
	template <class T>
		struct iterator_traits<T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename ft::remove_const<T> value_type; // stl source removes const altogether - they create const_iterator later
			typedef ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
		};

	// template <class T>
	// 	struct iterator_traits<const T*>{
	// 		typedef std::random_access_iterator_tag iterator_category;
	// 		typedef T value_type;
	// 		typedef ptrdiff_t difference_type;
	// 		typedef T* pointer;
	// 		typedef T& reference;
	// 	};
	
	// Constructing via iterator class template
	// class MyIterator : public iterator<class T, class std::random_access_iterator_tag>{
		
	// };


	template <class T>
	struct input_iterator : public iterator<T, input_iterator_tag> {
		typedef __base iterator<T, input_iterator_tag>;
		
		typedef typename iterator_traits<__base>::iterator_category		iterator_category;
		typedef typename iterator_traits<__base>::value_type			value_type;
		typedef typename iterator_traits<__base>::difference_type		difference_type;
		typedef typename iterator_traits<__base>::pointer				pointer;
		typedef typename iterator_traits<__base>::reference				reference;

		protected:
			pointer _it;
		
		virtual bool operator!=(const input_iterator& other) const{
					return _it != other._it;
				}
		
		virtual bool operator==(const input_iterator& other) const{
				return _it == other._it;
			}
		
		virtual reference operator*() const{
					return *_it;
				}
		virtual pointer operator->() const{
					return _it;
				}
		virtual reference& operator++(){
					this->_it++; return *this;
				}
		virtual void operator++(int){
					input_iterator tmp(*this);
					_it++; 
					return *tmp;  // NOTE: STL reference recommends converting to const reference
				}
	};


	template <class T>
		struct RAIterator
		{
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::reference				reference;

			protected:
				pointer _it;
			
			public:
			// Ctors
				RAIterator(): _it(0){};
				RAIterator(pointer it) : _it(it){};
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
				virtual RAIterator operator+(difference_type diff)const{
					return RAIterator(_it + diff);
				}
				virtual RAIterator operator-(difference_type diff)const{
					return RAIterator(_it - diff);
				} /* 
					+- return new object, so it can't be a constant reference
						Since returned object can't be const
							(because it  could be changed later)
						ret by ref won't work
					*/
				virtual difference_type operator-(RAIterator& other) const{
					return _it - other._it;
				}
				// Increment/Decrement
				virtual RAIterator& operator++(){
					_it++; return *this;
				}
				virtual RAIterator& operator--(){
					_it--; return *this;
				}
				virtual RAIterator operator++(int){
					RAIterator tmp(*this);
					_it++; 
					return *tmp;  // NOTE: STL reference recommends converting to const reference
				}
				virtual RAIterator operator--(int){
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
				virtual reference operator[](difference_type diff) const{
					return *(_it + diff);
				}
				reference operator*() const{
					return *_it;
				}
				pointer operator->() const{
					return _it;
				}
		};

		template <class Iter>
			struct reverse_iterator : public RAItererator< iterator_traits<Iter>::value_type >
			{
				/*
					Member type
					iterator_concept	
					If Iter models std::random_access_iterator, this is std::random_access_iterator_tag. 
					Otherwise, this is std::bidirectional_iterator_tag
				*/
				typedef Iter iterator_type;
				typedef typename iterator_type::iterator_category	iterator_category;
				typedef typename iterator_type::value_type			value_type;
				typedef typename iterator_type::difference_type		difference_type;
				typedef typename iterator_type::pointer				pointer;
				typedef typename iterator_type::reference			reference;

				typedef 
			// Ctors
				reverse_iterator(): RAItererator<value_type>(){};
				reverse_iterator(pointer it): RAItererator<value_type>(it){};
				reverse_iterator(const reverse_iterator &src) : RAItererator<value_type>(src){};
			// Dtor
				virtual ~reverse_iterator(){};

			// Arithmetic operators overload
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
			};


// 	template< class InputIt >
// typename ft::iterator_traits<InputIt>::difference_type
//     distance(InputIt first, InputIt last){

// 	}

};

#endif 
