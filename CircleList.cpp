//
// Created by ThinkPad on 2019/11/9.
//

#include "CircleList.h"

CircleList::CircleList() {
    head = tail = 0;
}

void CircleList::createList(int value) {
    if(head  == 0) {
        head = new MyListNode(value);
        tail = head;
        tail->next = head;
        head->pre = tail;
        return;
    } else{
        tail ->next = new MyListNode(value);
        MyListNode* p = tail->next;
        p->pre = tail;
        p->next = head;
        head->pre = p;
        tail = p;
        return;
    }
}

void CircleList::Delete(int value) {
    MyListNode* p = head;
    for (;p->next!=head&&p->value!=value;p = p->next);
    if(p->value==value) {
        MyListNode * afterp = p->next;
        MyListNode* beforep = p->pre;
        afterp->pre = beforep;
        beforep->next = afterp;
        delete p;
        return;
    }
    return;
}

void CircleList::display() {
    MyListNode* p = head;
    for (; p->next!=head; p = p->next) {
        cout<<p->value<<endl;
    }
    cout<<p->value<<endl;

}
