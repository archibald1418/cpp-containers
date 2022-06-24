#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include "tests.hpp"
#include <assert.h>
#include <stack>
#include "ft_containers.hpp"

#ifdef MY
#define MY 1
#include "ft_containers.hpp"
using ft::vector;
#endif

#ifndef MY
#define MY 0
using std::vector;
#endif


// template <int B, template<class>  std::vector<T> >

// template <int B, typename T = void>
// struct vector_type{};

// template <typename T>
// struct vector_type<1, T>{
//   typedef std::vector v;};
// template <typename T>
// struct vector_type<0, T>{
//   typedef ft::vector v;
//   };
// typedef vector_type<MY, int>::v vector;




template <typename Container>
void create_vector_of_ints(Container &vector, int elems)
{

  for (int i = 0; i < elems; i++)
  {
    vector.push_back(i);
  };
}




template <typename T>
class VectorFactory{

  typedef T value_type;
  typedef vector<value_type> Container;
  typedef Container* pointer;

  public:
    template <typename V>
      struct ifactory{
        static Container* create(void){
          return VectorFactory::create(V());
          }
      };

    typedef struct ifactory<value_type> factory;

    pointer p;

    VectorFactory(){};
    virtual ~VectorFactory(){
      // if (p){
      //   delete p;
      // };
    };

template<bool B, class T = void>
	struct enable_if {};

void f1(int a, int)


template <typename T>



private:

    static Container* create(char)
    {
      Container* cc = new Container;

      Container& c = *cc;

      c.push_back('H');c.push_back('e');
      c.push_back('l');c.push_back('l');c.push_back('o');

      c.push_back(',');c.push_back(' ');

      c.push_back('W');c.push_back('o');
      c.push_back('r');c.push_back('l');c.push_back('d');

      c.push_back('!');      

      return cc;
    };

    static Container* create(int)
    {
      Container* c = new Container;
      create_vector_of_ints(*c, 10);
      return c;
    };
  
    static Container* create(std::string){
      Container* cc = new Container;
      Container& c = *cc;
      c.push_back("Hello");
      c.push_back("This");
      c.push_back("Is");
      c.push_back("Dog");
      return cc;
    }
};



extern const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")};

template <typename V>
void test_iterators(V &v)
{
  typename V::iterator start = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rstart = v.rbegin();
  typename V::reverse_iterator rend = v.rend();

  std::cout << "First elem of vector V:\t" << *start << "\n";
  std::cout << "Last elem of vector V:\t" << *(end - 1) << std::endl;
  std::cout << "First elem of vector V[::-1]:\t" << *rstart << std::endl;    // will take the last item of array
  std::cout << "Last elem of vector V[::-1]:\t" << *(rend - 1) << std::endl; // will move reverse iterator to first position in array
}


template <typename V>
void test_iterate_vector(V &v)
{
  typename V::iterator start = v.begin();
  typename V::iterator end = v.end();
  typename V::reverse_iterator rstart = v.rbegin();
  typename V::reverse_iterator rend = v.rend();

  std::cout << "Iterating through vector" << std::endl;
  for (; start != end; ++start)
  {
    std::cout << *start << " ";
  }
  std::cout << "\n";

  std::cout << std::string(20, '>') << std::endl;
  ol_

  std::cout << "Iterating through vector backwards" << std::endl;
  for (; rstart != rend; ++rstart)
  {
    std::cout << *rstart << " ";
  }
  std::cout << "\n";
}

template <typename V>
void test_vector_sizes(V &v)
{
  int i = 0;
  // std::cout << v.size() << ' ' << v.capacity() << ' ' << v[i] << std::endl;
  std::cout << "size"
            << "\t"
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(i);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;
  }
  v.size();
  v.capacity(); // _cap *= 2, if newer elem.size overflows capacity
}

template <typename V>
void test_create_vector_custom_type(V &v)
{

  test::my_class my_obj;

  int i = 0;
  std::cout << "size"
            << "\t"
            << "_cap"
            << "\t"
            << "elem" << std::endl;
  for (; i < 10; ++i)
  {
    v.push_back(my_obj);
    std::cout << v.size() << '\t' << v.capacity() << '\t' << v[i] << std::endl;

    my_obj++;
  }
}

// template <typename T>
void test_vector_reserve()
{
  std::cout << WHITE
            << "Changing of capacity during adding 100 new elements"
            << std::endl;

  typedef vector<int>::size_type size_type;

  int amount = 33;

  vector<int> foo;
  size_type sizefoo = foo.size();

  std::cout << "SIZES OF FOO" << std::endl;
  for (int i = 0; i < amount; ++i)
  {
    foo.push_back(i);
    std::cout << BLUE << " " << sizefoo;
    sizefoo = foo.capacity();
  }

  std::cout << "\n";
  std::cout << WHITE
            << "Changing of capacity during adding 100 new elements (100 were reserved)"
            << std::endl;

  vector<int> bar;
  size_type sizebar = bar.size();

  bar.reserve(static_cast<size_type>(amount) - 2);

  std::cout << "SIZES OF BAR" << std::endl;
  for (int i = 0; i < amount; ++i)
  {
    bar.push_back(i);
    std::cout << BLUE << " " << sizebar;
    sizebar = bar.capacity();
  }
  std::cout << std::endl;
  std::cout << "------------------" << std::endl;
  test_iterate_vector(bar);
  std::cout << "------------------" << std::endl;
  test_iterate_vector(foo);

  std::cout << std::endl
            << "RESERVE >MAX SIZE TEST" << std::endl;

  typedef vector<test::my_class>::size_type stype;
  vector<test::my_class> evil(10);
  evil.reserve(40);
  test_iterate_vector(evil);
  std::cout << "max size = " << evil.max_size() << std::endl;
  stype max_size = evil.max_size();
  try
  {
    evil.reserve(max_size + 1);
  }
  catch (const std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

template <typename T>
void test_vector_resize_with_default_value(const T &value = T())
{
  vector<T> vints;

// Create size 10
  create_vector_of_ints(vints, 10);
  std::cout << WHITE << "Elements in vector 10" << std::endl;
  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Truncate to size 5
  vints.resize(5);
  std::cout << WHITE << "Elements in vectors after resize(5):" << std::endl;

  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Extend to size 10 again and fill with value
  vints.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors back to resize(10) and value " <<\
      value << std::endl;
  
  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

// Resize to 10, should be idempotent
  vints.resize(10, value);
  std::cout << WHITE <<\
     "Elements in vectors after resize(10) again and value " << value << std::endl;


  for (vector<int>::size_type i = 0; i < vints.size(); ++i){
    std::cout << BLUE << ' ' << vints[i];
  };
  std::cout << std::endl;

}


void  test_erase_vector(){
  vector<int> vints;

  create_vector_of_ints(vints, 10);
  test_iterate_vector(vints);  

  std::cout << "Delete start" << std::endl;
  vints.erase(vints.begin());
  test_iterate_vector(vints);  
  std::cout << "Delete end" << std::endl;
  vints.erase(vints.end() - 1);
  test_iterate_vector(vints);  

  std::cout << "Delete middle element" << std::endl;
  vints.erase(vints.begin() + (vints.size() / 2));
  test_iterate_vector(vints);
}

int main()
{
  std::cout << "TESTING " << vector_types[MY] << std::endl;

  // vector<int> vzero; //
  // test::my_class my_object;

  // vector<int> vnonzero(5);
  // vector<test::my_class> vmyclass(5);

  // vector<int> v;

  // test_vector(vzero);
  // test_vector(vnonzero);
  // test_create_vector_custom_type(vmyclass);
  // test_iterate_vector(vmyclass);
  // test_vector_reserve();

  // const int &n = -1;
  // test_vector_resize_with_default_value<int>(n);
  
  // typedef int ftype;

  // VectorFactory<int> VF;
  
  // vector<int>* v = VectorFactory<int>::factory::create();

  test_iterate_vector(*VectorFactory<char>::factory::create());

  // test_iterate_vector(*VectorFactory<char>().create());
  // test_iterate_vector(*VectorFactory<std::string>().create());

  // test_erase_vector();
  
  // vector<int> v;
  
  // create_vector_of_ints(v, 10);
  // test_erase_vector();

  
  // system("leaks test");

};
