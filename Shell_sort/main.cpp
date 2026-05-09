#include <iostream>
using namespace std;
template<class Type>
void Shell_sort(Type *data , int size);
int main() {
    int data [6] = {6 , 5 , 4 , 3 , 2 , 1};
    Shell_sort(data , 6);
    for (int i : data)
        cout<<i<<'\t';
    return 0;
}
template <class Type>
void Shell_sort(Type *data , int size) {
    Type tmp;
    int j;
    for (int step = size / 2 ; step >= 1 ; step /= 2) {
        for (int i = step ; i < size ; ++i) {
            tmp = data[i];
            for (j = i - step ; j >= 0 && tmp < data[j] ; j -= step)
                data[j + step] = data[j];
            data[j + step] = tmp;
        }
    }
}