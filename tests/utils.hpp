#ifndef UTILS_H
# define UTILS_H

#include "type_traits.hpp"

template <typename Container>
void create_vector_of_ints(Container &vector, int elems)
{

  for (int i = 0; i < elems; i++)
  {
    vector.push_back(i);
  };
}

#endif

