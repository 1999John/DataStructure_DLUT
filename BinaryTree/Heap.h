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
    public:
        Heap(T *arr, int num, int max);

        virtual void buildHeap()=0;

        virtual void sift(Position root)=0;

        virtual bool insert(T value)=0;

        virtual bool remove(Position pos)=0;

        bool isLeaf(Position pos) const;

        Position leftChild(Position pos) const;

        Position rightChild(Position pos) const;

        Position parent(Position pos) const;

        void display();

    protected:
        T *heapArray;
        int currentSize;
        int maxSize;
    };


    template<class T>
    class MaxHeap : public Heap<T> {
    public:
        MaxHeap(T *arr, int num, int max) : Heap<T>(arr, num, max) {}

        void buildHeap();

        void sift(Position root);

        bool insert(T value);

        void moveMax();

        T removeMax();

        bool remove(Position pos) override;


    };


    template<class T>
    class MinHeap : public Heap<T> {
    public:
        MinHeap(T *arr, int num, int max) : Heap<T>(arr, num, max) {}

        void buildHeap();

        void sift(Position root) override;

        bool insert(T value) override;

        bool remove(Position pos);

        void moveMin();

        T removeMin();
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
    void Heap<T>::display() {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << heapArray[i] << std::endl;
        }
    }


    template<class T>
    void MaxHeap<T>::buildHeap() {
        for (int i = (this->currentSize - 2) / 2; i >= 0; sift(i), --i);
    }

    template<class T>
    void MaxHeap<T>::sift(Position root) {
        Position i = root;
        Position j = this->leftChild(i);

        while (j < this->currentSize && j >= 0) {
            if ((j <= this->currentSize - 2) && (this->heapArray[j] < this->heapArray[j + 1])) {
                //  if have right child and right child is bigger than left child;
                j++;
            }
            if (this->heapArray[i] < this->heapArray[j]) {
                // if parent is less than the biggest child -> change;
                T temp = this->heapArray[i];
                this->heapArray[i] = this->heapArray[j];
                this->heapArray[j] = temp;
                i = j;
                j = this->leftChild(j);
            } else {
                break; // keep original status -> don't need adjust.
            }
        }
    }

    template<class T>
    bool MaxHeap<T>::insert(T value) {
        if (this->currentSize < this->maxSize) {
            Position j = this->currentSize;
            this->heapArray[this->currentSize++] = value;

            Position i = (j - 1) / 2;

            for (; i >= 0;  i = (i - 1) / 2){
                sift(i);
                if(i==0){
                    break;
                }
            }
            return true;
        }
        return false;
    }

    template<class T>
    bool MaxHeap<T>::remove(Position pos) {
        if (pos < 0 || pos >= this->currentSize) {
            return false;
        } else if (pos == this->currentSize - 1) {
            this->currentSize--;
            return true;
        } else {
            this->heapArray[pos] = this->heapArray[this->currentSize--];
            sift(pos);
        }
    }

    template<class T>
    void MaxHeap<T>::moveMax() {
        remove(0);
    }

    template<class T>
    T MaxHeap<T>::removeMax() {
        if(this->currentSize>0){
            T ret = this->heapArray[0];
            moveMax();
            return ret;
        }
        throw "empty heap";
    }

    template<class T>
    void MinHeap<T>::sift(Position root) {
        Position i = root;
        Position j = this->leftChild(i);
        T temp = this->heapArray[i];
        while (j < this->currentSize && j >= 0) {
            if ((j <= this->currentSize - 2) && this->heapArray[j] > this->heapArray[j + 1]) {
                // if have the right child and right child is less than left child;
                j++;
            }
            if (temp > this->heapArray[j]) {
                this->heapArray[i] = this->heapArray[j];
                this->heapArray[j] = temp;
                i = j;
                j = this->leftChild(j);
            } else {
                break;
            }
        }
    }


    template<class T>
    void MinHeap<T>::buildHeap() {
        for (int i = (this->currentSize - 1) / 2; i >= 0; this->sift(i), --i);
    }

    template<class T>
    bool MinHeap<T>::insert(T value) {
        if (this->currentSize < this->maxSize) {
            Position j = this->currentSize;
            this->heapArray[j] = value;
            this->currentSize++;
            Position i = (j - 1) / 2;
            for (; i >= 0; --i)
            {
                sift(i);
                if(i==0){
                    break;
                }
            }
            return true;
        }
        return false;
    }

    template<class T>
    bool MinHeap<T>::remove(Position pos) {
        if (pos < 0 || pos > this->currentSize) {
            return false;
        } else if (pos == this->currentSize - 1) {
            this->currentSize--;
            return true;
        } else {
            this->heapArray[pos] = this->heapArray[this->currentSize--];
            sift(pos);
        }
    }

    template<class T>
    void MinHeap<T>::moveMin() {
        if (this->currentSize > 0) {
            remove(0);
        }
    }

    template<class T>
    T MinHeap<T>::removeMin() {
        if (this->currentSize > 0) {
            T min = this->heapArray[0];
            moveMin();
            return min;
        }
        throw "empty heap";
    }

}
#endif //WORKPLACE_HEAP_H






