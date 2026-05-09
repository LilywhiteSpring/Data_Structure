#include <iostream>
#include <string>
using namespace std;
class  strtest{
private:
    string data;
    int length;
public:
    strtest(const string&);
    int find(const strtest&);
};
int main() {
    string x="1234567",y= "345";
    cin>> x>>y;
    strtest a(x),b(y);
    cout<<a.find(b);

    return 0;
}
strtest::strtest(const string& x):data(x),length(x.size()){};
int strtest::find(const strtest& sub) {
    if (sub.length>length)
        return -1;
    int *invalid = new int[sub.length];
    invalid[0] = -1;
    int j;
    for (int i=1;i<sub.length;++i) {
        j=i-1;
        while (invalid[j]>=0 && sub.data[i] != sub.data[invalid[j]+1])
            j = invalid[j];
        if (invalid[j]<0)
            invalid[i] = -1;
        else
            invalid[i] = 1 + invalid[j];
    }
    int i=j=0;
    while (i+j<length) {
        if (sub.length-1 == j) {
            if (sub.data[j] == data[i+j]) {
                delete [] invalid;
                return i;
            }
        }
        if (sub.data[j] != data[i+j]) {
            i += j-invalid[j];
            j = invalid[j];;
        }
        j++;
    }
    cout<<"未找到相应子串！";
    delete [] invalid;
    return -1;
}

