#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>
# include <cstddef>

namespace ft{

	
template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1 != last1)
  {
    if (first2 == last2 || (*first2) < (*first1))
		return false;
    else if (*first1 < *first2)
		return true;
    ++first1; 
	++first2;
  }
  return (first2 != last2);
};

template <typename T>
struct is_const{
	static const bool value = false;
	};

template<typename T>
struct is_const<const T>{
	static const bool value = true;
	};

template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T>{
	typedef T type;
};

template <class T, T v> struct integral_constant
{
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T,v> type;
  operator T() const { return v; }
};

template <class T> struct is_integral				: public ft::integral_constant<bool, false> {};
template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char32_t>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};


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
			typedef typename It::difference_type          difference_type;
			typedef typename It::pointer                pointer;
			typedef typename It::reference              reference;
		};

	// Define iterator in terms of type
	template <class T>
		struct iterator_traits<T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
		};

	template <class T>
		struct iterator_traits<const T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
		};
	
	// Constructing via iterator class template
	// class MyIterator : public iterator<class T, class std::random_access_iterator_tag>{
		
	// };

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
				// Increment/Decrement
				RAIterator& operator++(){
					_it++; return *this;
				}
				RAIterator& operator--(){
					_it--; return *this;
				}
				RAIterator operator++(int){
					RAIterator tmp(*this);
					_it++; 
					return *tmp;  // NOTE: STL reference recommends converting to const reference
				}
				RAIterator operator--(int){
					RAIterator tmp(*this);
					_it--; return *tmp;
				}
				RAIterator& operator+=(difference_type n){
					this->_it += n; return *this;
				}
				RAIterator& operator-=(difference_type n){
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
		};

		template <class T>
			struct RARIterator : public RAIterator<T>
			{
				typedef typename iterator_traits<T*>::iterator_category		iterator_category;
				typedef typename iterator_traits<T*>::value_type			value_type;
				typedef typename iterator_traits<T*>::difference_type			difference_type;
				typedef typename iterator_traits<T*>::pointer				pointer;
				typedef typename iterator_traits<T*>::reference				reference;
			// Ctors
				RARIterator(): RAIterator<T>(){};
				RARIterator(pointer it): RAIterator<T>(it){};
				RARIterator(const RARIterator &src) : RAIterator<T>(src){};
			// Dtor
				virtual ~RARIterator(){};

			// Arithmetic operators overload
				RARIterator operator+(difference_type diff) const{
					return RARIterator(this->_it - diff);
				}
				RARIterator operator-(difference_type diff) const{
					return RARIterator(this->_it + diff);
				}
				difference_type operator-(RARIterator& other) const{
					return this->_it + other._it;
				}
				// Increment/Decrement
				RARIterator& operator++(){
					this->_it--; return *this;
				}
				RARIterator& operator--(){
					this->_it++; return *this;
				}
				RARIterator operator++(int){
					RARIterator tmp(*this);
					this->_it--; return *tmp; 
				}
				RARIterator operator--(int){
					RARIterator tmp(*this);
					this->_it++; return *tmp;
				}
				RARIterator& operator+=(difference_type n){
					this->_it -= n; return *this;
				}
				RARIterator& operator-=(difference_type n){
					this->_it += n; return *this;
				}
				reference operator[](difference_type diff) const{
					return *(this->_it - diff);
				}
			};
};

#endif 
