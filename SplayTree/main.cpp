#include "SplayTree.h"
int main() {
    SplayTree<int , char> tr;
    set<int , char> x ;
    for (int i = 0 ; i < 5 ; ++i) {
        x = {i , char(i + 'a')};
        tr.insert(x);
    }
    for (int i = 0 ; i < 5 ; ++i)
        cout<<tr.find(i)<<endl;
    return 0;
}