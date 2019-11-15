//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_RLNODE_H
#define WORKPLACE_RLNODE_H

#include <iostream>
namespace BinaryTree{
    template <class T>
    struct rlNode{
        T value;
        rlNode* leftChild;
        rlNode* rightChild;
        rlNode(T value) : value(value) {
                leftChild = rightChild = NULL;
        }
    };
}


#endif //WORKPLACE_RLNODE_H
