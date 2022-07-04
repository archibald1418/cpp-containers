#ifndef TEMPLATES_H
# define TEMPLATES_H
# include <cwctype>

namespace ft {

    struct true_type{
        static const bool value = true;
    };
    struct false_type{
        static const bool value = false;
    };

template <typename T>
struct is_const : public ft::false_type{};

template<typename T>
struct is_const<const T> : public ft::true_type{};

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
template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};



};

#endif