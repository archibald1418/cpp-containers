#ifndef SET_H
# define SET_H

# include "map.hpp"
# include "node.hpp"

namespace ft{

    template <
            typename Key,
            class Predicate,
            class Alloc,
            bool MultiFlag = false, 
            template<typename> class NodeType = Node>
        struct set_traits : map_traits<Key, Key, Predicate, Alloc, Multiflag, NodeType>{};
}


#endif