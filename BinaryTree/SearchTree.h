//
// Created by ThinkPad on 2019/11/14.
//

#ifndef WORKPLACE_SEARCHTREE_H
#define WORKPLACE_SEARCHTREE_H

#include "RLNode.h"
#include <cmath>

namespace BinaryTree {
    template<class T>
    class SearchTree {
    private:
        rlNode<T> *root;
        void getWidthArr(rlNode<T>* root,int height,int *widthArr);

        bool allInleft(rlNode<T>* root);
    public:
        SearchTree(T value);

        bool find(rlNode<T> *root, T value);

        void insert(T value);

        void twoChild(rlNode<T>* root,int* num);

        void oneChild(rlNode<T>* root,int* num);

        void noChild(rlNode<T>* root,int* num);

        void getHeight(rlNode<T>* root,int* height);

        void getWidth(rlNode<T>* root,int* width);

        void getMax(rlNode<T>* root,T* max);

        void exchange(rlNode<T>* root);

        void inOrder(rlNode<T>* root);

        void deleteCurrentLeaf(rlNode<T>* root,rlNode<T>* parent);

        bool isCompleteBinaryTree();

        rlNode<T> *getRoot() const;
    };

    template<class T>
    SearchTree<T>::SearchTree(T value) {
        this->root = new rlNode<T>(value);
    }

    template<class T>
    void SearchTree<T>::insert(T value) {
        if(!root) {
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
    bool SearchTree<T>::find(rlNode<T> *root, T value) {
        if (root) {
            if (root->value == value) {
                return true;
            } else {
                return find(root->leftChild, value) || find(root->rightChild, value);
            }
        }
        return false;
    }

    template<class T>
    void SearchTree<T>::twoChild(rlNode<T> *root, int *num) {
        if(root) {
            if(root->leftChild&&root->rightChild){
                (*num)++;
            }
            twoChild(root->leftChild,num);
            twoChild(root->rightChild,num);
        }
    }

    template<class T>
    rlNode<T> *SearchTree<T>::getRoot() const {
        return root;
    }

    template<class T>
    void SearchTree<T>::oneChild(rlNode<T> *root, int *num) {
        if(root) {
            if((root->leftChild&&!root->rightChild)||(!root->leftChild&&root->rightChild)){
                (*num)++;
            }
            oneChild(root->leftChild,num);
            oneChild(root->rightChild,num);
        }
    }

    template<class T>
    void SearchTree<T>::noChild(rlNode<T> *root, int *num) {
        if(root) {
            if(!(root->leftChild||root->rightChild)) {
                (*num)++;
            } else{
                noChild(root->leftChild,num);
                noChild(root->rightChild,num);
            }
        }
    }

    template<class T>
    void SearchTree<T>::getHeight(rlNode<T> *root, int *height) {
        if(root) {
            (*height)++;
            int leftHeight = 0;
            int rightHeight = 0;
            getHeight(root->leftChild,&leftHeight);
            getHeight(root->rightChild,&rightHeight);
            (*height) += (leftHeight > rightHeight) ? leftHeight : rightHeight;
        }
    }

    template<class T>
    void SearchTree<T>::getWidthArr(rlNode<T> *root,int height,int* widthArr) {
        if(root) {
            widthArr[height]++;
            getWidthArr(root->leftChild,height+1,widthArr);
            getWidthArr(root->rightChild,height+1,widthArr);
        }
    }

    template<class T>
    void SearchTree<T>::getWidth(rlNode<T> *root, int *width) {
        int height = 0;
        getHeight(root,&height);
        int widthArr[height];
        for (int j = 0; j < height; ++j) {
            widthArr[j] = 0;
        }
        getWidthArr(root,0,widthArr);
        (*width) = widthArr[0];
        for (int i = 0; i < height; ++i) {
            if(widthArr[i]>(*width)) {
                (*width) = widthArr[i];
            }
        }
    }

    template<class T>
    void SearchTree<T>::getMax(rlNode<T> *root, T *max) {
        if(root) {
            if(root->value>(*max))
                (*max) = root->value;
            getMax(root->leftChild,max);
            getMax(root->rightChild,max);
        }
    }

    template<class T>
    void SearchTree<T>::exchange(rlNode<T> *root) {
        if(root) {
            rlNode<T>* left = root->leftChild;
            rlNode<T>* right = root->rightChild;
            root->leftChild = right;
            root->rightChild = left;

            exchange(root->leftChild);
            exchange(root->rightChild);
        }
    }

    template<class T>
    void SearchTree<T>::inOrder(rlNode<T> *root) {
        if(root) {
            std::cout<<root->value<<std::endl;
            inOrder(root->leftChild);
            inOrder(root->rightChild);
        }
    }

    template<class T>
    void SearchTree<T>::deleteCurrentLeaf(rlNode<T> *root,rlNode<T>* parent) {
        if(root) {
            if(!(root->leftChild||root->rightChild)) {
                std::cout<<"delete "<<root->value<<std::endl;
                if(root==parent->leftChild) {
                    parent->leftChild = NULL;
                    delete root;
                } else{
                    parent->rightChild = NULL;
                    delete root;
                }
            } else{
                deleteCurrentLeaf(root->leftChild,root);
                deleteCurrentLeaf(root->rightChild,root);
            }
        }
    }

    template<class T>
    bool SearchTree<T>::isCompleteBinaryTree() {
        int height = 0;
        this->getHeight(this->root,&height);
        int widthArr[height];
        for (int i = 0; i < height; ++i) {
            widthArr[i] = 0;
        }
        getWidthArr(this->root,0,widthArr);

        if(height==1) {
            return true;
        }
        if(widthArr[height-2]!=pow(2,height-2)){
            return false;
        } else{
            return allInleft(this->root);
        }
    }

    template<class T>
    bool SearchTree<T>::allInleft(rlNode<T>* root) {
        if(root) {
            if(root->rightChild&&!root->leftChild) {
                return false;
            } else{
                return allInleft(root->leftChild)&&allInleft(root->rightChild);
            }
        }
        return true;
    }

}


#endif //WORKPLACE_SEARCHTREE_H
