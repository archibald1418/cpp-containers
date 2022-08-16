#ifndef TREE_H
# define TREE_H

# include "node.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "tree_utils.hpp"
# include "functional.hpp"
# include <memory>
# include <stdexcept>

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
            BaseTree(const value_compare& comp) : traits(comp)
            {
                this->Init();
            };
            BaseTree(node_t*& root){
                if (!root)
                    this->Init();
                else
                    this->root = node_t::clone(*root);
            }
            ~BaseTree(){
                delete root;
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
            bool& isnil(nodeptr& node){
                return node->Isnil();
            }



            node_t* buynode(node_t* new_parent)
            {
                node_t* ptr = _alloc_node.allocate(1);
                
                // Same node for all pointers
                _alloc_ptr.construct(&Left(ptr),   (node_t*)0);
                _alloc_ptr.construct(&Right(ptr),  (node_t*)0);
                _alloc_ptr.construct(&Parent(ptr), new_parent);

                ptr->Isnil() = false;
                // ...
                return ptr; 
            }

            void Init(){
                // Buy null node for root
                root = buynode(NULL); // init parent with NULL
                root->Isnil() = true;
                End() = root;
                Lmost() = root;
                Rmost() = root;
            }
            
            // TODO: coplien form, destructors, allocators(?)
            
            value_compare value_comp() const{
                return this->comp;
            }

            node_t* search(node_t* node, const value_type& key)
            {
                while (node != NULL && node->key != key)
                {
                    if (node->key > key)
                        node = node->left;
                    else
                        node = node->right;
                }
                return node;
            }

            node_t* tree_min(node_t* node){
                while (node->left != NULL)
                    node = node->left;
                return node;
            }  
            node_t* tree_max(node_t* node){
                while (node->right != NULL)
                    node = node->right;
                return node;
            }
            node_t* tree_next(node_t* node){
                // Searching for next item in an ordered sequence

                // Next item is the next greatest to the current item
                // So it's in the right subtree
                if (node->right)
                    return tree_min(node->right);

                // Otherwise go up and search the first parent which is also a left node
                node_t* node_parent = node->parent;
                while (node_parent != NULL and node == node_parent->right){
                    node = node_parent;
                    node_parent = node_parent->parent;
                }
                return node;
            }
            node_t* tree_prev(node_t* node){
                // Same, but searching for rightmost child
                if (node->left)
                    return tree_max(node->left);

                node_t* node_parent = node->parent;
                while (node_parent != NULL and node == node_parent->left){
                    node = node_parent;
                    node_parent = node_parent->parent;
                }
                return node;
            }

            node_t* Insert(const value_type& item)
            {
                node_t* tree_root = static_cast<node_t*>(End());
                node_t* new_node = node_t::create(item, NULL, NULL);
                this->Inserter(new_node);
                return new_node;
            };
            node_t* Inserter(node_t*& new_node)
            {
                if (!root)
                    return (root = new_node);

                node_t* tmproot = End();
                node_t* tmphead = root;
                bool add_left = true;
                (void)add_left;

                while (!tmproot){
                    tmphead = tmproot;
                    add_left = comp(get(new_node), get(tmproot));
                }
                
                
            }

            // node_t* Deleter(const value_type& item){
            //     // throw std::exception("Not Implemented");
            //     // return this->Delete(tree_root, new_node);
            //     (void)item;
            //     return NULL;
            // }

            // Happy tree friends
            template <typename U>
            friend int height(node_t* root);

            template <typename U>
            friend bool is_avl_balanced(node_t* root);

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
        typedef typename __base::node_t                 node_t;
        

        AVLTree(const value_compare& comp) : __base(comp){};
        AVLTree(AVLNode<T>*& root) : __base(root){};

        private:

            node_t* get_node(const value_type& item, 
            node_t* lptr, node_t* rptr)
            {
                return node_t::create(item, lptr, rptr);
            }

            void Insert(node_t*& new_node){
                // int revise_balance_factor = 0; // ????
                (void)new_node;
            }
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



#endif
