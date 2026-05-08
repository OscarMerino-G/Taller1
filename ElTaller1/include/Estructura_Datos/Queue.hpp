#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "LinkedList.hpp"

template <typename T>
class Queue {
private:
    LinkedList<T> list;
    
public:
    Queue();
    ~Queue();
    
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    void enqueue(const T& data);
    void dequeue();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    
    T& at(size_t index);
    const T& at(size_t index) const;
    void insertAt(size_t index, const T& data); // Inserta el elemento en X posicion
    void removeAt(size_t index); // Elimina el elemento en la posicon X
    void shuffle(); // Mezcla
    LinkedList<T>& getList();
    const LinkedList<T>& getList() const;
};

#include "../../src/Estructura_Datos/Queue.cpp"
#endif