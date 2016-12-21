//
//  LinkedList.h
//  Mind the Gap
//
//  Created by A Philipeit on 07/12/2016.
//  Copyright © 2016 Arne Philipeit. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>

template <typename T> class LinkedListNode {
private:
    T data;
    LinkedListNode * next;
public:
    LinkedListNode<T>();
    ~LinkedListNode<T>();
    
    T getData() const;
    void setData(T data);
    
    LinkedListNode * getNext() const;
    void setNext(LinkedListNode * next);
};

template <typename T> class LinkedList {
private:
    LinkedListNode<T> * head;
    LinkedListNode<T> * tail;
public:
    LinkedList<T>();
    ~LinkedList<T>();
    
    int count() const;
    
    T elementAtIndex(int index) const;
    void setElementAtIndex(int index, T element);
    
    int indexOf(T element);
    
    void addElement(T element);
    void insertElement(int index, T element);
    T removeElement(int index);
};

template <typename T> LinkedListNode<T>::LinkedListNode() {
    next = NULL;
}

template <typename T> LinkedListNode<T>::~LinkedListNode() {
    next = NULL;
}

template <typename T> T LinkedListNode<T>::getData() const {
    return  data;
}

template <typename T> void LinkedListNode<T>::setData(T d) {
    data = d;
}

template <typename T> LinkedListNode<T> * LinkedListNode<T>::getNext() const {
    return next;
}

template <typename T> void LinkedListNode<T>::setNext(LinkedListNode<T> * n) {
    next = n;
}

template <typename T> LinkedList<T>::LinkedList() {
    head = NULL;
    tail = NULL;
}

template <typename T> LinkedList<T>::~LinkedList() {
    LinkedListNode<T> *c = head;
    
    while (c != NULL) {
        LinkedListNode<T> * a = c;
        
        c = c->getNext();
        
        delete a;
    }
    
    head = NULL;
    tail = NULL;
}

template <typename T> int LinkedList<T>::count() const {
    int c = 0;
    
    LinkedListNode<T> *a = head;
    
    while (a != NULL) {
        c++;
        
        a = a->getNext();
    }
    
    return c;
}

template <typename T> T LinkedList<T>::elementAtIndex(int index) const {
    if (index < 0) {
        return NULL;
    }
    
    int c = 0;
    
    LinkedListNode<T> *a = head;
    
    while (a != NULL) {
        if (c == index) {
            return a->getData();
        }
        
        c++;
        
        a = a->getNext();
    }
    
    return NULL;
}

template <typename T> void LinkedList<T>::setElementAtIndex(int index, T element) {
    if (index < 0) {
        return;
    }
    
    int c = 0;
    
    LinkedListNode<T> *a = head;
    
    while (a != NULL) {
        if (c == index) {
            a->setData(element);
        }
        
        c++;
        
        a = a->getNext();
    }
}

template <typename T> int LinkedList<T>::indexOf(T element) {
    int c = 0;
    
    LinkedListNode<T> *a = head;
    
    while (a != NULL) {
        if (element == a->getData()) {
            return c;
        }
        
        c++;
        
        a = a->getNext();
    }
    
    return -1;
}

template <typename T> void LinkedList<T>::addElement(T element) {
    LinkedListNode<T> * node = new LinkedListNode<T>();
    node->setData(element);
    
    if (head == NULL) {
        head = node;
        tail = node;
    }else{
        tail->setNext(node);
        tail = node;
    }
}

template <typename T> void LinkedList<T>::insertElement(int index, T element) {
    if (index < 0 || element == NULL) {
        return;
    }
    
    if (index == 0) {
        LinkedListNode<T> * node = new LinkedListNode<T>();
        node->setData(element);
        
        if (head != NULL) {
            node->setNext(head);
            
            head = node;
            
        }else{
            head = node;
            tail = node;
        }
        
    }else{
        int c = 0;
        
        LinkedListNode<T> *a = head;
        
        while (a != NULL) {
            if (c == index) {
                LinkedListNode<T> * node = new LinkedListNode<T>();
                node->setData(element);
                node->setNext(a);
                
                return;
            }
            
            c++;
            
            a = a->getNext();
        }
    }
}

template <typename T> T LinkedList<T>::removeElement(int index) {
    if (index < 0) {
        return NULL;
    }
    
    if (index == 0) {
        if (head == NULL) {
            return NULL;
        }
        
        LinkedListNode<T> *node = head;
        T element = node->getData();
        
        head = head->getNext();
        
        if (head == NULL) {
            tail = NULL;
        }
        
        delete node;
        
        return element;
    }
    
    int c = 0;
    
    LinkedListNode<T> *a = NULL;
    LinkedListNode<T> *b = head;
    
    while (a != NULL) {
        if (c == index) {
            a->setNext(b->getNext());
            
            if (tail == b) {
                tail = a;
            }
            
            T element = b->getData();
            
            delete b;
            
            return element;
        }
        
        c++;
        
        a = b;
        b = b->getNext();
    }
    
    return NULL;
}
