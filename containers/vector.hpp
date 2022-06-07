#include "iterators.hpp"

namespace ft {

    typedef int8_t byte;

    template <typename T, class Alloc = std::allocator<T> >
    class vector {
        private:
            
            // TODO: rewrite and test with traits
            typedef T                       value_type;
            typedef Alloc		            allocator_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            typedef std::ptrdiff_t          difference_type;
            typedef size_t                  size_type;

            pointer arr;
            size_type sz; // size 
            size_type cap; // capacity
            allocator_type  _alloc;
            
        public:
            // reserve enough memory for n elements 
            void reserve(size_t n)
            {
                if (n <= this->cap)
                    return; 
                // T* newarr = new T[n]; 
                size_t i = 0;
                T* newarr = reinterpret_cast<T*>(new byte[n * sizeof(T)]); // 1 * n * sizeof bytes
                // this is bad, objects might be enormous or resource-hungry (mutex, connection etc or a big object)
                // solution: allocate!
                try {
                    for (size_t i = 0; i < sz; ++i){
                        new (newarr + i) T(arr[i]); // placement-new syntax; new [address] object
                        // newarr[i] = arr[i]; 
                        /* with reint_cast this line 27 would be UB
                        newarr[i] has no object, just bare memory
                        */
                    }
                } catch (...) {
                    for (size_t j = 0; j < i; ++j){
                        (newarr + i)->~T(); // backwards loop for garbage collection
                    }
                    delete[] reinterpret_cast<byte*>(newarr);
                    throw; // throw to next
                }
                for (size_t i = 0; i < sz; ++i){
                    // explicit dtor call:
                    (arr + i)->~T(); // no handling in case of exceptions
                }
                delete [] reinterpret_cast<byte*>(arr); 
                // we might have extra unfilled memory, so this is bad
                // moreover, on line 19 our array became interpreted as chararr;
                arr = newarr;
                this->cap = n;
            }

            void resize(size_t n, const T& value = T()){ // T might not have a default ctor
                try {
                    if (n > this->cap)
                        reserve(n);
                } catch (...) {
                    return;
                }
                if (n > sz){
                    for (size_t i = sz; i < n; ++i){
                        new (arr + i) T(value); // ctor might throw an error!
                    }
                    if (n < sz) {
                        sz = n;
                    }
                }
            }

            // ver 1
            // FIXME: fails for zero arg vector
            void push_back(const T& value){
                if (cap == 0 && sz == 0){
                    reserve(1);
                }
                if (cap == sz){
                    reserve(2 * sz);
                }
                new (arr + sz) T(value);
                ++sz;
            }

            void pop_back(){
                --sz;
                (arr + sz)->~T();
            }

            /*
            Exception safety:
            - strong guarantee
                - if no reallocations happen,
                    there are no changes in the container in case of exception (strong guarantee).
            - basic guarantee
                - the container is guaranteed to end in a valid state
            */
        T& operator[](size_t i) {
            return *(arr + i);
        }

        const T& operator[](size_t i)const {
            return *(arr + i);
        }

        T& at(size_t i) { // every []-defined container has .at, which throws an error
            if (i >= sz)
                    throw std::out_of_range("Index out of range");
                return arr[i];
        }

        size_t size(){
            return this->sz;
        }
        size_t capacity(){
            return this->cap;
        }
            
            // explicit means 'No, compiler! No arguments means this ctor is called, don't second-guess'
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), cap(0), sz(0), arr(NULL) {}
        explicit vector(size_type size, 
                            const value_type& value = value_type(),
                            const allocator_type& alloc = allocator_type())
                            : _alloc(alloc), sz(size), cap(size){
            arr = _alloc.allocate(size);
            for (size_type i = 0; i < size; i++){
                _alloc.construct(arr + i, value);
            }
        }
    };

};