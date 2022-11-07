#ifndef UTILS_H
# define UTILS_H

# include <iostream>
# include <iomanip>

# include "type_traits.hpp"
# include "Test.hpp"
# include "types.hpp"
# include "tree.hpp"
# include "node.hpp"
# include "colors.hpp"
# include "tree_utils.hpp"
# include "map.hpp"

template <typename Container>
void create_vector_of_ints(Container &vector, int elems)
{

  for (int i = 0; i < elems; i++)
  {
    vector.push_back(i);
  };
}

template <typename Container>
void create_vector_of_chars(Container& vector){
  vector.push_back('S'); 
  vector.push_back('h');
  vector.push_back('e');
  vector.push_back(' ');
  vector.push_back('b');
  vector.push_back('e');
  vector.push_back('l');
  vector.push_back('i');
  vector.push_back('e');
  vector.push_back('v');
  vector.push_back('e');
  vector.push_back('d');
}

template <typename Container>
void cut_vector_of_chars(Container& vector){
  vector.erase(vector.begin()); // he believed
  vector.erase(vector.begin() + 3, vector.begin() + 5); // he lieved
  vector.erase(vector.end() - 3, vector.end() - 1); // he lied
}


namespace test{
  
    template <bool B>
    struct signal_const {
      static void print(){}
    };
    template <>
    struct signal_const<true>{
      static void print(){std::cout << "CONST!" << std::endl;}
    };

  template <typename T>
  struct unique_ptr
  {
    typedef T* pointer;
    typedef T element_type;
    typedef element_type& reference;
    
    pointer _ptr;
    
    unique_ptr(T* ptr) : _ptr(ptr){};
    unique_ptr() : _ptr(NULL){};
    ~unique_ptr(){
      if (_ptr) delete _ptr;
    }
    unique_ptr(const unique_ptr& other){
      *this = other;
    }
    reference operator*()const{
      return *_ptr;
    }
    pointer operator->()const{
      return _ptr;
    }
    unique_ptr<T>& operator=(const unique_ptr<T>& other){
      if (this == &other)
        return *this;
      _ptr = other._ptr;
      return *this;
    }
  };

  // template <typename T>
  // unique_ptr<T> make_unique(T* ptr){
  //   return unique_ptr<T>(ptr);
  // }

  template <typename T>
  class IsDereferenceable{
    private:
        typedef char YesType[1];
        typedef char NoType[2];
        

        template <typename U> static YesType& test(void* = &U::operator*);
        template <typename U> static NoType& test(...);
    public:
        static const bool value = (
            ft::is_pointer<T>::value || (sizeof(test<T>(0)) == sizeof(YesType))
        );
  }; 
  
}


// Printing functions
void print(std::string s, Color color = RED);
void print(const char* s, Color color = RED);
void delineate(int n = 40);

template <typename T>
void print(
    T ptr, 
    Color color = GREEN,
    typename ft::enable_if<test::IsDereferenceable<T>::value, T>::type* = 0)
{
  std::cout << color << *ptr << "\n\n" << RESET;
}


// Print typeinfo message
template <typename T>
void        print_type(T)
{
    const char* typeinfo = typeid(T).name();
    std::string value = test::CreateMap::TheMap[typeinfo];
    if (value.empty())
        std::cout << BOLDRED << "Unknown Type: [" << typeinfo << "]" << "\n\n" << RESET;
    else
        std::cout << BOLDMAGENTA << value << "\n\n" << RESET;
}


// Test information ::= [title, type]
template <typename T>
void print_test_info(const char *title, Color color = GREEN)
{
  print(title, color);
  print_type(T());
}

// #include <set>



// ------------------------------ Trees -----------------------



template <typename node>
void print_tree(node* p, int indent = 4, 
  typename node::__node_tag* = 0)
{

  if (!p)
    return ;
  if(!p->IsPhony()) {
      if(!p->Right()->IsPhony()) {
          print_tree(p->Right(), indent+4);
      }
      if (indent) {
          std::cout << std::setw(indent) << ' ';
      }
      if (!p->Right()->IsPhony())
        std::cout<<" /\n" << std::setw(indent - 1) << ' ';
      std::cout << p->Get() << ":" << p->get_balance_factor() << "\n"; // Prints balfac ok!
      if(!p->Left()->IsPhony()) {
          std::cout << std::setw(indent) << ' ' <<" \\\n";
          print_tree(p->Left(), indent+4);
      }
  }
}

template <typename tree>
void print_tree(tree* t, 
  typename tree::traits* = 0){
  if (t->empty())
    return print("Tree is empty", BOLDBLUE);
  std::cout << "*" << std::endl;
  print_tree(t->Root());
  std::cout << "*" << std::endl;
}

template <typename node>
void print_node(node* t, Color color = WHITE, bool nl = true){
  if (!t)
  {
    std::cout << color << "nullptr" << RESET;
    if (nl)
      std::cout << std::endl;
    return ;
  }
  if (t->IsPhony())
  {
    std::cout << color << "empty" << RESET;
    if (nl)
      std::cout << std::endl;
    return ;
  }
  std::cout << color <<  "{" << t->Get() << ":"  << t->get_balance_factor() << "}" << RESET;
  if (nl)
    std::cout << std::endl;
}

template <typename node>
void print_adjacent_nodes(node* t){
  if (t->IsPhony())
    return print("Empty node", BOLDWHITE);
  if (!t)
    return print("Null node", BOLDWHITE);
  int indent = 4;
  std::cout << std::setw(indent * 4);            
  print_node(t->Parent(), BLUE, 1);
  std::cout << std::setw(indent * 3) << "⬆" << std::endl;
  std::cout << std::setw(indent * 2) << "-";  
  print_node(t, BOLDRED, 0);                
  std::cout << "-\n";
  std::cout << std::setw(indent * 3) << "↙️" << std::setw(indent * 3) << "↘" << std::endl;
  std::cout << std::setw(indent * 2); 
  print_node(t->Left(), YELLOW, 0); 
  std::cout << std::setw(indent * 3); 
  print_node(t->Right(), YELLOW, 1);
  std::cout << std::setw(indent * 4) << "⬇️" << std::endl;
}

/* ---------------------- Map ------------------------- */


template<typename Key, typename Value>
void print_map_tree(ft::map<Key, Value>& m){
	print_tree(m.getRoot());
}



#endif // UTILS_H

