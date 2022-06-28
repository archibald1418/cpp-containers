#include <iostream>
#include <vector>

struct Shape{
	virtual Shape* Clone() = 0;
	virtual ~Shape(){};
};

template <typename T>
struct ShapeCRTP : public Shape {

	virtual Shape* Clone() {
		return new T(*static_cast<T*>(this));
	};	
};

// "Curiously Recurring Template Pattern"
struct Square : public ShapeCRTP<Square>{
	static const int x = 1;
};

struct Circle : public ShapeCRTP<Circle>{
	static const int x = 1;
};

int main(){
	typedef std::vector<Shape*> V;
	V v;
	
	
	v.push_back(new Square);
	v.push_back(new Circle);

	for (V::iterator it = v.begin(); it != v.end(); ++it){
		Shape *c = (*it)->Clone();
		int i = 0;	
	};
		
}
