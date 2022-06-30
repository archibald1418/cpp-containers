#include <iostream>

// Template functions overloading

template <typename T>
void f(T x, T y){
	// 2. This gets called.
	// 					no type casting > type casting						
	std::cout << "I am same-typed template function\n";
};

void f(int x){
	// 1. This gets called
	// 						Special case > General case
	std::cout << "I am int function\n";
};

template <typename T>
void f(T x){
	std::cout << "I am single argument template function\n";
}


template <typename T, typename U>
void f(T x, U y){
	std::cout << "I am two-typed template function\n";
}

void f(int x, double y){
	std::cout << "I am two-typed int + double function\n";
}

void fo(const int& z)
{
	std::cout << "I am const int ref function\n";
}

void fo(int& z)
{
	std::cout << "I am int ref function\n";
}

int main()
{
	// 1
	f(0); // (int) vs (T)
	// number of arguments fit
	// int is more specific than T

	// 2
	f(0, 0); // (int, double) vs (T, T) vs (T, U)
	// (T, T) needs no type casting (0 -> 0.0 is redundant)
	
	// 3
	f(0, 0.0); // (int, double) vs (T, T) vs (T, U) 
	// (int, double) is more specific and fit the types
	
	// 4
	f(0.0, 0); // (int, double) vs (T, T) vs (T, U) 
	// (T, U) needs no casting
	

	// 5
	// non-const ref > const ref

	
	// 6
	// pass by value > pass by ref
}
