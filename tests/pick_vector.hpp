#ifndef PICK_VECTOR_H
# define PICK_VECTOR_H

# include <iterator>

extern const std::string vector_types[2] = {
    std::string("SYS_VECTOR"),
    std::string("MY_VECTOR")
    };

# ifdef MY
#  if MY == 1
#   include "vector.hpp"
    using ft::vector;
#  else
#   include <vector>
    using std::vector;
#  endif
# endif


#ifndef MY
# define MY 0
#  include <vector>
   using std::vector;
# endif

#endif // PICK_VECTOR_H

