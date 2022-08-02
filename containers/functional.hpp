
namespace ft {

    template <
        class Arg1,
        class Arg2,
        class Result
    > struct binary_function {
        typedef first_argument_type Arg1;
        typedef second_argument_type Arg2;
        typedef result_type Result;
    };

    template <typename T>
    struct less : public binary_function<T, T, bool>{

        bool operator()(const T& lhs, const T& rhs){
            return lhs < rhs;
        }
        
    };

}