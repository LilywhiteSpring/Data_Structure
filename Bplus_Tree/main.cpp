#include "BplusTree.h"

int main() {
    set<int , char>x;
    BlkTree<int , char , 3 , 3>tr;
    // tr.PrintData();
    for (int i  = 0 ; i < 4 ; ++i) {
        x = {i , static_cast<char>(i + 'a')};
        tr.insert(x);
    }
    return 0;
}
