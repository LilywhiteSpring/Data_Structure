//
// Created by 85375 on 2025/12/15.
//
#ifndef AATREE_AATREE_H
#define AATREE_AATREE_H
#include <iostream>
using namespace std;
template <class KEY , class OTHER>
struct set {
    KEY key;
    OTHER other;
};

template <class KEY , class OTHER>
class AATree {
private:
    struct AANode {
        set<KEY , OTHER> data;

        AANode *l_child;
        AANode *r_child;
        int layer;
        explicit AANode(const set<KEY , OTHER> &s , AANode *left = nullptr, AANode *right = nullptr , int h = 1): data(s) , l_child(left) , r_child(right) , layer(h){};
    };

    AANode *root;
public:
    AATree(): root(nullptr){}
    ~AATree() { Clear(root) ; root = nullptr; }
    void Clear(){ Clear(root);}
    OTHER* Find(const KEY &key) const;
    void insert(const set<KEY , OTHER> &x){ insert(x ,root); }
    void remove(const KEY &x){ remove(x , root); }
private:
    void Clear(AANode *n);
    void insert(const set<KEY , OTHER> &x , AANode *&p);
    void remove(const KEY &x , AANode *&p);
    void LL(AANode *&p);
    void RR(AANode *&p);
};

template <class KEY , class OTHER>
OTHER* AATree<KEY , OTHER>::Find(const KEY &key) const {
    AANode *tmp = root;
    while (tmp) {
        if (key == tmp-> data.key)
            return &tmp-> data.other;
        if (key > tmp-> data.key)
            tmp = tmp-> r_child;
        else
            tmp = tmp-> l_child;
    }
    return nullptr;
}

template <class KEY , class OTHER>
void AATree<KEY , OTHER>::Clear(AANode *n) {
    if (!n)
        return;
    Clear(n-> l_child);
    Clear(n-> r_child);
    delete n;
}
template <class KEY , class OTHER>
void AATree<KEY , OTHER>::insert(const set<KEY , OTHER> &x , AANode *&p) {
    if (!p){
        p = new AANode(x);
        cout<<x.key<<"Insert finishes!"<<endl;
        return;
    }
    if (x.key == p-> data.key) {
        cout<<"Repeated Key!"<<endl;
        return;
    }
    if (x.key > p-> data.key)
        insert(x , p-> r_child);
    else
        insert(x , p-> l_child);
    LL(p);
    RR(p);
};

template <class KEY , class OTHER>
void AATree<KEY , OTHER>::LL(AANode *&p) {
    if (p-> l_child && p-> layer == p-> l_child-> layer ) {
        AANode *tmp = p-> l_child;
        p-> l_child = tmp-> r_child;
        tmp-> r_child = p;
        p = tmp;
    }
}
template <class KEY , class OTHER>
void AATree<KEY , OTHER>::RR(AANode *&p) {
    if (p-> r_child && p-> r_child && p-> r_child-> r_child && p-> layer == p-> r_child -> r_child -> layer) {
        AANode *tmp = p-> r_child;
        p-> r_child = tmp-> l_child;
        tmp-> l_child = p;
        ++tmp-> layer;
        p = tmp;
    }
}
template <class KEY , class OTHER>
void AATree<KEY , OTHER>::remove(const KEY &x , AANode *&p) {
    if (!p)
        return;
    if (x > p-> data.key)
        remove(x , p-> r_child);
    else if (x < p-> data.key)
        remove(x , p-> l_child);
    else {
        if (p-> r_child && p-> l_child) {
            AANode * tmp = p-> r_child;
            while (tmp-> l_child)
                tmp = tmp-> l_child;
            p-> data = tmp-> data;
            remove(tmp-> data.key , p-> r_child);
        }
        else{
            AANode *tmp = p;
            p= p-> r_child;
            delete tmp;
            return;
        }
    }

    if (!p-> l_child || !p-> r_child)
        p-> layer = 1;
    else p-> layer = (p-> l_child-> layer < p-> r_child-> layer) ? p-> l_child-> layer + 1 : p-> r_child -> layer + 1;
    if (p-> r_child && p-> layer < p-> r_child-> layer) {
        p-> r_child-> layer = p-> layer;
    }
    LL(p);
    if (p-> r_child)
        LL(p-> r_child);
    if (p-> r_child && p-> r_child-> r_child)
        LL(p-> r_child-> r_child);
    RR(p);
    if (p-> r_child)
        RR(p-> r_child);
}

#endif //AATREE_AATREE_H