#include "seqQueue.h"
int main() {
    seqQueue<int> que;
    for (int i=0;i<13;++i) {
        que.enQueue(i);
    }
    que.print_all();
    return 0;
}