#ifndef NODE_CPP
#define NODE_CPP

#include "../../include/Estructura_Datos/Node.hpp"

template <typename T>
Node<T>::Node() : next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* next, Node<T>* prev) 
    : data(data), next(next), prev(prev) {}

template <typename T>
Node<T>::~Node() {
    // No eliminar los nodos siguientes aquí para evitar recursión infinita
    next = nullptr;
    prev = nullptr;
}

#endif