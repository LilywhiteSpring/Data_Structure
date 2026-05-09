//
// Created by 85375 on 2025/11/23.
//

#ifndef SEQQUEUE_SEQQUEUE_H
#define SEQQUEUE_SEQQUEUE_H
#include <iostream>
using namespace std;

template <typename elemType>
class seqQueue {
private:
    elemType * array;
    int capacity;
    int length;
    int front;
    void double_size() {
        elemType *tmp = array;
        array = new elemType [capacity *2];
        for (int i=1;i<=length;++i)
            array[i] = tmp[(front +i)%capacity];
        front = 0;
        capacity *=2;
        delete tmp;


    };
public:
    explicit seqQueue( int length = 10 ): capacity(length) ,length(0) , front(-1) {
        array = new elemType[length];
    }
    ~seqQueue(){delete [] array;};

    bool empty() {
        if ( 0 == length) {
            return true;
        }
        return false;
    }

    void enQueue(const elemType &x) {
        if (length == capacity)
            double_size();
        array [(front +length+1) % capacity] = x;
        ++length;
    }

    elemType deQueue() {
        if (empty()) {
            cout<<"队列为空！！"<<endl;
            throw;
        }
        --length;
        front = (++front) % capacity;
        return array[front];
    }

    elemType getHead() {
        return array[(front+1) % capacity];
    }
    int size() {return length;}
    int scale(){return capacity;}

    void print_all() {
        for (int i=1;i<=length;++i) {
            cout<<array[(front+i) % capacity]<<' ';
        }
        cout<<'\n';
    }
};



#endif //SEQQUEUE_SEQQUEUE_H