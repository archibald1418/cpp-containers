#ifndef TREE_UTILS_H
# define TREE_UTILS_H

# include "node.hpp"

namespace ft {
    template <typename U>
    int height(AVLNode<U>* root)
    {
        int leftheight = 0;
        int rightheight = 0;
        if (!root)
            return -1;
        if (root->Left())
            leftheight = (1 + height(root->Left()));
        if (root->Right())
            rightheight = (1 + height(root->Right()));
        
        return max(leftheight, rightheight);
}

    template <typename U>
    bool is_avl_balanced(AVLNode<U> *root)
    {
        // DEBUG: test this
        int balfac = height(root->Right()) - height(root->Left());
        return (-1 <= balfac && balfac <= 1);
    }

}

#endif