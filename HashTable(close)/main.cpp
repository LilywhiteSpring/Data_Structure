#include "HashTable.h"
int main() {
    set<int , char> x;
    HashTable<int , char> table;
    for (int i = 1 ; i < 10 ; ++i) {
        x = {i , char(i + 'a')};
        table.insert(x);
        table.print();
    }
    table.insert(set<int , char>(3 , 'a'));
    for (int i = 1 ; i < 10 ; ++i) {
        table.remove(i);
    }
    table.find(12);
    table.remove(12);
    table.insert(set<int , char>(3 , 'a'));
    return 0;
}