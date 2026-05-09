#include "RedBlackTree.h"
int main() {
    RedBlackTree<int , char> t;
    set<int , char> s = {0 , '\0'};
    for (int i = 0 ; i < 10 ; ++i) {
        s = {i , static_cast<char>('a' + i)};
        t.insert(s);
    }
    for (int i = 1 ; i < 5 ; ++i)
        t.remove(i);
    return 0;
}