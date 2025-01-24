#pragma once
template <typename T>
class Node
{
private:
    T element;
    Node* next;
    Node* previous;
public:
    Node(T element);
    T& getElement();
    Node* getNext();
    Node* getPrevious();
    void setElement(T element);
    void setNext(Node<T>* node);
    void setPrevious(Node<T>* node);
};

template<typename T>
Node<T>::Node(T element)
{
    element = element;
    next = nullptr;
}

template<typename T>
T& Node<T>::getElement()
{
    return element;
}

template<typename T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template<typename T>
Node<T>* Node<T>::getPrevious()
{
    return previous;
}

template<typename T>
void Node<T>::setElement(T element)
{
    element = element;
}

template<typename T>
void Node<T>::setNext(Node<T>* node)
{
    next = node;
}

template<typename T>
void Node<T>::setPrevious(Node<T>* node)
{
    previous = node;
}