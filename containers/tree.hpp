#ifndef TREE_H
# define TREE_H

# include <memory>
# include <stdexcept>

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

        typedef typename traits::allocator_type                             allocator_type;
        typedef typename allocator_type::template rebind<node_t>::other     allocator_node;
        typedef typename allocator_type::template rebind<node_t*>::other    allocator_node_pointer;


        protected:
            nodeptr root;
        
        protected:
            allocator_node          _alloc_node;
            allocator_node_pointer  _alloc_ptr;
            allocator_type          _alloc;

        public:

            size_t _size;

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
                else if (other_root->Isleaf())
                    root = other_root; // concatenate two trees
                else {
                    Init();
                    // root->set(other_root->get());
                    // just copy a value, can't grow from middle of tree
                }
            }
            ~BaseTree(){
                freenode(root);
            }


            nodeptr& End(){
                return root->Parent();
            }
            nodeptr& Lmost(){
                return root->Left();
            }
            nodeptr& Rmost(){
                return root->Right();
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
            bool& Isleaf(nodeptr& node){
                return node->Isleaf();
            }



            nodeptr buynode(nodeptr new_parent)
            {
                // nodeptr ptr = _alloc_node.allocate(1); // FIXME: reinded allocator not working properly, trashes vtable
                nodeptr ptr = new node_t();
                
                // Same node for all pointers
                _alloc_ptr.construct(&Left(ptr),   nullptr_my); 
                _alloc_ptr.construct(&Right(ptr),  nullptr_my);
                _alloc_ptr.construct(&Parent(ptr), new_parent);

                ptr->Isleaf() = false;
                // ...
                return ptr;
            }

            void freenode(nodeptr node){
                _alloc_ptr.destroy(&Parent(node));
                _alloc_ptr.destroy(&Right(node));
                _alloc_ptr.destroy(&Left(node));
                _alloc_node.deallocate(node, 1);
            }

            void Init(){
                // Buy null node for root
                root = buynode(nullptr_my); // init parent with NULL
                root->Isleaf() = true;
                End() = root;
                Lmost() = root;
                Rmost() = root;
                _size = 0;
            }
            
            bool empty(){
                return (_size == 0);
            }
            
            // TODO: coplien form, destructors, allocators(?)
            
            value_compare value_comp() const{
                return this->comp;
            }

            nodeptr search(nodeptr node, const value_type& key)
            {
                while (node and node->key != key)
                {
                    if (node->key > key)
                        node = node->left;
                    else
                        node = node->right;
                }
                return node;
            }

            nodeptr tree_min(nodeptr node){
                while (node->left)
                    node = node->left;
                return node;
            }  
            nodeptr tree_max(nodeptr node){
                while (node->right)
                    node = node->right;
                return node;
            }
            nodeptr tree_next(nodeptr node){
                // Searching for next item in an ordered sequence

                // Next item is the next greatest to the current item
                // So it's in the right subtree
                if (node->right)
                    return tree_min(node->right);

                // Otherwise go up and search the first parent which is also a left node
                nodeptr node_parent = node->parent;
                while (node_parent and (node == node_parent->right)){
                    node = node_parent;
                    node_parent = node_parent->parent;
                }
                return node;
            }
            nodeptr tree_prev(nodeptr node){
                // Same, but searching for rightmost child
                if (node->left)
                    return tree_max(node->left);

                nodeptr node_parent = node->parent;
                while (node_parent and node == node_parent->left){
                    node = node_parent;
                    node_parent = node_parent->parent;
                }
                return node;
            }

            nodeptr Insert(const value_type& item)
            {
                // Find tree position to insert to insert and return it

                if (empty())
                {
                    // root->set(item);
                    root->Isleaf();
                    _size++;
                    return nullptr_my;
                }
                // if (root->Isleaf())
                //     return this->Inserter(true, root, item); // a tree with one root only node has one leaf

                nodeptr tmproot = End();
                nodeptr tmphead = root;
                bool add_left = true;

                while (!tmproot->Isleaf()){
                    tmphead = tmproot;
                    add_left = this->comp(item, get(tmproot));
                    tmproot = add_left ? Left(tmproot) : Right(tmproot);
                }
                return this->Inserter(add_left, tmphead, item);
            };
            virtual nodeptr Inserter(bool& add_left, nodeptr& tree_position, const value_type& item)
            {
                nodeptr new_node = buynode(tree_position);
                new_node->setYourMomma(item);
                if (add_left)
                    tree_position->Left() = new_node;
                else
                    tree_position->Right() = new_node;
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
        AVLTree(AVLNode<T>*& root) : BaseTree<T, AVLNode>(root){};

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

