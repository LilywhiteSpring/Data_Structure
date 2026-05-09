#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <iostream>
#include <random>
using namespace std;

template <class elemType , int height_max>
class SkipList {
private:
    struct SkipNode {
        elemType data;
        int height;
        SkipNode **next;

        SkipNode(elemType d , int h): data(d) , height(h) {
            next = new SkipNode*[h];
            for (int i = 0 ; i < h ; ++i)
                next[i] = nullptr;
        }

        ~SkipNode() {
            delete [] next;
        }
    };

    int height_cur;
    SkipNode **head;

    static mt19937 generator;
    static bool upgrade();

public:
    SkipList(): height_cur(0) {
        head = new SkipNode*[height_max];
        for (int i = 0 ; i < height_max ; ++i)
            head[i] = nullptr;
        random_device rd;
        generator.seed(rd());
    }

    ~SkipList() {
        SkipNode *p = head[0];
        while (p) {
            SkipNode *q = p->next[0];
            delete p;
            p = q;
        }
        delete [] head;
    }

    SkipNode* find(const elemType &x) const;
    void insert(const elemType &x);
    void remove(const elemType &x);
    void display() const;
};

template<class elemType , int height_max>
mt19937 SkipList<elemType , height_max>::generator;

template<class elemType , int height_max>
bool SkipList<elemType , height_max>::upgrade() {
    static bernoulli_distribution dist(0.5);
    return dist(generator);
}

template<class elemType , int height_max>
typename SkipList<elemType , height_max>::SkipNode*
SkipList<elemType , height_max>::find(const elemType &x) const {
    for (int h = height_cur - 1; h >= 0; --h) {
        SkipNode *p = head[h];
        while (p) {
            if (p->data == x) return p;
            if (!p->next[h] || p->next[h]->data > x) break;
            p = p->next[h];
        }
    }
    return nullptr;
}

template<class elemType , int height_max>
void SkipList<elemType , height_max>::insert(const elemType &x) {
    SkipNode *update[height_max]{};

    for (int h = height_cur - 1; h >= 0; --h) {
        SkipNode *p = head[h];
        SkipNode *prev = nullptr;
        while (p && x > p-> data) {
            prev = p;
            p = p->next[h];
        }
        update[h] = prev;
    }

    if (update[0] && update[0]->next[0] &&
        update[0]->next[0]->data == x) {
        cout << "该值已存在\n";
        return;
    }

    int newHeight = 1;
    while (upgrade() && newHeight < height_max)
        newHeight++;

    if (newHeight > height_cur)
        height_cur = newHeight;

    SkipNode *node = new SkipNode(x, newHeight);

    for (int i = 0; i < newHeight; ++i) {
        if (!update[i]) {
            node->next[i] = head[i];
            head[i] = node;
        } else {
            node->next[i] = update[i]->next[i];
            update[i]->next[i] = node;
        }
    }
}

template<class elemType , int height_max>
void SkipList<elemType , height_max>::remove(const elemType &x) {
    SkipNode *update[height_max]{};

    for (int h = height_cur - 1; h >= 0; --h) {
        SkipNode *p = head[h];
        SkipNode *prev = nullptr;
        while (p && x > p-> data) {
            prev = p;
            p = p->next[h];
        }
        update[h] = prev;
    }

    SkipNode *target = update[0] ? update[0]->next[0] : head[0];

    if (!target || target->data != x) {
        cout << "删除失败\n";
        return;
    }

    for (int i = 0; i < target->height; ++i) {
        if (!update[i])
            head[i] = target->next[i];
        else
            update[i]->next[i] = target->next[i];
    }

    delete target;

    while (height_cur > 0 && !head[height_cur - 1])
        height_cur--;
}

template<class elemType , int height_max>
void SkipList<elemType , height_max>::display() const {
    SkipNode *p = head[0];
    while (p) {
        cout << p->data << " ";
        p = p->next[0];
    }
    cout << endl;
}

#endif
