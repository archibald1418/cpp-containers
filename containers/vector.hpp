#include "iterator.hpp"
#include "utility.hpp"
#include <cstdint>

namespace ft
{

    typedef int8_t byte;

    template <typename T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        // Member types
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;

        // Iterator types
        typedef RAIterator<pointer> iterator;
        typedef RAIterator<const_pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        allocator_type _alloc;
        size_type _cap;
        size_type _size;
        pointer _first;
        /* 
            REVIEW:
            pointer _end;    will accelerate many low-level functions instead of hopping to end() 
        */

        iterator __make_iter(pointer __p)
        {
            return iterator(__p);
        }
        const_iterator __make_iter(const_pointer __p) const
        {
            return const_iterator(__p);
        }

        void    __move_range(pointer from_s, pointer from_e, pointer to){
            pointer old_last = _first + _size;
            difference_type n = old_last - to;
            pointer i = from_s + n;
            pointer pos;
            if ((to - from_s) >= 0)
                for (pos = i; pos >= from_s; pos--)
                {
                    _alloc.construct(&pos[1], T(*pos));
                }
            else 
                // REVIEW: not tested for deletion case
                for (pos = from_s; pos <= from_e; pos++)
                {
                    _alloc.construct(&pos[-1], T(*pos));
                }
        }

        

    public:
        size_type max_size() const
        {
            /*
            This value typically reflects the theoretical limit on the size of the container,
            -- at most std::numeric_limits<difference_type>::max() --
            */
            return std::min<size_type>(
                _alloc.max_size(),
                std::numeric_limits<difference_type>::max());
        }

        size_type size() const
        {
            return _size;
        }

        size_type capacity() const
        {
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
            // T* newarr = new T[n]; // Calls default constructor n times - too expensive, objects may be large
            // this is bad, objects might be enormous or resource-hungry (mutex, connection etc or a big object)
            // T* newarr = reinterpret_cast<T*>(new byte[n * sizeof(T)]); // 1 * n * sizeof bytes

            /*
                Doing reinterpret_cast is a risky procedure with limited contexts.
                Abusing r_cast can lead to inconsistent memory handling, such as comparing pointers of different types,
                which reeks of UB.
            */
            pointer newarr = _alloc.allocate(new_cap); /* Raises std::bad_alloc if allocation fails */
            size_type i = 0;
            try
            {
                for (; i < _size; ++i)
                {
                    _alloc.construct(newarr + i, *(_first + i)); // does the same placement-new call
                    // new (newarr + i) T(_first[i]); // placement-new syntax; new [address] object
                    // --- newarr[i] = arr[i]; ---
                    /* with reint_cast last line would be UB
                    newarr[i] has no object, just bare memory
                    */
                }
            }
            catch (const std::exception &e)
            {
                size_type j = 0;
                for (; j < i; ++j)
                {
                    // (newarr + i)->~T(); // backwards loop for garbage collection
                    _alloc.destroy(newarr + j);
                    // Dtors in c++ are no-throw guarantee
                    // It's on the destructor's side to catch errors before they rise up the stack
                }
                std::cout << "Error:" << e.what() << '\n'
                          << "Deallocating array" << '\n';
                // delete[] reinterpret_cast<byte*>(newarr);
                _alloc.deallocate(newarr, j);
                throw; // rethrow to next
            }
            for (size_type i = 0; i < _size; ++i)
            {
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

        void resize(size_type n, const_reference value = T())
        { // T  either DefaultConstructible or CopyInsertible ('placement new'-constructible)
            try
            {
                if (n > this->_cap)
                    reserve(n);
            }
            catch (...)
            {
                return; // Strong guarantee (=no effect)
            }
            if (n > _size)
            {
                for (size_type i = _size; i < n; ++i)
                    _alloc.construct(_first + i, T(value));
                // new (_first + i) T(value); // ctor might throw an error! + redundant heap call
            }
            else if (n < _size)
            {
                for (size_type i = n; i < _size; ++i)
                    _alloc.destroy(_first + i);
            }
            _size = n;
        }

        void push_back(const_reference value)
        {
            const T& copy = T(value);
            try
            {
                if (_cap == 0 && _size == 0)
                {
                    reserve(1);
                }
                else if (_cap == _size)
                {
                    reserve(2 * _size);
                }
            }
            catch (...){throw;};
            // new (_first + _size) T(value);
            _alloc.construct(_first + _size, copy);
            ++_size;
        }

        void pop_back()
        {
            if (empty())
                return;
            _alloc.destroy(_first + _size - 1);
            --_size;
        }

        /* Exception safety:
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
        reference operator[](size_type i)
        {
            return *(_first + i);
        }

        const_reference operator[](size_type i) const
        {
            return *(_first + i);
        }

        const_reference at(size_type i) const
        {
            if (i >= _size)
                throw std::out_of_range("Index out of range");
            // every []-defined container has .at, which throws an error
            return _first[i];
        }

        reference at(size_type i)
        {
            if (i >= _size)
                throw std::out_of_range("Index out of range");
            return _first[i];
        }

        size_type size()
        {
            return this->_size;
        }
        size_type capacity()
        {
            return this->_cap;
        }

        // Front and Back
        reference front()
        {
            return _first[0];
        }
        const_reference front() const
        {
            return _first[0];
        }

        bool empty() const
        {
            return (_size == 0);
        }

        reference back()
        {
            if (empty())
                return _first[0]; // UB
            return _first[_size - 1];
        }
        const_reference back() const
        {
            if (empty())
                return _first[0];
            return _first[_size - 1];
        }

        pointer data()
        {
            return _first;
        }

        // explicit means 'No, compiler! No arguments means this ctor is called, don't second-guess'
        explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _cap(0), _size(0), _first(NULL) {}
        explicit vector(size_type size,
                        const value_type &value = value_type(),
                        const allocator_type &alloc = allocator_type())
            : _alloc(alloc), _cap(size), _size(size)
        {
            _first = _alloc.allocate(_cap);
            for (size_type i = 0; i < size; i++)
                _alloc.construct(_first + i, T(value));
        }

        // Range constructor. Leveraging SFINAE to distinguish from previous version
        template <typename InputIt>
        vector(InputIt first,
               typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last,
               const allocator_type &alloc = allocator_type())
            : _alloc(alloc)
        {
            _size = static_cast<size_type>(last - first);
            _cap = _size;
            _first = _alloc.allocate(_cap);
            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(_first + i, T(first[i]));
        }

        // Copy constructor
        vector(const vector &other)
            : _alloc(other._alloc), _cap(other._size), _size(other._size), _first(NULL)
        {
            // cap := size when copying (STL vector allocates _size number of objects)
            _first = _alloc.allocate(_cap);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(_first + i, T(other._first[i]));
        }

        // Destructor
        ~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_first + i);
            if (_cap)
                _alloc.deallocate(_first, _cap);
        }

        allocator_type get_allocator() const
        {
            return (_alloc);
        }

        iterator erase(iterator pos)
        {
            if (not(begin() <= pos && pos <= end()))
                return (0); // not found in vector
            // no behaviour defined for pos == end()
            iterator it = begin();
            size_type del_index = 0;
            // REVIEW: try rewriting with __move_range
            while (it != pos)
            {
                ++it;
                ++del_index;
            }
            _alloc.destroy(_first + del_index);
            --_size;
            // pulling the vector parts to the left
            size_type insert_index = del_index;
            while (insert_index < _size)
            {
                _first[insert_index] = _first[insert_index + 1];
                ++insert_index;
            }

            // destroy extra bit of T typed memory, left after resizing
            _alloc.destroy(_first + _size);
            return begin() + del_index; // return new position
        }

        iterator erase(iterator first, iterator last)
        {
            if ( 
                not(begin() <= first &&
                    first <= last &&
                    last <= end()))
                return (0);
            if (first == last)
                return (last); // empty range

            bool isEnd = (last == end());

            // REVIEW: try rewriting with __move_range

            size_type len = last - first; // guaranteed to be > 0
            _size -= len;

            // Delete elems
            for (size_type i = 0; i < len; i++)
                _alloc.destroy(&first[i]);
            if (isEnd)
                return (last); // No moving required

            // Move elems
            size_type j = first - begin();
            for (size_type i = 0; i < _size; ++i)
                first[i] = T(_first[j + i + len]);
            return last - len;
        }

        void clear()
        {
            for (iterator it = begin(); it < end(); ++it)
            {
                _alloc.destroy(&(*it));
                // it->~value_type();
            }
            _size = 0;
        }

        void assign(size_type count, const T &value)
        {
            if (count > max_size())
            {
                throw std::length_error(
                    "ft::vector<T, Alloc>::assign(size_type count, const T& value) 'count' exceeds maximum supported size");
            }
            if (!empty())
                clear();
            if (_cap < count)
                reserve(count);
            for (size_type i = 0; i < count; i++)
                _alloc.construct(_first + i, T(value));
            _size = count;
        }

        // SFINAE overload to account for vector<:integral_type:> cases
        template <typename InputIt>
        void assign(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type isIterator = InputIt())
        {
            (void)isIterator;

            size_type len = static_cast<size_type>(last - first);
            if (len > max_size())
            {
                throw std::length_error(
                    "ft::vector<T, Alloc>::assign(InputIt first, InputIt last) iterator difference exceeds maximum supported size");
            }
            if (_size > 0)
                clear();
            size_type new_size = len;
            if (_cap < new_size)
                reserve(new_size);
            while (_size < new_size)
            {
                _alloc.construct(_first + _size, T(*first));
                _size++;
                ++first;
            }
        }

        vector &operator=(const vector &other)
        {
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
        // Direct iterators
        iterator begin() { return iterator(_first); };
        const_iterator begin() const { return const_iterator(_first); };
        const_iterator cbegin() const { return const_iterator(_first); };

        iterator end() { return iterator(_first + _size); };
        const_iterator end() const { return const_iterator(_first + _size); };
        const_iterator cend() const { return const_iterator(_first + _size); };

        // Reverse iterators
        reverse_iterator rbegin() { return reverse_iterator(end()); };
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); };

        reverse_iterator rend() { return reverse_iterator(begin()); };
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };
        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); };

        void swap(vector &other)
        {
            vector tmp(*this);
            *this = other;
            other = tmp;
        }

        // TODO: rewrite this with call to another insert (with size_type n)
        iterator insert(iterator pos, const T& value){
            bool isEnd = (pos == end());
            size_type offset = pos - begin();
            size_type roffset = end() - pos;
            push_back(value);
            if (isEnd)
                return begin() + offset;
            pointer position = _first + offset;
            pointer old_end = position + roffset;
            const T& value_copy = T(end()[-1]);
            __move_range(position, old_end, position + 1);
            begin()[offset] = value_copy;
            return begin() + offset;
        }  
    };

    // Non-member comparison operators

    template <class T, class Alloc>
    bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        if (rhs.size() != lhs.size())
            return false;
        for (typename ft::vector<T, Alloc>::size_type i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }

    template <class T, class Alloc>
    bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
};