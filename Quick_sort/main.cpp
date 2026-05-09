#include <iostream>
using namespace std;
template <class Type>
void Quick_sort(Type *data , int size);
template <class Type>
void Quick_sort(Type *data , int begin , int end);
template <class Type>
int divide(Type *data , int begin , int end);
int main() {
    int a[] = {3 , 2 , 1 , 5 ,  4 , 2 , 43 , 2 , 1};
    Quick_sort(a , 9);
    for (int i : a)
        cout<<i<<'\t';
    return 0;
}
template <class Type>
void Quick_sort(Type *data , int size) {
    if (size <= 1)
        return;
    int pos = divide(data , 0 , size - 1);
    Quick_sort(data , 0 , pos - 1 );
    Quick_sort(data , pos + 1 , size - 1);
}

template <class Type>
void Quick_sort(Type *data , int begin , int end) {
    if (1 == end - begin) {
        if (data[begin] > data[end]) {
            Type tmp = data[begin];
            data[begin] = data[end];
            data[end] = tmp;
        }
        return;
    }
    if (end <= begin)
        return;
    int pos = divide(data , begin , end);
    Quick_sort(data , begin , pos - 1);
    Quick_sort(data , pos + 1 , end);
}
;
template <class Type>
int divide(Type *data , int begin , int end) {
    if (1 < end - begin) {
        Type tmp = data[begin];
        int low = begin , high = end;
        bool right = true;
        while ( high > low) {
            if (right) {
                for ( ; high > low && data[high] >= tmp ; --high);
                if (high == low )
                    break;
                data[low] = data[high];
                right = false;
            }
            else {
                for ( ; high > low && data[low] <= tmp ; ++low);
                if (low == high)
                    break;
                data[high] = data[low];
                right = true;
            }
        }
        data[low] = tmp;
        return low;
    }
    return begin;
}
