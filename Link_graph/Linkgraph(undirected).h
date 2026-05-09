//
// Created by 85375 on 2025/12/28.
//

#ifndef LINK_GRAPH_LINKGRAPH_H
#define LINK_GRAPH_LINKGRAPH_H
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<class TypeVer = int , class TypeEdge = int>
class graph {
public:
    graph(): ver(0) , edge(0){}
    virtual ~graph() = default;

    int num_ver() const {return ver; }
    int num_edge() const {return edge; }
    virtual void insert(TypeVer x , TypeVer y , TypeEdge value) = 0;
    virtual void remove(TypeVer x , TypeVer y) = 0;
    virtual bool exist(TypeVer x , TypeVer y) const = 0;

protected:
    int ver;
    int edge;
};

//以下是一个无向图类
template<class TypeVer , class TypeEdge>
class LinkGraph : public graph<TypeVer , TypeEdge> {
private:
    struct EdgeNode {
        int end;
        TypeEdge weight;
        EdgeNode *next;

        EdgeNode(int i , TypeEdge w , EdgeNode *node = nullptr): end(i) , weight(w) , next(node){}
    };

    struct VerNode {
        TypeVer name;
        EdgeNode *head;

        VerNode(): head(nullptr){}
    };

    VerNode *VerList;
    int find(TypeVer x) const;


public:
    LinkGraph() {
        int size;
        cout<<"请输入顶点数量：\n";

        if (cin>>size) {
            graph<TypeVer , TypeEdge>::ver = size;
            graph<TypeVer , TypeEdge>::edge = 0;
            VerList = new VerNode [size];
            for (int i = 0 ; i < size ; ++i) {
                cout<<"请输入第"<<i + 1<<"个顶点的名称（数据）:\n";
                cin>>VerList[i].name;
            }
            cout<<"图初始化完成！\n";
        }
    }

    LinkGraph(int size , TypeVer *list) {
        this-> graph<TypeVer , TypeEdge>::ver = size;
        this-> edge = 0;
        VerList = new VerNode [size];
        for (int i = 0 ; i < size ; ++i)
            VerList[i].name = list[i];
    }
    ~LinkGraph() override;

    void display() const;
    void insert(TypeVer x , TypeVer y , TypeEdge w) override;
    void remove(TypeVer x , TypeVer y) override;
    bool exist(TypeVer x , TypeVer y) const override;

    void dfs() const;
    void bfs() const;
    void UnweighDistance(TypeVer start , TypeVer end) const;
    void Dijkstra(TypeVer start , TypeVer end) const;
    void NegativeDistance(TypeVer start , TypeVer end) const;
    void Floyd() const;

//欧拉环路类
    void EulerCircuit(TypeVer start);
private:
    struct EulerNode {
        int seq;
        EulerNode *next;

        explicit EulerNode(int x , EulerNode *node = nullptr): seq(x) , next(node){}
    };

       void EulerCircuit(int begin , EulerNode *&beg , EulerNode *&end);
        VerNode *clone() const;
};

template<class TypeVer , class TypeEdge>
LinkGraph<TypeVer , TypeEdge>::~LinkGraph() {
    EdgeNode *tmp;
    for (int i = 0 ; i < graph<TypeVer , TypeEdge>::ver ; ++i) {
        tmp = VerList[i].head;
        while (tmp != nullptr) {
            VerList[i].head = tmp-> next;
            delete tmp;
            tmp = VerList[i].head;
        }
    }
    delete [] VerList;
}


template<class TypeVer , class TypeEdge>
int LinkGraph<TypeVer , TypeEdge>::find(TypeVer x) const {
    for (int i = 0 ; i < graph<TypeVer , TypeEdge>::ver ; ++i) {
        if (VerList[i].name == x)
            return i;
    }
    cout<<"未查找到顶点"<<x<<endl;
    return -1;
}


template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::display() const {
    cout<<"当前图中点的个数为："<<this-> graph<TypeVer , TypeEdge>::ver<<endl;
    cout<<"顶点为:\t";
    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i)
        cout<<VerList[i].name<<' ';
    cout<<"\n当前边的个数为："<<this-> edge<<endl;
}


template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::insert(TypeVer x , TypeVer y , TypeEdge w) {
    int u = find(x);
    int v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点！\n\n";
        return;
    }
    EdgeNode *tmp;
    if (!VerList[u].head)
        VerList[u].head = new EdgeNode(v , w);
    else {
        tmp = VerList[u].head;
        while (tmp) {
            if (v == tmp-> end) {
                cout<<"插入的边发生重复!\n\n";
                return;
            }
            tmp = tmp-> next;
        }

        auto *NewNode = new EdgeNode(v , w);
        NewNode-> next = VerList[u].head;
        VerList[u].head = NewNode;
    }
    if (!VerList[v].head)
        VerList[v].head = new EdgeNode(u , w);
    else {
        auto *NewNode = new EdgeNode(u , w);
        NewNode-> next = VerList[v].head;
        VerList[v].head = NewNode;
    }
    ++graph<TypeVer , TypeEdge>::edge;
    cout<<"插入成功\n\n";
    //注意这里我不知道是不是应该检查一下插入的边有没有发生重复(需要
}

template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::remove(TypeVer x , TypeVer y) {
    int u = find(x) , v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点呀！\n\n";
        return;
    }
    EdgeNode *tmp , *tmp0;
    tmp = VerList[u].head;
    bool flag = false;
    if (!tmp) {
        cout<<"该边不存在！\n\n";
        return;
    }
    if (v == tmp-> end) {
        VerList[u].head = VerList[u].head-> next;
        delete tmp;
        flag = true;
    }
    else {
        while (tmp-> next) {
            if (v == tmp-> next-> end) {
                tmp0 = tmp-> next;
                tmp-> next = tmp0-> next;
                delete tmp0;
                flag = true;
                break;
            }
            tmp = tmp-> next;
        }
    }
    if (!flag) {
        cout<<"该边不存在！\n\n";
        return;
    }
    tmp = VerList[v].head;
    if (u == tmp-> end) {
        VerList[v].head = tmp-> next;
        delete tmp;
        cout<<"删除成功啦！\n\n";
    }
    else {
         while (tmp-> next) {
            if (u == tmp-> next-> end) {
                tmp0 = tmp-> next;
                tmp-> next = tmp0-> next;
                delete tmp0;
                cout<<"删除成功啦！\n\n";
                break;
            }
            tmp = tmp-> next;
        }
    }
    --graph<TypeVer , TypeEdge>::edge;
}

template<class TypeVer , class TypeEdge>
bool LinkGraph<TypeVer , TypeEdge>::exist(TypeVer x , TypeVer y ) const {
    int u = find(x) , v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点！\n\n";
        return false;
    }

    EdgeNode *tmp = VerList[u].head;
    while (tmp) {
        if (v == tmp-> end) {
            cout<<"该边存在捏！\n\n";
            return true;
        }
        tmp = tmp-> next;
    }
    cout<<"该边不存在呀qwq!\n\n";
    return false;
}

template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::dfs() const {
    cout<<"当前图的深搜序列为：\n";
    auto visit = new bool [this-> graph<TypeVer , TypeEdge>::ver];
    for (int i = 0 ; i <  this-> graph<TypeVer , TypeEdge>::ver ; ++i)
        visit[i] = false;
    stack<int> sequence;
    int tmpInt;
    EdgeNode *tmpEdge;

    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i) {
        if (visit[i])
            continue;
        sequence.push(i);
        while (!sequence.empty()) {
            tmpInt = sequence.top();
            sequence.pop();
            if (visit[tmpInt])
                continue;

            visit[tmpInt] = true;
            cout<<VerList[tmpInt].name<<' ';

            tmpEdge = VerList[tmpInt].head;
            while (tmpEdge) {
                if (!visit[tmpEdge-> end])
                    sequence.push(tmpEdge-> end);
                tmpEdge = tmpEdge-> next;
            }
        }
    }
    cout<<endl<<endl;
    delete [] visit;
}

template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::bfs() const {
    cout<<"当前图的广搜序列为：\n";
    auto visit = new bool [this-> graph<TypeVer , TypeEdge>::ver];
    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i)
        visit[i] = false;
    int tmpInt;
    EdgeNode *tmpNode;
    queue<int> sequence;

    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i) {
        if (visit[i])
            continue;
        sequence.push(i);
        while (!sequence.empty()) {
            tmpInt = sequence.front();
            sequence.pop();
            if (visit[tmpInt])
                continue;
            visit[tmpInt] = true;
            cout<<VerList[tmpInt].name<<' ';

            tmpNode = VerList[tmpInt].head;
            while (tmpNode) {
                if (!visit[tmpNode-> end])
                    sequence.push(tmpNode-> end);
                tmpNode = tmpNode-> next;
            }
        }
    }
    cout<<endl<<endl;
    delete [] visit;
}

template<class TypeVer , class TypeEdge>
typename LinkGraph<TypeVer , TypeEdge>::VerNode *LinkGraph<TypeVer , TypeEdge>::clone() const {
    auto NewList = new VerNode [this-> graph<TypeVer , TypeEdge>::ver];
    EdgeNode *tmpEdge1 , *tmpEdge2;
    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i) {
        NewList[i].name = VerList[i].name;
        if (!VerList[i].head)
            continue;
        NewList[i].head = new EdgeNode(VerList[i].head-> end , VerList[i].head-> weight);
        tmpEdge1 = VerList[i].head;
        tmpEdge2 = NewList[i].head;
        while (tmpEdge1-> next) {
            tmpEdge2-> next = new EdgeNode (tmpEdge1-> next-> end , tmpEdge1-> next-> weight);
            tmpEdge1 = tmpEdge1-> next;
            tmpEdge2 = tmpEdge2-> next;
        }
    }

    return NewList;
}

template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::EulerCircuit(TypeVer start) {
    //判断是否存在欧拉环路
    if (0 == this-> graph<TypeVer , TypeEdge>::ver) {
        cout<<"无欧拉环路qwq\n\n";
        return;
    }
    EdgeNode* tmpEdge;
    int degree;
    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i) {
        if (!VerList[i].head) {
            cout<<"无欧拉环路qwq\n\n";
            return;
        }
        degree = 1;
        tmpEdge = VerList[i].head-> next;
        while (tmpEdge) {
            ++degree;
            tmpEdge = tmpEdge-> next;
        }
        if (0 != degree % 2 ) {
            cout<<"无欧拉环路qwq\n\n";
            return;
        }
    }
    cout<<"以 "<<start<<"点 为开端的一条欧拉环路：\n";

    VerNode *tmp = clone();
    EulerNode *beg , *end , *tmpEuler1 , *tmpEuler2 , *tmp1 , *tmp2;
    int i = find(start);
    EulerCircuit(i , beg , end);
    tmpEuler1 = beg;
    while (true) {
        while (tmpEuler1-> next) {
            if (VerList[tmpEuler1-> next-> seq].head)
                break;
            tmpEuler1 = tmpEuler1-> next;
        }
        if (!tmpEuler1-> next)
            break;

        tmpEuler2 = tmpEuler1-> next;
        EulerCircuit(tmpEuler2-> seq , tmp1 , tmp2);
        tmpEuler1-> next = tmp1;
        tmp2-> next = tmpEuler2-> next;
        delete tmpEuler2;
    }

    delete [] VerList;
    VerList = tmp;
    //这里没有检查连通性！！
    while (beg) {
        cout<<VerList[beg-> seq].name<<"->";
        tmpEuler1 = beg;
        beg = beg-> next;
        delete tmpEuler1;
    }
    cout<<"end"<<endl<<endl;
}

template<class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::EulerCircuit(int begin , EulerNode *&beg , EulerNode *&end) {
    beg = end = new EulerNode (begin);
    int tmp = begin;
    while (VerList[tmp].head) {
        end-> next = new EulerNode (VerList[tmp].head-> end);
        end = end-> next;
        begin = tmp;
        tmp = end-> seq;
        remove(VerList[begin].name , VerList[tmp].name);
    }
}

template <class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::UnweighDistance(TypeVer start , TypeVer end) const {
    auto distance = new int [this-> ver];
    auto visit = new bool [this-> ver];
    auto *prev = new int [this-> ver];
    queue<int> sequence;
    EdgeNode *tmpEdge;
    constexpr int MAX = 32767;
    int cur , tmpInt , s = find(start) , e = find(end);
    for (int i = 0 ; i < this-> ver ; ++i) {
        distance[i] = MAX;
        visit[i] = false;
    }
    cur = s;
    distance[cur] = 0;
    prev[cur] = -1;
    sequence.push(cur);

    while (!sequence.empty() && !visit[e]) {

        tmpInt = sequence.front();
        sequence.pop();
        if (!visit[tmpInt]){
            visit[tmpInt] = true;
            tmpEdge = VerList[tmpInt].head;
            while (tmpEdge) {
                if (!visit[tmpEdge-> end]) {
                    distance[tmpEdge-> end] = distance[tmpInt] + 1;
                    prev[tmpEdge-> end] = tmpInt;
                    sequence.push(tmpEdge-> end);
                }
                tmpEdge = tmpEdge-> next;
            }
        }
    }

    // for (int i = 0 ; i < this-> ver ; ++i) {
    //     if (visit[i])
    //         cout<<"顶点"<<find(start)<<"的距离为："<<distance[i]<<endl;
    //     else
    //         cout<<"顶点"<<find(start)<<" 不存在到 顶点"<<i<<endl;
    // }
    if (visit[e]) {
        cout<<"顶点"<<start<<" 到 顶点"<<end<<" 的距离为："<<distance[e]<<endl;
        cout<<"路径为: ";
        cur = e;
        stack<int> path;
        while (cur != -1) {
            path.push(cur);
            cur = prev[cur];
        }
        cur = path.top();
        path.pop();
        cout<<VerList[cur].name;
        while (!path.empty()) {
            cur = path.top();
            path.pop();
            cout<<" -> "<<VerList[cur].name;
        }
        cout<<endl;
    }

    else
        cout<<"顶点"<<start<<" 不存在到 顶点"<<end<<" 的路径\n";
    delete [] distance;
    delete [] visit;
    delete [] prev;
}

template <class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::Dijkstra(TypeVer start , TypeVer end) const {
    auto distance = new int [this-> ver];
    auto visit = new bool [this-> ver];
    auto *prev = new int [this-> ver];
    EdgeNode *tmpEdge;
    constexpr int MAX = 32767;
    int cur , s = find(start) , e = find(end) , min;
    for (int i = 0 ; i < this-> ver ; ++i) {
        distance[i] = MAX;
        visit[i] = false;
    }
    cur = s;
    distance[cur] = 0;
    prev[cur] = -1;
    while (!visit[e]) {
        min = MAX;
        for (int i = 0 ; i < this-> ver ; ++i) {
            if (!visit[i]) {
                if (distance[i] < min) {
                    cur = i;
                    min = distance[i];
                }
            }
        }
        if (MAX == min)
            break;
        visit[cur] = true;
        tmpEdge = VerList[cur].head;
        while (tmpEdge) {
            if (distance[tmpEdge-> end] > distance[cur] + tmpEdge-> weight) {
                distance[tmpEdge-> end] = distance[cur] + tmpEdge-> weight;
                prev[tmpEdge-> end] = cur;
            }
            tmpEdge = tmpEdge-> next;
        }
    }


    if (visit[e]) {
        cout<<"顶点"<<start<<" 到 顶点"<<end<<" 的最短距离为: "<<distance[e]<<endl;
        cout<<"路径为:  ";
        cur = e;
        stack<int> path;
        while (cur != -1) {
            path.push(cur);
            cur = prev[cur];
        }
        cur = path.top();
        path.pop();
        cout<<VerList[cur].name;
        while (!path.empty()) {
            cur = path.top();
            path.pop();
            cout<<" -> "<<VerList[cur].name<<" (distance: " <<distance[cur] - distance[prev[cur]] <<")";
        }
        cout<<endl;
    }

    else
        cout<<"顶点"<<start<<" 不存在到 顶点"<<end<<" 的路径\n";
    delete [] distance;
    delete [] visit;
    delete [] prev;
}

template <class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::NegativeDistance(TypeVer start , TypeVer end) const {
    auto distance = new int [this-> ver];
    auto visit = new bool [this-> ver];
    auto *prev = new int [this-> ver];
    EdgeNode *tmpEdge;
    queue<int> sequence;
    constexpr int MAX = 32767;
    int cur , s = find(start) , e = find(end);
    for (int i = 0 ; i < this-> ver ; ++i) {
        distance[i] = MAX;
        visit[i] = false;
    }
    cur = s;
    distance[cur] = 0;
    prev[cur] = -1;
    sequence.push(cur);

    while (!sequence.empty()) {
        cur = sequence.front();
        visit[cur] = false;
        sequence.pop();
        tmpEdge = VerList[cur].head;
        while (tmpEdge) {
            if (distance[tmpEdge-> end] > distance[cur] + tmpEdge-> weight) {
                distance[tmpEdge-> end] = distance[cur] + tmpEdge-> weight;
                prev[tmpEdge-> end] = cur;
                if (!visit[tmpEdge-> end]) {
                    sequence.push(tmpEdge-> end);
                    visit[tmpEdge-> end] = true;
                }
            }
            tmpEdge = tmpEdge-> next;
        }
    }

    if (MAX != distance[e]) {
        cout<<"顶点"<<start<<" 到 顶点"<<end<<" 的最短距离为: "<<distance[e]<<endl;
        cout<<"路径为:  ";
        cur = e;
        stack<int> path;
        while (cur != -1) {
            path.push(cur);
            cur = prev[cur];
        }
        cur = path.top();
        path.pop();
        cout<<VerList[cur].name;
        while (!path.empty()) {
            cur = path.top();
            path.pop();
            cout<<" -> "<<VerList[cur].name<<" (distance: " <<distance[cur] - distance[prev[cur]] <<")";
        }
        cout<<endl;
    }

    else
        cout<<"顶点"<<start<<" 不存在到 顶点"<<end<<" 的路径\n";
    delete [] distance;
    delete [] visit;
    delete [] prev;
}

template <class TypeVer , class TypeEdge>
void LinkGraph<TypeVer , TypeEdge>::Floyd() const {
    constexpr int MAX = 32767;
    EdgeNode *tmpEdge;
    auto distance = new TypeEdge *[this-> ver];
    auto prev = new int *[this-> ver];
    for (int i = 0 ; i < this-> ver ; ++i) {
        distance[i] = new int [this-> ver];
        prev[i] = new int [this-> ver];
        for (int j = 0 ; j <= this-> ver ; ++j) {
            distance[i][j] = MAX;
            prev[i][j] = (i == j) ? i : -1;
        }
    }
    for (int i = 0 ; i < this-> ver ; ++i) {
        distance[i][i] = 0;
        tmpEdge = VerList[i].head;
        while (tmpEdge) {
            distance[i][tmpEdge-> end] = tmpEdge-> weight;
            tmpEdge = tmpEdge-> next;
        }
    }

    for (int k = 0 ; k < this-> ver ; ++k) {
        for (int i = 0 ; i < this-> ver ; ++i) {
            for (int j = 0 ; j < this-> ver ; ++j) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    prev[i][j] = k;
                }
            }
        }
    }
    cout<<"最短路径为："<<endl;
    for (int i = 0 ; i < this-> ver ; ++i) {
        for (int j = 0 ; j < this-> ver ; ++j) {
            cout<<distance[i][j]<<' ';
        }
        cout<<endl;
    }
    for (int i = 0 ; i < this-> ver ; ++i) {
        delete [] distance[i];
        delete [] prev[i];
    }
    delete [] distance;
    delete [] prev;
}


#endif //LINK_GRAPH_LINKGRAPH_H




//气死惹，每次写程序都要遇到小情侣，好……