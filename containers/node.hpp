#ifndef NODE_H
# define NODE_H

# include "algorithm.hpp"
# include "stack.hpp"
# include "tree.hpp"

template <typename Key>
class Tree;


template <typename Key>
struct Node {
    typedef Node<Key>   node_type;
    typedef Key         value_type;
    typedef Node*       pointer;

    protected:
        pointer left;
        pointer right;
        pointer parent;
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
    typedef Node<Key> NodeBase;
    typedef AVLNode<Key>* pointer;
    typedef AVLNode<Key> Node;

    private:
        int balance_factor; 
            // Insertion and deletion are in charge of this field
    public:
        pointer Left(){
            return static_cast<pointer>(this->left);
        }
        pointer Right(){
            return static_cast<pointer>(this->right);
        }

        AVLNode() : NodeBase(), balance_factor(0){};
        AVLNode(const Key& key) : NodeBase(key), balance_factor(0){};
        AVLNode(const Key& key, pointer left, pointer right, int balfac = 0)
        :
        NodeBase(key, left, right), balance_factor(balfac){};

        int get_balance_factor(){return this->balance_factor;}
};


#endif
