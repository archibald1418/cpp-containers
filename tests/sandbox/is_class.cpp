#include <cstddef>

template <typename T>
struct is_class{
	private:
		template<typename C>
		static int f(int C::*p){return 0;}

		template <typename ...>
		static char f(...){return 0;}
	public:
	static const bool value = sizeof(f<T>(NULL) == sizeof(int));
};
