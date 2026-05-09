//
// Created by 85375 on 2025/11/20.
//
#include "sLinklist.h"
#include <cstring>
int main() {
    sLinklist<char> list;
    list.print_all();
    list.push_back('a');
    list.print_all();
    list.erase(0);
    char a[10]="big";
    list.list_get(a,3);
    list.print_all();
    sLinklist<char> list1,list2;
    char x[] = "eating";
    char y[] = "funking";
    cout<<strlen(x)<<' '<<strlen(y)<<endl;
    list1.list_get(x,static_cast<int>(strlen(x)));
    list2.list_get(y,static_cast<int>(strlen(y)));
    sList_tail(list1,list2);

    return 0;
}