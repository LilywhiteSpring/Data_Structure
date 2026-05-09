//
// Created by 85375 on 2025/11/20.
//

#ifndef INC_2_1_10_SLINKLIST__SLINKLIST_H
#define INC_2_1_10_SLINKLIST__SLINKLIST_H

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
        for (int step=0;step<po;++step) {//need check
            tmp = tmp->next;
        }
        return tmp; //!!这里补药删除tmp，因为没有分配新的空间
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

    void push_back(const  elemType& x){        //别忘了push_back 的作用是把存储类型直接加在尾部，咱不需要知道node
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
    void list_get(elemType *x ,int length = 0) {
        if (length==0) {
            return;
        }
        for (int i=0;i<length;++i) {
            push_back(x[i]);
        }
    }//读入数组存储

    node * front() {
        return head;
    }
    node *end() {
        node *tmp= head ->next;
        while (tmp != nullptr) {
            tmp = tmp->next;
        }
        return tmp;
    }

    elemType & operator[] (int index) const {
        if (index > current_length) throw;
        node *tmp = move(index);
        return tmp->data;
    }
    node* visit(int index) const {//这里visit 和 move 的功能搞反了qwq
        if (index >current_length-1) throw;
        return move(index);
    }

    friend typename sLinklist<elemType>::node* sList_tail(sLinklist &s1 , sLinklist &s2);

};
template<class elemType>
sLinklist<elemType>::node *sList_tail(sLinklist<elemType> &s1,sLinklist<elemType> &s2) {
    if ( &s1 == &s2) {//tiang!!
        cout<<"不能操作同一链表！"<<endl;
        return nullptr; // or throw ?
    }
    if (s1.get_size() == 0 ||s2.get_size() == 0) {
        cout<<"一链表为空"<<endl;
        return nullptr;
    }
    int seq1 = s1.get_size() -1,seq2 = s2.get_size() -1;
    if (s1[seq1] != s2[seq2]) {
        cout<<"两数据无相同尾部！"<<endl;
        return nullptr;
    }
    typename sLinklist<elemType>::node *tmp;
    while (seq1>=0 &&seq2>=0){
        if (s1[seq1] == s2[seq2]) {
            tmp = s2.visit(seq2);
            if ( 0 == seq2)
                s2.head->next = s1.visit(seq1);
            else {
                s2.visit(seq2-1)->next = s1.visit(seq1);
            }
            delete tmp;
            --seq1;
            --seq2;
        }
        else {
            cout<<"合并尾部成功"<<endl;
            return s1.visit(seq1+1);
        }
    }
    cout<<"合并尾部成功"<<endl;
    return (s1.current_length<=s2.current_length) ? s1.head->next : s2.head->next;
}
#endif //INC_2_1_10_SLINKLIST__SLINKLIST_H