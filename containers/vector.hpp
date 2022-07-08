#include "iterator.hpp"
#include "utility.hpp"
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
            typedef typename Alloc::reference        reference;
            typedef typename Alloc::const_reference  const_reference;
            typedef typename Alloc::pointer          pointer;    
            typedef typename Alloc::const_pointer    const_pointer;

        
            typedef RAIterator<pointer> iterator;
            typedef RAIterator<const_pointer> const_iterator; // const_iterator should be convertible to iterator, but it is not : (check traits(
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        private:
            allocator_type  _alloc;
            size_type _cap; // capacity
            size_type _size; // size 
            pointer _first;

            iterator __make_iter(pointer __p){
                return iterator(__p);
            }
            const_iterator __make_iter(const_pointer __p)const{
                return const_iterator(__p);
            }

        
        public:
            

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
                        // Dtors in c++ are no-throw guarantee
                        // It's on the destructor's side to catch errors before they rise up the stack
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
                _alloc.construct(_first + _size, T(value));
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
        vector(const vector& src){
            *this = src;
        }

        // Destructor
        ~vector(){
            for (size_type i = 0; i < _size; ++i){
                _alloc.destroy(_first + i);
            }
            if (_cap){
                _alloc.deallocate(_first, _cap);
            }
        }

        allocator_type get_allocator()const{
            return (_alloc);
        }

        iterator erase(iterator pos){
            // REVIEW: rewrite int fail-fast style
            // if (not (pos <= ))
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

        iterator erase(iterator first, iterator last){
            
            // Check if they in vector at all

            if (not (
                begin() <= first && \
                first <= last && \
                last <= end())) return (0);
            if (first == last) return (last); // empty range

            size_type len = static_cast<size_type>(last - first); // guaranteed to be > 0

            for (iterator it = first; it < last; ++it){
                _alloc.destroy(&(*it));
                _size--;
            }
            // REVIEW: can do in one pass
            for (size_type i = 0; i < len; ++i){
                _alloc.construct(&first[i], T(last[i]));
                _alloc.destroy(&last[i]);
            }

            return last;
        }

        void clear(){
            for (iterator it = begin(); it < end(); ++it){
                _alloc.destroy(&(*it));
            }
            _size = 0;
        }

        void assign(size_type count, const T& value){
            if (count > max_size()){
                throw std::length_error(
                        "ft::vector<T, Alloc>::assign(size_type count, const T& value) 'count' exceeds maximum supported size"
                    );
            }
            clear();
            try {
                if (_cap < count)
                    reserve(count);
            } catch (...){
                throw;
            }
            for (; _size < count; _size++)
                _alloc.construct(_first + _size, T(value));
        }

        // SFINAE overload to account for vector<:integral_type:> cases
        template <typename InputIt>
        void assign(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type isIterator = InputIt())
        {
            (void)isIterator;
            size_type len = static_cast<size_type>(last - first);
            if (len > max_size()){
                throw std::length_error(
                        "ft::vector<T, Alloc>::assign(InputIt first, InputIt last) iterator difference exceeds maximum supported size"
                    );
            }
            clear();
            size_type new_size = len;
            try {
                if (_cap < new_size)
                    reserve(new_size);
            } catch (...){
                throw;
            }
            while (_size < new_size)
            {
                _alloc.construct(_first + _size, *first);
                _size++;
                ++first;
            }
        }

        vector& operator=(const vector& other){
            if (this == &other)
                return *this;

           this->_alloc = allocator_type(other._alloc);
            /*
                std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value  ( since C++11 )
                Different allocators might share a memory pool
            */
           this->_first = NULL;
           assign(other.begin(), other.end()); // changes size and capacity
           return *this;
        }

        
        

        

        // Iterators
        iterator                begin(){return iterator(_first);};
        const_iterator          begin()const{return cbegin();};
        const_iterator         cbegin()const{
            return const_iterator(const_cast<const_pointer>(_first));
        };

        reverse_iterator        rbegin(){return reverse_iterator(_first + _size - 1);};
        const_reverse_iterator  rbegin()const{
            return const_reverse_iterator(const_cast<const_pointer>(_first + _size - 1));
        };
        const_reverse_iterator  crbegin()const{return rbegin();};

        iterator                end(){return iterator(_first + _size);};
        const_iterator          end()const{
            return const_iterator(const_cast<const_pointer>(_first + _size));
        };
        const_iterator         cend()const{return end();};

        reverse_iterator        rend(){return reverse_iterator(_first - 1);};
        const_reverse_iterator  rend()const{
            return const_reverse_iterator(const_cast<const_pointer>(_first - 1));
        };
        const_reverse_iterator  crend()const{return rend();};

        void swap (vector& other)
        {
            vector tmp(*this);
            *this = other;
            other = tmp;
        }
        
    };


// Non-member comparison operators

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs){
    if (rhs.size() != lhs.size())
        return false;
    for (typename ft::vector<T, Alloc>::size_type i = 0; i < lhs.size(); ++i){
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return !(lhs == rhs);
}

template <class T, class Alloc>
    bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

template <class T, class Alloc>
    bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
        return !(rhs < lhs);
    }

template <class T, class Alloc>
    bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
        return rhs < lhs;
    }

template <class T, class Alloc>
    bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
        return !(lhs < rhs);
    }

template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs){
        lhs.swap(rhs);
    }
};