#include "Map.h"
#include <iomanip>
int main() {
    Map m(10);
    m.create_map();
    cout<<fixed<<setprecision(2)<<m.shortest_road();
    return 0;
}