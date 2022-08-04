#ifndef NODE_H
# define NODE_H

# include "algorithm.hpp"
# include "stack.hpp"
# include "tree.hpp"

template <typename T, template<typename> class NodeType>
struct Tree;

template <typename Key, template<typename> class NodeType>
struct node_traits{
    typedef NodeType<Key>       node_t;
    typedef Key                 value_type;
    typedef node_t*             pointer;
};

template <typename Key>
struct Node{

    typedef node_traits<Key, Node>          traits;
    typedef typename traits::node_t         node_t;
    typedef typename traits::value_type     value_type;
    typedef typename traits::pointer        pointer;

    protected:
        pointer left;
        pointer right;
        pointer parent;
        Key key;
        
    friend struct Tree<Key, Node>; 
    // Tree has to have access to protected members

    public:

    /* FIX: 
        CRTP, with Tree and Node metaclasses, 
        hold shared functionality of the children,
        take designated child class as a template template parameter
        and generating traits based on the parameter
    
    */

        pointer Left(){
            return dynamic_cast<pointer>(this->left);
        }
        pointer Right(){
            return dynamic_cast<pointer>(this->right); // FIXME: Object slicing
        }
        pointer Parent(){
            return static_cast<pointer>(this->parent);
        }

        Node() : left(NULL), right(NULL), parent(NULL), key(Key()){};
        Node(const Key& key, pointer left = NULL, pointer right = NULL, pointer parent = NULL)
        :
        left(left), right(right), parent(parent), key(key){};
        Node(const Node& other)
        :
        left(other.left), right(other.right), parent(other.parent), key(other.key){};

        virtual ~Node(){
            // TODO: 
        }

        Key& get(){ return this->key;};

        static pointer create_node(const Key& item, pointer left = NULL, pointer right = NULL){
            return new Node(item, left, right);
        }
        static pointer clone_node(const Node& node){
            return new Node(node);
        }
};

template <typename Key>
struct AVLNode : public Node<Key>
{
    typedef Node<Key>                       NodeBase;
    typedef node_traits<Key, AVLNode>       traits;
    typedef typename traits::node_t         node_t;
    typedef typename traits::value_type     value_type;
    typedef typename traits::pointer        pointer;
    

    private:
        int balance_factor;
            // Insertion and deletion are in charge of this field
    public:
        

        AVLNode() : NodeBase(), balance_factor(0){};
        AVLNode(const Key& key, pointer left = NULL, pointer right = NULL, int balfac = 0)
        :
        NodeBase(key, left, right), balance_factor(balfac){};

        int get_balance_factor(){return this->balance_factor;}
};


#endif
