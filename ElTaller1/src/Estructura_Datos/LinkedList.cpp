#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "../../include/Estructura_Datos/LinkedList.hpp"
#include <cstdlib>
#include <ctime>

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
size_t LinkedList<T>::size() const {
    return count;
}

template <typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

template <typename T>
T& LinkedList<T>::front() {
    return head->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    return head->data;
}

template <typename T>
T& LinkedList<T>::back() {
    return tail->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    return tail->data;
}

template <typename T>
Node<T>* LinkedList<T>::getNodeAt(size_t index) const {
    if (index >= count) return nullptr;
    
    Node<T>* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template <typename T>
T& LinkedList<T>::at(size_t index) {
    return getNodeAt(index)->data;
}

template <typename T>
const T& LinkedList<T>::at(size_t index) const {
    return getNodeAt(index)->data;
}

template <typename T>
void LinkedList<T>::pushFront(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

template <typename T>
void LinkedList<T>::pushBack(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

template <typename T>
void LinkedList<T>::insertAt(size_t index, const T& data) {
    if (index == 0) {
        pushFront(data);
    } else if (index == count) {
        pushBack(data);
    } else if (index < count) {
        Node<T>* current = getNodeAt(index);
        Node<T>* newNode = new Node<T>(data);
        
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        
        count++;
    }
}

template <typename T>
void LinkedList<T>::popFront() {
    if (isEmpty()) return;
    
    Node<T>* temp = head;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    delete temp;
    count--;
}

template <typename T>
void LinkedList<T>::popBack() {
    if (isEmpty()) return;
    
    Node<T>* temp = tail;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    delete temp;
    count--;
}

template <typename T>
void LinkedList<T>::removeAt(size_t index) {
    if (index >= count) return;
    
    if (index == 0) {
        popFront();
    } else if (index == count - 1) {
        popBack();
    } else {
        Node<T>* current = getNodeAt(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }
}

template <typename T>
bool LinkedList<T>::remove(const T& data) {
    int index = find(data);
    if (index != -1) {
        removeAt(index);
        return true;
    }
    return false;
}

template <typename T>
int LinkedList<T>::find(const T& data) const {
    Node<T>* current = head;
    int index = 0;
    
    while (current != nullptr) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
bool LinkedList<T>::contains(const T& data) const {
    return find(data) != -1;
}

template <typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail() const {
    return tail;
}

template <typename T>
void LinkedList<T>::shuffle() {
    if (count <= 1) return;
    
    // Arreglo temporal para mezcla
    T* tempArray = new T[count];
    Node<T>* current = head;
    for (size_t i = 0; i < count; i++) {
        tempArray[i] = current->data;
        current = current->next;
    }
    
    
    srand(time(nullptr)); // Knuth
    for (size_t i = count - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        T temp = tempArray[i];
        tempArray[i] = tempArray[j];
        tempArray[j] = temp;
    }
    

    clear(); // Rearma la lista
    for (size_t i = 0; i < count; i++) {
        pushBack(tempArray[i]);
    }
    
    delete[] tempArray;
}

#endif