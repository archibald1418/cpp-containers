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
#	include "pair.hpp"
    using ft::map;
	using ft::pair;
#  else
#   include <map>
#   include <iterator>
#	include <utility>
    using std::map;
	using std::pair;
#  endif
# endif


# ifndef MY
#  define MY 0
#	include <map>
#	include <iterator>
#	include <utility>
    using std::map;
	using std::pair;
# endif

#endif //PICK_MAP_H

