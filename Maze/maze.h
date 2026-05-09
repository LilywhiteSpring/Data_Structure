//
// Created by 85375 on 2025/11/24.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class maze {
private:
    int scale;
    bool **map;
    void print_step(stack<pair<int,int>> step) const;
    [[nodiscard]] bool isValid(int x,int y) const{
        if (x>=0 && x<scale && y>=0 && y<scale && map[x][y] )
            return true;
        return false;
    }
public:
    void print_map() const;
    maze() {
        cout<<"请输入迷宫的大小："<<endl;
        cin>>scale;
        while (scale <= 0 ) {
            cout<<"请输入一个大于0的整数！"<<endl;
            cin>>scale;
        }
        map = new bool* [scale];
        for (int i=0;i<scale;++i) {
            map[i] = new bool [scale];
            for (int j=0;j<scale;++j) {
                cout<<"请输入("<<i<<" , "<<j<<")点的开闭(“0”为闭，“1”为开)"<<endl;
                cin>>map[i][j];
            }
        }
    };
    ~maze() {
        for (int i=0;i<scale;++i) {
            delete [] map[i];
        }
        delete [] map;
    }
    void shortest_step() const;
};

#endif //MAZE_MAZE_H