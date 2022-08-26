#ifndef PICK_MAP_H
# define PICK_MAP_H


// # include <set>
# include <iostream>

extern const std::string map_types[2] = {
    std::string("SYS_MAP"),
    std::string("MY_MAP")
    };

# ifdef MY
#  if MY == 1
#   include "map.hpp"
    using ft::map;
#  else
#   include <map>
#   include <iterator>
    using std::map;
#  endif
# endif


# ifndef MY
#  define MY 0
#    include <map>
#    include <iterator>
     using std::map;
# endif

#endif //PICK_MAP_H

