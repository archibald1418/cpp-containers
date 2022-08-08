#ifndef TREE_H
# define TREE_H

# include "node.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "tree_utils.hpp"

# define LEFTHEAVY  -1
# define BALANCED   0
# define RIGHTHEAVY 1 


namespace ft {

        template <class Node>
    struct tree_traits{
        typedef Node                            node_t;
        typedef typename node_t::pointer        node_pointer;
        typedef typename node_t::value_type     value_type;
    };

        template <class T, template<typename> class NodeType>
    struct BaseTree{

        typedef tree_traits< NodeType<T> >      traits;
        typedef BaseTree<T, NodeType>           tree_t;
        typedef typename traits::node_t         node_t;
        typedef typename traits::node_pointer   node_pointer;
        typedef typename traits::value_type     value_type;

        node_t* root;
        
        // TODO: coplien form, destructors, allocators(?)


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

        virtual void Insert(const value_type& item) = 0;
        virtual void Delete(const value_type& iterm) = 0;


    // Happy tree friends
    template <typename U>
    friend int height(NodeType<U>* root);

    template <typename U>
    friend bool is_avl_balanced(AVLNode<U>* root);

    // These functions are essential for balancing,
    // because they need access to protected fields

    };

    
    template <typename T>
    struct AVLTree : public BaseTree<T, AVLNode>{
        
        typedef Tree<T, AVLNode>                BaseTree;
        typedef tree_traits< AVLNode<T> >       traits;
        
        typedef typename traits::node_t         node_t;
        typedef typename traits::node_pointer   node_pointer;
        typedef typename traits::value_type     value_type;
        
        private:
            node_t* get_node(const value_type& item, 
            node_t* lptr, node_t* rptr){
                return node_t::create(item, lptr, rptr);
            }

            void Insert(const T& item){
                (void)item;
            }
            void Delete(const T& item){
                (void)item;
            }

            void SingleRotateLeft (node_t* &p);
            void SingleRotateRight (node_t* &p);
            void DoubleRotateLeft (node_t* &p);
            void DoubleRotateRight (node_t* &p);
            void UpdateLeftTree (node_t* &tree,  int &reviseBalanceFactor);
            void UpdateRightTree (node_t* &tree, int &reviseBalanceFactor);
    };
}




#endif
