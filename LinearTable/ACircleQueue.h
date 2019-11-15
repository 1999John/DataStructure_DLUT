//
// Created by ThinkPad on 2019/11/13.
//

#ifndef WORKPLACE_ACIRCLEQUEUE_H
#define WORKPLACE_ACIRCLEQUEUE_H


namespace LinearTable {
    template<class T>
    class ACircleQueue {
    private:
        T *myQueue;
        int front;
        int rear;
        int maxSize;
    public:
        ACircleQueue(int maxSize);

        bool push(T value);

        T Front();

        void pop();

        bool empty();

        bool full();

        int len();
    };

    template<class T>
    ACircleQueue<T>::ACircleQueue(int maxSize) {
        this->maxSize = maxSize + 1;
        front = rear = 0;
        myQueue = new T[this->maxSize];
    }

    template<class T>
    bool ACircleQueue<T>::push(T value) {
        if ((rear + 1) % maxSize == front) {
            return false;
        } else {
            this->myQueue[rear] = value;
            rear = (rear + 1) % maxSize;
            return true;
        }
    }

    template<class T>
    T ACircleQueue<T>::Front() {
        if (!empty())
            return this->myQueue[front];
        else {
            throw "empty";
        }
    }

    template<class T>
    void ACircleQueue<T>::pop() {
        if (!empty())
            front = (front + 1) % maxSize;
        else return;
    }

    template<class T>
    bool ACircleQueue<T>::empty() {
        return rear == front;
    }

    template<class T>
    bool ACircleQueue<T>::full() {
        return (rear + 1) % maxSize == front;
    }

    template<class T>
    int ACircleQueue<T>::len() {
        return (rear - front + maxSize) % maxSize;
    }
}
#endif //WORKPLACE_ACIRCLEQUEUE_H
