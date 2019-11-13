//
// Created by ThinkPad on 2019/11/12.
//

#ifndef WORKPLACE_CIRCLEDOUBLELIST_H
#define WORKPLACE_CIRCLEDOUBLELIST_H

#include <iostream>

template<class T>
struct DoubleNode {
    T value;
    DoubleNode *pre;
    DoubleNode *next;

    DoubleNode(T v, DoubleNode *p = NULL, DoubleNode *n = NULL) : value(v), pre(p), next(n) {}
};

template<class T>
class CircleDoubleList {
private:
    DoubleNode<T> *head;
public:
    CircleDoubleList();

    void insert(T value);

    void insert(int posi,T value);

    void Delete(T value);

    bool empty();

    void clear();

    void display();
};

template<class T>
CircleDoubleList<T>::CircleDoubleList() {
    head = new DoubleNode<T>(0);
    head->next = head;
    head->pre = head;
}

template<class T>
void CircleDoubleList<T>::insert(T value) {
    DoubleNode<T> *p = new DoubleNode<T>(value);
    if (!empty()) {
        DoubleNode<T>* tail = head->pre;

        p->pre = tail;
        tail->next = p;

        p->next = head;
        head->pre = p;
    }else{
        head->next = p;
        p->pre = head;

        head->pre = p;
        p->next = head;
    }
}

template<class T>
void CircleDoubleList<T>::Delete(T value) {
    if(empty()) {
        return;
    }
    DoubleNode<T>* p = head->next;
    for (; p!=head; p=p->next) {
        if(p->value==value) {
            DoubleNode<T>* pre = p->pre;
            DoubleNode<T>* next = p->next;
            pre->next = next;
            next->pre = pre;
            delete p;
            p = pre;
        }
    }
}

template<class T>
void CircleDoubleList<T>::display() {
    if(empty()) {
        cout<<"empty list"<<endl;
        return;
    }
    DoubleNode<T>* p = head->next;
    for (; p!=head; cout<<p->value<<endl,p=p->next);
}

template<class T>
bool CircleDoubleList<T>::empty() {
    return head->next ==head;
}

template<class T>
void CircleDoubleList<T>::clear() {
    DoubleNode<T>* p = head->next;
    for (; p!=head; p=p->next) {
        Delete(p->value);
    }
}



#endif //WORKPLACE_CIRCLEDOUBLELIST_H
