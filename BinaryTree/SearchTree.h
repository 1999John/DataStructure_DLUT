//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_SEARCHTREE_H
#define WORKPLACE_SEARCHTREE_H

#include "Node.h"
#include "Binary.h"

#include <cmath>
#include <queue>

namespace BinaryTree {
    template<class T>
    class SearchTree {
    private:
        rlNode<T> *root;

        void getWidthArr(rlNode<T> *root, int height, int *widthArr);

    public:
        SearchTree(T value);

        /*
         * root: start node
         * value:the value that you want
         * get:the node of the value if have
         */
        bool find(rlNode<T> *root, T value,rlNode<T>* &get);

        void insert(T value);

        void deleteByCopying(T value);

        void deleteByMerging(T value);

        void twoChild(rlNode<T> *root, int *num);  // numbers of the node who has two child

        void oneChild(rlNode<T> *root, int *num);   // numbers of the node who has one child

        void noChild(rlNode<T> *root, int *num);    // numbers of the node who donnot have child

        void getHeight(rlNode<T> *root, int *height);   // the height of the tree

        void getWidth(rlNode<T> *root, int *width);     // the width of the tree

        void getMax(rlNode<T> *root, T *max);   // the max value node

        void exchange(rlNode<T> *root);     // exchange node's left child and right child

        void inOrder(rlNode<T> *root);

        void deleteCurrentLeaf(rlNode<T> *root, rlNode<T> *parent);     // delete current leaf node

        bool isCompleteBinaryTree();        // wether or not a complete binary tree

        rlNode<T> *getRoot() const;
    };


    template<class T>
    SearchTree<T>::SearchTree(T value) {
        this->root = new rlNode<T>(value);
    }

    template<class T>
    void SearchTree<T>::insert(T value) {
        if (!root) {
            root = new rlNode<T>(value);
            return;
        }
        rlNode<T> *pointer = this->root;
        rlNode<T> *pre = this->root;
        while (pointer) {
            if (pointer->value > value) {
                pre = pointer;
                pointer = pointer->leftChild;
                continue;
            }
            if (pointer->value < value) {
                pre = pointer;
                pointer = pointer->rightChild;
                continue;
            } else {
                return;
            }
        }
        if (pre->value > value) {
            pre->leftChild = new rlNode<T>(value);
            return;
        }
        if (pre->value < value) {
            pre->rightChild = new rlNode<T>(value);
            return;
        }
        return;
    }

    template<class T>
    bool SearchTree<T>::find(rlNode<T> *root, T value,rlNode<T>* &get) {
        if (root) {
            if (root->value == value) {
                get = root;
                return true;
            } else {
                return find(root->leftChild, value,get) || find(root->rightChild, value,get);
            }
        }
        return false;
    }

    template<class T>
    void SearchTree<T>::twoChild(rlNode<T> *root, int *num) {
        if (root) {
            if (root->leftChild && root->rightChild) {
                (*num)++;
            }
            twoChild(root->leftChild, num);
            twoChild(root->rightChild, num);
        }
    }

    template<class T>
    rlNode<T> *SearchTree<T>::getRoot() const {
        return root;
    }

    template<class T>
    void SearchTree<T>::oneChild(rlNode<T> *root, int *num) {
        if (root) {
            if ((root->leftChild && !root->rightChild) || (!root->leftChild && root->rightChild)) {
                (*num)++;
            }
            oneChild(root->leftChild, num);
            oneChild(root->rightChild, num);
        }
    }

    template<class T>
    void SearchTree<T>::noChild(rlNode<T> *root, int *num) {
        if (root) {
            if (!(root->leftChild || root->rightChild)) {
                (*num)++;
            } else {
                noChild(root->leftChild, num);
                noChild(root->rightChild, num);
            }
        }
    }

    template<class T>
    void SearchTree<T>::getHeight(rlNode<T> *root, int *height) {
        if (root) {
            (*height)++;
            int leftHeight = 0;
            int rightHeight = 0;
            getHeight(root->leftChild, &leftHeight);
            getHeight(root->rightChild, &rightHeight);
            (*height) += (leftHeight > rightHeight) ? leftHeight : rightHeight;
        }
    }

    template<class T>
    void SearchTree<T>::getWidthArr(rlNode<T> *root, int height, int *widthArr) {
        if (root) {
            widthArr[height]++;
            getWidthArr(root->leftChild, height + 1, widthArr);
            getWidthArr(root->rightChild, height + 1, widthArr);
        }
    }

    template<class T>
    void SearchTree<T>::getWidth(rlNode<T> *root, int *width) {
        int height = 0;
        getHeight(root, &height);
        int widthArr[height];
        for (int j = 0; j < height; ++j) {
            widthArr[j] = 0;
        }
        getWidthArr(root, 0, widthArr);
        (*width) = widthArr[0];
        for (int i = 0; i < height; ++i) {
            if (widthArr[i] > (*width)) {
                (*width) = widthArr[i];
            }
        }
    }

    template<class T>
    void SearchTree<T>::getMax(rlNode<T> *root, T *max) {
        if (root) {
            if (root->value > (*max))
                (*max) = root->value;
            getMax(root->leftChild, max);
            getMax(root->rightChild, max);
        }
    }

    template<class T>
    void SearchTree<T>::exchange(rlNode<T> *root) {
        if (root) {
            rlNode<T> *left = root->leftChild;
            rlNode<T> *right = root->rightChild;
            root->leftChild = right;
            root->rightChild = left;

            exchange(root->leftChild);
            exchange(root->rightChild);
        }
    }

    template<class T>
    void SearchTree<T>::inOrder(rlNode<T> *root) {
        if (root) {
            inOrder(root->leftChild);
            std::cout << root->value << std::endl;
            inOrder(root->rightChild);
        }
    }

    template<class T>
    void SearchTree<T>::deleteCurrentLeaf(rlNode<T> *root, rlNode<T> *parent) {
        if (root) {
            if (!(root->leftChild || root->rightChild)) {
                std::cout << "delete " << root->value << std::endl;
                if (root == parent->leftChild) {
                    parent->leftChild = NULL;
                    delete root;
                } else {
                    parent->rightChild = NULL;
                    delete root;
                }
            } else {
                deleteCurrentLeaf(root->leftChild, root);
                deleteCurrentLeaf(root->rightChild, root);
            }
        }
    }

    template<class T>
    bool SearchTree<T>::isCompleteBinaryTree() {    //基于广度优先的判断
        rlNode<T> *pointer = this->root;
        bool cannotHaveChild = false;
        bool ret = true;
        using std::queue;

        queue<rlNode<T> *> q;
        q.push(this->root);
        while (!q.empty()) {
            pointer = q.front();
            q.pop();
            if (pointer->leftChild) {
                if (cannotHaveChild) {
                    return false;
                }
                q.push(pointer->leftChild);
            }
            if (pointer->rightChild) {
                if (cannotHaveChild) {
                    return false;
                }
                q.push(pointer->rightChild);
            }
            if (pointer->leftChild && !pointer->rightChild) {
                cannotHaveChild = true;
            }
            if(!pointer->leftChild&&pointer->rightChild) {
                return false;
            }
        }
        return true;

    }

    template<class T>
    void SearchTree<T>::deleteByCopying(T value) {
        rlNode<T>* node;
        if(find(this->root,value,node)){
            if (node->rightChild==NULL){
                rlNode<T>* left = node->leftChild;
                node->value = left->value;
                node->leftChild = left->leftChild;
                node->rightChild = left->rightChild;
                delete left;
            } else if (node->leftChild==NULL){
                rlNode<T>* right = node->rightChild;
                node->value = right->value;
                node->leftChild = right->leftChild;
                node->rightChild = right->rightChild;
                delete right;
            } else{
                rlNode<T>* q = node->leftChild;
                rlNode<T>* p = node;
                for (; q->rightChild; p = q,q=q->rightChild);
                node->value = q->value;
                if(p==node){
                    node->leftChild=q->leftChild;
                }else{
                    p->rightChild=q->leftChild;
                }
                delete q;
            }
        }
        return;
    }

    template<class T>
    void SearchTree<T>::deleteByMerging(T value) {
        rlNode<T>* current = this->root;
        while(current->value!=value){
            if(current->value<value){
                current = current->rightChild;
            } else{
                current = current->leftChild;
            }
        }
        if(current->leftChild==NULL){
            rlNode<T>* right = current->rightChild;

            current->value = right->value;
            current->leftChild = right->leftChild;
            current->rightChild = right->rightChild;
            delete right;
        } else{
            rlNode<T>* right = current->rightChild;
            rlNode<T>* left = current->leftChild;

            rlNode<T>* p=left;
            for (; p->rightChild; p=p->rightChild);

            p->rightChild = right;

            current->value = left->value;
            current->leftChild = left->leftChild;
            current->rightChild = left->rightChild;
            delete left;
        }
    }

}


#endif //WORKPLACE_SEARCHTREE_H
