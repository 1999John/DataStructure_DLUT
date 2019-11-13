//
// Created by ThinkPad on 2019/11/10.
//

#ifndef WORKPLACE_CIRCLEQUEUE_H
#define WORKPLACE_CIRCLEQUEUE_H

template<class T>
class CircleQueue {
private:
    T *myQueue;
    int maxSize;
    int front;
    int rear;
    bool notEmptyTag;
public:
    CircleQueue(int maxSize);

    bool push(T value);

    T Front();

    void pop();

    int length();

    bool empty();
};
template <class T>
CircleQueue<T>::CircleQueue(int maxSize) : maxSize(maxSize) {
    myQueue = new T[this->maxSize];
    front = rear = 0;
    notEmptyTag = false;
}
template<class T>
bool CircleQueue<T>::push(T value) {
    if (notEmptyTag && rear == front) {
        return false;
    } else {
        if (notEmptyTag == false) {
            notEmptyTag = true;
        }
        myQueue[rear] = value;
        rear = (rear + 1) % maxSize;
        return true;
    }
}

template<class T>
T CircleQueue<T>::Front() {
    if(empty()) {
        throw "error empty queue";
    }
    return myQueue[front];
}

template<class T>
void CircleQueue<T>::pop() {
    if(!notEmptyTag) {
        return;
    } else{
        front = (front+1)%maxSize;
        if(front==rear) notEmptyTag = false;
        return;
    }
}

template<class T>
int CircleQueue<T>::length() {
    if(!empty()&&rear==front) return maxSize;
    return (rear-front+maxSize)%maxSize;
}

template<class T>
bool CircleQueue<T>::empty() {
    return !notEmptyTag;
}


#endif //WORKPLACE_CIRCLEQUEUE_H
