//
// Created by 85375 on 2025/12/3.
//

#ifndef MAP_DIJKSTRA__MAP_H
#define MAP_DIJKSTRA__MAP_H
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
class Map {
private:
    struct node{
        double x;
        double y;
        void set(double x1,double y1) {
            x = x1;
            y = y1;
        };
    };
    struct wall {
        double x;
        double y_down;
        double y_up;
        void set(double x0 , double yd , double yu) {
            x = x0;
            y_down = yd;
            y_up = yu;
        }
    };
    struct s_node {
        node* po;
        int seq;
        s_node(): po(nullptr) , seq(-1){};
    };
    node* point;
    wall* walls;
    int num;
    int size = 10;
    bool is_Valid(node *pt1 , node *pt2) const;
    double distance(node pt1 ,node pt2) const;
public:
    explicit Map(int size): size(size) , point(nullptr) , walls(nullptr) , num(0){};
    void create_map() ;
    double shortest_road() const;
};
#endif //MAP_DIJKSTRA__MAP_H