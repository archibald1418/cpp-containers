#ifndef TREE_H
# define TREE_H

# include "node.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "tree_utils.hpp"

namespace ft {
        template <class T, template<typename> class NodeType>
    class Tree{
        typedef NodeType<T> Node;
        typedef typename Node::pointer node_pointer;
        typedef T value_type;

        // TODO: coplien form, destructors!

        Node* search(Node* node, T key)
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

        Node* tree_min(Node* node){
            while (node->left != NULL)
                node = node->left;
            return node;
        }  
        Node* tree_max(Node* node){
            while (node->right != NULL)
                node = node->right;
            return node;
        }
        Node* tree_next(Node* node){
            // Searching for next item in an ordered sequence

            // Next item is the next greatest to the current item
            // So it's in the right subtree
            if (node->right)
                return tree_min(node->right);

            // Otherwise go up and search the first parent which is also a left node
            Node* node_parent = node->parent;
            while (node_parent != NULL and node == node_parent->right){
                node = node_parent;
                node_parent = node_parent->parent;
            }
            return node;
        }
        Node* tree_prev(Node* node){
            // Same, but searching for rightmost child
            if (node->left)
                return tree_max(node->left);

            Node* node_parent = node->parent;
            while (node_parent != NULL and node == node_parent->left){
                node = node_parent;
                node_parent = node_parent->parent;
            }
            return node;
        }


    // Happy tree friends
    template <typename U>
    friend int height(::Node<U>* root);

    template <typename U>
    friend bool is_avl_balanced(::AVLNode<U>* root);

    // These functions are essential for balancing,
    // because they need access to protected fields

    };

    
}




#endif
