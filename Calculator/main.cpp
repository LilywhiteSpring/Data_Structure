#include "calc.h"
int main() {
    char c[20] = " 1 + 3 - 5*4";
    calc ans1(c);
    ans1.result();
    cin>>c;
    calc ans2(c);
    ans2.result();
    return 0;
}