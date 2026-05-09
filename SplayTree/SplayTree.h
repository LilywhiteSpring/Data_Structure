//
// Created by 85375 on 2025/12/16.
//

#ifndef SPLAYTREE_SPLAYTREE_H
#define SPLAYTREE_SPLAYTREE_H
#include <iostream>
#include <stack>
using namespace std;
template <class KEY , class OTHER>
struct set {
    KEY key;
    OTHER other;
};

template <class KEY , class OTHER>
class SplayTree {
private:
    enum type {
        Zig,
        Zag,
        X,
        False,
    };

    struct Node {
        set<KEY , OTHER> data;
        Node *l_child;
        Node *r_child;
        explicit Node(const set<KEY , OTHER> &x , Node *lc = nullptr , Node *rc = nullptr):data(x) , l_child(lc) , r_child(rc){}
    };

    Node *root;
public:
    SplayTree(): root(nullptr){};
    ~SplayTree(){clear() ;};
    bool find(const KEY &x);
    void clear();
    void insert(const set<KEY , OTHER> &x);
private:
    type find(const KEY &x , Node *& node);
    type insert(const set<KEY , OTHER> &x , Node *& node);
    void zigzig(Node *& node);
    void zagzag(Node *& node);
    void zigzag(Node *& node);
    void zagzig(Node *& node);
    void LL(Node *& node);
    void RR(Node *& node);
};
template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::clear() {
    if (!root)
        return;
    stack<Node *> del;
    del.push(root);
    Node* tmp;
    while (!del.empty()) {
        tmp = del.top();
        del.pop();
        if (tmp-> r_child)
            del.push(tmp-> r_child);
        if (tmp-> l_child)
            del.push(tmp-> l_child);
        delete tmp;
    }
    root = nullptr;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::insert(const set<KEY , OTHER> &x) {
    if (!root) {
        root = new Node (x);
        return;
    }
    type rn = insert(x , root);
    switch (rn) {
        case False: cout<<"The key already exists!!\n";
        case X: return;
        case Zig: LL(root) ; return;
        case Zag: RR(root) ;
    }
}

template <class KEY , class OTHER>
SplayTree<KEY , OTHER>::type SplayTree<KEY , OTHER>::insert(const set<KEY , OTHER> &x , Node *& node) {
    if (!node) {
        node = new Node (x);
        return X;
    }
    if (x.key == node-> data.key)
        return False;
    if (x.key > node-> data.key) {
        type rn = insert(x , node-> r_child);
        switch (rn) {
            case False: return False;
            case X: return Zag;
            case Zag: zagzag(node) ; return X;
            case Zig: zagzig(node) ; return X;
            default: return False;
        }
    }
    else {
        type rn = insert(x , node-> l_child) ;
        switch (rn) {
            case False: return False;
            case X: return Zig;
            case Zig: zigzig(node) ; return X;
            case Zag: zigzag(node) ; return X;
            default: return False;
        }
    }
}

template <class KEY , class OTHER>
bool SplayTree<KEY , OTHER>::find(const KEY &x) {
    if (!root)
        return false;
    type rn = find(x , root);
    switch (rn) {
        case False: return false;
        case X: return true;
        case Zig: LL(root) ; return true;
        case Zag: RR(root) ; return true;
        default: return false;
    }
}

template <class KEY , class OTHER>
SplayTree<KEY , OTHER>::type SplayTree<KEY , OTHER>::find(const KEY &x , Node *& node) {
    if (!node)
        return False;
    if (x == node-> data.key)
        return X;
    if (x > node-> data.key) {
        type rn = find(x, node-> r_child);
        switch (rn) {
            case False: return False;
            case X: return Zag;
            case Zag: zagzag(node) ; return X;
            case Zig: zagzig(node) ; return X;
            default: return False;
        }
    }
    else {
        type rn = find(x , node-> l_child);
        switch (rn) {
            case False: return False;
            case X: return Zig;
            case Zig: zigzig(node) ; return X;
            case Zag: zigzag(node) ; return X;
            default: return False;
        }
    }
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::zigzig(Node *&node) {
    Node *p = node-> l_child , *c = p-> l_child;
    node-> l_child = p-> r_child;
    p-> l_child = c-> r_child;
    p-> r_child = node;
    c-> r_child = p;
    node = c;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::zagzag(Node *&node) {
    Node *p = node-> r_child , *c = p-> r_child;
    node-> r_child = p-> l_child;
    p-> r_child = c-> l_child;
    p-> l_child = node;
    c-> l_child = p;
    node = c;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::zigzag(Node *&node) {
    Node *p = node-> l_child , *c = p-> r_child;
    node-> l_child = c-> r_child;
    p-> r_child = c-> l_child;
    c-> r_child = node;
    c-> l_child = p;
    node = c;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::zagzig(Node *&node) {
    Node *p = node-> r_child , *c = p-> l_child;
    node-> r_child = c-> l_child;
    p-> l_child = c-> r_child;
    c-> l_child = node;
    c-> r_child = p;
    node = c;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::LL(Node *&node) {
    Node *tmp = node-> l_child;
    node-> l_child = tmp-> r_child;
    tmp-> r_child = node;
    node = tmp;
}

template <class KEY , class OTHER>
void SplayTree<KEY , OTHER>::RR(Node *&node) {
    Node *tmp = node-> r_child;
    node-> r_child = tmp-> l_child;
    tmp-> l_child = node;
    node = tmp;
}
#endif //SPLAYTREE_SPLAYTREE_H