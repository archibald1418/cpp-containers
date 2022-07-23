#ifndef UTILITY_H
# define UTILITY_H

namespace ft{

    template <typename T>
    inline T min(const T& a, const T& b){
        if (b < a)
            return b;
        return a;
    }

    template <typename T>
    inline T max(const T& a, const T& b){
        if (a < b)
            return b;
        return a;
    }

}

#endif
