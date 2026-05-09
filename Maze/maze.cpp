//
// Created by 85375 on 2025/11/24.
//\

#include "maze.h"

void maze::print_map() const{
    for (int i=0;i<scale;++i) {
        for (int j=0;j<scale;++j) {
            if (map[i][j])
                cout<<0<<' ';
            else
                cout<<1<<' ';
        }
        cout<<'\n';
    }
}
void maze::shortest_step() const {
    if (scale<1){
        cout<<"地图错误！"<<endl;
    return;
    }
    if (!map[0][0] || !map[scale-1][scale-1]) {
        cout<<"地图无解！"<<endl;
        return;
    }
    bool **visited = new bool *[scale];
    for (int i=0;i<scale;++i) {
        visited[i] = new bool [scale];
        for (int j=0;j<scale;++j)
            visited[i][j] = false;
    }
    visited[0][0] = true;
    auto **prev = new pair<int,int>*[scale];
    for (int i=0;i<scale;++i) {
        prev[i] = new pair<int,int> [scale];
    }
    queue<pair<int,int>> nodes;

    nodes.emplace(0,0); //这里emplace避免了移动构造，直接原地构造，能够减少开销
    pair<int,int> move[4] = {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1},
    };

    int nx,ny;bool pass = false;
    while (!nodes.empty()) {
        auto[x,y] = nodes.front();
        nodes.pop();

        if (scale-1 == x&& scale-1 == y) {
            pass = true;
            break;
        }
        for (auto [dx,dy] : move) {
            nx=x+dx ; ny= y+dy;
            if ( isValid(nx,ny) && !visited[nx][ny] ) {
                nodes.emplace(nx,ny);
                visited[nx][ny] = true;
                prev[nx][ny] = {x,y};
            }
        }
    }
    if (! pass) {
        cout<<"此路不通！！"<<endl;
        for (int i=0;i<scale;++i) {
            delete [] visited [i];
            delete [] prev[i];
        }
        delete [] visited;
        delete [] prev;
        return;
    }
    stack<pair<int,int>> step;
    pair node = {scale-1,scale-1};
    auto[x,y] = node;
    while (x!= 0 || y!= 0) {
        step.emplace(x,y);
        node = prev[x][y];
        x= node.first;
        y= node.second;
    }
    step.emplace(x,y);
    print_step(step) ;
    for (int i=0;i<scale;++i) {
        delete [] visited [i];
        delete [] prev[i];
    }
    delete [] visited;
    delete [] prev;
}

void maze::print_step(stack<pair<int, int>> step) const {
    bool ** path = new bool *[scale];
    for (int i=0;i<scale;++i) {
        path[i] = new bool[scale];
        for (int j=0;j<scale;++j) {
            path[i][j] = false;
        }
    }
    int steps=0;
    while (!step.empty()) {
        auto[x,y] = step.top();
        step.pop();
        ++steps;
        cout<<'('<<x<<" , "<<y<<')'<<" -> ";
        path[x][y] = true;
    }
    cout<<'\n'<<"最短路径总共为"<<steps<<"步"<<endl;
    for (int i=0;i<scale;++i) {
        for (int j=0;j<scale;++j) {
            if (path[i][j])
                cout<<'*'<<' ';
            else if (map[i][j])
                cout<<'0'<<' ';
            else cout<<'1'<<' ';
        }
        cout<<'\n';
    }
    for (int i=0;i<scale;++i)
        delete [] path[i];
    delete [] path;
}
// 1 1 0 0 0 0 0 1 1 1
// 0 1 0 1 1 1 1 1 0 0
// 0 1 1 1 0 0 1 0 0 0
// 0 0 1 0 0 0 1 0 0 0
// 0 0 1 0 0 0 1 1 1 0
// 0 1 1 0 0 0 1 0 0 0
// 0 0 1 1 1 1 1 0 0 0
// 0 0 1 0 0 1 0 0 0 0
// 0 0 0 0 0 1 1 1 1 1
// 0 0 0 0 0 1 0 0 1 1