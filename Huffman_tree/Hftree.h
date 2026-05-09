//
// Created by 85375 on 2025/11/30.
//

#ifndef HUFFMAN_TREE_HFTREE_H
#define HUFFMAN_TREE_HFTREE_H
#include <iostream>
#include <string>
using namespace std;
template <class elemType>
class Hf_tree {
private:
    struct node { //不太搞得清楚这里要不要构造函数
        elemType data;
        int parent , l_child , r_child;
        int weight;
    };
    node* elem;
    int length;
public:
    Hf_tree(const elemType* t , const int *weigh , int size);
    void get_code();
};

template <class elemType>
Hf_tree<elemType>::Hf_tree(const elemType* t ,const int *weigh , int size) {
    const int MAX = 32767;
    elem = new node [2 * size];
    length = size * 2;
    for (int i=0 ; i<size ; ++i) {
        elem[size + i].data = t[i];
        elem[size + i].l_child = elem[size + i].r_child = elem[size + i ].parent = 0;
        elem[size + i ].weight = weigh[i];
    }
    int min1,min2,seq1,seq2;
    for (int i=size ; i>1 ; --i) {
        min1 = min2 = MAX;
        seq1 = seq2 = 0;
        for (int j=i ; j<length ; ++j) {
            if (0 == elem[j].parent) {
                if (elem[j].weight <min1) {
                    min2 = min1;
                    min1 = elem[j].weight;
                    seq2 = seq1;
                    seq1 = j;
                }
                else if (elem[j].weight < min2) {
                    min2 = elem[j].weight ;
                    seq2 = j;
                }
            }
        }
        elem[i-1].weight = elem[seq1].weight + elem[seq2].weight;
        elem[seq1].parent = i-1;
        elem[seq2].parent = i-1;
        elem[i-1].l_child = seq1;
        elem[i-1].r_child = seq2;
        elem[i-1].parent = 0;
    }
}

template <class elemType>
void Hf_tree<elemType>::get_code() {
    int size = length/2 , tp_p,tp_c;
    string tmp;
    for (int i=size ; i<length ; ++i) {
        tmp = "";
        tp_p = tp_c = i;
        cout<<elem[i].data<<" 对应的哈弗曼编码是：\n";
        while (tp_p != 1) {
            tp_p = elem[tp_p].parent;
            if (elem[tp_p].l_child == tp_c)
                tmp = '0' + tmp;
            else
                tmp = '1' + tmp;
            tp_c = tp_p;
        }
        cout<<tmp<<endl;
    }
}
#endif //HUFFMAN_TREE_HFTREE_H