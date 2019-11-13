//
// Created by ThinkPad on 2019/11/9.
//

#ifndef WORKPLACE_CIRCLELIST_H
#define WORKPLACE_CIRCLELIST_H

#include <iostream>
#include "MyListNode.h"

using namespace std;


class CircleList {
private:
    MyListNode *head;
    MyListNode *tail;
public:
    CircleList();

    void createList(int value);

    void Delete(int value);

    void display();
};


#endif //WORKPLACE_CIRCLELIST_H
