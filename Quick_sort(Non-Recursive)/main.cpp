#include <iostream>
#include <queue>
using namespace std;
//非递归版本的快速排序（分割值取中间）ascending实际上应该说是取end ， begin ， 和 mid的中值
template <class KEY>
void Quick_sort(KEY *data , int size);
template <class KEY>
int divide(KEY *data , int begin , int end);
template <class KEY>
void Swap(KEY &x , KEY &y){KEY tmp = x ; x = y ; y = tmp;}
int main() {
    int a[] = {1 , 5 , 2 , 5 , 77 , 10 , 8 , 33 , 101 , 33 };
    Quick_sort(a , 10);
    for (int i : a)
        cout<<i<<'\t';
    return 0;
}

template <class KEY>
void Quick_sort(KEY  *data , int size) {
    queue< pair<int , int>> event;
    int begin , mid , end;
    KEY tmp;
    event.emplace(0 , size -1);
    while (!event.empty()) {
        begin = event.front().first;
        end = event.front().second;
        event.pop();
        if (1 > end - begin)
            continue;
        if (1 == end - begin) {
            if (data[end] < data[begin]) {
                tmp = data[begin];
                data[begin] = data[end];
                data[end] = tmp;
            }
        }
        int pos = divide(data , begin , end);
        event.emplace(begin , pos - 1);
        event.emplace(pos + 1 , end);
    }
}

template <class KEY>
int divide(KEY *data , int begin , int end) {
    int mid = (begin + end) / 2 ;

    if (data[begin] < data[mid])
        swap(data[begin] , data[mid]);
    if (data[begin] > data[end])
        swap(data[begin] , data[end]);
    if (data[begin] < data[mid])
        swap(data[begin] , data[mid]);
    KEY std = data[begin];
    bool right = true;
    while (end > begin) {
        if (right) {
            for ( ; end > begin && data[end] >= std ; --end);
            data[begin] = data[end];
            right =false;
        }
        else {
            for ( ; end > begin && data[begin] <= std ; ++begin);
            data[end] = data[begin];
            right = true;
        }
    }
    data[begin] = std;
    return end;
}