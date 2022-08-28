#ifndef STACK_H
# define STACK_H

# include "vector.hpp"
#include <stack>

namespace ft {
    template <typename T, class Container = vector<T> >
    class stack
    {
        protected:  
            Container           _c; // must be protected as per specs
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;

            explicit stack(const container_type &ctnr = container_type()) : _c(ctnr) {};
            stack(const stack& other) : _c(other._c){};
            ~stack(){};

            stack& operator=(const stack& other)
            {
                if (this == &other)
                    return *this;
                _c = other._c;
                return *this;
            }
            // First tests ok
            bool empty() const
            {
                return _c.empty();
            }

            size_type size() const
            {
                return _c.size();
            }

            value_type &top()
            {
                return _c.back();
            }

            const value_type &top() const
            {
                return _c.back();
            }

            void push(const value_type &val)
            {
                _c.push_back(val);
            }

            void pop()
            {
                _c.pop_back();
            }
            
            template <class _Tp, class _C>
            friend bool operator== (const stack<_Tp, _C>& lhs, const stack<_Tp,_C>& rhs);
            template <class _Tp, class _C>
            friend bool operator< (const stack<_Tp,_C>& lhs, const stack<_Tp,_C>& rhs);

            /*
                These two define total order so they need access to container
            */ 
    };
        template <class T, class Container>
            bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c == rhs._c);
            }

        template <class T, class Container>
            bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c != rhs._c);
            }

        template <class T, class Container>
            bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c < rhs._c);
            }

        template <class T, class Container>
            bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c <= rhs._c);
            }

        template <class T, class Container>
        bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c > rhs._c);
            }

        template <class T, class Container>
        bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs._c >= rhs._c);
            }
}

#endif // STACK_H

