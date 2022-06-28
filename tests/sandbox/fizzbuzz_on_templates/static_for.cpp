#include <iostream>

template <int n>
struct is_one{
	static const bool value = n == 1;
};


template <int n, bool is_neg>
struct absolute{
	static const int value = n;
};

template <int n>
struct absolute<n, true>{
	static const int value = -n;
};

template <int start, int end, int direction, bool error>
struct static_for{
	static void value(){
		std::cout << "Some error occured" << std::endl;
		//std::cout << start << end << direction << error;
	};
};

template <int start, int end, int direction>
struct static_for<start, end, direction, false>{
	static void value(){
		static_for<start + direction, end, direction, false>::value();
		std::cout << start <<  std::endl;	
	};
};


template <int N, int M>
struct static_for<N, N, M, false>{
	static void value(){
		std::cout << N << std::endl;
	};
};

int main(){	
	const int start = 5;
	const int end = 0;
	const int dir = -1;
	
	static_for<start, \
		end,\
		dir,\
		!is_one< absolute< dir, dir<0 >::value >::value>::value();
}
