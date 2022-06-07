#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

#ifdef MY
# define MY 1
# include "ft_containers.hpp"
  using ft::vector;
#endif

#ifndef MY
# define MY 0
  using std::vector;
#endif

typedef struct test {
  int a;
  char b;
  std::string c;

  test(int a, char b, std::string &c) : a(a), b(b), c(c)
  {};
  test() : a(1), b('1'), c(std::string("1")){};
  test(const struct test& other){
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
  }

  friend std::ostream& operator<<(std::ostream& os, const struct test& t)
  {
      (void)t;
      os << "{a: " << t.a \
        << ", b: " << '\'' << t.b << '\'' \
          << ", c: \"" << t.c << "\"}" << std::endl;
      return (os);
  }
  
  struct test& operator++(int){
    this->a++;
    this->b++;
    this->c = std::string(std::to_string(this->b));
    return (*this);
  } 

} my_class;


const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")
};


template <typename V>
void  test_vector(V &v){
    int i = 0;
    // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
    std::cout << "size" << "\t" << "cap" << "\t" << "elem" << std::endl;
    for (; i < 10; ++i)
    {
        v.push_back(i);
        std::cout <<  v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
    }
    v.size();
    v.capacity(); // cap *= 2, if newer elem.size overflows capacity
}



template <typename V>
void test_vector_custom_type(V &v){

  my_class my_obj;

  int i = 0;
  std::cout << "size" << "\t" << "cap" << "\t" << "elem" << std::endl;
  for (; i < 10; ++i){
    v.push_back(my_obj);
    std::cout <<  v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
    my_obj++;
  }
}

int main(){
    std::cout << "TESTING " << vector_types[MY] << std::endl;

    // vector<int> vzero; //
    my_class my_object;

    vector<int> vnonzero(5);
    vector<my_class> vmyclass(5);

    // test_vector(vzero);
    // test_vector(vnonzero);
    test_vector_custom_type(vmyclass);


};
