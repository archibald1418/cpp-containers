#ifndef PICK_VECTOR_H
# define PICK_VECTOR_H

# include <iterator>

extern const std::string stack_types[2] = {
    std::string("SYS_STACK"),
    std::string("MY_STACK")
    };

# ifdef MY
#  if MY == 1
#   include "stack.hpp"
    using ft::stack;
#  else
#   include <stack>
    using std::stack;
#  endif
# endif


#ifndef MY
# define MY 0
#  include <stack>
   using std::stack;
# endif

#endif // PICK_VECTOR_H

