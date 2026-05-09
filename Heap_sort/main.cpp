#include <iostream>
using namespace std;
template<class Type>
void Heap_sort(Type *data , int size);
template<class Type>
void percolate(Type *data , int size , int seq);
int main() {
    int a[] = {0 , 4 , 6 , 3 , 3 , 8 , 11};
    Heap_sort(a , 7);
    for (int i : a)
        cout<<i<<'\t';
    return 0;
}
template<class Type>
void Heap_sort(Type *data , int size) {
    Type tmp;
    for (int i = size / 2 - 1 ; i >= 0 ; --i)
        percolate(data , size , i);
    for (int i = 0 ; i < size ; ++i) {
        tmp = data[0];
        data[0] = data[size - 1 - i];
        data[size - 1 - i] = tmp;
        percolate(data , size - i - 1 , 0);
    }
}
template<class Type>
void percolate(Type *data , int size , int seq) {//这个代码可以变得非常简单
    Type tmp;
    int now = seq , child;
    for ( ; now * 2 + 1 < size ; now = child) {
        child = now * 2 + 1 ;
        if (child != size - 1 && data[child + 1] > data[child])
            child++;
        if (data[child] <= data[now])
            return;
        tmp = data[now];
        data[now] = data[child];
        data[child] = tmp;
    }
}
//     Type tmp;
//     int now = seq;
//     while (2 * now + 1 < size) {
//         tmp = data[now];
//         if (2 * now + 2 < size) {
//             if (data[now] <= data[2 * now + 1] && data[now] <= data[2 * now + 2])
//                 return;
//             if (data[now] > data[2 * now + 1]) {
//                 if (data[2 * now + 2] < data[2 * now + 1]) {
//                     data[now] = data[2 * now + 2];
//                     data[2 * now + 2] = tmp;
//                     now = 2 * now + 2;
//                 }
//                 else {
//                     data[now] = data[2 * now + 1];
//                     data[2 * now + 1] = tmp;
//                     now = 2 * now + 1;
//                 }
//             }
//             else {
//                 data[now] = data[2 * now + 2];
//                 data[2 * now + 2] = tmp;
//                 now = 2 * now + 2;
//             }
//         }
//         else {
//             if (data[now] <= data[2 * now + 1])
//                 return;
//             data[now] = data[2 * now +  1];
//             data[2 * now + 1] = tmp;
//             now = 2 * now + 1;
//         }
//     }
// }
