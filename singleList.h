//
// Created by ThinkPad on 2019/11/9.
//

#ifndef WORKPLACE_SINGLELIST_H
#define WORKPLACE_SINGLELIST_H

#include <iostream>
#include "MyListNode.h"
using namespace std;

class singleList {
private:
    MyListNode* head;
public:
    singleList();

    void createList();

    void display();

    void invert();

    int getMax();

    int getcurlen();

    double getaverage();
};


#endif //WORKPLACE_SINGLELIST_H
