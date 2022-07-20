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

	// Explicitly parametric iterator 
	template<
			class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
		struct iterator 
		{
			// Type defenitions for addressing and manipulating allocated objects
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
		};

	// Copy iterator template (traits class)
	template<class It> 
		struct iterator_traits
		{
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

			protected:
				pointer _it;
			
			public:
			// Ctors
				RAIterator(): _it(0){};
				RAIterator(pointer it) : _it(it){};
				template <typename Iter>
				RAIterator(const RAIterator<Iter>& src, 
				typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0) : _it(src.base()){};

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
				} 
				/* 
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

				// Base method - for tag-agnostic operations
				pointer base()const{
					return _it;
				}

		};


	template <class Container>
		struct insert_iterator : public iterator< output_iterator_tag,
											void,void,void,void >
		{
			typedef typename Container::iterator iterator;

			protected:
				Container* container;
				iterator iter;
				
			
			public:
				insert_iterator(Container& c, typename Container::iterator i) : container(&c), iter(i){};
				insert_iterator& operator=(const typename Container::const_reference value)
				{	
					iter = 	container->insert(iter, value);
					++iter;
					return *this;
				}
				insert_iterator& operator*(){return *this;}; 
				// placeholder for output iterator reqs
				// also calls operator= when doing '*iter = value'
				insert_iterator& operator++(){return *this;};
				insert_iterator& operator++(int){return *this;}; // same
		};
		

	template< class Container >
		struct back_insert_iterator : public iterator< output_iterator_tag,
													void, void, void, void >
		{
			typedef typename Container::iterator iterator;

			protected:
				Container* container;

			public:
				explicit back_insert_iterator(Container& c) : container(&c){};
				back_insert_iterator& operator=(const typename Container::const_reference value){
					container->push_back(value);
					return (*this);
				}
				back_insert_iterator& operator*(){return *this;};
				back_insert_iterator& operator++(){return *this;};
				back_insert_iterator& operator++(int){return *this;};
		};


	template <class Container>
		struct front_insert_iterator : public iterator< output_iterator_tag,
													void, void, void, void >
		{
			typedef typename Container::iterator iterator;

			protected:
				Container* container;
			
			public:
				explicit front_insert_iterator(Container& c) : container(&c){};
				front_insert_iterator<Container>& operator=(typename Container::const_reference value){
					container->push_front(value);
					return (*this);
				}
				front_insert_iterator& operator*(){return *this;};
				front_insert_iterator& operator++(){return *this;};
				front_insert_iterator& operator++(int){return *this;};
		};



// ------------------------------- Inserter functions
template< class Container >
insert_iterator<Container> inserter(Container& c, typename Container::iterator i)
{
    return insert_iterator<Container>(c, i);
}

template< class Container >
back_insert_iterator<Container> back_inserter( Container& c )
{
	return back_insert_iterator<Container>(c);
}
		
template< class Container >
front_insert_iterator<Container> front_inserter( Container& c )
{
	return front_insert_iterator<Container>(c);
}


// ------------------------------ Iterator non-member operators
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



// Reverse iterator adapter

	template <class Iter>
		struct reverse_iterator : public iterator<typename Iter::iterator_category, typename Iter::value_type>
		{
			typedef Iter iterator_type; // base iterator type
			typedef typename iterator_type::iterator_category	iterator_category;
			typedef typename iterator_type::value_type			value_type;
			typedef typename iterator_type::difference_type		difference_type;
			typedef typename iterator_type::pointer				pointer;
			typedef typename iterator_type::reference			reference;

		private:
			iterator_type _it;

		public:
		// Ctors
			reverse_iterator() : _it(iterator_type()){};
			explicit reverse_iterator(iterator_type it): _it(it){};
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

					I guess,  operator* := *(copy - 1) is to use the original behaviour of the begin() and end() methods 
					(without writing '- 1' add-on, which is error-prone) 
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


// ------------------------------------------------------- Iterator universal non-member functions
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
			--it; // Complexity is linear
	}
}

template< class InputIt, class Distance >
inline void
advance( InputIt& it, Distance n){
	typename ft::iterator_traits<InputIt>::difference_type d = n;
	ft::advance(it, d, 
				typename InputIt::iterator_category());
}

template <class InputIt>
inline typename InputIt::difference_type
distance (InputIt& first, InputIt& last, input_iterator_tag){
	typename iterator_traits<InputIt>::difference_type n = 0;
	while (first != last)
	{
		++first;
		++n;
	}		
	return n;
}

template <class RAIter>
inline typename RAIter::difference_type
distance (RAIter& first, RAIter& last, random_access_iterator_tag){
	return (last - first);
}

template <class InputIt>
inline typename iterator_traits<InputIt>::difference_type
distance (InputIt& first, InputIt& last){
	return distance(first, last, 
					typename InputIt::iterator_category());
}




};

#endif 
