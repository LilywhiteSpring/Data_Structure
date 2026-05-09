//
// Created by 85375 on 2025/12/7.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H
#include <iostream>
using namespace std;
template <class KEY , class OTHER>
struct set {
    KEY key;
    OTHER other;
};

template <class KEY , class OTHER>
class RedBlackTree {
private:
    enum Color {
        Red = 0,
        Black = 1,
    };
    struct RDnode {
        set<KEY , OTHER> data;
        RDnode *l_child;
        RDnode *r_child;
        Color color;

        RDnode(const RDnode &node): data(node.data) , l_child(node.l_child) , r_child(node.r_child) , color(node.color){}
        RDnode(const set<KEY , OTHER> &x , Color type): data(x) , color(type) , l_child(nullptr) , r_child(nullptr){}
        bool operator> (RDnode *node){return (data.key > node-> data.key);}
    };

    RDnode *root;
public:
    RedBlackTree(): root(nullptr){}
    ~RedBlackTree(){Clear(root) ; root = nullptr;}
    set<KEY , OTHER>* find(const KEY &x) const;
    void Clear() {Clear(root);}
    void insert(const set<KEY , OTHER> &x);
    void remove(const KEY &x);
private:
    void Clear(RDnode *node);
    void LL(RDnode *node);
    void RR(RDnode *node);
    void LR(RDnode *node);
    void RL(RDnode *node);
    void insertAdjust(RDnode *gp , RDnode *p , RDnode *node);
    void removeAdjust(RDnode *&p , RDnode *&node , RDnode *&bro ,const KEY &x);
};

template<class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::Clear(RDnode *node) {
    if(node) {
        Clear(node-> l_child);
        Clear(node-> r_child);
        delete node;
    }
}

template<class KEY , class OTHER>
set<KEY , OTHER>* RedBlackTree<KEY , OTHER>::find(const KEY &x) const {
    RDnode *tmp = root;
    while (tmp) {
        if (x == tmp-> data.key)
            return &tmp-> data;
        if (x > tmp-> data.key)
            tmp = tmp-> r_child;
        if (x < tmp-> data.key)
            tmp = tmp-> l_child;
    }
    return nullptr;
}

template<class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::insert(const set<KEY , OTHER> &x) {
    if (!root) {
        root = new RDnode(x , Black);
        return;
    }
    RDnode *gp , *p , *node = root;
    //当node不为空时向下移动并重新着色
    while (node) {
        if (x.key == node-> data.key) {
            node-> data.other = x.other;
            cout<<"插入过程发生替换操作\n";
            return;
            //替换，但我不知道合不合理
        }
        if (node-> l_child && node-> r_child && Red == node-> l_child-> color && Red == node-> r_child-> color) {
            node-> color = Red;
            node-> l_child-> color = Black;
            node-> r_child-> color = Black;
            insertAdjust(gp , p , node);
        }
        gp = p;
        p = node;
        node = (x.key > node-> data.key) ? node-> r_child : node-> l_child;
    }
    //注意这里node已经不再是原来的孩子了，分配新空间后它变味了野指针，所以咱要给她重新链接
    node = new RDnode(x , Red);
    if (x.key > p-> data.key)
        p-> r_child = node;
    else
        p-> l_child = node;
    //最后一次调整
    insertAdjust(gp , p ,node);
}

template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::insertAdjust(RDnode *gp , RDnode *p , RDnode *node){
    //先处理特殊情况
    if (root == node) {
        node-> color = Black;
        return;
    }
    if (p == node)
        return;

    if (Red == p-> color) {
        if (p-> data.key < gp-> data.key) {
            if (node-> data.key < p->data.key)
                LL(gp);
            //这里鸡毛颜色也不用调，因为旋转函数太牛逼了
            else
                LR(gp);
        }
        else {
            if (node-> data.key > p->data.key)
                RR(gp);
            else
                RL(gp);
        }
    }
}

//咱需要注意一下rh数滴旋转没有引用指针 ， 所以必须转移数据
//旋转函数中不要调色，应该由adjust执行
template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::LL(RDnode *node) {
    RDnode *p = node-> l_child , *t = p-> l_child;
    RDnode tmp = *node;
    node-> data = p-> data;
    node-> l_child = t;
    node-> r_child = p;
    p-> data = tmp.data;
    p-> l_child = p-> r_child ;
    p-> r_child =tmp.r_child;
}
template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::RR(RDnode *node) {
    RDnode *p = node-> r_child , *t = p-> r_child;
    RDnode tmp = *node;
    node-> data = p-> data;
    node-> r_child = t;
    node-> l_child = p;
    p-> data = tmp.data;
    p-> r_child = p-> l_child;
    p-> l_child = tmp.l_child
}

template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::LR(RDnode *node) {
    RDnode *p = node-> l_child , *t = p-> r_child;
    RDnode tmp = *node;
    node-> data = t-> data;
    node-> r_child = t;
    p-> r_child = t-> l_child;
    t-> data = tmp.data;
    t-> l_child = t-> r_child;
    t-> r_child = tmp.r_child;
}
template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::RL(RDnode *node) {
    RDnode *p = node->r_child , *t = p-> l_child;
    RDnode tmp = *node;
    node-> data = t-> data;
    node-> l_child = t;
    p-> l_child = t-> r_child;
    t-> data = tmp.data;
    t-> r_child = t-> l_child;
    t-> l_child = tmp.l_child;
}

template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::remove(const KEY &x) {
    KEY del = x;
    if (!root)
        return;
    if (x == root-> data.key && !root-> l_child && !root-> r_child) {
        delete root;
        root = nullptr;
        return;
    }
    RDnode *p , *bro , *node;
    p = bro = node = root;
    while (node) {
        removeAdjust(p , node , bro , del);
        if (del == node-> data.key && node-> l_child && node-> r_child) {
            RDnode *tmp = node-> r_child;
            while (tmp-> l_child)
                tmp = tmp-> l_child;
            node-> data = tmp-> data;
            del = tmp-> data.key;
            p = node;
            bro = p-> l_child;
            node = node-> r_child;
            continue;
        }
        if (del == node-> data.key) {
            delete node;
            (bro == p-> l_child) ? p-> r_child : p-> l_child = nullptr;
            root-> color = Black;
            cout<<"删除完成！"<<endl;
            return;
        }
        p = node;
        node = (del > node-> data.key) ? node-> r_child : node-> l_child;
        bro = (del > node-> data.key) ? node-> l_child : node-> r_child;
    }
}

template <class KEY , class OTHER>
void RedBlackTree<KEY , OTHER>::removeAdjust(RDnode *&p , RDnode *&node , RDnode *&bro , const KEY &x) {
    if (Red == node-> color)
        return;
    if (root == node && node-> l_child && node-> r_child && node-> l_child-> color == node-> r_child-> color) {
        node-> color = Red;
        node-> l_child-> color = node-> r_child-> color = Black;
        return;
    }

    if ( (!node-> l_child || Black == node-> l_child-> color) && (!node-> r_child || Black == node-> r_child-> color) ) {
        if ( (!bro-> l_child || Black == bro-> l_child-> color) && (!bro-> r_child || Black == bro-> r_child-> color) ) {
            p-> color = Black;
            bro-> color = node-> color = Red;
            return;
        }

        if (bro == p-> l_child) {
            if (bro-> l_child && Red == bro-> l_child-> color) {
                bro-> l_child-> color = Black;
                LL(p);
                node-> color = Red;
                return;
            }
            //姑且这么写
            else {
                LR(p);
                p = p-> r_child;
                p-> color = Black;
                node-> color = Red;
                return;
            }
        }
        else {
            if (bro-> r_child && Red == bro-> r_child-> color) {
                bro-> r_child-> color = Black;
                RR(p);
                node-> color = Red;
                return;
            }
            else {
                RL(p);
                p = p->l_child;
                p-> color = Black;
                node-> color = Red;
                return;
            }
        }
    }
    if (x == node-> data.key) {
        if (node-> l_child && node-> r_child) {
            if (Black == node-> r_child-> color)
                LL(node);
            node = node-> r_child;
            return;
        }
        if (node-> l_child) {
            LL(node);
            p = node;
            node = node-> r_child;
            return;
        }
        else {
            RR(node);
            p = node;
            node = node-> l_child;
            return;
        }
    }
    else {
            p = node;
            node = (x > node-> data.key) ? node-> r_child : node-> l_child;
            bro = (x > node-> data.key) ? node-> l_child : node-> r_child;
            if (Black == node-> color) {
                if (node == p-> l_child)
                     RR(node);
                else
                    LL(node);
                p = bro;
                bro = (node == p-> l_child) ? p-> r_child : p-> l_child;
                removeAdjust(p , node , bro , x);
            }
    }
}
#endif //REDBLACKTREE_REDBLACKTREE_H