#include "Linkgraph(undirected).h"

int main() {
    int a[] = {1 , 2 , 3};
    LinkGraph<int , int> map(3 , a);
    //插入测试
    map.display();
    map.insert(1 , 2 , 1);
    map.display();
    map.insert(1 , 2 , 1);
    map.display();
    map.remove(1 , 2);
    map.insert(1 , 3 , 1);
    //遍历测试
    map.dfs();
    map.bfs();

    //欧拉回路
    map.insert(2 , 3 , 3);
    map.insert(1 , 2 , 5);
    for (int i : {1 , 2 , 3})
        map.EulerCircuit(i);

  //BFS最短路径
    map.UnweighDistance(1 , 1);
    map.UnweighDistance(1 , 3);

    //Dijkstra最短路径
    map.Dijkstra(1 , 1);
    map.Dijkstra(1 , 2);
    map.Dijkstra(1 , 3);

    //Floyd最短路径
    map.Floyd();
    return 0;

}