//
// Created by 85375 on 2025/12/3.
//
#include "Map.h"

void Map::create_map() {
    int n ;
    double x , yd , yu;
    cin>>n;
    num = 4 * n + 2;
    walls = new wall [3 * n];
    point = new node[2 + 4 * n];
    point[0].set(0 , static_cast<double>(size) / 2);
    point[num - 1].set(size , static_cast<double>(size) / 2);
    for (int i = 1 ; i <= n ; ++i) {
        cin>>x;
        cin>>yd;
        walls[3 * i - 3].set(x , 0 , yd);
        cin>>yu;
        point[4 * i - 3].set(x , yd);
        point[4 * i - 2].set(x , yu);
        cin>>yd;
        walls[3 * i - 2].set(x , yu ,yd);
        cin>>yu;
        walls[3 * i - 1].set(x , yu,size);
        point[4 * i - 1].set(x , yd);
        point[4 * i].set(x , yu);
    }
    if (is_Valid(&point[0] , &point[num-1]))
        cout<<1<<endl;
    else
        cout<<0<<endl;
}

bool Map::is_Valid(node* pt1 , node* pt2) const {
    if (pt1 == pt2)
        return true;
    if (pt1-> x == pt2-> x)
        return true;
    if (pt1-> x > size || pt2-> x > size || pt1-> x < 0 || pt2-> x < 0 || pt1-> y > size || pt1-> y < 0 || pt2-> y > size || pt2-> y < 0)
        return false;
    double x_max , x_min ;
    if (pt1-> x > pt2-> x) {
        x_max = pt1-> x;
        x_min = pt2-> x;
    }
    else {
        x_max = pt2-> x;
        x_min = pt1-> x;
    }
    for (int i = 0 ; i < (num - 2) / 4 * 3 ; ++i) {
        if (walls[i].x > x_min && walls[i].x < x_max) {
            double k = (pt1-> y - pt2-> y) / (pt1-> x - pt2-> x);
            double y0 = k * (walls[i].x - pt1-> x) + pt1-> y;
            if (y0 <= walls[i].y_up && y0 >= walls[i].y_down)
                return false;
        }
    }
    return true;
}
double Map::distance(node pt1,node pt2) const {
    double dis = sqrt(pow(pt1.x - pt2.x , 2) + pow(pt1.y - pt2.y , 2));
    return dis;
}
double Map::shortest_road() const {
    double MAX = 32627;
    auto s_points = new s_node[num];
    for (int i = 0 ; i < num ; ++i) {
        s_points[i].po = &point[i];
        s_points[i].seq = i;
    }
    queue<s_node> ways;
    auto *is_visited = new bool [num];
    auto *path = new double [num];
    s_node* tmp;
    double dis;
    path [0] = 0;
    for (int i = 1 ; i < num ; ++i) {
        path[i] = MAX;
        is_visited[i] = false;
    }
    ways.push(s_points[0]);

    while (!ways.empty()) {
        tmp = &ways.front();
        ways.pop();
        for (int i = 1 ; i < num ; ++i) {
            if (i == tmp-> seq)
                continue;
            if (is_Valid( &point[i] , tmp-> po )) {
                if (s_points-> seq != num - 1 && !is_visited[i]) {
                    is_visited[i] = true;
                    ways.push(s_points[i]);
                }
                dis = distance(point[i] , *tmp-> po);
                if (dis + path[tmp-> seq] < path[i]) {
                    path[i] = dis + path[tmp-> seq];
                }
            }
        }
    }
    double result = path[num-1];
    delete [] path;
    delete [] is_visited ;
    delete [] s_points;
    return result;
}