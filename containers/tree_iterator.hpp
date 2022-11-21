#ifndef TREE_ITERATOR_H
# define TREE_ITERATOR_H

# include "iterator.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft{

    template <class T, class NodeType>
        struct tree_iterator : public iterator<bidirectional_iterator_tag, NodeType>
        {
            typedef iterator<bidirectional_iterator_tag, T>  __base;
			// 

            typedef typename __base::iterator_category		    	iterator_category;
			typedef typename __base::value_type						value_type;
			typedef typename __base::pointer				        pointer;
			typedef const pointer				    				const_pointer;
			typedef typename remove_const<T>::type&				    reference;
			typedef const T											const_value_type;
			typedef const T&										const_reference;

            typedef tree_node_types<NodeType*, value_type>          node_types;
        /*
            NOTE: 
            stl here does some crpytic voidptr->valueptr pointer rebinds
            to keep compatibility with smart pointers 
        */
            typedef typename        node_types::node_type               node_type;
            typedef typename        node_types::node_value_type         node_value_type;
            typedef typename        node_types::const_node_value_type   const_node_value_type;           
				
			/*
			 *TODO: test these typedefs ^ especially tree_node_types
			 * */	

            protected:
                node_type* _it;
            
            public:
            // Ctors
                tree_iterator(): _it(0){};
                tree_iterator(node_type* ptr) : _it(ptr){};
                /* tree_iterator(const tree_iterator& src) : _it(src.base()){}; */

            // Dtor
                virtual ~tree_iterator(){};

            public:

                tree_iterator(const tree_iterator& x){
                    _it = x._it;
                }


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
			
                reference operator*(){
                    return _it->Get();
                }

                const_reference operator*() const{
                    return _it->Get();
                }

                pointer operator->(){
                    return &**this;
                }

                const_pointer operator->() const {
                    return &**this;
                }

		        bool operator==(const tree_iterator& x){
                    return _it == x._it;
                }
		        
                bool operator!=(const tree_iterator& x){
                    return !(_it == x._it);
                }

                node_type*	base() const{
                    return _it;
                }

            // Traversals
                void Dec()
                {
				/* TODO: test this */
                    if (_it->IsPhony()) {return ;}
                        /* _it = _it->Right(); // DEBUG: will it stop the other way round? */
                    else if (!_it->Left()->IsPhony())
                        _it = Max(_it->Left());
                    else {
                        node_type* tmp;
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
                        node_type* tmp;
                        while(!((tmp = _it->Parent())->IsPhony()) && _it == tmp->Right())
                            _it = tmp;
                        _it = tmp;
                    }
                }

                static node_type* Max(node_type* ptr) 
                {
                    while (!ptr->Right()->IsPhony())
                        ptr = ptr->Right();
                    return ptr;
                }

                static node_type* Min(node_type* ptr)
                {
                    while (!ptr->Left()->IsPhony())
                        ptr = ptr->Left();
                    return ptr;
                } 
            };
    
	template<class T, class NodeType>
        class const_tree_iterator : public ft::iterator<bidirectional_iterator_tag, NodeType>
        {
            public:
				typedef iterator<bidirectional_iterator_tag, T>         __base;

				typedef typename __base::iterator_category		    iterator_category;
				typedef typename __base::value_type				        value_type;
				typedef typename __base::difference_type		        difference_type;
				typedef typename __base::pointer				        pointer;
				typedef typename __base::reference				        reference;

				typedef tree_node_types<NodeType*, value_type>          node_types;

				typedef typename        node_types::node_type               node_type;
				typedef typename        node_types::node_value_type         node_value_type;
				typedef typename        node_types::const_node_value_type   const_node_value_type;           
				//TODO: const_node_value_type check

                // Constructors

                const_tree_iterator(void)
                {
                    _ptr = nullptr_my;
                }

                const_tree_iterator(node_type* ptr) : _ptr(ptr) {}

				// NOTE: !!! This constructor makes non-const iterator compatible!
                const_tree_iterator(const tree_iterator<value_type, node_type>& x)
                {
                    _ptr = x._ptr;
                }

                /* const_tree_iterator(const tree_iterator<value_type, node_type>& x) */
                /* { */
                /*     _ptr = x.base(); */
                /* } */

                ~const_tree_iterator() {}

                // Member operators

                const_tree_iterator &operator=(const const_tree_iterator& x)
                {
                    if (this != &x)
                    {
                        _ptr = x._ptr;
                    }
                    return *this;
                }

                const_tree_iterator& operator++()
                {
                    Inc();
                    return *this;
                }

                const_tree_iterator operator++(int)
                {	
                    const_tree_iterator temp = *this;
                    ++*this;
                    return temp;
                }

                const_tree_iterator& operator--()
                {
                    Dec();
                    return *this;
                }

                const_tree_iterator operator--(int)
                { 
                    const_tree_iterator temp = *this;
                    --*this;
                    return temp;
                }
			
                reference& operator*()
                {
                    return _ptr->_value;
                }

                const reference& operator*() const
                {
                    return _ptr->_value;
                }

                pointer operator->()
                {
                    return &**this;
                }

                const pointer operator->() const 
                {
                    return &**this;
                }

		        bool operator==(const const_tree_iterator& x)
                {
                    return _ptr == x._ptr;
                }
		        
                bool operator!=(const const_tree_iterator& x)
                {
                    return !(_ptr == x._ptr);
                }

                node_type*	base() const
                {
                    return _ptr;
                }

		    protected:
			    node_type*	_ptr;

                void Dec()
                {
                    if (_ptr->_isnil)
                        _ptr = _ptr->_right;
                    else if (!_ptr->_left->_isnil)
                        _ptr = Max(_ptr->_left);
                    else {
                        node_type* tmp;
                        while(!((tmp = _ptr->_parent)->_isnil) && _ptr == tmp->_left)
                            _ptr = tmp;
                        if (!tmp->_isnil)
                            _ptr = tmp;
                    }
                }

                void Inc()
                {
                    if (_ptr->_isnil) { ; }
                    else if (!_ptr->_right->_isnil)
                        _ptr = Min(_ptr->_right);
                    else {
                        node_type* tmp;
                        while(!((tmp = _ptr->_parent)->_isnil) && _ptr == tmp->_right)
                            _ptr = tmp;
                        _ptr = tmp;
                    }
                }

                static node_type* Max(node_type* ptr) 
                {
                    while (!ptr->_right->_isnil)
                        ptr = ptr->_right;
                    return ptr;
                }

                static node_type* Min(node_type* ptr)
                {
                    while (!ptr->_left->_isnil)
                        ptr = ptr->_left;
                    return ptr;
                }
        };	
}

#endif // TREE_ITERATOR_H
