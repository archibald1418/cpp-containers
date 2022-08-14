#ifndef PICK_MAP_H
# define PICK_MAP_H

# include <map>
// # include <set>
# include <iterator>
# include "ft_containers.hpp"

extern const std::string map_types[2] = {
    std::string("SYS_MAP"),
    std::string("MY_MAP")
    };

# ifdef MY
#  if MY == 1
    using ft::map;
#  else
    using std::map;
#  endif
# endif

#ifndef MY
# define MY 0
    using std::map;
# endif

#endif
