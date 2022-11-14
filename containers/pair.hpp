#ifndef PAIR_H
# define PAIR_H

# include <iostream>

namespace ft{

    template <typename T1, typename T2>
    struct pair{
        typedef T1 first_type;
        typedef T2 second_type;

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

		friend std::ostream& operator<<(std::ostream& os, const pair& p){
			os << "{'" << p.first << "' : '" << p.second << "'}" <<   std::endl;
			return os;
		}
    };

}

#endif // PAIR_H

