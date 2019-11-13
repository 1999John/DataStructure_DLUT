//
// Created by ThinkPad on 2019/11/9.
//

#ifndef WORKPLACE_MYLISTNODE_H
#define WORKPLACE_MYLISTNODE_H

#include <iostream>

struct MyListNode {
    int value;
    MyListNode *next;
    MyListNode *pre;

    MyListNode(int value, MyListNode *next = NULL, MyListNode *pre = NULL) : value(value), next(next),
                                                                             pre(pre) {}
};
class SS{
public:
    SS(){}
};

#endif //WORKPLACE_MYLISTNODE_H
