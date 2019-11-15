//
// Created by ThinkPad on 2019/11/9.
//

#include "singleList.h"

using namespace LinearTable;
singleList::singleList() {
    head = 0;
}


void singleList::createList() {
    while(true) {
        int i=0;
        cin>>i;
        if(i<0){
            break;
        }else{
            if(head == 0){
                head = new MyListNode(i);
                continue;
            }
            MyListNode* p = head;
            while(p->next){
                p = p->next;
            }
            p->next = new MyListNode(i);
        }
    }
}

void singleList::display() {
    MyListNode* p = head;
    while (p) {
        cout<<p->value<<endl;
        p = p->next;
    }
}

void singleList::invert() {
    MyListNode* p = head;
    MyListNode* q = 0;
    MyListNode* r = 0;
    while(p) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    head = q;
}

int singleList::getMax() {
    if(head==0) {
        throw "no max";
    }
    int max = head->value;
    MyListNode* p = head;
    for (; p ;max=p->value>max?p->value:max, p = p->next);
    return max;
}

int singleList::getcurlen() {
    if(head==0) {
        return 0;
    }
    MyListNode* p = head;
    int i=0;
    for (; p ; p = p->next,++i) ;
    return i;
}

double singleList::getaverage() {
    MyListNode* p = head;
    double sum = 0;
    for (;p;sum+=p->value, p = p->next);
    if(getcurlen()==0) {
        throw "cannot get average";
    }else{
        double ave = sum/getcurlen();
        return ave;
    }
}


