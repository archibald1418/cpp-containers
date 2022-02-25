#include <iostream>

// Primary template
template <typename T>
struct Node{

    T* next;
    T* prev;
    T  content;

    Node(T content){
        this->content = content;
        this->next = NULL;
        this->prev = NULL;
    }
    Node(){
        this->content = std::string("EMPTY");
        this->next = NULL;
        this->prev = NULL;
    }
};

template <>
struct Node<std::string> : public Node<std::string>{};

// Partial specialization
template <typename T>
struct Node<T*>{
    std::cout << "Hey! No pointers in Nodes allowed!" << std::endl;
};

template <typename T>
Node<T>* find_last(Node<T> *phead)
{
    while (phead)
        phead = phead->next;
    return phead;
}

template <typename T>
void    add_to_list(Node<T> *phead, Node<T> *elem)
{
    plast = find_last(phead);
    plast->next = elem;
    elem->next = NULL;
}

template <typename T>
Node<T>* create(T content)
{
    return new Node<T>(content);
}