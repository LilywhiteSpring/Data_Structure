#include "Hftree.h"
#include "cstring"
int main() {
    int size;
    cin>>size;
    char *str = new char[size];
    int *weigh = new int[size];
    cout<<"请输入待编码的字符和对应的权重\n";
    for (int i=0 ; i<size ; ++i) {
        cin>>str[i]>>weigh[i];
    }

    Hf_tree<char> tree((str),weigh,size);
    tree.get_code();

    return 0;
}