#ifndef FUNCTIONAL_H
# define FUNCTIONAL_H

namespace ft {

    template <
        class Arg1,
        class Arg2,
        class Result
    > struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    template <typename T>
    struct less : public binary_function<T, T, bool>{

        bool operator()(const T& lhs, const T& rhs)const{
            return lhs < rhs;
        }
        
    };

}

#endif // FUNCTIONAL_H

