#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <cstddef>

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t count;
    
public:
	
	// constructor y destructor
    LinkedList();
    ~LinkedList();
    
    bool isEmpty() const; // cap
    size_t size() const;
    void clear();
    

    T& front(); // Acecso 
    const T& front() const;
    T& back();
    const T& back() const;
    T& at(size_t index);
    const T& at(size_t index) const;
    
    

    void pushFront(const T& data); // Insercion
    void pushBack(const T& data);
    void insertAt(size_t index, const T& data);


    void popFront(); // Eliminacion
    void popBack();
    void removeAt(size_t index);
    bool remove(const T& data);
    

    int find(const T& data) const; // Busqueda
    bool contains(const T& data) const;

    Node<T>* getHead() const; // Recorre la lista
    Node<T>* getTail() const;
    
    void shuffle(); // Mezcla la lista
    
private:
    Node<T>* getNodeAt(size_t index) const;
};

#include "../../src/Estructura_Datos/LinkedList.cpp"
#endif