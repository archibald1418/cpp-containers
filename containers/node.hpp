#ifndef NODE_H
# define NODE_H



template <typename Key>
struct Node {
    
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Key key;
    
    Node() : left(NULL), right(NULL), parent(NULL), key(Key()){};
    Node(const Key& key) : left(NULL), right(NULL), parent(NULL), key(key){};
};

#endif