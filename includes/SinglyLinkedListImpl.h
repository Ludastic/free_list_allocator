#pragma once
#include "SinglyLinkedList.h"

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(){
    
}

template <class T>
void SinglyLinkedList<T>::insert(Node* previousNode, Node* newNode){
    if (previousNode == nullptr) {
        if (head != nullptr) {
            newNode->next = head;           
        } else {
            newNode->next = nullptr;
        }
        head = newNode;
    } else {
        if (previousNode->next == nullptr){
            previousNode->next = newNode;
            newNode->next = nullptr;
        } else {
            newNode->next = previousNode->next;
            previousNode->next = newNode;
        }
    }
}

template <class T>
void SinglyLinkedList<T>::remove(Node* previousNode, Node* deleteNode){
    if (previousNode == nullptr) {
        if (deleteNode->next == nullptr){
            head = nullptr;            
        } else {
            head = deleteNode->next;
        }
    } else {
        previousNode->next = deleteNode->next;
    }
}