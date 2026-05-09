//
// Created by 85375 on 2025/12/18.
//

#ifndef HASHTABLE_CLOSE__HASHTABLE_H
#define HASHTABLE_CLOSE__HASHTABLE_H
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <class KEY , class OTHER>
struct set {
    KEY key;
    OTHER other;
};

template <class KEY , class OTHER>
class HashTable {
private:
    enum State {
        Empty,
        Del,
        Active,
    };
    struct Node{
        set<KEY , OTHER> data;
        State state;

        Node():state(Empty){};
        explicit Node(const set<KEY , OTHER> &x): data(x) , state(Active){}
    };
    Node *array;
    int capacity;
    int length;
    int (*key_cast) (const KEY &x);

    void double_space();
    static int default_key(const int &x) {return x;}
    static int max_prime(int capacity);

public:
    explicit HashTable(int size = 10 , int (*f) (const KEY &x) = default_key): capacity(size) , key_cast(f) , length(0){
        array = new Node [capacity];
    }
    ~HashTable() {
        delete [] array;
    }
    set<KEY , OTHER>* find(const KEY &x);
    void insert(const set<KEY , OTHER> &x);
    void remove(const KEY &x);
    void print() const;
};



template <class KEY , class OTHER>
int HashTable<KEY , OTHER>::max_prime(int capacity) {
    int i = capacity;
    if (i <= 2)
        return 2;
   if (capacity % 2 == 0)
       i--;
        for (int j = 2 ; j <= sqrt(i) ; ++j ) {
            if (0 == i % j) {
                i -= 2;
                j = 2;
            }
        }
    return i;
}

template <class KEY , class OTHER>
void HashTable<KEY , OTHER>::insert(const set<KEY , OTHER> &x) {
    if (length >= capacity / 2)
        double_space();
    ++length;
     int div = max_prime(capacity) , key = key_cast(x.key) % div;
    while (true) {
        if (Active == array[key].state && x.key == array[key].data.key) {
            cout<<"重复插入，关键字已存在！！\n";
            length--;//这步很重要，回退长度！！或者长度插入成功后再加更好，这里是为了提醒自己逻辑问题
            return;
        }
        if (array[key].state != Active) {
            array[key].data = x;
            array[key].state = Active;
            break;
        }
        key = (key + 1) % div;
    }
}

template <class KEY , class OTHER>
set<KEY , OTHER>* HashTable<KEY , OTHER>::find(const KEY &x) {
    int div = max_prime(capacity) , init = key_cast(x) % div;
    int key = init;
    do {
        if (Empty == array[key].state)
            break;
        if (Active == array[key].state && x == array[key].data.key) {
            return &array[key].data;
        }
        key = (key + 1) % div;
    }while (key != init);
    cout<<"未查找到关键字为"<<x<<"的数据！\n";
    return nullptr;
}


template <class KEY , class OTHER>
void HashTable<KEY , OTHER>::remove(const KEY &x) {
    int div = max_prime(capacity) , init = key_cast(x) % div;
    int key = init;
    do {
        if (Empty == array[key].state)
            break;
        if (Active == array[key].state && x == array[key].data.key) {
            array[key].state = Del;
            length--;//这里就是删除成功后再修改长度
            return;
        }
        key = (key + 1) % div;
    }while (key != init);
    cout<<"关键字不存在！！\n";
}
template <class KEY , class OTHER>
void HashTable<KEY , OTHER>::print() const {
    for (int i = 0 ; i < capacity ; ++i) {
        if (Active == array[i].state)
            cout<<array[i].data.key<<'\t'<<array[i].data.other<<endl;
    }
}
template <class KEY , class OTHER>
void HashTable<KEY , OTHER>::double_space() {
    vector<Node*> nodes ;
    set<KEY , OTHER> tmp;
    for (int i = 0 ; i < capacity ; ++i) {
        if (Active == array[i].state)
            nodes.push_back(&array[i]);
    }
    capacity *= 2;
    Node* old = array;
    array = new Node [capacity];
    length = 0;
    while (!nodes.empty()) {
        tmp = nodes.back()-> data;
        nodes.pop_back();
        insert(tmp);
    }
    delete[] old;
}
#endif //HASHTABLE_CLOSE__HASHTABLE_H