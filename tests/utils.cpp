#include "colors.hpp"

#include <iostream>


void print(std::string s, Color color){
  std::cout << color << s << "\n\n" << RESET;
}

void print(const char* s, Color color){
  std::cout << color << std::string(s) << "\n\n" << RESET;
}

void delineate(int n){
  std::cout << "\n" << std::string(n, '-') << "\n\n";
}
