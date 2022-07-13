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
			typedef typename ft::remove_const<T>::type	value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef const T*							pointer;
			typedef const T& 							reference;
		};

	template <class T>
		struct RAIterator : public iterator<random_access_iterator_tag, T>
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
				// RAIterator(const T it) : _it(it){};
				// RAIterator(const pointer it) : _it(it){};
				// RAIterator(const RAIterator &src) : _it(src._it){};
				template <typename Iter>
				RAIterator(const RAIterator<Iter>& src, 
				typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0) : _it(src.base()){};
				// RAIterator(const RAxrIterator<T>& src) : _it(src.base());
				// RAIterator(const RAIterator& src) : 
				// template <>
				// RAIterator<const pointer>(const RAIterator& src) : _it(src._it){};
				// RAIterator<const T*>(const RAIterator& src) : _it(src._it){};
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
				// RAIterator<const pointer>& operator=(const RAIterator& other)
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
					return tmp;
				}
				RAIterator operator--(int){
					RAIterator tmp(*this);
					_it--; return tmp;
				}
				virtual RAIterator& operator+=(difference_type n){
					this->_it += n; return *this;
				}
				virtual RAIterator& operator-=(difference_type n){
					this->_it -= n; return *this;
				}
				// // Comparisons
				// bool operator==(const RAIterator& other) const{
				// 	return _it == other._it;
				// }
				// bool operator!=(const RAIterator& other) const{
				// 	return _it != other._it;
				// }
				// bool operator<(const RAIterator& other) const{
				// 	return _it < other._it;
				// }
				// bool operator>(const RAIterator& other) const{
				// 	return _it > other._it;
				// }
				// bool operator<=(const RAIterator& other) const{
				// 	return _it <= other._it;
				// }
				// bool operator>=(const RAIterator& other) const{
				// 	return _it >= other._it;
				// }
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
	
				pointer base()const{
					return _it;
				}

		};

template <typename T, typename U>
inline bool 
operator==( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename T, typename U>
inline bool 
operator!=( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() != rhs.base();
}
template <typename T, typename U>
inline bool 
operator<( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() < rhs.base();
}
template <typename T, typename U>
inline bool 
operator>( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() > rhs.base();
}
template <typename T, typename U>
inline bool 
operator<=( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() <= rhs.base();
}
template <typename T, typename U>
inline bool 
operator>=( const RAIterator<T>& lhs, const RAIterator<U>& rhs) {
	return lhs.base() >= rhs.base();
}

template <typename T, typename U>
inline typename RAIterator<T>::difference_type 
operator-(const RAIterator<T>& lhs, const RAIterator<U>& rhs){
	return (lhs.base() - rhs.base());
}

template <typename T>
inline RAIterator<T>
operator+(typename RAIterator<T>::difference_type diff, const RAIterator<T>& lhs){
	return RAIterator<T>(lhs.base() + diff);
}

		template <class Iter>
			struct reverse_iterator : public iterator<typename Iter::iterator_category, typename Iter::value_type>
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
				reverse_iterator() : _it(iterator_type()){};
				explicit reverse_iterator(iterator_type it): _it(it){};
				reverse_iterator(const reverse_iterator &src) : _it(src._it){};
				// template <class Iterator>
				// 	reverse_iterator(const reverse_iterator<Iterator>& rev_it) : _it(rev_it._it){};
			// Dtor
				virtual ~reverse_iterator(){};

			// Arithmetic operators override
				reverse_iterator operator+(difference_type diff) const{
					return reverse_iterator(this->_it - diff);
				}
				reverse_iterator operator-(difference_type diff) const{
					return reverse_iterator(this->_it + diff);
				}
				reverse_iterator& operator=(const reverse_iterator& other){
					this->_it = other._it;
					return (*this);
				}

				reference operator*()const{
					iterator_type copy = _it;
					return (*--copy);
					/*
						NOTE: 
						reverse_iterator is an ADAPTER - it extends a source class (ADAPTEE) to behave differently
						(suiting certain needs that source class can't meet)
						Adapter adapts source class interface (RAIterator<T>) to meet new requirements (iterating backwards)
						without changing the source class (=without modifying the class)
						and without changing the contexts that source class is usually used in

						I guess,  operator* := *(copy - 1) is to use the original behaviour of the begin() and end() methods (without '- 1' add-on) 
					*/ 
				}
				pointer operator->()const{
					(&(operator*()));
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
					return (base()[-diff - 1]);
				}

				iterator_type base()const {
					return (this->_it);
				}
			};



// Reverse iterator non-members
// TODO: compile-time checks of
template <typename _It1, typename _It2>
inline bool 
operator==(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs){
	return lhs.base() == rhs.base();
}
template <typename _It1, typename _It2>
inline bool 
operator!=(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs) {
	return lhs.base() != rhs.base();
}
template <typename _It1, typename _It2>
inline bool 
operator<(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs) {
	return lhs.base() <	 rhs.base();
}
template <typename _It1, typename _It2>
inline bool 
operator>(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs) {
	return rhs.base() > lhs.base();
}
template <typename _It1, typename _It2>
inline bool 
operator<=(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs) {
	return rhs.base() < lhs.base();
}
template <typename _It1, typename _It2>
inline bool 
operator>=(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs) {
	return lhs.base() >= rhs.base();
}

template <typename _It1, typename _It2>
inline typename _It1::difference_type
operator-(const reverse_iterator<_It1>& lhs, const reverse_iterator<_It2>& rhs){
	return (rhs.base() - lhs.base());
}

template <typename _It>
inline reverse_iterator<_It>
operator+(typename reverse_iterator<_It>::difference_type diff, const reverse_iterator<_It>& lhs){
	return reverse_iterator<_It>(lhs.base() - diff);
}

template< class InputIt, class Distance >
inline void
advance( InputIt& it, Distance n, random_access_iterator_tag){
	// Avoids unnecessary copying
	if (n == 1)
		++it; 
	else if (n == -1)
		--it;
	else
		it += n; // Complexity is constant
}
template< class InputIt, class Distance >
inline void
advance( InputIt& it, Distance n, bidirectional_iterator_tag){
	if (n > 0){
		while (n--)
			++it;
	}
	else if (n < 0){
		while (n++)
			--it;
	}
	// Complexity is linear
}

template< class InputIt, class Distance >
inline void
advance( InputIt& it, Distance n){
	typename ft::iterator_traits<InputIt>::difference_type d = n;
	ft::advance(it, d, typename InputIt::iterator_category());
}

// TODO: advance, distance, front_inserter, back_inserter, inserter
// TODO: iterators: back_insert_iterator, front_insert_iterator, insert_iterator
// 	template< class InputIt >
// typename ft::iterator_traits<InputIt>::difference_type
//     distance(InputIt first, InputIt last){

// 	}

};

#endif 
