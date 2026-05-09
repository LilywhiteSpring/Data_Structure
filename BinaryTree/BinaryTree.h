//
// Created by 85375 on 2025/11/29.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template<class elemType>
class binaryTree {
private:
    struct node {
        elemType data;
        node *left,*right;

        node():left(nullptr),right(nullptr){};
        explicit node(const elemType& x,node* l=nullptr,node *r=nullptr):data(x),left(l),right(r){};
    };
    struct s_node {
        node* Node;
        int time;

        explicit s_node(node* x= nullptr):Node(x),time(0){};
    };

    node* root;
public:
    binaryTree():root(nullptr){};
    explicit binaryTree(elemType x) {
        root = new node(x);
    }
    ~binaryTree(){clear(root);};
    void clear();
    bool empty() const;
    elemType Root () const;
    elemType lchild(const elemType &x) const;
    elemType rchild(const elemType &x) const;
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void createTree(elemType flag) ;
    elemType parent(elemType x) const;
private:
    node* find(const elemType &x) const;
    void clear(node *& t);
    void preOrder(node *t) const;
    void midOrder(node *t) const;
    void postOrder(node *t) const;
};
template<class elemType>
void binaryTree<elemType>::clear()  {
    if (nullptr == root) return;
    clear(root);
}
template<class elemType >
void binaryTree<elemType>::clear(node *& t) {
    if (nullptr ==  t) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t=nullptr;
}
template<class elemType>
bool binaryTree<elemType>::empty() const {
    if (nullptr == root) return false;
    return true;
}
template<class elemType>
void binaryTree<elemType>::levelOrder() const {
    queue<node*> seq;
    if (! root) return;
    seq.push(root);
    node *current;
    while (!seq.empty()) {
        current = seq.front();
        cout<<seq.front()->data<<' ';
        seq.pop();
        if (current-> left )
            seq.push(current->left);
        if (current-> right)
            seq.push(current->right);
    }
}
template <class elemType>
void binaryTree<elemType>::createTree(elemType flag) {
    clear(root);
    elemType x,l_data,r_data;
    node* tmp;
    queue<node *> seq;
    cout<<"请输入根节点的值\n";
    cin>>x;
    root =new node(x);
    seq.push(root);
    while (!seq.empty()) {
        tmp=seq.front();
        seq.pop();
        cout<<"请分别输入"<<tmp-> data<<"的左子节点和柚子节点的值（"<<flag<<"代表空）\n";
        cin>>l_data>>r_data;
        if (l_data != flag) {
            tmp-> left = new node(l_data);
            seq.push(tmp-> left);
        }
        if (r_data != flag){
            tmp-> right = new node(r_data);
            seq.push(tmp-> right);
        }
    }
    cout<<"Creation complete!\n";
}
template<class elemType >
void binaryTree<elemType>::postOrder() const{ // 尝试后序遍历的非递归形式
    if (! root)
        return;
    stack<s_node> seq;
    s_node current(root) ;
    seq.push(current);
    while (!seq.empty()) {
        current = seq.top();
        ++current.time;
        seq.pop();
        if (current.time == 2) {
            cout<<current.Node-> data<<' ';
        }
        else {
            seq.push(current);
            if (current.Node-> right) {
                seq.push(s_node(current.Node-> right));
            }
            if (current.Node-> left) {
                seq.push(s_node(current.Node-> left));
            }
        }
    }
}

#endif //BINARYTREE_BINARYTREE_H
//几个问题：自建库怎么使用、类和结构体成员函数的内存、*&、elemType flag、createTree
//简化了后序遍历
