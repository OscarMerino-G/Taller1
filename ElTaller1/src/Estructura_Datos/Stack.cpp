#ifndef STACK_CPP
#define STACK_CPP

#include "../../include/Estructura_Datos/Stack.hpp"

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
size_t Stack<T>::size() const {
    return list.size();
}

template <typename T>
void Stack<T>::clear() {
    list.clear();
}

template <typename T>
void Stack<T>::push(const T& data) {
    list.pushFront(data);
}

template <typename T>
void Stack<T>::pop() {
    list.popFront();
}

template <typename T>
T& Stack<T>::top() {
    return list.front();
}

template <typename T>
const T& Stack<T>::top() const {
    return list.front();
}

#endif