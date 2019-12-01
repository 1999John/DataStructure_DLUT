//
// Created by ThinkPad on 2019/11/19.
//

#ifndef WORKPLACE_HUFFMANTREE_H
#define WORKPLACE_HUFFMANTREE_H

#include "Node.h"
#include "Heap.h"
#include <map>
namespace BinaryTree{
    using std::map;
    template <class T>
    class HuffmanTree{
    private:
        HuffmanTreeNode<T>* root;
        void MergeTree(HuffmanTreeNode<T> *&ht1,HuffmanTreeNode<T> *&ht2,HuffmanTreeNode<T>* parent);
        // merge ht1 and ht2 with parent
        void deleteTree(HuffmanTreeNode<T>* root);

    public:
        HuffmanTree(T weight[],char* arr,int n);

        map<T,char*> getlist();
    };

    template<class T>
    HuffmanTree<T>::HuffmanTree(T weight[],char * arr,int n) {
        // weight is the weight array,n is th length of array
        MinHeap<HuffmanTreeNode<T>> heap(weight,0,n);
        HuffmanTreeNode<T>* parent;
        HuffmanTreeNode<T>* Nodelist = new HuffmanTreeNode<T>[n];
        for (int i = 0; i < n; ++i) {
            Nodelist[i].value = weight[i];
            Nodelist[i].parent = Nodelist[i].leftChild = Nodelist[i].rightChild = NULL;
            heap.insert(Nodelist[i]);
        }
        for (int i = 0; i < n-1; ++i) {
            parent = new HuffmanTreeNode<T>(0);
            try {
                HuffmanTreeNode<T>& firstChild = heap.removeMin();
                HuffmanTreeNode<T>& secondChild = heap.removeMin();
                MergeTree(firstChild,secondChild,parent);
            }
            catch (const char* e){
                std::cout<<e<<std::endl;
            }
            heap.insert(*parent);
            root = parent;
        }
        delete[] Nodelist;
    }

    template<class T>
    void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> *&ht1, HuffmanTreeNode<T> *&ht2, HuffmanTreeNode<T> *parent) {
        ht1->parent=parent;
        ht2->parent=parent;
        parent->leftChild=ht1;
        parent->rightChild=ht2;
    }

    template<class T>
    void HuffmanTree<T>::deleteTree(HuffmanTreeNode<T> *root) {
        if (root){
            deleteTree(root->leftChild);
            deleteTree(root->rightChild);
            delete root;
        }
    }

    template<class T>
    map<T, char *> HuffmanTree<T>::getlist() {
        map<T, char*> ret;

    }
}
#endif //WORKPLACE_HUFFMANTREE_H
