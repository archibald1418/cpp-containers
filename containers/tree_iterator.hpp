#ifndef TREE_ITERATOR_H
# define TREE_ITERATOR_H

# include "iterator.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft{

    template <class T, class NodeType>
        struct tree_iterator : public iterator<bidirectional_iterator_tag, T>
        {
            typedef iterator<bidirectional_iterator_tag, T>         __base;
            typedef typename __base::__baseator_category		    itereator_category;
			typedef typename __base::value_type				        value_type;
			typedef typename __base::difference_type		        difference_type;
			typedef typename __base::pointer				        pointer;
			typedef typename __base::reference				        reference;

            typedef tree_node_types<NodeType*, T>                   node_types;
        /*
            NOTE: 
            stl here does some crpytic voidptr->valueptr pointer rebinds
            to keep compatibility with smart pointers 
        */
            typedef typename        node_types::node_type               node_type;
            typedef typename        node_types::node_value_type         node_value_type;
            typedef typename        node_types::const_node_value_type   const_node_value_type;           

            protected:
                pointer _it;
            
            public:
            // Ctors
                tree_iterator(): _it(0){};
                tree_iterator(pointer ptr) : _it(ptr){};
                template <typename Iter>
                tree_iterator(const tree_iterator<Iter>& src,
				typename enable_if<!is_integral<Iter>::value>::type* = 0) : _it(src.base()){};
            // Dtor
                virtual ~tree_iterator(){};

            public:
                tree_iterator(void){
                    _it = NULL;
                }

                tree_iterator(pointer ptr) : _it(ptr) {}

                tree_iterator(const tree_iterator& x){
                    _it = x._it;
                }

                ~tree_iterator() {}

                // Member operators

                tree_iterator& operator=(const tree_iterator& x){
                    if (this == &x)
                        return *this;
                    _it = x._it;
                    return *this;
                }

                tree_iterator& operator++(){
                    Inc();
                    return *this;
                }

                tree_iterator operator++(int){	
                    tree_iterator temp = *this;
                    ++*this;
                    return temp;
                }

                tree_iterator& operator--(){
                    Dec();
                    return *this;
                }

                tree_iterator operator--(int){ 
                    tree_iterator temp = *this;
                    --*this;
                    return temp;
                }
			
                reference& operator*(){
                    return _it->_value;
                }

                const reference& operator*() const{
                    return _it->_value;
                }

                pointer operator->(){
                    return &**this;
                }

                const pointer operator->() const {
                    return &**this;
                }

		        bool operator==(const tree_iterator& x){
                    return _it == x._it;
                }
		        
                bool operator!=(const tree_iterator& x){
                    return !(_it == x._it);
                }

                pointer	base() const{
                    return _it;
                }

            // Traversals
                void Dec()
                {
                    if (_it->IsPhony())
                        _it = _it->Right();
                    else if (!_it->Left()->IsPhony())
                        _it = Max(_it->Left();
                    else {
                        pointer tmp;
                        while(!((tmp = _it->Parent())->IsPhony()) && _it == tmp->Left())
                            _it = tmp;
                        if (!tmp->IsPhony())
                            _it = tmp;
                    }
                }

                void Inc()
                {
                    if (_it->IsPhony()) { ; }
                    else if (!_it->Right()->IsPhony())
                        _it = Min(_it->Right());
                    else {
                        pointer tmp;
                        while(!((tmp = _it->Parent())->IsPhony()) && _it == tmp->Right())
                            _it = tmp;
                        _it = tmp;
                    }
                }

                static pointer Max(pointer ptr) 
                {
                    while (!ptr->Right()->IsPhony())
                        ptr = ptr->Right();
                    return ptr;
                }

                static pointer Min(pointer ptr)
                {
                    while (!ptr->Left()->IsPhony())
                        ptr = ptr->Left();
                    return ptr;
                } 
            };
    
}

#endif // TREE_ITERATOR_H