#include <iostream>
using namespace std;
int Catalan(int n) ;
int main() {
    int n;cin>>n;
    cout <<Catalan(n);
    return 0;
}
int Catalan(int n) {
    int **path = new int *[n+1];
    for (int i = 0;i<n+1;++i) {
        path[i] = new int [n+1];
    }
    path[0][0] = 1;
    for (int pop=1;pop<=n;++pop) {
        for (int back = 0;back<=pop;++back) {
            if (pop == back) {
                path[pop][back] = path[pop][back-1];
            }
            else if (0 == back) {
                path[pop] [back] =1;
            }
            else {
                path[pop][back] = path[pop][back-1] +path[pop-1][back];
            }
        }
    }
    int ans = path[n][n];
    for (int i=0;i<=n;++i)
        delete [] path[i];
    delete []path;
    return ans;
}