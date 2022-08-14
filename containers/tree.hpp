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
        typedef BaseTree<T, NodeType>           tree_t;
        typedef typename traits::value_type     value_type;
        typedef typename traits::value_compare  value_compare;
        typedef value_type                      V;

        protected:
            node_t* root;
        public:
            node_t*& Root(){
                return root->parent;
            }

            void Init(){
                root = node_t::create(V());
                root->Left() = NULL;
                root->Right() = NULL;
                root->Parent() = NULL;
            }

            // TODO: coplien form, destructors, allocators(?)

            BaseTree(const value_compare& comp) : traits(comp)
            {
                Init();
            };
            BaseTree(node_t*& root){
                if (!root)
                    Init();
                else
                    this->root = node_t::clone(*root);
            }
            ~BaseTree(){
                delete root;
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

            node_t* Inserter(const value_type& item)
            {
                node_t* tree_root = static_cast<node_t*>(Root());
                node_t* new_node = node_t::create(item, NULL, NULL);
                this->Insert(tree_root, new_node);
                return new_node;
            };
            void Insert(node_t**& root, node_t**& new_node)
            {
                if (!root)
                    return ;
                (void)new_node;
                // TODO: use comparators for correct insertion
                
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

            void Insert(const T& item){
                node_t* tree_root = static_cast<node_t*>(this->Root());
                node_t* new_node = node_t::create(item, NULL, NULL);

                // int revise_balance_factor = 0; // ????
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
