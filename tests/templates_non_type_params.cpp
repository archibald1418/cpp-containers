#include <iostream>
#include <ratio>

// Non-type template parameters


// Type parameter
template <typename T>
struct S {

};

// Non-type parameter
template <int N>
struct Sn {
	Sn(){		
		std::cout << "I am " << N << " template parameter struct\n";
	};
};

template <typename T, size_t N>
struct array {
	array()	{
		std::cout << "Array of size " << N << " created" << std::endl;
	}
};

// Matrix class
template <size_t M, size_t N, typename Field>
struct Matrix {
// public visibility by default
};

// Operator*
template <size_t M, size_t N, size_t K, typename Field>
Matrix<M, K, Field> operator*(const Matrix<M, N, Field>, const Matrix<N, K, Field>);

int main(){
	S<int> s;
	
	Sn<3> sn;
	Sn<5> sn2;
	
	array<int, 5> array_five;
	array<int, -1> array_overflow;
}
