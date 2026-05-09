// //
// // Created by 85375 on 2025/12/23.
// //
//
// #ifndef BPLUS_TREE_BPLUSTREE_H
// #define BPLUS_TREE_BPLUSTREE_H
// #include <iostream>
// using namespace std;
//
// template <class KEY , class OTHER>
// struct set {
//     KEY key;
//     OTHER other;
//
//     set()= default;
//     set(const KEY &k , const OTHER &o): key(k) , other(o){}
// };
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// class BlkTree {
// private:
//
//     class Node {
//     public:
//         bool isLeaf;
//
//         Node(): isLeaf(false) {}
//         explicit Node(bool i = true): isLeaf(i){}
//         virtual ~Node() = default;
//     };
//
//     class idxNode : public Node {
//     public:
//         KEY idx[idxSize];
//         Node *children[idxSize + 1];
//         int length;
//
//         idxNode(): Node(false) , length(0) {
//             for (int i = 0 ; i <= idxSize  ; ++i)
//                 children[i] = nullptr;
//         }
//         ~idxNode() override = default;
//     };
//
//     class dataNode : public Node {
//     public:
//         set<KEY , OTHER> data[dataSize + 1];
//         int length;
//         dataNode *next;
//
//         dataNode(): Node(true) , length(0) , next(nullptr) {}
//         ~dataNode() override = default;
//     };
//
//     idxNode *root;
//     dataNode *head;
//
//     void Clear(Node * node);
//     Node* insert(Node * node , const set<KEY , OTHER> &s);
//     Node* NodeSplit(Node *node);
//     bool remove(Node *node , const KEY &x);
//     void merge(idxNode *p , Node *node , int index);
//     void lend_right(idxNode *p , Node *node , int index);
//     void lend_left(idxNode *p , Node *node , int index);
//
// public:
//     BlkTree(): root(nullptr) , head(nullptr){}
//     ~BlkTree(){Clear( ) ; };
//     void Clear(){if (!root) return ; Clear(root) ; root = nullptr ;}
//     bool find(const KEY &s) const;
//     void PrintData() const;
//     void insert(const set<KEY , OTHER> &s);
//     void remove(const KEY &x);
//
// };
//
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// void BlkTree<KEY , OTHER , idxSize , dataSize >::Clear(Node *node) {
//     Node *tmp = node;
//     if (tmp-> isLeaf) {
//         auto *tmpData = static_cast<dataNode *>(tmp);
//         delete tmpData;
//         return;
//     }
//     auto *tmpIdx = static_cast<idxNode *>(tmp);
//     for (int i = 0 ; i < tmpIdx-> length ; ++i)
//         Clear(tmpIdx-> children[i]);
//     delete tmpIdx;
// }
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// void BlkTree<KEY , OTHER , idxSize , dataSize >::PrintData() const {
//     if (!head) {
//         cout<<"NO DATA !!\n";
//         return;
//     }
//     dataNode *tmp = head;
//     while (tmp) {
//         for (int i = 0 ; i < tmp-> length ; ++i)
//             cout<<tmp-> data[i].key<<' ';
//         tmp = tmp-> next;
//     }
// }
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// bool BlkTree<KEY , OTHER , idxSize , dataSize >::find(const KEY &s) const {
//     if (!root)
//         return false;
//     int i;
//     Node *tmp = root;
//     idxNode *tmpIdx;
//     dataNode *tmpData;
//     while (true) {
//         if (tmp-> isLeaf) { // 数据节点
//             tmpData = static_cast<dataNode *>(tmp);
//             for (i = 0 ; i < tmpData-> length && tmpData-> data[i].key < s ; ++i) {
//                 if (s == tmpData-> data[i].key)
//                     return true;
//             }
//             return false;
//         }
//         //索引节点
//         tmpIdx = static_cast<idxNode *>(tmp);
//         for (i = 0 ; i < tmpIdx-> length && tmpIdx-> idx[i] < s ; ++i){};
//         tmp = tmpIdx-> children[i];
//     }
// }
//
//
//
//
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// void BlkTree<KEY , OTHER , idxSize , dataSize >::insert(const set<KEY , OTHER> &s)  {
//     if (!root) {
//         root = new idxNode;
//         root-> idx[0] = s.key;
//         root-> children[0] = new dataNode;
//         root-> children[1] = new dataNode;
//         auto *tmp1 = static_cast<dataNode *>(root-> children[0]);
//         auto *tmp2 = static_cast<dataNode *>(root-> children[1]);
//
//         tmp1-> next = tmp2;
//         tmp1-> data[0] = s;
//         ++tmp1-> length;
//         head = tmp1;
//
//         ++root-> length;
//         return ;
//     }
//     //root存在
//     auto * z = static_cast<Node *>(root);
//     auto* tmp = static_cast<idxNode *>(insert(z , s));
//     if (tmp) {
//         auto *newRoot = new idxNode;
//         newRoot-> idx[0] = root-> idx[(idxSize - 1) / 2];
//         newRoot-> children[0] = root;
//         newRoot-> children[1] = tmp;
//         root = newRoot;
//     }
// }
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// BlkTree<KEY , OTHER , idxSize , dataSize >::Node *BlkTree<KEY , OTHER , idxSize , dataSize >::insert(Node *node , const set<KEY , OTHER> &s) {
//     //如果是数据节点
//     int i;
//     if (node-> isLeaf) {
//         auto* tmpData = static_cast<dataNode *>(node);
//         for (i = 0 ; i < tmpData-> length && s.key > tmpData-> data[i].key ; ++i){};
//         if (s.key == tmpData-> data[i].key) {
//             cout<<"重复的数据捏\n";
//             return nullptr;
//         }
//         for ( int j = tmpData-> length ; j > i ; --j )
//             tmpData-> data[j] = tmpData-> data[j - 1];
//         tmpData-> data[i] = s;
//         if (dataSize + 1 == ++tmpData-> length) {
//             Node *tmp = NodeSplit(tmpData);
//             return tmp;
//         }
//         return nullptr;
//     }
//     //如果是索引节点
//     auto* tmpIdx = static_cast<idxNode *>(node);
//     for (i = 0 ; i < tmpIdx-> length && s.key > tmpIdx-> idx[i] ; ++i){};
//     Node *herit = insert(tmpIdx-> children[i] , s);
//
//     if (herit) {
//         //如果发生分裂且孩子是叶节点
//         if (herit-> isLeaf){
//             auto *heritData = static_cast<dataNode *>(herit);
//             for (int j = tmpIdx-> length ; j > i ; --j) {
//                 tmpIdx-> idx[j] = tmpIdx-> idx[j - 1];
//                 tmpIdx-> children[j] = tmpIdx-> children[j - 1];
//             }
//             tmpIdx-> children[i + 1] = heritData;
//             tmpIdx-> idx[i] = static_cast<dataNode *>(tmpIdx-> children[i])-> data[dataSize / 2].key;
//
//
//         }
//         //当前节点是内部节点且发生了分裂
//         else {
//             auto *heritIdx = static_cast<idxNode *>(herit);
//             for (int j = tmpIdx-> length ; j > i ; --j) {
//                 tmpIdx-> idx[j] = tmpIdx-> idx[j - 1];
//                 tmpIdx-> children[j + 1] = tmpIdx-> children[j];
//             }
//             tmpIdx-> children[i + 1] = heritIdx;
//             tmpIdx-> idx[i] = static_cast<idxNode *>(tmpIdx-> children[i])-> idx[idxSize / 2];
//
//         }
//     }
//      if (idxSize == ++tmpIdx-> length) {
//          Node *tmp = NodeSplit(tmpIdx);
//          return tmp;
//      }
//     return nullptr;
// }
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// BlkTree<KEY , OTHER , idxSize , dataSize>::Node *BlkTree<KEY , OTHER , idxSize , dataSize>::NodeSplit(Node* node) {
//     //如果是叶节点
//     if (node-> isLeaf) {
//         auto *tmpData = static_cast<dataNode *>(node);
//         auto *newNode = new dataNode;
//         for (int i = 0 ; i < (dataSize + 1) / 2; ++i)
//             newNode-> data[i] = tmpData-> data[i + dataSize / 2 + 1];//懒得验证了
//         tmpData-> length = dataSize / 2 + 1;
//         newNode-> length = (dataSize + 1) / 2;
//         //链接新节点
//         tmpData-> next = newNode;
//
//         return newNode;
//     }
//
//     auto *tmpIdx = static_cast<idxNode *>(node);
//     auto *newNode = new idxNode;
//     int i;
//     for (i = 0 ; i < (idxSize + 1) / 2 ; ++i) {
//         newNode-> idx[i] = tmpIdx-> idx[i + idxSize / 2 + 1];
//         newNode-> children[i] = tmpIdx-> children[i + idxSize / 2 + 1];
//     }
//     newNode-> children[i] = tmpIdx-> children[idxSize + 1];
//     newNode-> length = (idxSize + 1) / 2;
//     tmpIdx-> length = idxSize / 2 + 1;
//
//     return newNode;
// }
//
// template <class KEY , class OTHER , int idxSize , int dataSize>
// void BlkTree<KEY , OTHER , idxSize , dataSize>::remove(const KEY &x) {
//     if (!root) {
//         cout<<"未查找到"<<x<<endl;
//         return;
//     }
//
// }
//
// #endif //BPLUS_TREE_BPLUSTREE_H
//
// Created by 85375 on 2025/12/23.
// 完整可运行 B+ 树（插入 + 查找）
//

#ifndef BPLUS_TREE_BPLUSTREE_H
#define BPLUS_TREE_BPLUSTREE_H

#include <iostream>
using namespace std;

template <class KEY , class OTHER>
struct set {
    KEY key;
    OTHER other;
    set() = default;
    set(const KEY &k , const OTHER &o): key(k) , other(o){}
};

template <class KEY , class OTHER , int idxSize , int dataSize>
class BlkTree {
private:
    class Node {
    public:
        bool isLeaf;
        explicit Node(bool leaf = false): isLeaf(leaf) {}
        virtual ~Node() = default;
    };

    class idxNode : public Node {
    public:
        KEY idx[idxSize];
        Node *children[idxSize + 1];
        int length;

        idxNode(): Node(false), length(0) {
            for (int i = 0 ; i <= idxSize ; ++i)
                children[i] = nullptr;
        }
    };

    class dataNode : public Node {
    public:
        set<KEY , OTHER> data[dataSize + 1];
        int length;
        dataNode *next;

        dataNode(): Node(true), length(0), next(nullptr) {}
    };

    Node *root;
    dataNode *head;

    void Clear(Node *node);
    Node* insert(Node *node , const set<KEY , OTHER> &s);
    Node* NodeSplit(Node *node);
    bool remove(Node *node , const KEY &x);

    void lend_left(idxNode *p , Node *node , int index);
    void lend_right(idxNode *p , Node *node , int index);
    void merge(idxNode *p , Node *node , int index);

public:
    BlkTree(): root(nullptr), head(nullptr) {}
    ~BlkTree(){ Clear(); }

    void Clear();
    bool find(const KEY &x) const;
    void insert(const set<KEY , OTHER> &s);
    void remove(const KEY &x);
    void PrintData() const;
};


template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::Clear() {
    if (!root) return;
    Clear(root);
    root = nullptr;
    head = nullptr;
}

template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::Clear(Node *node) {
    if (node->isLeaf) {
        delete static_cast<dataNode *>(node);
        return;
    }
    auto *idx = static_cast<idxNode *>(node);
    for (int i = 0 ; i <= idx->length ; ++i)
        Clear(idx->children[i]);
    delete idx;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::PrintData() const {
    dataNode *p = head;
    while (p) {
        for (int i = 0 ; i < p->length ; ++i)
            cout << p->data[i].key << ' ';
        p = p->next;
    }
    cout << endl;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
bool BlkTree<KEY , OTHER , idxSize , dataSize>::find(const KEY &x) const {
    if (!root) return false;
    Node *p = root;

    while (!p->isLeaf) {
        auto *idx = static_cast<idxNode *>(p);
        int i = 0;
        while (i < idx->length && x >= idx->idx[i]) ++i;
        p = idx->children[i];
    }

    auto *leaf = static_cast<dataNode *>(p);
    for (int i = 0 ; i < leaf->length ; ++i)
        if (leaf->data[i].key == x)
            return true;
    return false;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::insert(const set<KEY , OTHER> &s) {
    if (!root) {
        auto *leaf = new dataNode;
        leaf->data[0] = s;
        leaf->length = 1;
        root = head = leaf;
        return;
    }

    Node *ret = insert(root, s);
    if (ret) {
        auto *newRoot = new idxNode;
        newRoot->children[0] = root;
        newRoot->children[1] = ret;

        newRoot->idx[0] = ret->isLeaf
            ? static_cast<dataNode *>(ret)->data[0].key
            : static_cast<idxNode *>(ret)->idx[0];

        newRoot->length = 1;
        root = newRoot;
    }
}

template <class KEY , class OTHER , int idxSize , int dataSize>
typename BlkTree<KEY , OTHER , idxSize , dataSize>::Node *
BlkTree<KEY , OTHER , idxSize , dataSize>::insert(Node *node , const set<KEY , OTHER> &s) {

    if (node->isLeaf) {
        auto *leaf = static_cast<dataNode *>(node);
        int i = 0;
        while (i < leaf->length && s.key > leaf->data[i].key) ++i;

        if (i < leaf->length && s.key == leaf->data[i].key)
            return nullptr;

        for (int j = leaf->length ; j > i ; --j)
            leaf->data[j] = leaf->data[j - 1];

        leaf->data[i] = s;
        ++leaf->length;

        if (leaf->length > dataSize)
            return NodeSplit(leaf);
        return nullptr;
    }

    auto *idx = static_cast<idxNode *>(node);
    int i = 0;
    while (i < idx->length && s.key >= idx->idx[i]) ++i;

    Node *childSplit = insert(idx->children[i], s);
    if (!childSplit) return nullptr;

    for (int j = idx->length ; j > i ; --j) {
        idx->idx[j] = idx->idx[j - 1];
        idx->children[j + 1] = idx->children[j];
    }

    idx->idx[i] = childSplit->isLeaf
        ? static_cast<dataNode *>(childSplit)->data[0].key
        : static_cast<idxNode *>(childSplit)->idx[0];

    idx->children[i + 1] = childSplit;
    ++idx->length;

    if (idx->length > idxSize)
        return NodeSplit(idx);
    return nullptr;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
typename BlkTree<KEY , OTHER , idxSize , dataSize>::Node *
BlkTree<KEY , OTHER , idxSize , dataSize>::NodeSplit(Node *node) {

    if (node->isLeaf) {
        auto *leaf = static_cast<dataNode *>(node);
        auto *newLeaf = new dataNode;

        int mid = leaf->length / 2;
        for (int i = mid ; i < leaf->length ; ++i)
            newLeaf->data[i - mid] = leaf->data[i];

        newLeaf->length = leaf->length - mid;
        leaf->length = mid;

        newLeaf->next = leaf->next;
        leaf->next = newLeaf;

        return newLeaf;
    }

    auto *idx = static_cast<idxNode *>(node);
    auto *newIdx = new idxNode;

    int mid = idx->length / 2;
    for (int i = mid + 1 ; i < idx->length ; ++i) {
        newIdx->idx[i - mid - 1] = idx->idx[i];
        newIdx->children[i - mid - 1] = idx->children[i];
    }
    newIdx->children[idx->length - mid - 1] = idx->children[idx->length];

    newIdx->length = idx->length - mid - 1;
    idx->length = mid;

    return newIdx;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::remove(const KEY &x) {
    if (!root) return;

    remove(root, x);

    if (!root->isLeaf) {
        auto *r = static_cast<idxNode *>(root);
        if (r->length == 0) {
            root = r->children[0];
            delete r;
        }
    }
}

template <class KEY , class OTHER , int idxSize , int dataSize>
bool BlkTree<KEY , OTHER , idxSize , dataSize>::remove(Node *node , const KEY &x) {

    if (node->isLeaf) {
        auto *leaf = static_cast<dataNode *>(node);
        int i = 0;
        while (i < leaf->length && leaf->data[i].key != x) ++i;
        if (i == leaf->length) return false;

        for (int j = i ; j < leaf->length - 1 ; ++j)
            leaf->data[j] = leaf->data[j + 1];
        --leaf->length;

        return leaf->length < (dataSize + 1) / 2;
    }

    auto *idx = static_cast<idxNode *>(node);
    int i = 0;
    while (i < idx->length && x >= idx->idx[i]) ++i;

    bool under = remove(idx->children[i], x);
    if (!under) return false;

    if (i > 0 &&
        idx->children[i - 1]->isLeaf &&
        static_cast<dataNode *>(idx->children[i - 1])->length > (dataSize + 1) / 2) {
        lend_left(idx, idx->children[i], i);
        return false;
    }

    if (i < idx->length &&
        idx->children[i + 1]->isLeaf &&
        static_cast<dataNode *>(idx->children[i + 1])->length > (dataSize + 1) / 2) {
        lend_right(idx, idx->children[i], i);
        return false;
    }

    merge(idx, idx->children[i], i);
    return idx->length < (idxSize + 1) / 2;
}


template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::lend_left(
        idxNode *p , Node *node , int index) {

    auto *leaf = static_cast<dataNode *>(node);
    auto *left = static_cast<dataNode *>(p->children[index - 1]);

    for (int i = leaf->length ; i > 0 ; --i)
        leaf->data[i] = leaf->data[i - 1];

    leaf->data[0] = left->data[left->length - 1];
    --left->length;
    ++leaf->length;

    p->idx[index - 1] = leaf->data[0].key;
}

template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::lend_right(
        idxNode *p , Node *node , int index) {

    auto *leaf = static_cast<dataNode *>(node);
    auto *right = static_cast<dataNode *>(p->children[index + 1]);

    leaf->data[leaf->length++] = right->data[0];

    for (int i = 0 ; i < right->length - 1 ; ++i)
        right->data[i] = right->data[i + 1];

    --right->length;
    p->idx[index] = right->data[0].key;
}

template <class KEY , class OTHER , int idxSize , int dataSize>
void BlkTree<KEY , OTHER , idxSize , dataSize>::merge(
        idxNode *p , Node *node , int index) {

    auto *leaf = static_cast<dataNode *>(node);
    auto *left = static_cast<dataNode *>(p->children[index - 1]);

    for (int i = 0 ; i < leaf->length ; ++i)
        left->data[left->length + i] = leaf->data[i];

    left->length += leaf->length;
    left->next = leaf->next;
    delete leaf;

    for (int i = index - 1 ; i < p->length - 1 ; ++i) {
        p->idx[i] = p->idx[i + 1];
        p->children[i + 1] = p->children[i + 2];
    }
    --p->length;
}

#endif
// I hate cpp for typing those utter s**t codes
// Ah s**t