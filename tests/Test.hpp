#ifndef TEST_H
# define TEST_H

# include <iostream>

# include "colors.hpp"

namespace test {

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
      this->c = std::string(1, this->b); // compatible with c++98
      return (*this);
    }

    bool operator==(const struct test& other){
      return (this->a == other.a && \
              this->b == other.b && \
              this->c == other.c);
    }

  } my_class;
}

#endif // TEST_H

