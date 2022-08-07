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

template <typename Key, template<typename> class NodeImpl>
struct BaseNode{
    typedef node_traits<Key, NodeImpl>      traits;
    typedef typename traits::node_t         node_t;
    typedef typename traits::value_type     value_type;
    typedef typename traits::pointer        pointer;

    protected:
        pointer     left;
        pointer     right;
        pointer     parent;
        value_type  key;

    public:
        pointer Left(){
            return dynamic_cast<pointer>(this->left);
        }
        pointer Right(){
            return dynamic_cast<pointer>(this->right); // FIXME: Object slicing
        }
        pointer Parent(){
            return static_cast<pointer>(this->parent);
        }


        BaseNode() : left(NULL), right(NULL), parent(NULL), key(Key()){};
        BaseNode(const Key& key, pointer left = NULL, pointer right = NULL, pointer parent = NULL)
        :
        left(left), right(right), parent(parent), key(key){};
        BaseNode(const BaseNode& other)
        :
        left(other.left), right(other.right), parent(other.parent), key(other.key){};


        virtual value_type& get(){ return this->key;};

        virtual ~BaseNode(){
            // TODO: 
        }

// Should these be abstract ?
        static pointer create_node(const value_type& item, 
        pointer left = NULL, pointer right = NULL, pointer parent = NULL){
            return new BaseNode(item, left, right, parent);
        }
        static pointer clone_node(const node_t& node){
            return new BaseNode(node);
        }
    
};

template <typename Key>
struct Node : public BaseNode<Key, Node>{};

template <typename Key>
struct AVLNode : public BaseNode<Key, AVLNode>
{
    /* FIX: 
        CRTP, with Tree and Node metaclasses, 
        hold shared functionality of the children,
        take designated child class as a template template parameter
        and generating traits based on the parameter
    */
    typedef BaseNode<Key, AVLNode>          __base;
    typedef typename __base::traits         traits;
    
    typedef typename traits::node_t         node_t;
    typedef typename traits::value_type     value_type;
    typedef typename traits::pointer        pointer;
    

    private:
        int balance_factor;
            // Insertion and deletion are in charge of this field
    public:
        

        AVLNode() : __base(), balance_factor(0){}
        AVLNode(const value_type& key,
        pointer left = NULL, pointer right = NULL, int balfac = 0, pointer parent = NULL)
        :
        __base(key, left, right, parent), balance_factor(balfac){};
        AVLNode(const node_t& other)
        :
        __base(other), balance_factor(other.balance_factor){};

        int get_balance_factor(){return this->balance_factor;}

        static pointer clone_node(const node_t& node){
            return new AVLNode(node);
        }
        static pointer create_node(const value_type& key,
        pointer left = NULL, pointer right = NULL, int balfac = 0, pointer parent = NULL){
            new AVLNode(key, left, right, parent, balfac);
        }
        
};


#endif
