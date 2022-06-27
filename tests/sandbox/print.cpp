#include <iostream>

struct string_type{
	static const char* value;
};

template <bool A, bool B>
struct fizzbuzz : public string_type{};

template <>
struct fizzbuzz<true, false> : public string_type{

	static const char* value;
};
template <>
struct fizzbuzz<false, false> : public string_type{

	static const char* value;
};
template <>
struct fizzbuzz<false, true> : public string_type{

	static const char* value;
};
template <>
struct fizzbuzz<true, true> : public string_type{

	static const char* value;
};

typedef fizzbuzz<true, false> Fizz;
typedef fizzbuzz<false, true> Buzz;
typedef fizzbuzz<true, true> FizzBuzz;

const char* Fizz::value = "fizz";
const char* Buzz::value = "buzz";
const char* FizzBuzz::value = "fizzbuzz";
const char* fizzbuzz<false, false>::value = "";

int main()
{

	std::cout << Fizz::value << std::endl;
	std::cout << Buzz::value << std::endl;
	std::cout << FizzBuzz::value << std::endl;
	std::cout << fizzbuzz<false, false>::value << std::endl;
}

