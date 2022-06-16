#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>
# include <cstddef>

namespace ft{

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
			typedef typename It::distance_type          distance_type;
			typedef typename It::pointer                pointer;
			typedef typename It::reference              reference;
		};

	// Define iterator in terms of type
	template <class T>
		struct iterator_traits<T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t distance_type;
			typedef T* pointer;
			typedef T& reference;
		};

	template <class T>
		struct iterator_traits<const T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t distance_type;
			typedef T* pointer;
			typedef T& reference;
		};
	
	template <class T>
		struct RAIterator
		{
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::distance_type			distance_type;
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
				RAIterator& operator+(distance_type diff) const{
					return RAIterator(_it + diff);
				}
				RAIterator& operator-(distance_type diff) const{
					return RAIterator(_it - diff);
				}
				distance_type operator-(RAIterator& other) const{
					return _it - other._it;
				}
				// Increment/Decrement
				RAIterator& operator++(){
					_it++; return *this;
				}
				RAIterator& operator--(){
					_it--; return *this;
				}
				RAIterator& operator++(int){
					RAIterator tmp(*this);
					_it++; return *tmp; 
				}
				RAIterator& operator--(int){
					RAIterator tmp(*this);
					_it--; return *tmp;
				}
				RAIterator& operator+=(distance_type n){
					this->_it += n; return *this;
				}
				RAIterator& operator-=(distance_type n){
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
				reference operator[](distance_type diff) const{
					return *(_it + diff);
				}
				reference operator*() const{
					return *_it;
				}
				pointer operator->() const{
					return _it;
				}
		};

		template <class T>
			// TODO: test this inheritance
			struct RARIterator : public RAIterator<T>
			{
				typedef typename iterator_traits<T*>::iterator_category		iterator_category;
				typedef typename iterator_traits<T*>::value_type			value_type;
				typedef typename iterator_traits<T*>::distance_type			distance_type;
				typedef typename iterator_traits<T*>::pointer				pointer;
				typedef typename iterator_traits<T*>::reference				reference;

				RARIterator& operator+(distance_type diff) const{
					return RARIterator(this->_it - diff);
				}
				RARIterator& operator-(distance_type diff) const{
					return RARIterator(this->_it + diff);
				}
				distance_type operator-(RARIterator& other) const{
					return this->_it + other._it;
				}
				// Increment/Decrement
				RARIterator& operator++(){
					this->_it--; return *this;
				}
				RARIterator& operator--(){
					this->_it++; return *this;
				}
				RARIterator& operator++(int){
					RARIterator tmp(*this);
					this->_it--; return *tmp; 
				}
				RARIterator& operator--(int){
					RARIterator tmp(*this);
					this->_it++; return *tmp;
				}
				RARIterator& operator+=(distance_type n){
					this->_it -= n; return *this;
				}
				RARIterator& operator-=(distance_type n){
					this->_it += n; return *this;
				}
				reference operator[](distance_type diff) const{
					return *(this->_it - diff);
				}
			};
};

#endif 
