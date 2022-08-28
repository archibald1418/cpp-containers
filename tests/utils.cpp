#include "colors.hpp"
#include "tree.hpp"
#include "node.hpp"
#include "type_traits.hpp"
#include <iostream>

void print(std::string s, Color color){
  std::cout << color << s << "\n\n" << RESET;
}

void print(const char* s, Color color){
  std::cout << color << std::string(s) << "\n\n" << RESET;
}

template <typename Node>
void print(Node* n, Color color, typename Node::__node_tag* = 0){
  std::cout << color << "{" << n->Get() << "}" << std::endl;
}

void delineate(int n){
  std::cout << "\n" << std::string(n, '-') << "\n\n";
}
