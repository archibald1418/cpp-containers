#include <iostream>

struct true_type{
	static const bool value = true;
};
struct false_type{
	static const bool value = false;
};

template <int a, int b>
struct divides{
	static const bool value = (a % b == 0);
};

		
template <typename T, int N>
struct fizzbuzz_traits{
	typedef T type;
	static const int value = N;
};

template <>
struct fizzbuzz_traits<char*, 0>{
	typedef char* type;
};


// FizzBuzz solvers

/*
 * FIXME options:
 * - const char*s -> char array/int array
 * - fizzbuzz_type_traits with storing the type of value (for printing template)
 * - empty string checks (crutch)
 * - int as third argument of fizzbuzz template (also crutch)
 * - some kind of sfinae magic for printing templates
 * */
template <bool A, bool B>
struct fizzbuzz{};


template <> struct fizzbuzz<true, false> : public fizzbuzz_traits<char*, 0> {
	static const char* value;
};
typedef fizzbuzz<true, false> fizz_type;
const char* fizz_type::value = "fizz";

template <> struct fizzbuzz<true, true> : public fizzbuzz_traits<char*, 0> {
	static const char* value;
};
typedef fizzbuzz<true, true> fizzbuzz_type;
const char *fizzbuzz_type::value = "fizzbuzz";

template <> struct fizzbuzz<false, true> : public fizzbuzz_traits<char*, 0> {
	static const char* value;
};

typedef fizzbuzz<false, true> buzz_type;
const char *buzz_type::value = "buzz";

template <>
struct fizzbuzz<false, false> : public false_type{};


template <bool B, typename T, typename U>
struct conditional{
	typedef T type;
};

template <typename T, typename U>
struct conditional<false, T, U>{
	typedef U type;
};

template <typename T, typename U>
struct is_same : public false_type{};

template <typename T>
struct is_same<T, T> : public true_type{};

template <int N>
class FizzBuzz{
	struct is_divisible : public true_type{

		struct by3 : public divides<N, 3>{};

		struct by5 : public divides<N, 5>{};
	};


	public: 
		typedef fizzbuzz< is_divisible::by3::value, is_divisible::by5::value > solution_type; 
		// stores string or 'false'
		
		typedef fizzbuzz_traits<int, N> non_divisible_type; 
		// stores number in question
		typedef typename conditional< is_same<bool, typename solution_type::type>::value,\
			solution_type, \
			non_divisible_type>::type print_type;
};



int main(){
};

