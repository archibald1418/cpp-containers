#ifndef TREE_H
# define TREE_H

# include <memory>
# include <stdexcept>
# include <iostream>
// # include <cstdint>

# include "node.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "tree_utils.hpp"
# include "functional.hpp"
# include "utility.hpp"
# include "stack.hpp"


# define LEFTHEAVY  -1
# define BALANCED   0
# define RIGHTHEAVY 1 


namespace ft{

    template <
        typename T,
		template<typename> class NodeType,
        class Alloc = std::allocator<T>, 
        class Predicate = less<T> // value_compare for insertion
    > 
    struct tree_traits
    {
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef Predicate                       value_compare; // oblivious to whether pair is a mapping or not
        typedef Alloc                           allocator_type;

		typedef BaseNode<T, NodeType>			__base_node;
		typedef	NodeType<T>						node_t;
		typedef node_t*							nodeptr;

        typedef typename allocator_type::template rebind<node_t>::other     allocator_node;
        typedef typename allocator_type::template rebind<node_t*>::other    allocator_node_pointer;

        value_compare comp; // comparator should be created before it could be called

        tree_traits(value_compare& comp) : comp(comp){};
        tree_traits(){};
        ~tree_traits(){};
    };

	
        template <class Traits>
    struct BaseTree : public Traits
    {
        typedef Traits					        traits;
		
		typedef typename traits::__base_node	__base_node;

		typedef typename traits::node_t			node_t;
		typedef typename traits::nodeptr		nodeptr;
        typedef typename traits::value_type     value_type;
        typedef typename traits::value_compare  value_compare;
        /* typedef NodeType<T>                     node_t; */
        /* typedef node_t*                         nodeptr; */

        typedef value_type                      V;
        typedef std::size_t                     size_type;

        typedef typename traits::allocator_type                             allocator_type;
		typedef typename traits::allocator_node								allocator_node;
		typedef typename traits::allocator_node_pointer						allocator_node_pointer;
        /* typedef typename allocator_type::template rebind<node_t>::other     allocator_node; */
        /* typedef typename allocator_type::template rebind<node_t*>::other    allocator_node_pointer; */


        protected:
            nodeptr root;
            nodeptr phony; // placeholder for nodes
			nodeptr lmost;
			nodeptr rmost;

			// functional singly-linked 'end' node for reverse iterator
			nodeptr n_rbegin;	
			// his parent is rmost, rmost doesn't know about him
			// deref is undefined
			// children are null
			// can do -- to rmost: rmost has no children so it will be prev

        
        protected:
            allocator_node          _alloc_node;
            allocator_node_pointer  _alloc_ptr;
            allocator_type          _alloc;

        public:

            size_type _size;
			value_compare comp;

            BaseTree(const value_compare& comp, const allocator_type& alloc = allocator_type()) :
            _alloc_node(allocator_node()),
            _alloc_ptr(allocator_node_pointer()),
            _alloc(alloc),
	    comp(comp)
            {
                Init();
            };
            BaseTree(nodeptr& other_root){
                if (!other_root) {
                    Init();
                    other_root = root; // incoming pointer now points to root
                }
                else if (other_root->IsPhony())
                    root = other_root; // concatenate two trees
                else {
                    Init();
                    // root->set(other_root->get());
                    // just copy a value, can't grow from middle of tree
                }
            }
            BaseTree(const BaseTree& other){
                if (this == &other)
                    return *this;
                *this = other;
                return *this;
            }
			static void swap_nodes(nodeptr& a, nodeptr& b){
				nodeptr tmp = a;
				a = b;
				b = tmp;
			}
			void	swap_tree(BaseTree& other){
				swap_nodes(Root(), other.Root());
				swap_nodes(Lmost(), other.Lmost());
				swap_nodes(Rbegin(), other.Rbegin());
				swap_nodes(phony, other.phony);
			}
            BaseTree& operator=(const BaseTree& other){
               _alloc_node = other._alloc_node;
               _alloc = other._alloc;
               _size = other._size;
               _alloc_ptr = other._alloc_ptr;
               // deepcopy root and phony
            }

			// Destructor
            virtual ~BaseTree(){
                if (empty()){
					std::cout << "destroying root" << std::endl;
					freenode(n_rbegin);
				}
				else 
				{
					ft::stack<nodeptr> S;
					/*
					 *should go post-order, since reads from dead parents
					* OR USE STACK (allows to avoid deleted nodes)
					 * */		
					nodeptr curr = root;
					nodeptr right;
					while (!IsPhony(curr) || !S.empty())
					{
						while (!IsPhony(curr))
						{
							S.push(curr);
							curr = curr->Left();
						}
						curr = S.top();
						right = curr->Right();
						S.pop();
						freenode(curr);
						curr = right;
					}
				}
				freenode(phony);
				/* freenode(n_rbegin); */
			}

    // Tree parameter nodes
            nodeptr& End(){
                return n_rbegin;
            }
            nodeptr& Rbegin(){
                return n_rbegin; // another end, which supports operator--
            }
            nodeptr& Root(){
                return root;
            }
            nodeptr& Begin(){
                return Lmost();
            }
            nodeptr& Lmost(){
                return lmost;
            }
            nodeptr& Rmost(){
                return rmost;
            }

    //  Node getters
            static nodeptr& Left(nodeptr& node){
                return node->Left();
            }
            static nodeptr& Right(nodeptr& node){
                return node->Right();
            }
            static nodeptr& Parent(nodeptr& node){
                return node->Parent();
            }

    // Null node checks
            static bool& IsPhony(nodeptr& node){
                return node->IsPhony();
            }
            static bool IsNotPhony(nodeptr& node){
                return !IsPhony(node);
            }
            static bool& is_nil(nodeptr& node){
                return IsPhony(node);
            }
            static bool& is_not_nil(nodeptr& node){
                return !is_nil(node);
            }
            static bool& IsLeaf(nodeptr& node){
                return IsPhony(Right(node)) && IsPhony(Left(node));
            }
            static bool& IsNotLeaf(nodeptr& node){
                return !IsLeaf(node);
            }

    // Create node
            nodeptr buynode(nodeptr new_parent)
            {
                nodeptr ptr = _alloc_node.allocate(1);
                
                // Same node for all pointers
                _alloc_ptr.construct(&Left(ptr),   phony); 
                _alloc_ptr.construct(&Right(ptr),  phony);
                _alloc_ptr.construct(&Parent(ptr), new_parent);
                ptr->IsPhony() = false;
                ptr->get_balance_factor() = 0;
                // ...
                return ptr;
            }

            void freenode(nodeptr& node){
				std::cout << "deleting ..." << node->Get() << "...\n";
                _alloc_ptr.destroy(&Parent(node));
                _alloc_ptr.destroy(&Right(node));
                _alloc_ptr.destroy(&Left(node));
                _alloc_node.deallocate(node, 1);
                
                node = nullptr_my;
            }

			// Function for hard-replacing node content
			void	Replace(nodeptr& where, const value_type& what){
				_alloc.destroy(&where->Get());
				_alloc.construct(&where->Get(), what);
			}


    // Tree initializers
            void Init()
            {
                /* 
                        >>>>> shared phony node instead of null pointers <<<<

                            null                        phony                     
                             |                           |
                           phony          ->           root
                        /         \                  /        \
                    null             null        phony          phony
                */
                phony = _alloc_node.allocate(1); // init parent with NULL
				_alloc_node.construct(phony, value_type());
                _alloc_ptr.construct(&Left(phony), nullptr_my);
                _alloc_ptr.construct(&Right(phony), nullptr_my); 
                _alloc_ptr.construct(&Parent(phony), nullptr_my);
                phony->IsPhony() = true;

                root = buynode(phony); // init parent with phony
                root->IsPhony() = true; // root has no content yet
                Root()  = root; 
                Lmost() = phony;
                Rmost() = phony;
                _size = 0;

				// init rbegin
                n_rbegin = _alloc_node.allocate(1);
                _alloc_ptr.construct(&Left(n_rbegin), phony);
                _alloc_ptr.construct(&Right(n_rbegin), phony); 
                _alloc_ptr.construct(&Parent(n_rbegin), Rmost());
                n_rbegin->IsPhony() = false; // should support operator--
            }


            bool empty(){
                return (_size == 0);
            }
            size_type size(){
                return _size;
            }
            
            
            value_compare value_comp() const{
                return this->comp;
            }

    // Tree traversals
            nodeptr search(nodeptr begin, const value_type& item)
            {
                while (!IsPhony(begin) && begin->Get() != item)
                {
                    if (begin->Get() > item)
                        begin = begin->Left();
                    else
                        begin = begin->Right();
                }
                return begin;
            }

            nodeptr tree_min(nodeptr node){
                while (!IsPhony(node->Left()))
                    node = node->Left();
                return node;
            }  
            nodeptr tree_max(nodeptr node){
                while (!IsPhony(node->Right()))
                    node = node->Right();
                return node;
            }
            nodeptr tree_next(nodeptr node){
                // Searching for next item in an ordered sequence
                std::cout << "entered tree next" << std::endl;
                if (IsPhony(node) || node == Rmost())
                    return phony;

                std::cout << "check right node" << std::endl;
                // Next item is the next greatest to the current item
                // So it's in the right subtree
                if (!IsPhony(node->Right()))
                    return tree_min(node->Right());
                std::cout << "checked right node" << std::endl;
                // Otherwise go up and search the first parent which is also a left node
                nodeptr node_parent = node->Parent();
                std::cout << "finding next node" << std::endl;
                while (!IsPhony(node_parent) and (node == node_parent->Right())){
                    std::cout << "next" << std::endl;
                    node = node_parent;
                    node_parent = node_parent->Parent();
                }
                return node_parent;
            }
            nodeptr tree_prev(nodeptr node){
                if (IsPhony(node) || node == Lmost())
                    return phony;

                // Same, but searching for rightmost child
                if (!IsPhony(node->Left()))
                    return tree_max(node->Left());

                nodeptr node_parent = node->Parent();
                while (!IsPhony(node_parent) and node == node_parent->Left()){
                    node = node_parent;
                    node_parent = node_parent->Parent();
                }
                return node_parent;
            }

// ---------- Insertion -------------

            nodeptr Insert(const value_type& item)
            {
                // Find tree position to insert to insert and return it

                if (empty())
                {
                    /* root->Set(item); */
					Replace(root, item);
                    root->IsPhony() = false;
                    _size++;
                    Lmost() = root;
                    Rmost() = root;

					End()->Parent() = Rmost();
					Rmost()->Right() = End();

                    return root; // return last inserted position
                }

                nodeptr tmproot = Root();
                nodeptr tmphead = tmproot;
                bool add_left = this->comp(item, Get(tmproot));

                while (!tmproot->IsPhony() && tmproot != End()){
                    tmphead = tmproot;
                    add_left = this->comp(item, Get(tmproot));
                    tmproot = add_left ? Left(tmproot) : Right(tmproot);
                }
                return this->Inserter(add_left, tmphead, item);
            };
            nodeptr Inserter(bool& add_left, nodeptr& tree_position, const value_type& item)
            {
                nodeptr new_node = buynode(tree_position);
                /* new_node->Set(item); */
				Replace(new_node, item);
                if (add_left)
                {
                    tree_position->Left() = new_node;
                    if (tree_position == Lmost())
                        Lmost() = new_node;
                } else {
                    tree_position->Right() = new_node;
                    if (tree_position == Rmost()){
                        Rmost() = new_node;

						End()->Parent() = Rmost();
						Rmost()->Right() = End();
					}
                }
                _size++;

                    /*
                    ** 
                            Balancing logic goes here
                    **
                    */
               return new_node;
            }
            

// ---------- Deletion -------------


            nodeptr Delete(const value_type& item)
            {
            	nodeptr node = search(Root(), item);
			   	if (is_nil(node))
			   		return node;
				return this->Deleter(node);
            }

            void shift_nodes(nodeptr& x, nodeptr& y)
            {
				/* bool islmost = (x == Lmost()); */
				/* bool isrmost = (x == Rmost()); */
				if (x == Lmost()){ 
					Lmost() = y;
					
				}				
				/* if (x == Rmost()){ */
				/* 	Rmost() = y; */
				/* 	End()->Parent() = Rmost(); */
				/* } */

                nodeptr& parentx = Parent(x);
                nodeptr& left_child = parentx->Left();
                nodeptr& right_child = parentx->Right();
                if (IsPhony(parentx)){
                    this->root = y;
                }
                else if (x == left_child)
                    left_child = y;
                else
                    right_child = y;
                
                if (IsNotPhony(y))
                    Parent(y) = parentx;
				/* if (islmost == true) */
				/* 	Lmost() = parentx; */
				/* if (isrmost == true){ */
				/* 	Rmost() = parentx; */
				/* 	End()->Parent() = Rmost(); */
				/* } */
                // NOTE: after the 'shift', node 'x' is knocked out of the tree
            }

            nodeptr Deleter(nodeptr& node)
            { // REVIEW: check all kinds of trees against this

				
				/* if (node == Lmost()){ */
				/* 	shift_nodes(node, node->Parent()); */
				/* 	/1* Lmost() = node->Parent(); *1/ */
				/* } */
				if (IsPhony(Left(node))){
                    shift_nodes(node, node->Right());
                }
                else if (IsPhony(Right(node))){
                    shift_nodes(node, node->Left());
                } else {
                    nodeptr next = tree_next(node);
                    if (Parent(next) != node){ // If successor is not an immediate child
                        // do a proper swap
                        shift_nodes(next, next->Right());
                        next->Right() = node->Right(); // this is a proper swap, so we should patch the links after shift_nodes is called
                        Parent(next->Right()) = next;
                        // the successor is raised next to the to-be-deleted node
                    }
                    shift_nodes(node, next); 
                    next->Left() = node->Left();
                }
                freenode(node); // DEBUG: can I safely delete the node? (should be ok)
		        node = phony;
				_size--;
				if (_size == 0)
					Lmost() = End();
                return phony;
            }

            // Happy tree friends
            template <typename U>
            friend int height(nodeptr root);

            template <typename U>
            friend bool is_avl_balanced(nodeptr root);

            // These functions are essential for balancing,
            // because they need access to protected fields

    };

	
    

    template <typename T>
    struct AVLTree : public BaseTree<tree_traits<T, AVLNode> >
    {
        typedef tree_traits<T, AVLNode>                 traits;
        typedef BaseTree<traits>                    	__base;
        typedef typename traits::value_compare          value_compare;
        typedef typename traits::value_type             value_type;
        typedef typename traits::node_t					node_t;
        

        AVLTree(const value_compare& comp) : __base(comp){};
        AVLTree() : __base(){};
        AVLTree(AVLNode<T>*& root) : __base(root){};
        virtual ~AVLTree(){};

        private:

            node_t* get_node(const value_type& item, 
            node_t* lptr, node_t* rptr)
            {
                return node_t::create(item, lptr, rptr);
            }

            // void Insert(node_t*& new_node){
            //     // int revise_balance_factor = 0; // ????
            //     (void)new_node;
            // }
            // void Delete(const T& item){
            //     (void)item;
            // }

        // Rotations
            // int reviseBalanceFactor = 0; // flag for height-fixing
            
            void SingleRotateLeft (node_t* &p);
            void SingleRotateRight (node_t* &p);
            void DoubleRotateLeft (node_t* &p);
            void DoubleRotateRight (node_t* &p);
            void UpdateLeftTree (node_t* &tree,  int &reviseBalanceFactor);
            void UpdateRightTree (node_t* &tree, int &reviseBalanceFactor);
    };

	

}


#endif // TREE_H

