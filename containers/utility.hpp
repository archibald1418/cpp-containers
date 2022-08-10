#ifndef UTILITY_H
# define UTILITY_H
# include "pair.hpp"

namespace ft{

/* ----------------------------- Pair non-members -------------------------------- */

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 t, T2 u){
        return pair<T1, T2>(t, u);
    }

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        if (lhs.first < rhs.first)
            return true;
        if (rhs.first < lhs.first)
            return false;
        if (lhs.second < rhs.second)
            return true;
        else
            return false;
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
