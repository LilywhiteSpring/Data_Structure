#include <iostream>
using namespace std;
struct node {
    int key;
    node *next;

    node(): key(-1) , next(nullptr){}
    explicit node(int key): key(key) , next(nullptr){}
};
void Bucket_sort(int *data , int size);
int main() {
    int a[] = {1 , 6 , 3 , 2 , 7 , 3 , 4 , 11 , 50 , 100 , 302 , 102 , 1};
    Bucket_sort(a , 13);
    for (int i : a)
        cout<<i<<' ';
    return 0;
}
void Bucket_sort(int *data , int size) {
    if (size <= 1)
        return;
    int i = 0 , base = 1;
    auto head = new node(data[i]);
    node *rear = head , *tmp;
    for (i = 1 ; i < size ; ++i) {
        rear-> next = new node(data[i]);
        rear = rear-> next;
    }
    rear-> next = nullptr;
    node *Bucket[10] , *Last[10];
    int max = head-> key , len = 0;
    for (rear = head-> next ; rear != nullptr ; rear = rear-> next) {
        if (rear-> key > max)
            max = rear-> key;
    }
    while (max > 0) {
        max /= 10;
        len++;
    }

    for (int j = 1 ; j <= len ; ++j) {
        for (int seq = 0 ; seq < 10 ; ++seq)
            Bucket[seq] = Last[seq] = nullptr;
        for (tmp = head ; tmp != nullptr ; tmp = tmp-> next) {
            int tail = tmp-> key / base % 10;
            if (!Bucket[tail])
                Bucket[tail] = Last[tail] = tmp;
            else {
                Last[tail]-> next = tmp;
                Last[tail] = Last[tail]-> next;
            }
        }
        head = nullptr;
        for (int seq = 0 ; seq < 10 ; ++seq) {
            if (!Bucket[seq])
                continue;
            if (!head) {
                head = Bucket[seq];
                tmp = Last[seq];
            }
            else {
                tmp-> next = Bucket[seq];
                tmp = Last[seq];
            }
        }
        tmp-> next = nullptr;
        base *= 10;
    }
    tmp = head;
    for (int seq = 0 ; seq < size ; ++seq) {
        data[seq] = tmp-> key;
        tmp = tmp-> next;
    }
    for (i = 0 ; i < size ; ++i) {
        rear = head-> next;
        delete head;
        head = rear;
    }
}
