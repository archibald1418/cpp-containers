#ifndef TREE_H
# define TREE_H

# include <memory>
# include <stdexcept>
# include <cstdint>

# include "node.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "tree_utils.hpp"
# include "functional.hpp"
# include "utility.hpp"


# define LEFTHEAVY  -1
# define BALANCED   0
# define RIGHTHEAVY 1 


namespace ft{

    template <
    // TODO: extend this to handle mappings (kv pairs with comparators)
        typename T,
        class Alloc = std::allocator<T>, 
        class Predicate = ft::less<T> // value_compare for insertion
    > 
    struct tree_traits
    {
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef Predicate                       value_compare; // oblivious to whether pair is a mapping or not
        typedef Alloc                           allocator_type;
        // typedef Predicate                    key_compare; -> 'set traits'

        value_compare comp; // comparator should be created before it could be called

        tree_traits(value_compare& comp) : comp(comp){};
        tree_traits(){};
        ~tree_traits(){};
    };

        template <
            class T,
            template<typename> class NodeType
        >
    struct BaseTree : public tree_traits<T>
    {
        typedef tree_traits<T>                  traits;
        typedef NodeType<T>                     node_t;
        typedef BaseNode<T, NodeType>           __base_node;
        typedef node_t*                         nodeptr;
        typedef BaseTree<T, NodeType>           tree_t;
        typedef typename traits::value_type     value_type;
        typedef typename traits::value_compare  value_compare;
        typedef value_type                      V;
        typedef std::size_t                     size_type;

        typedef typename traits::allocator_type                             allocator_type;
        typedef typename allocator_type::template rebind<node_t>::other     allocator_node;
        typedef typename allocator_type::template rebind<node_t*>::other    allocator_node_pointer;


        protected:
            nodeptr root;
            nodeptr phony; // placeholder for nodes
        
        protected:
            allocator_node          _alloc_node;
            allocator_node_pointer  _alloc_ptr;
            allocator_type          _alloc;

        public:

            size_type _size;

            BaseTree(const value_compare& comp) : traits(comp),
            _alloc_node(allocator_node()),
            _alloc_ptr(allocator_node_pointer()),
            _alloc(allocator_type())
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
            ~BaseTree(){
                if (!IsPhony(root))
                {
                    nodeptr curr = Lmost();
                    nodeptr next = curr;
                    while (!curr->IsPhony())
                    {
                        next = tree_next(curr);
                        freenode(curr);
                        curr = next;
                    }
                }
                freenode(phony);
                    // freenode(root);
                    // TODO: traverse tree delete nodes separately
            }


            nodeptr& End(){
                return phony;
            }
            nodeptr& Root(){
                return root;
            }
            nodeptr& Begin(){
                return Lmost();
            }
            nodeptr& Lmost(){
                return phony->Left();
            }
            nodeptr& Rmost(){
                return phony->Right();
            }
            nodeptr& Left(nodeptr& node){
                return node->Left();
            }
            nodeptr& Right(nodeptr& node){
                return node->Right();
            }
            nodeptr& Parent(nodeptr& node){
                return node->Parent();
            }
            bool& IsPhony(nodeptr& node){
                return node->IsPhony();
            }
            bool& is_nil(nodeptr& node){
                return IsPhony(node);
            }


            nodeptr buynode(nodeptr new_parent)
            {
                nodeptr ptr = _alloc_node.allocate(1); // FIXME: rebound allocator not working properly, trashes vtable
                // nodeptr ptr = new node_t();
                
                // Same node for all pointers
                _alloc_ptr.construct(&Left(ptr),   phony); 
                _alloc_ptr.construct(&Right(ptr),  phony);
                _alloc_ptr.construct(&Parent(ptr), new_parent);
                ptr->IsPhony() = false;
                ptr->get_balance_factor() = 0;
                // ...
                return ptr;
            }

            void freenode(nodeptr node){
                _alloc_ptr.destroy(&Parent(node));
                _alloc_ptr.destroy(&Right(node));
                _alloc_ptr.destroy(&Left(node));
                _alloc_node.deallocate(node, 1);
                // FIXME: node freeing not working properly
            }

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
                _alloc_node.construct(&Left(phony), nullptr_my);
                _alloc_node.construct(&Right(phony), nullptr_my); 
                _alloc_node.construct(&Parent(phony), nullptr_my);
                phony->IsPhony() = true;

                root = buynode(nullptr_my); // init parent with NULL
                root->IsPhony() = true; // root has no content yet
                Root()  = root; 
                Lmost() = phony;
                Rmost() = phony;
                _size = 0;
            }
            
            bool empty(){
                return (_size == 0);
            }
            size_type size(){
                return _size;
            }
            
            
            // TODO: coplien form, destructors, allocators(?)
            
            value_compare value_comp() const{
                return this->comp;
            }

            nodeptr search(nodeptr node, const value_type& key)
            {
                while (!IsPhony(node) and node->key != key)
                {
                    if (node->key > key)
                        node = node->Left();
                    else
                        node = node->Right();
                }
                return node;
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
                if (IsPhony(node) || node == Rmost())
                    return phony;

                // Next item is the next greatest to the current item
                // So it's in the right subtree
                if (!IsPhony(node->Right()))
                    return tree_min(node->Right());
                // Otherwise go up and search the first parent which is also a left node
                nodeptr node_parent = node->Parent();
                while (!IsPhony(node_parent) and (node == node_parent->Right())){
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

            nodeptr Insert(const value_type& item)
            {
                // Find tree position to insert to insert and return it

                if (empty())
                {
                    root->Set(item);
                    root->IsPhony() = false;
                    _size++;
                    Lmost() = root;
                    Rmost() = root;
                    return root; // return last inserted position
                }
                // if (root->IsPhony())
                //     return this->Inserter(true, root, item); // a tree with one root only node has one leaf

                nodeptr tmproot = Root();
                nodeptr tmphead = tmproot;
                bool add_left = this->comp(item, Get(tmproot));

                while (!tmproot->IsPhony()){
                    tmphead = tmproot;
                    add_left = this->comp(item, Get(tmproot));
                    tmproot = add_left ? Left(tmproot) : Right(tmproot);
                }
                return this->Inserter(add_left, tmphead, item);
            };
            // virtual 
            nodeptr Inserter(bool& add_left, nodeptr& tree_position, const value_type& item)
            {
                nodeptr new_node = buynode(tree_position);
                new_node->Set(item);
                if (add_left) {
                    tree_position->Left() = new_node;
                    if (tree_position == Lmost())
                        Lmost() = new_node;
                } else {
                    tree_position->Right() = new_node;
                    if (tree_position == Rmost())
                        Rmost() = new_node;
                }
                _size++;
                /* 
                ** Balancing logic goes here
                */
               return new_node;
            }
            

            // nodeptr Deleter(const value_type& item){
            //     // throw std::exception("Not Implemented");
            //     // return this->Delete(tree_root, new_node);
            //     (void)item;
            //     return NULL;
            // }

            // Happy tree friends
            template <typename U>
            friend int height(nodeptr root);

            template <typename U>
            friend bool is_avl_balanced(nodeptr root);

            // These functions are essential for balancing,
            // because they need access to protected fields

    };
    
    template <typename T>
    struct AVLTree : public BaseTree<T, AVLNode>
    {
        typedef tree_traits<T>                          traits;
        typedef BaseTree<T, AVLNode>                    __base;
        typedef typename traits::value_compare          value_compare;
        typedef typename traits::value_type             value_type;
        typedef AVLNode<T>                              node_t;
        

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

