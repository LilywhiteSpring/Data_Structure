//
// Created by 85375 on 2025/11/18.
//

#ifndef INC_2_1_LINKLIST_LIST_H
#define INC_2_1_LINKLIST_LIST_H
#include <iostream>
using namespace std;

template <class elemType>
class list {
public:
    virtual void display();
    virtual void clear();
    virtual void insert(list * , const elemType &x);
    virtual int scale();
    virtual void push_back(const elemType &);
    virtual int search(const elemType &x);
    virtual elemType visit(list *);
    virtual ~list();
};

template<class elemType>
class Linklist: public list<elemType> {
private:

    class node {
    private:
        elemType data;
        node *prev;
        node *next;

    public:
        node(): prev(nullptr) , next (nullptr){};
        explicit node(elemType x,node * node1 = nullptr ,node *node2 =nullptr):data(x) , prev(node1),next(node2) {};
    };

    int scale;
    node *head, * tail;

public:
    Linklist():scale(0) {
        head = new node;
        head ->next = tail =new node;
        tail ->prev = head;
    };
    explicit Linklist(int n) {
        scale = n;
        elemType x;
        head = new node ;
        head->next = tail = new node;
        node src = head;
        for (int i=1;i<=n;++i) {
            node tmp = new node ;
            cin>>x;
            tmp ->data = x;
            tmp ->next = src ->next;
            tmp ->prev = src ;
            src ->next ->prev = tmp;
            src ->next = tmp;
            src =tmp;
        }
    }
    ~Linklist() {
        node *tmp1 = head ,*tmp2;
        while ( tmp1 ->next != nullptr) {
            tmp2 =tmp1->next;
            delete tmp1;
            tmp1 = tmp2;
        }
    }

    void push_back(const elemType &x) {
        scale ++;
        node *tmp = new node ;
        tmp -> data = x;
    }

    class Itr {
        node *current;
    public:

        explicit Itr(node *p = nullptr):current(p){};

        const Itr& operator++() {
            current = current->next;
            return *this;
        }
        bool operator != (const node* tmp) {
            return (!tmp == current);
        }

        // friend class Linklist<elemType>;
    };
    void insert( Itr& p ,const elemType &x) {
        node *tmp = new node;
        tmp ->data = x;
        p.current->next->prev = tmp;
        tmp ->next =p.current->next;
        p.current->next = tmp;
        tmp->prev =p.current;
    }
    void erase(Itr &p ) {
        p.current->prev->next = p.current->next;
        p.current->next->prev = p.current->prev;
        delete p->current ;
    }
    elemType &visit(Itr &p) {
        return (p.current->data);
    }
    Itr begin() {return (Ire(head));}
    Itr end() {return Itr(tail);}
    void display() {
        Itr itr = begin();
        for
    }

};

#endif //INC_2_1_LINKLIST_LIST_H