
namespace ft{

    template <typename T1, typename T2>
    struct pair{
        typedef first_type T1;
        typedef second_type T2;

        T1 first;
        T2 second;

        pair() : first(T1()), second(T2()){};
        pair(const T1& x, const T2& y) : first(x), second(y){};

        template <typename U1, typename U2>
        pair(const pair<U1, U2>&  p){
            first = p.first;
            second = p.second;
        }

        pair& operator=(const pair& other){
            if (this == &other)
                return *this;    
            this->first = other.first;
            this->second = other.second;
        }  
    };

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 t, T2 u){
        return pair(t, u);
    }
    
}