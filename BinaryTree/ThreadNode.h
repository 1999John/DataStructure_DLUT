//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_THREADNODE_H
#define WORKPLACE_THREADNODE_H

#include <iostream>
#include "Binary.h"


namespace BinaryTree{
    template <class T>
    struct ThreadNode{
        T value;
        ThreadNode* leftChild;
        int leftTag;
        ThreadNode* rightChild;
        int rightTag;
        ThreadNode(T value) : value(value) {
            leftChild = rightChild = NULL;
            leftTag = rightTag = 0;
        }
    };

}
#endif //WORKPLACE_THREADNODE_H
