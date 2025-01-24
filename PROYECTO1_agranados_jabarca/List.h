#pragma once
#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Node.h"
using namespace std;
//using namespace sf;
template<typename T>
class List
{
private:
    Node<T>* head;
public:
    Node<T>* getHead();
    void addNewNode(T element);
    void deleteNode(int position);
    void setHead(Node<T>* newHead);
    ~List();
};

template<typename T>
inline Node<T>* List<T>::getHead()
{
    return head;
}

template<typename T>
void List<T>::addNewNode(T element)
{
    Node<T>* newNode = new Node<T>(element);
    if (head == nullptr)
    {
        head = new Node<T>(element);
        return;
    }
    Node<T>* current = head;
    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }
    current->setNext(newNode);
    newNode->setPrevious(current);
}

template<typename T>
void List<T>::deleteNode(int position)
{
    if (position < 0 || head == nullptr)
    {
        return;
    }
    Node<T>* current = head;
    if (position == 0)
    {
        head = head->getNext();
        if (head != nullptr)
        {
            head->setPrevious(nullptr);
        }
        delete current;
        return;
    }
    for (int i = 0; i < position; i++)
    {
        current = current->getNext();
        if (current == nullptr)
        {
            return;
        }
    }
    if (current->getPrevious() != nullptr)
    {
        current->getPrevious()->setNext(current->getNext());
    }
    if (current->getNext() != nullptr)
    {
        current->getNext()->setPrevious(current->getPrevious());
    }
    delete current;
}

template<typename T>
inline void List<T>::setHead(Node<T>* newHead)
{
    head = newHead;
    if (head != nullptr)
    {
        head->setPrevious(nullptr);
    }
}

template<typename T>
inline List<T>::~List()
{
    Node<T>* current = head;
    Node<T>* next = nullptr;
    while (current != nullptr)
    {
        next = current->getNext();
        delete current;
        current = next;
    }
    head = nullptr;
}