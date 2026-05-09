#include <iostream>
using namespace std;
template<class Type>
void Merge_sort(Type *data , int size);
template<class Type>
void Merge_sort(Type *data , int begin , int end);
template<class Type>
void merge(Type *data , int begin , int mid , int end);
int main() {
    int a[] = {4 , 5 , 2 , 1 , 1 , 6 , 2 , 52};
    Merge_sort(a , 8);
    for (int i : a)
        cout << i << ' ';
    return 0;
}
template<class Type>
void Merge_sort(Type *data , int size) {
    Merge_sort(data , 0 , size - 1);
}

template<class Type>
void Merge_sort(Type *data , int begin , int end) {
    if (0 >= end - begin)
        return;
    int mid = (begin + end) / 2;
    Merge_sort(data , begin , mid);
    Merge_sort(data , mid + 1 , end);
    merge(data , begin , mid , end);
}

template<class Type>
void merge(Type *data , int begin , int mid , int end) {
    auto *tmp = new Type [end - begin + 1];
    int lx = begin , rx = mid + 1 , i = 0;
        while (lx <= mid && rx <= end) {
            if (data[lx] <= data[rx]) {
                tmp[i] = data[lx];
                lx++;
                i++;
            }
            else {
                tmp[i] = data[rx];
                rx++;
                i++;
            }
        }
    while (lx <= mid) {
        tmp[i] = data[lx];
        lx++;
        i++;
    }
    while (rx <= end) {
        tmp[i] = data[rx];
        rx++;
        i++;
    }
    for (int j = 0 ; j < end - begin + 1 ; ++j)
        data[begin + j] = tmp [j];
    delete [] tmp;
}