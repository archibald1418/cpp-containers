#include <iostream>

// 6.3 Template specialization
//


// Simple template (general version)
template <typename T>
class vector {

};

// full (explicit) specialization
template <> // No template parameters because we have defaults
class vector<bool> {
	// BOOL-typed vectors work differently than other-typed vectors
};

template <typename T>
struct S {
	void f(){
		std::cout << "I am just a simple template struct\n";
	}
};

template <>
struct S<int> { // for int-structs f is defined as this
	void f(){
		std::cout << "I am some int template struct\n";
	}
};

// NOTE: You can't write specialization without general tempalte (compile error)


// partial specialization
// For pointers
template <typename T>
struct S<T*> { // for pointer-structs f is defined as this
	void f(){
		std::cout << "I am some pointer template struct\n";
	}
};
// For refs
template <typename T>
struct S<T&> { // for type-ref-structs f is defined as this
	void f(){
		std::cout << "I am some ref template struct\n";
	}
};
// For arrays
template <typename T>
struct S<T[]> { // for type-array-structs f is defined as this
	void f(){
		std::cout << "I am some array template struct\n";
	}
};
// (=>for complex types)


// partial specialization for several types requires some sugar magic, so use copypaste for now


template <typename T>
void f(T x)
{
	std::cout << "I am one typed function\n";
}
template <>
void f(bool x)
{
	std::cout << "I am one typed bool-specialized function\n";
}




// Map declaration
template <typename Key, 
		 typename Value, 
		 typename Comparator=std::less<Key>, 
		 typename Allocator=std::allocator<std::pair<Key, Value> >  >
class myMap{

};

// Default template argument specification

// template <typename T, typename U = int> // default template args - is c+11
template <typename T, typename U>
void f(T x, U y = 10){
	std::cout << "I am two-typed function with default second argument int = 10";
}
template <typename, typename>
void f(bool x, int y = 10){
	std::cout << "I am two-typed function with default second argument int = 10";
}

int main()
{
	S<int> sInt; // Int-typed struct
	S<double> sT; // Generic-typed struct (not int, not ptr)
	S<int*> sPointer; // Ptr-typed struct

	// S.f gets overloaded differently
	sT.f();
	sInt.f();
	sPointer.f();
	
	f(true);
	f(4, 10);
	f(4); // It's ambiguous'
	f(5, 5);
}
