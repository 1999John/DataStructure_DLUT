//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_THREADTREE_H
#define WORKPLACE_THREADTREE_H


#include "Node.h"

namespace BinaryTree {


    template<class T>
    class ThreadTree {
    private:
        threadNode<T>* root;
    public:
        ThreadTree(T val)
        {
            root = new threadNode<T>(val);
        }

        void insert(T value);

        void PreThread(threadNode<T> *root, threadNode<T> *&pre);

        void PreOrder(threadNode<T> *root);

        void InThread(threadNode<T> *root, threadNode<T> *&pre);

        void InOrder(threadNode<T> *root);

        void PostThread(threadNode<T> *root, threadNode<T> *&pre);

        void PostOrder(threadNode<T> *root);

        threadNode<T>* getRoot();
    };


    template<class T>
    void ThreadTree<T>::insert(T value) {
        if (!root) {
            root = new threadNode<T>(value);
            return;
        } else {
            threadNode<T> *current = root;
            threadNode<T>* pre = root;
            while (current) {
                if (value > current->value) {
                    pre =current;
                    current = current->rightChild;
                    continue;
                } else if (value < current->value) {
                    pre = current;
                    current = current->leftChild;
                    continue;
                } else {
                    return;
                }
            }
            if(value < pre->value) {
                pre->leftChild = new threadNode<T>(value);
            }else{
                pre->rightChild = new threadNode<T>(value);
            }
            return;
        }
    }

    template<class T>
    void ThreadTree<T>::InThread(threadNode<T> *root, threadNode<T> *&pre) {
        threadNode<T> *current = root;
        if (current != NULL) {
            InThread(current->leftChild, pre);   //左看看

            //visit
            if (current->leftChild == NULL) {
                current->leftChild = pre;
                current->leftTag = THREAD;
            }
            if ((pre) && pre->rightChild == NULL) {
                pre->rightChild = current;
                pre->rightTag = THREAD;
            }
            pre = current;

            InThread(current->rightChild, pre);  //右看看
        }
    }


    template<class T>
    void ThreadTree<T>::PreThread(threadNode<T> *root, threadNode<T> *&pre) {
        threadNode<T> *current = root;
        while (current) {
            if (current->leftChild == NULL) {
                current->leftChild = pre;
                current->leftTag = THREAD;
            }
            if (pre && pre->rightChild == NULL) {
                pre->rightChild = current;
                pre->rightTag = THREAD;
            }
            pre = current;
            PreThread(current->leftChild, pre);
            PreThread(current->rightChild, pre);
        }
    }

    template<class T>
    void ThreadTree<T>::PostThread(threadNode<T> *root, threadNode<T> *&pre) {
        threadNode<T> *current = root;
        while (current) {
            PreThread(root->leftChild, pre);
            PreThread(root->rightChild, pre);
            if (current->leftChild == NULL) {
                current->leftChild = pre;
                current->leftTag = THREAD;
            }
            if (pre && pre->rightChild == NULL) {
                pre->rightChild = current;
                pre->rightTag = THREAD;
            }
            pre = current;
        }
    }

    template<class T>
    void ThreadTree<T>::PreOrder(threadNode<T> *root) {
        if (!root) {
            return;
        } else {
            using std::cout;
            using std::endl;
            threadNode<T> *current = root;
            while (current) {
                while (current->leftChild && current->leftTag == LINK) {
                    cout << current->value << endl;
                    current = current->leftChild;
                }
                cout << current->value << endl;
                if (current->rightTag == THREAD) {
                    current = current->rightChild;
                }
            }
        }
    }

    template<class T>
    void ThreadTree<T>::InOrder(threadNode<T> *root) {
        if (!root) {
            return;
        } else {
            using std::cout;
            using std::endl;
            threadNode<T> *current = root;
            while (current) {
                while (current->leftTag == LINK) {
                    current = current->leftChild;
                }
                cout << current->value << endl;
                while (current && current->rightTag == THREAD) {
                    current = current->rightChild;
                    cout << current->value << endl;
                }
                current = current->rightChild;
            }
        }
    }

    template<class T>
    void ThreadTree<T>::PostOrder(threadNode<T> *root) {
        if (!root) {
            return;
        } else {
            using std::cout;
            using std::endl;
            threadNode<T> *current;
            // too easy to write
        }
    }

    template<class T>
    threadNode<T>* ThreadTree<T>::getRoot(){
        return root;
    }
}
#endif //WORKPLACE_THREADTREE_H
