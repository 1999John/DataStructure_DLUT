//
// Created by ThinkPad on 2019/11/19.
//

#ifndef WORKPLACE_HEAP_H
#define WORKPLACE_HEAP_H

#include <iostream>

namespace BinaryTree {
    typedef int Position;

    template<class T>
    class Heap {
    private:
        T *heapArray;
        int currentSize;
        int maxSize;
    public:
        Heap(T *arr, int num, int max);

        void buildMaxHeap();

        bool isLeaf(Position pos) const;

        Position leftChild(Position pos) const;

        Position rightChild(Position pos) const;

        Position parent(Position pos) const;

//        bool remove(int pos);
        void siftDown(Position root);

        void siftUp(Position root);

        void display();

        bool insert(T &value);

        void moveMax();         // 从堆顶移动最大值到尾部
        T &RemoveMax();         //从堆顶删除最大值并且返回
    };

    template<class T>
    Heap<T>::Heap(T *arr, int num, int max) {
        maxSize = max;
        heapArray = new T[maxSize];
        currentSize = num;
        for (int i = 0; i < currentSize; ++i) {
            heapArray[i] = arr[i];
        }
    }

    template<class T>
    bool Heap<T>::isLeaf(Position pos) const {
        Position tail = currentSize - 1;
        if (pos > (tail - 1) / 2) return true;
        return false;
    }

    template<class T>
    Position Heap<T>::leftChild(Position pos) const {
        Position leftposition = pos * 2 + 1;
        if (leftposition >= currentSize)
            return -1;
        else {
            return leftposition;
        }
    }

    template<class T>
    Position Heap<T>::rightChild(Position pos) const {
        Position rightposition = pos * 2 + 2;
        if (rightposition >= currentSize) {
            return -1;
        } else {
            return rightposition;
        }
    }

    template<class T>
    Position Heap<T>::parent(Position pos) const {
        Position parentposition = (pos - 1) / 2;
        if (parentposition < 0) {
            return -1;
        } else {
            return parentposition;
        }
    }

    template<class T>
    void Heap<T>::buildMaxHeap() {
        for (int i = (currentSize - 1) / 2; i >= 0; --i) {
            siftDown(i);
        }
    }

    template<class T>
    void Heap<T>::siftDown(Position root) {
        Position i = root;
        Position j = leftChild(i);
        T temp = heapArray[i];
        while (j < currentSize && j >= 0) {
            if ((j < currentSize - 2) && (heapArray[j] < heapArray[j + 1])) {
                //  if have right child and right child is bigger than left child;
                j++;
            }
            if (temp < heapArray[j]) {
                // if parent is less than the biggest child -> change;
                heapArray[i] = heapArray[j];
                heapArray[j] = temp;
                i = j;
                j = leftChild(j);
            } else {
                break; // keep original status -> don't need adjust.
            }
        }
    }

    template<class T>
    void Heap<T>::siftUp(Position root) {
        Position i = root;
        Position j = leftChild(i);
        T temp = heapArray[i];
        while (j < currentSize && j >= 0) {
            if ((j < currentSize - 2) && heapArray[j] > heapArray[j + 1]) {
                // if have the right child and right child is less than left child;
                j++;
            }
            if (temp > heapArray[j]) {
                heapArray[i] = heapArray[j];
                heapArray[j] = temp;
                i = j;
                j = leftChild(j);
            } else {
                break;
            }
        }
    }

    template<class T>
    void Heap<T>::display() {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << heapArray[i] << std::endl;
        }
    }
}
#endif //WORKPLACE_HEAP_H

//李超同学工作认真，积极上进，豪迈大气，能非常好的解决他人的困惑，解决班级矛盾，能为许多事情提神而出






