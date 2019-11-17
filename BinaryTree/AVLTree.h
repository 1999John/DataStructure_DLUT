//
// Created by ThinkPad on 2019/11/15.
//

#ifndef WORKPLACE_AVLTREE_H
#define WORKPLACE_AVLTREE_H

#include <iostream>
#include <stack>

#define Left false
#define Right true
template <class T>
struct avlNode{
    T value;
    avlNode<T>* leftChild;
    avlNode<T>* rightChild;
    avlNode<T>* parent;
    bool posi;
    int balFactor;
    avlNode(T v,avlNode<T>* p,bool po,avlNode<T>* l=NULL,avlNode<T>* r = NULL,int b=0):value(v){
        this->parent = p;
        posi = po;
        leftChild = l;
        rightChild = r;
        balFactor = b;
    }
};

namespace BinaryTree{
    template <class T>
    class AVLTree {
    private:
        avlNode<T>* root;

        void AdjustMent(avlNode<T>* insertNode);

        void singleLeft(avlNode<T>* A,avlNode<T>* B);

        void singleRight(avlNode<T>* A,avlNode<T>* B);

        void doubleLeftAndRight(avlNode<T>* A,avlNode<T>* B,avlNode<T>* C);

        void doubleRightAndLeft(avlNode<T>* A,avlNode<T>* B,avlNode<T>* C);

        void Rotate(avlNode<T>* A,avlNode<T>* B,avlNode<T>* C);

        void setAllbalFacto(avlNode<T>* root);
    public:
        AVLTree();
        void insert(T value);

        void getHeight(avlNode<T>* root,int * height);

        void inOrder(avlNode<T>* root);

        avlNode<T>* getRoot() { return root;}
    };

    template<class T>
    AVLTree<T>::AVLTree() {
        root = NULL;
    }

    template<class T>
    void AVLTree<T>::insert(T value) {
        if (!root) {
            root = new avlNode<T>(value,NULL,Left);
            return;
        }
        avlNode<T> *pointer = this->root;
        avlNode<T> *pre = this->root;
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
            pre->leftChild = new avlNode<T>(value,pre,Left);
            AdjustMent(pre->leftChild);
            return;
        }
        if (pre->value < value) {
            pre->rightChild = new avlNode<T>(value,pre,Right);
            AdjustMent(pre->rightChild);
//            插入调整平衡因子
            return;
        }
        return;
    }

    template<class T>
    void AVLTree<T>::setAllbalFacto(avlNode<T> *root) {
        if(root) {
            int leftheight = 0;
            int rightheight = 0;
            getHeight(root->leftChild,&leftheight);
            getHeight(root->rightChild,&rightheight);
            root->balFactor = rightheight - leftheight;
            setAllbalFacto(root->leftChild);
            setAllbalFacto(root->rightChild);
        }
    }

    template<class T>
    void AVLTree<T>::getHeight(avlNode<T> *root, int *height) {
        if(root) {
            (*height)++;
            int leftHeight = 0;
            int rightHeight = 0;
            getHeight(root->leftChild,&leftHeight);
            getHeight(root->rightChild,&rightHeight);
            (*height)+=leftHeight>rightHeight?leftHeight:rightHeight;
        }
    }

    template<class T>
    void AVLTree<T>::AdjustMent(avlNode<T> *insertNode) {
        setAllbalFacto(root);
        avlNode<T>* point = insertNode;
        using std::stack;

        stack<avlNode<T>*> st;

        while(point) {
            if(point->balFactor<-1||point->balFactor>1) {
                avlNode<T>* A = point;
                avlNode<T>* B = st.top();
                st.pop();
                avlNode<T>* C = st.top();
                st.pop();
                Rotate(A,B,C);
                setAllbalFacto(root);
                return;
            } else{
                st.push(point);
                point = point->parent;
            }
        }
    }

    template<class T>
    void AVLTree<T>::Rotate(avlNode<T> *A, avlNode<T> *B, avlNode<T> *C) {
        if(C->posi==Right&&B->posi==Right) {
            singleLeft(A,B);
            return;
        }
        if(C->posi==Left&&B->posi==Left) {
            singleRight(A,B);
            return;
        }
        if(C->posi==Right&&B->posi==Left) {
            doubleLeftAndRight(A,B,C);
            return;
        }
        if(C->posi==Left&&B->posi==Right) {
            doubleRightAndLeft(A,B,C);
            return;
        }
    }

    template<class T>
    void AVLTree<T>::singleRight(avlNode<T> *A, avlNode<T> *B) {
        avlNode<T>* parent = A->parent;
        if(A->posi==Left) {
            parent->leftChild = B;
            B->posi = Left;
        }
        if(A->posi==Right) {
            parent->rightChild = B;
            B->posi = Right;
        }

        B->parent = parent;
        avlNode<T>* BRightChild = B->rightChild;
        B->rightChild = A;

        A->posi = Right;
        A->parent = B;
        A->leftChild = BRightChild;

        if(BRightChild) {
            BRightChild->posi = Left;
            BRightChild->parent = A;
        }
    }

    template<class T>
    void AVLTree<T>::singleLeft(avlNode<T> *A, avlNode<T> *B) {
        avlNode<T>* parent = A->parent;
        if(A->posi==Left) {
            parent->leftChild = B;
            B->posi = Left;
        }
        if(A->posi==Right) {
            parent->rightChild = B;
            B->posi = Right;
        }

        B->parent = parent;
        avlNode<T>* BLeftChild = B->leftChild;
        B->leftChild = A;

        A->posi = Left;
        A->parent = B;
        A->rightChild = BLeftChild;

        if(BLeftChild) {
            BLeftChild->parent = A;
            BLeftChild->posi = Right;
        }

    }

    template<class T>
    void AVLTree<T>::doubleLeftAndRight(avlNode<T> *A, avlNode<T> *B, avlNode<T> *C) {
        avlNode<T>* parent = A->parent;
        if(A->posi==Left) {
            C->posi = Left;
            C->parent = parent;
        }
        if(A->posi==Right) {
            C->posi = Right;
            C->parent = parent;
        }

        avlNode<T>* CL = C->leftChild;
        avlNode<T>* CR = C->rightChild;

        A->parent = C;
        A->posi = Right;
        A->leftChild = CR;

        if(CR) {
            CR->posi = Left;
            CR->parent = A;
        }

        B->parent = C;
        B->posi = Left;
        B->rightChild = CL;

        if(CL) {
            CL->posi = Right;
            CL->parent = B;
        }
    }

    template<class T>
    void AVLTree<T>::doubleRightAndLeft(avlNode<T> *A, avlNode<T> *B, avlNode<T> *C) {
        singleRight(B,C);
        singleLeft(A,C);
    }

    template<class T>
    void AVLTree<T>::inOrder(avlNode<T> *root) {
        if(root) {
            std::cout<<root->value<<std::endl;
            inOrder(root->leftChild);
            inOrder(root->rightChild);
        }
    }

}

#endif //WORKPLACE_AVLTREE_H
