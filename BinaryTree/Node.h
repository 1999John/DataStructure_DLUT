//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_NODE_H
#define WORKPLACE_NODE_H

#include <iostream>

namespace BinaryTree {

    template<class T>
    struct rlNode {
        T value;
        rlNode *leftChild;
        rlNode *rightChild;

        rlNode(T value) : value(value) {
            leftChild = rightChild = NULL;
        }

        bool operator>(rlNode<T> *other) {
            return this->value > other->value;
        }

        bool operator<(rlNode<T> *other) {
            return this->value < other->value;
        }

        bool operator>=(rlNode<T> *other) {
            return this->value >= other->value;
        }

        bool operator<=(rlNode<T> *other) {
            return this->value <= other->value;
        }

        bool operator==(rlNode<T> *other) {
            return this->value == other->value;
        }
    };

#define THREAD 1
#define LINK 0

    template<class T>
    struct threadNode {
        T value;
        threadNode<T> *leftChild;
        int leftTag;
        threadNode<T> *rightChild;
        int rightTag;

        threadNode(T val) : value(val) {
            leftChild = NULL;
            rightChild = NULL;
            leftTag = LINK;
            rightTag = LINK;
        }

        bool operator>(threadNode<T> *other) {
            return this->value > other->value;
        }

        bool operator<(threadNode<T> *other) {
            return this->value < other->value;
        }

        bool operator>=(threadNode<T> *other) {
            return this->value >= other->value;
        }

        bool operator<=(threadNode<T> *other) {
            return this->value <= other->value;
        }

        bool operator==(threadNode<T> *other) {
            return this->value == other->value;
        }
    };

    template<class T>
    struct avlNode {
        T value;
        avlNode<T> *leftChild;
        avlNode<T> *rightChild;
        avlNode<T> *parent;
        bool posi;
        int balFactor;

        avlNode(T v, avlNode<T> *p, bool po, avlNode<T> *l = NULL, avlNode<T> *r = NULL, int b = 0) : value(v) {
            this->parent = p;
            posi = po;
            leftChild = l;
            rightChild = r;
            balFactor = b;
        }

        bool operator>(avlNode<T> *other) {
            return this->value > other->value;
        }

        bool operator<(avlNode<T> *other) {
            return this->value < other->value;
        }

        bool operator>=(avlNode<T> *other) {
            return this->value >= other->value;
        }

        bool operator<=(avlNode<T> *other) {
            return this->value <= other->value;
        }

        bool operator==(avlNode<T> *other) {
            return this->value == other->value;
        }
    };

    template<class T>
    class HuffmanTreeNode {
    public:
        T value;
        HuffmanTreeNode<T> *leftChild;
        HuffmanTreeNode<T> *rightChild;
        HuffmanTreeNode<T> *parent;

        HuffmanTreeNode(T val) {
            value = val;
            leftChild = NULL;
            rightChild = NULL;
            parent = NULL;
        }

        bool operator>(HuffmanTreeNode<T> &other) {
            return this->value > other.value;
        }

        bool operator<(HuffmanTreeNode<T> &other) {
            return this->value < other.value;
        }

        bool operator>=(HuffmanTreeNode<T> &other) {
            return this->value >= other.value;
        }

        bool operator<=(HuffmanTreeNode<T> &other) {
            return this->value <= other.value;
        }

        bool operator==(HuffmanTreeNode<T> &other) {
            return this->value == other.value;
        }
    };
}


#endif //WORKPLACE_NODE_H
