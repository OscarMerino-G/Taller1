#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
public:
    T data;
    
    // Nodo doble enlace
    Node<T>* next;
    Node<T>* prev; 
    
    Node();
    explicit Node(const T& data);
    Node(const T& data, Node<T>* next, Node<T>* prev = nullptr);
    
    
    ~Node();
};

#include "../../src/Estructura_Datos/Node.cpp"
#endif