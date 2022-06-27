#include <iostream>

template <typename T>
struct vector {
	template <typename U>
		void push_back(const U&); // Declaring a template method of a template class
	template <typename U>
		void push_back_class_kw(const U&); // Declaring a template method of a template class
};

// Nested template

template <typename T>
template <typename U>
void	vector<T>::push_back(const U&){
	// ...;
}

// 'class' keyword brings no difference, semantics stays the same
template <class T>
template <class U>
void vector<T>::push_back_class_kw(const U&){
	// ...;
}

