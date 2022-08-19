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
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
        // This helps to compare keys, otherwise if keys are equal, compare values.
        // Should accountfor both maps and multimaps (TODO: test)
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

/* --------------------------- Null-ptr type ----------------------- */

    const 
    class nullptr_t
        {
        public:
            template<class T>
                inline operator T*() const
                {
                    return static_cast<T*>(0);
                    // return 0;
                }

            template<class C, class T>
                inline operator T C::*() const
                {
                    return 0;
                }
            
            friend  bool operator==(nullptr_t&, nullptr_t&) {return true;}
            friend  bool operator!=(nullptr_t&, nullptr_t&) {return false;}

            private:
                void operator&() const;
        }
    nullptr_my = {};

    const nullptr_t& get_nullptr_t(){
        return ft::nullptr_my;
    }


}



// ---------------- nullptr my ---------------------

# define nullptr_my ft::get_nullptr_t()

// ---------------- nullptr my ---------------------



#endif
