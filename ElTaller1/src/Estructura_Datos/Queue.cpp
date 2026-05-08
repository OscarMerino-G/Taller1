#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "../../include/Estructura_Datos/Queue.hpp"

template <typename T>
Queue<T>::Queue() {}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
size_t Queue<T>::size() const {
    return list.size();
}

template <typename T>
void Queue<T>::clear() {
    list.clear();
}

template <typename T>
void Queue<T>::enqueue(const T& data) {
    list.pushBack(data);
}

template <typename T>
void Queue<T>::dequeue() {
    list.popFront();
}

template <typename T>
T& Queue<T>::front() {
    return list.front();
}

template <typename T>
const T& Queue<T>::front() const {
    return list.front();
}

template <typename T>
T& Queue<T>::back() {
    return list.back();
}

template <typename T>
const T& Queue<T>::back() const {
    return list.back();
}

template <typename T>
const T& Queue<T>::at(size_t index) const {
    return list.at(index);
}

template <typename T>
T& Queue<T>::at(size_t index) {
    return list.at(index);
}

template <typename T>
void Queue<T>::insertAt(size_t index, const T& data) {
    list.insertAt(index, data);
}

template <typename T>
void Queue<T>::removeAt(size_t index) {
    list.removeAt(index);
}

template <typename T>
void Queue<T>::shuffle() {
    list.shuffle();
}

template <typename T>
LinkedList<T>& Queue<T>::getList() {
    return list;
}

template <typename T>
const LinkedList<T>& Queue<T>::getList() const {
    return list;
}

#endif