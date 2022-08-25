#include <iostream>
#include <memory>


struct my_t{
	typedef std::allocator<my_t> alloc;
	alloc _alloc;

	my_t* p;
	int n;
	
	my_t() : _alloc(alloc()), n(0){
		p = _alloc.allocate(1);
	};
	my_t& operator=(const int& o){
		n = o; return *this;
	}
	~my_t(){
		// _alloc.destroy(p);
		_alloc.deallocate(p, 1);
	};
	my_t operator++(){
		n += 5; return *this;
	}
	my_t operator--(){
		n += 5; return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const struct my_t& t){
		os << "my_t: {n:" << t.n << "}" << std::endl; return os;
	}
};


template <typename T>
struct A {
	
	typedef std::allocator<T> alloc;

	T a;
	T *pa;
	alloc _alloc;

	A() : a(T()), _alloc(alloc()){
		pa = _alloc.allocate(1);
		_alloc.construct(pa, T());
		std::cout << "pa = " << *pa << std::endl;
		std::cout << "a = " << a << std::endl;
	};
	virtual void lol(){
		std::cout << "lol" << std::endl;
	}
	virtual T& Get(){
		std::cout << a << std::endl;
		std::cout << *pa << std::endl;
		return a;
	}
	virtual void set(){
		++a;
		--*pa;
	}

	virtual ~A(){
		_alloc.destroy(pa);
		_alloc.deallocate(pa, 1);
	};
};


struct B : public A<my_t>{
	B(){
		a = 666;	
	}
};

int main(){
	typedef A<my_t> A;
	// typedef B<my_t> B;

	A a = A();
	B b = B();
	
	A *pa = &a;
	B *pb = &b;
	
	a.lol();
	b.lol();

	b.set();
	b.Get();

	pa->lol();
	pb->lol();

	a.Get();
	b.Get();
}
