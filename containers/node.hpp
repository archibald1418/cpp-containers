#ifndef NODE_H
# define NODE_H

# include "algorithm.hpp"
# include "stack.hpp"
# include "tree.hpp"

template <typename Key>
class Tree;


template <typename Key>
struct Node {
    typedef Node<Key> pointer;

    protected:
        struct Node *left;
        struct Node *right;
        struct Node *parent;
        Key key;
    
        
    friend class Tree<Key>; // Tree has to have access to protected members

    public:
        Node() : left(NULL), right(NULL), parent(NULL), key(Key()){};
        Node(const Key& key) : left(NULL), right(NULL), parent(NULL), key(key){};
        Node(const Key& key, pointer left, pointer right)
        :
        key(key), left(left), right(right){};

        Key& get(){ return this->key;};

        virtual ~Node(){
            // TODO:
        }
};

template <typename Key>
struct AVLNode : public Node<Key>
{
    typedef AVLNode<Key>* pointer;
    typedef Node<Key> Node;

    private:
        int balance_factor; 
            // Insertion and deletion are in charge of this field
        pointer& Left(){
            return dynamic_cast<pointer>(this->left);
        }
        pointer& Right(){
            return dynamic_cast<pointer>(this->right);
        }

    public:
        AVLNode() : Node(), balance_factor(0){};
        AVLNode(const Key& key) : Node(key), balance_factor(0){};
        AVLNode(const Key& key, pointer left, pointer right, int balfac = 0)
        :
        Node(key, left, right), balance_factor(balfac){};

        int get_balance_factor(){return this->balance_factor;}
};


#endif
