//
// Created by 85375 on 2025/11/20.
//

#ifndef INC_2_2_10_SLINKLIST_H
#define INC_2_2_10_SLINKLIST_H

#include <iostream>
#include <cstring>
using namespace std;
class transcend_limit{};
template <class elemType>
class sLinklist {
private:
    struct node {
        elemType data;
        node *next;
        node() :next(nullptr){};
        explicit node(const elemType &x, node *rear = nullptr): data(x),next(rear){};
    };
    int current_length;
    node *head;

    node *move (int po) const {
        if (po>=current_length) throw;
        node *tmp = head;
        for (int step=0;step<po;++step) {
            tmp = tmp->next;
        }
        return tmp->data; //!!这里补药删除tmp，因为没有分配新的空间
    }
    node *end() {
        node *tmp= head ->next;
        while (tmp != nullptr) {
            tmp = tmp->next;
        }
        return tmp;
    }

public:
    sLinklist():current_length(0) {
        head = new node();
    }
    ~sLinklist() {
        clear();
        delete head;
    }

    void clear() {
        node *tmp = head->next,*q;
        while (tmp != nullptr){
            q= tmp->next;
            delete tmp;
            tmp = q;
            current_length =0;
        }
    }

    inline int get_size() const {return current_length;}

    void push_back(const  elemType& x){        //注意一下push_back 的作用是把存储类型直接加在尾部，咱不需要知道node
        node *tmp =new node(x);
        node *rear = head;
        for (int i=0;i<current_length;++i) {
            rear = rear->next;
        }
        rear->next = tmp;
        current_length++;
    }

    void push_front(const elemType& x) {
        node *tmp = new node(x);
        tmp->next = head->next;
        head->next = tmp;
        current_length++;
    }

    void insert(int seq,const elemType x) {
        if (seq<0 || seq >current_length)
            throw ;
        node *rear =head;
        for (int i=0;i<seq;++i) {
            rear = rear->next;
        }
        node *tmp = new node (x,rear->next);
        rear->next = tmp;
        current_length++;
    } // 在该位置之前插入内容中，0为head->next

    void erase(int seq) {
        if (seq>current_length-1)
            throw ;
        node *tmp = head;
        for (int i=0;i<seq;++i) {
            tmp = tmp->next;
        }
        node *rear = tmp->next;
        tmp->next = rear->next;
        delete rear;
        current_length--;
    }
    void print_all() const{
        if (0 == current_length) {
            cout<<"No data exists!!"<<endl;
            return;
        }
        node *tmp = head->next;
        while (tmp != nullptr) {
            cout << tmp->data;
            tmp = tmp->next;
        }
        cout<<'\n';
    }



};

#endif //INC_2_2_10_SLINKLIST_H
//
// Created by 85375 on 2025/11/20.
//
// #include "sLinklist.h"
//
// int main() {
//     sLinklist<char> list;
//     list.print_all();
//     list.push_back('a');
//     list.print_all();
//     return 0;
// }