#include "AATree.h"
int main() {
    AATree<int , char> tr;
    set<int  , char> x = {0 , '\0'};
    for (int i = 1 ; i <= 5; ++i) {
        x = {i , static_cast<char>('a' + i)};
        tr.insert(x);
    }
    for (int i = 1 ; i <= 5 ; ++i)
        tr.remove(i);
    return 0;
}