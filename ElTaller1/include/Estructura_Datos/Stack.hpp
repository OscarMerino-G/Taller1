#ifndef STACK_HPP
#define STACK_HPP

#include "LinkedList.hpp"

template <typename T>
class Stack {
private:
    LinkedList<T> list;
    
public:
    Stack();
    ~Stack();
    
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    void push(const T& data);
    void pop();
    T& top();
    const T& top() const;
};

#include "../../src/Estructura_Datos/Stack.cpp"
#endif