
#include <iostream>

struct true_type{
	static const bool value = true;
};

template <int a, int b>
struct divides{
	static const bool value = (a % b == 0);
};

class FizzBuzz{
	public:
		// FizzBuzz solvers
		template <bool A, bool B>
		struct fizzbuzz{};
		
		/*
		 * FIXME options:
		 * - const char*s -> char array/int array
		 * - fizzbuzz_type_traits with storing the type of value (for printing template)
		 * - empty string checks (crutch)
		 * - int as third argument of fizzbuzz template (also crutch)
		 * - some kind of sfinae magic for printing templates
		 * */

		template <>
		struct fizzbuzz<true, false>{
			static const char* value;
		};
		template <>
		struct fizzbuzz<false, false>{
			//static const bool value = false;
			static const char* value;
		};
		template <>
		struct fizzbuzz<false, true>{
			static const char* value;
		};
		template <>
		struct fizzbuzz<true, true>{
			static const char* value;
		};

		template <int a>
		struct is_divisible : public true_type{

			static const int divisor = a;
			
			struct by3 : public divides<a, 3>{};

			struct by5 : public divides<a, 5>{};
		};
};



template <int N, int M>
struct static_for{
	static void value(){
	std::cout << \
			FizzBuzz::fizzbuzz<  FizzBuzz::is_divisible<N>::by3::value, FizzBuzz::is_divisible<N>::by5::value>::value \
		<< std::endl;
		static_for<N + 1, M>::value();
	}
};

template <>
struct static_for<101, 100>
{
	static void value(){};
};


const char* FizzBuzz::fizzbuzz<true, false>::value = "fizz";
const char* FizzBuzz::fizzbuzz<false, true>::value = "buzz";
const char* FizzBuzz::fizzbuzz<true, true>::value = "fizzbuzz";
const char* FizzBuzz::fizzbuzz<false, false>::value = "---";


int main(){
	
	
		//std::cout << FizzBuzz::fizzbuzz<FizzBuzz::is_divisible<i>::by3::value, FizzBuzz::is_divisible<i>::by5::value>::value << std::endl;

	static_for<0, 100>::value();
}
