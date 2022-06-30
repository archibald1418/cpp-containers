#include "iterator.hpp"
#include <cstdint>

namespace ft {

    typedef int8_t byte;

    template <typename T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T                       value_type;
            typedef Alloc		            allocator_type;
            typedef std::size_t             size_type;
            typedef std::ptrdiff_t          difference_type;
            typedef T&                      reference;
            typedef const T&                const_reference;
            typedef T*                      pointer;    
            typedef const T*                const_pointer;

        private:
            allocator_type  _alloc;
            size_type _cap; // capacity
            size_type _size; // size 
            pointer _first;
            
        public:
            typedef RAIterator<value_type> iterator;
            typedef RAIterator<const value_type*> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

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

            void resize(size_type n, const_reference value = value_type()){ // T might not have a default ctor
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

            void push_back(const_reference value){
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
                if (!empty())
                    _alloc.destroy(_first + _size - 1);
                --_size;
                // (_first + _size)->~T();
            }

            /*
                Exception safety:
                // basic guarantee
                    - the container is guaranteed to end in a valid state
                    (i.e. the data is not corrupted,
                    and no resources left leaking)
                // strong guarantee
                    - if no reallocations happen,
                        there are no changes in the container in case of exception.
                    (i.e. the called code has no effect,
                        and exception handling should
                        rollback any changes that already happened)
                // no-throw guarantee
                    - the container should not throw errors,
                    meaning that no container code lets any errors
                    propagate out of the funciton, calling the container
                    (i.e. the lower exceptions are handled
                        before they reach the caller,
                        so the caller doesn't register any errors at all)
            */
        reference operator[](size_type i) {
            return *(_first + i);
        }

        const_reference operator[](size_type i)const {
            return *(_first + i);
        }

        const_reference at(size_type i)const {
            if (i >= _size)
                throw std::out_of_range("Index out of range");
                // every []-defined container has .at, which throws an error
            return _first[i];
        }

        reference at(size_type i) {
            if (i >= _size)
                throw std::out_of_range("Index out of range");
            return _first[i];
        }

        size_type size(){
            return this->_size;
        }
        size_type capacity(){
            return this->_cap;
        }
// Front and Back
        reference front(){
            return _first[0];
        }
        const_reference front()const{
            return _first[0];
        }

        bool empty()const{
            return (_size == 0);
        }

        reference back(){
            if (empty()){
                return _first[0];
            }
            return _first[_size - 1];
        }
        const_reference back()const{
            if (empty()){
                return _first[0];
            }
            return _first[_size - 1];
        }
            
            // explicit means 'No, compiler! No arguments means this ctor is called, don't second-guess'
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cap(0), _size(0), _first(NULL){}
        explicit vector(size_type size,
                            const value_type& value = value_type(),
                            const allocator_type& alloc = allocator_type())
                            : _alloc(alloc), _cap(size), _size(size) {
            _first = _alloc.allocate(size);
            for (size_type i = 0; i < size; i++){
                _alloc.construct(_first + i, value);
            }
        }

        allocator_type get_allocator()const{
            return (_alloc);
        }

        iterator erase(iterator pos){
            if (pos >= begin() && pos <= end()) {
            // no behaviour defined for pos == end()
                iterator it = begin();
                size_type del_index = 0;
                while (it != pos){
                    ++it; 
                    ++del_index;
                }
                _alloc.destroy(_first + del_index);
                --_size;
                // pulling the vector parts to the left
                size_type insert_index = del_index;
                while (insert_index < _size){
                    // 
                    _first[insert_index] = _first[insert_index + 1];
                    // TODO: write assignment
                    ++insert_index;
                }
                // destroy extra bit of T typed memory, left after resizing
                _alloc.destroy(_first + _size);
                return begin() + del_index; // return new position   
            }
            return (0); // not found in vector
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

        void swap (vector& other)
        {
            vector tmp(*this);
            *this = other;
            other = tmp;
        }
        
    };

// Non-member comparison operators

template <class T, class Alloc>
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }

template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

template <class T, class Alloc>
    void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
};