
#ifndef PICK_VECTOR_H
# define PICK_VECTOR_H

# include <vector>
# include "ft_containers.hpp"

# ifdef MY
#  if MY == 1
    using ft::vector;
#  else
    using std::vector;
#  endif
# endif

#ifndef MY
# define MY 0
    using std::vector;
# endif

#endif
