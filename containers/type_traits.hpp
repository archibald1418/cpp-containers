#ifndef TYPE_TRAITS_H
# define TYPE_TRAITS_H

# include <cwctype>

namespace ft {

    struct true_type{
        static const bool value = true;
    };
    struct false_type{
        static const bool value = false;
    };
	
	template <bool>
	struct boolean : public true_type{};
	template <>
	struct boolean<false> : public false_type{};

template <typename T>
struct is_const : public false_type{};

template<typename T>
struct is_const<const T> : public true_type{};

template <typename T, typename U>
struct is_same: public false_type{};
template <typename T>
struct is_same<T, T> : public true_type{};

template <typename T>
struct remove_const{typedef T type;};
template <typename T>
struct remove_const<const T>{typedef T type;};

template <typename T>
struct add_const{typedef const T type;};

template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T>{
	typedef T type;
};

template <bool B, class _If, class _Then>
struct conditional{
	typedef _Then type;
};

template <class _If, class _Then>
struct conditional<true, _If, _Then>{
	typedef _If type;
};

template <typename T, typename U, typename V>
struct is_one_of{
    typedef typename conditional<is_same<T, U>::value, U, V>::type type;
};


template <class T, T v>
struct integral_constant
{
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T,v> type;
  operator T() const { return v; }
};

template <class T> struct is_integral				: public ft::integral_constant<bool, false> {};
template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
// template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
// template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {}; // long long is a C++11 extension

template <typename T>
struct remove_pointer{typedef T type;};
template <typename T>
struct remove_pointer<T*>{typedef T type;};

template <typename T, typename D = void>
struct is_pointer : public false_type{};
template <typename T>
struct is_pointer<
    T, 
    typename enable_if<!is_same<typename remove_pointer<T>::type, T>::value>::type>
    :
    public true_type{};

    
    // Tree related
    template <class NodePtr, class T>
        struct tree_node_types {
            typedef typename        remove_pointer<NodePtr>::type		node_type;
            typedef typename        remove_const<NodePtr>::type         nodeptr;
			typedef const nodeptr										const_nodeptr;
            typedef T                                                   node_value_type;
            typedef T*                                                  node_value_type_pointer; 
            typedef const T*                                           	const_node_value_type_pointer;
			typedef const T												const_node_value_type;
        /*
        NOTE: 
            stl here does some crpytic voidptr->valueptr pointer rebinds
            to keep compatibility with smart pointers 
        */
        };

	
	// -------------------- Map types ---------------
	
	template <bool b>
	struct is_multi : public boolean<b>{};
}

#endif // TYPE_TRAITS_H

