#include <iostream>
using namespace std;
//Version of ascending merge sort:
template <class KEY>
struct Node {
    KEY data;
    Node *next;

    Node(): next(nullptr){};
    explicit Node(const KEY &x , Node *node = nullptr): data(x) , next(node){}
};
template <class KEY>
void Merge_sort(KEY *data , int size);
template <class KEY>
void Merge_sort(Node<KEY> *head , int size);
template <class KEY>
void merge(Node<KEY> *head1 , int size1 , Node<KEY> *head2 , int size2);

int main() {
    int a[] = {55 , 23 , 1 , 2 , 66 , 201 , 10 , 132 , 2 , 44};
    Merge_sort(a , 10);
    for (int i : a)
        cout<<i<<' ';

    return 0;
}

template <class KEY>
void Merge_sort(KEY *data , int size) {
    if (size <= 1)
        return;
    if (2 == size)
        if (data[0] > data[1]) {
            KEY tem = data[0];
            data[0] = data[1];
            data[1] = tem;
            return;
        }
    auto *head = new Node<KEY>;
    Node<KEY> *tmp = head;
    for (int i = 0 ; i < size ; ++i) {
        tmp-> next = new Node<KEY> (data[i]);
        tmp = tmp-> next;
    }
    tmp-> next = nullptr;


    Merge_sort(head , size / 2);
    tmp = head;
    for (int i = 1 ; i <= size / 2 ; ++i)
        tmp = tmp-> next;
    Merge_sort(tmp , size - size / 2);
    merge(head , size / 2 , tmp , size - size / 2);

    tmp = head-> next;
    delete head;
    for (int i = 0 ; i < size ; ++i) {
        data[i] = tmp-> data;
        head = tmp;
        tmp = tmp-> next;
        delete head;
    }
}

template <class KEY>
void Merge_sort(Node<KEY> *head , int size) {
    if (1 >= size)
        return;
    if (2 == size) {
        if (head-> next-> data > head-> next-> next-> data){
            KEY tmp = head-> next-> data;
            head-> next-> data = head-> next->next-> data;
            head-> next-> next-> data = tmp;
        }
        return;
    }
    Merge_sort(head , size / 2);
    Node<KEY> *tmp = head;
    for (int i = 0 ; i < size / 2 ; ++i)
        tmp = tmp-> next;
    Merge_sort(tmp , size - size / 2);
    merge(head , size / 2 , tmp , size - size / 2);
}

template <class KEY>
void merge(Node<KEY> *head1 , int size1 , Node<KEY> *head2 , int size2) {
    int front = 0 , back = front;
    Node<KEY> *tmp;
    while (back < size2 && front < size1) {
        if (head1-> next-> data > head2-> next-> data) {
            tmp = head2-> next;
            head2-> next = tmp-> next;
            tmp-> next = head1-> next;
            head1-> next = tmp;
            head1 = head1-> next;
            ++back;
        }
        else {
            head1 = head1-> next;
            ++front;
        }
    }
}