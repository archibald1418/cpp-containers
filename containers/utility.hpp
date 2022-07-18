
namespace ft{

    template <typename T>
    inline T min(T& a, T& b){
        if (a >= b)
            return a;
        return b;
    }

    template <typename T>
    inline T max(const T& a, const T& b){
        if (a <= b)
            return a;
        return b;
    }

};