
#ifndef ALGORITHM_H
# define ALGORITHM_H

# include "type_traits.hpp"

namespace ft{

    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || (*first2) < (*first1))
                    return false;
                else if (*first1 < *first2)
                    return true;
                ++first1; 
                ++first2;
            }
            return (first2 != last2);
        }

    template <class T, class U>
        typename enable_if
        <
            is_same<typename remove_const<T>::type, U>::value, U*
        >::type copy(T* __first, T* __last, U* __result){
            size_t n = static_cast<size_t>(__last - __first);
            if (n > 0){
                std::memmove(__result, __first, n * sizeof(U));
                return __result;
            }
            return __result;
        }

    template <class InputIt, class OutputIt>
        OutputIt copy(InputIt first, InputIt last, OutputIt result){
            for (; first != last; ++first, (void) ++result)
                *result = *first;
            return result;
        }

}


#endif
