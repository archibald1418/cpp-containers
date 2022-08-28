#ifndef NODE_H
# define NODE_H

# include "algorithm.hpp"
# include "stack.hpp"
# include "tree.hpp"
# include "type_traits.hpp"
# include "pair.hpp"

// /  /   /    /     /      /       /        /
# include <typeinfo> 
// /  /   /    /     /      /       /        /


# include <iostream>

namespace ft {

    template <typename T, template<typename> class NodeType>
    struct node_traits
    {
        typedef NodeType<T>         node_t;
        typedef T                   value_type;
        typedef node_t*             pointer;
    }; 

    struct node_tag{};


    template <typename T, template<typename> class NodeType>
    struct BaseNode
    {
        typedef NodeType<T>                         node_t;
        typedef T                                   value_type;
        typedef node_t*                             pointer;
        typedef BaseNode<T, NodeType>               __base;
        typedef node_tag                            __node_tag;

        protected:
            pointer     left;
            pointer     right;
            pointer     parent;
            value_type  item;
            bool        isleaf;

        public:

            pointer& Left(){
                return this->left;
            }
            pointer& Right(){
                return this->right;
            }
            pointer& Parent(){
                return this->parent; // шиза полная
            }
            bool& Isleaf(){
                return this->isleaf;
            }

            // ????????????????????????? 
            // virtual
            value_type& Get(){
                return this->item;
            }
            // virtual
            void        Set(const value_type& val) {
                this->item = value_type(val);
            };
            // ^ DEBUG: accessors cause segfaults if virtual


            BaseNode() : left(NULL), right(NULL), parent(NULL), item(T()), isleaf(true){};
            BaseNode(const T& item, pointer left = NULL, pointer right = NULL, pointer parent = NULL)
            :
            left(left), right(right), parent(parent), item(item), isleaf(parent || false){};
            BaseNode(const BaseNode& other)
            :
            left(other.left), right(other.right), parent(other.parent), item(other.item), isleaf(other.isleaf){};


            virtual ~BaseNode(){
                std::cout << "Calling base node dtor" << std::endl;
                delete left;
                delete right;
            }

            static pointer create(const value_type& item, 
            pointer left = NULL, pointer right = NULL, pointer parent = NULL){
                return new node_t(item, left, right, parent);
            }
            static pointer clone(const node_t& node){
                return new node_t(node);
            }
        
    };

            template <typename T>
        struct Node : public BaseNode<T, Node>{};

        template <typename T>
        struct AVLNode : public BaseNode<T, AVLNode>
        {            
            typedef BaseNode<T, AVLNode>          __base;
            typedef typename __base::node_t         node_t;
            typedef typename __base::value_type     value_type;
            typedef typename __base::pointer        pointer;
            
            private:
                int balance_factor;
                    // Insertion and deletion are in charge of this field
            public:
                AVLNode() : __base(), balance_factor(0){}
                AVLNode(const value_type& item,
                pointer left = NULL, pointer right = NULL, int balfac = 0, pointer parent = NULL)
                :
                __base(item, left, right, parent), balance_factor(balfac){};
                AVLNode(const node_t& other)
                :
                __base(other), balance_factor(other.balance_factor){};
                
                virtual ~AVLNode(){
                    
                };


                int get_balance_factor(){return this->balance_factor;}

                static pointer create(const value_type& item,
                pointer left = NULL, pointer right = NULL, int balfac = 0, pointer parent = NULL){
                    return (new AVLNode(item, left, right, balfac, parent));
                }

            // void        SetChild(const value_type& val)
            // {
            //     __base::Set(val);
            // };

            // void        Set(const value_type& val){
            //     this->item = val;
            // } 
                
            // void * getSet(){
            //     return &Set;
            // }
        };


/* 
                CRTP, with Tree and Node metaclasses, 
                hold shared functionality of the children,
                take designated child class as a template template parameter
                and generating traits based on the parameter
            */

        
        template <typename NodeInstance>
        typename NodeInstance::value_type& 
        Get(NodeInstance* node){
            return node->Get(); // FIXME: this does not work right, segfaults
        }
        template <typename NodeInstance>
        void
        Set(NodeInstance* node, const typename NodeInstance::value_type& item){
            node->Set(item);
        }
        template <typename NodeInstance>
        bool
        Isleaf(NodeInstance* node){
            return node->Isleaf();
        }
        
        // TODO: allocator
            // TODO: iterator




}

#endif // NODE_H

