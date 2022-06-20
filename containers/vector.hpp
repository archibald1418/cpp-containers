#include "iterators.hpp"
#include <cstdint>

namespace ft {

    typedef int8_t byte;

    template <typename T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T                       value_type;
            typedef Alloc		            allocator_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            typedef std::ptrdiff_t          difference_type;
            typedef std::size_t             size_type;

        private:
            pointer _first;
            size_type _size; // size 
            size_type _cap; // capacity
            allocator_type  _alloc;
            
        public:
            typedef RAIterator<value_type> iterator;
            typedef RAIterator<const value_type> const_iterator;
            typedef RARIterator<value_type> reverse_iterator;
            typedef RARIterator<const value_type> const_reverse_iterator;

            size_type max_size()const{
                /*
                This value typically reflects the theoretical limit on the size of the container,
                -- at most std::numeric_limits<difference_type>::max() --
                */
                return std::min<size_type>(
                    _alloc.max_size(),
                    std::numeric_limits<difference_type>::max()                 
                );
            }

            size_type size()const{
                return _size;
            }

            size_type capacity()const{
                return _cap;
            }

            void reserve(size_type new_cap)
            {
                /*
                ** Reserve enough memory for n elements of size T 
                ** if there is more memory needed
                */

                if (new_cap <= this->_cap)
                    return;
                if (new_cap > max_size())
                    throw std::length_error("allocator<T>::allocate(size_type n) 'n' exceeds maximum supported size"); // as per vector<...>::reserve docs
                // T* newarr = new T[n]; 
                // T* newarr = reinterpret_cast<T*>(new byte[n * sizeof(T)]); // 1 * n * sizeof bytes
                // T* newarr = _alloc.allocate
                pointer newarr = _alloc.allocate(new_cap);
                /* Raises std::bad_alloc if allocation fails */
                // this is bad, objects might be enormous or resource-hungry (mutex, connection etc or a big object)
                // solution: allocate!
                size_type i = 0;
                try {
                    for (; i < _size; ++i){
                        _alloc.construct(newarr + i, *(_first + i)); // does the same placement-new call
                        // new (newarr + i) T(_first[i]); // placement-new syntax; new [address] object
                        // --- newarr[i] = arr[i]; ---
                        /* with reint_cast last line would be UB
                        newarr[i] has no object, just bare memory
                        */
                    }
                } catch (const std::exception& e) {
                    size_type j = 0;
                    for (; j < i; ++j){
                        // (newarr + i)->~T(); // backwards loop for garbage collection
                        _alloc.destroy(newarr + j);
                    }
                    std::cout << "Error:" << e.what() << '\n' << "Deallocating array" << '\n';
                    // delete[] reinterpret_cast<byte*>(newarr);
                    _alloc.deallocate(newarr, j);
                    throw; // rethrow to next
                }
                for (size_type i = 0; i < _size; ++i){
                    // explicit dtor call:
                    // (_first + i)->~T(); // no handling in case of exceptions
                    _alloc.destroy(_first + i);
                }
                if (_cap)
                    // delete [] reinterpret_cast<byte*>(_first);
                    _alloc.deallocate(_first, _cap);
                // we might have extra unfilled memory, so this is bad
                // moreover, on line 19 our array became interpreted as bytearr;
                _first = newarr;
                this->_cap = new_cap;
            }

            void resize(size_type n, const value_type& value = T()){ // T might not have a default ctor
                try {
                    if (n > this->_cap)
                        reserve(n);
                } catch (...) {
                    return; // Strong guarantee (=no effect)
                }
                if (n > _size){
                    for (size_type i = _size; i < n; ++i){
                        // new (_first + i) T(value); // ctor might throw an error!
                        _alloc.construct(_first + i, value);
                    }
                } else if (n < _size) {
                    for (size_type i = n; i < _size; ++i){
                        _alloc.destroy(_first + i);
                    }
                }
                _size = n;
            }

            void push_back(const T& value){
                if (_cap == 0 && _size == 0){
                    reserve(1);
                } // TODO: check exception guarantees
                // else if
                else if (_cap == _size){
                    reserve(2 * _size);
                }
                // new (_first + _size) T(value);
                _alloc.construct(_first + _size, value);
                ++_size;
            }

            void pop_back(){
                --_size;
                // (_first + _size)->~T();
                _alloc.destroy(_first + _size);
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
            return *(_first + i);
        }

        const T& operator[](size_t i)const {
            return *(_first + i);
        }

        T& at(size_t i) { // every []-defined container has .at, which throws an error
            if (i >= _size)
                throw std::out_of_range("Index out of range");
            return _first[i];
        }

        size_t size(){
            return this->_size;
        }
        size_t capacity(){
            return this->_cap;
        }
            
            // explicit means 'No, compiler! No arguments means this ctor is called, don't second-guess'
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cap(0), _size(0), _first(NULL){}
        explicit vector(size_type size,
                            const value_type& value = value_type(),
                            const allocator_type& alloc = allocator_type())
                            : _alloc(alloc), _size(size), _cap(size){
            _first = _alloc.allocate(size);
            for (size_type i = 0; i < size; i++){
                _alloc.construct(_first + i, value);
            }
        }

        // Iterators
        iterator                begin(){return iterator(_first);};
        const_iterator          begin()const{return const_iterator(_first);};
        reverse_iterator        rbegin(){return reverse_iterator(_first + _size - 1);};
        const_reverse_iterator  rbegin()const{return const_reverse_iterator(_first + _size - 1);};
        iterator                end(){return iterator(_first + _size);};
        const_iterator          end()const{return const_iterator(_first + _size);};
        reverse_iterator        rend(){return reverse_iterator(_first - 1);};
        const_reverse_iterator  rend()const{return const_reverse_iterator(_first - 1);};


        
    };

};