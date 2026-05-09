//
// Created by 85375 on 2025/12/30.
//

#ifndef LINK_GRAPH_LINKGRAPH_DIRECTED_H
#define LINK_GRAPH_LINKGRAPH_DIRECTED_H
#include "Linkgraph(undirected).h"

template<class TypeVer , class TypeEdge>
class BiLinkGraph : public graph<TypeVer , TypeEdge> {
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
    bool loop_check(int seq , bool *visit , bool *check) const;

public:
    BiLinkGraph() {
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

    BiLinkGraph(int size , TypeVer *list) {
        this-> graph<TypeVer , TypeEdge>::ver = size;
        this-> edge = 0;
        VerList = new VerNode [size];
        for (int i = 0 ; i < size ; ++i)
            VerList[i].name = list[i];
    }
    ~BiLinkGraph() override;

    void display() const;
    void insert(TypeVer x , TypeVer y , TypeEdge w) override;
    void remove(TypeVer x , TypeVer y) override;
    bool exist(TypeVer x , TypeVer y) const override;

    void dfs() const;
    void bfs() const;
    bool loop_check() const;
    void AOV() const;
    void AOE() const;

};
template <class TypeVer , class TypeEdge>
BiLinkGraph<TypeVer , TypeEdge>::~BiLinkGraph() {
    EdgeNode *tmp;
    for (int i = 0 ; i < this-> ver ; ++i) {
        while (VerList[i].head) {
            tmp = VerList[i].head;
            VerList[i].head = VerList[i].head-> next;
            delete tmp;
        }
    }
    delete [] VerList;
}

template<class TypeVer , class TypeEdge>
int BiLinkGraph<TypeVer , TypeEdge>::find(TypeVer x) const {
    for (int i = 0 ; i < graph<TypeVer , TypeEdge>::ver ; ++i) {
        if (VerList[i].name == x)
            return i;
    }
    cout<<"未查找到顶点"<<x<<endl;
    return -1;
}

template<class TypeVer , class TypeEdge>
void BiLinkGraph<TypeVer , TypeEdge>::display() const {
    cout<<"当前图中点的个数为："<<this-> graph<TypeVer , TypeEdge>::ver<<endl;
    cout<<"顶点为:\t";
    for (int i = 0 ; i < this-> graph<TypeVer , TypeEdge>::ver ; ++i)
        cout<<VerList[i].name<<' ';
    cout<<"\n当前边的个数为："<<this-> edge<<endl<<endl;
}

template<class TypeVer , class TypeEdge>
bool BiLinkGraph<TypeVer , TypeEdge>::exist(TypeVer x , TypeVer y ) const {
    int u = find(x) , v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点！\n\n";
        return false;
    }

    EdgeNode *tmp = VerList[u].head;
    while (tmp) {
        if (v == tmp-> end) {
            cout<<"边 "<<x<<"->"<<y<<" 存在！\n\n";
            return true;
        }
        tmp = tmp-> next;
    }
    cout<<"边 "<<x<<"->"<<y<<" 不存在！\n\n";
    return false;
}


template<class TypeVer , class TypeEdge>
void BiLinkGraph<TypeVer , TypeEdge>::insert(TypeVer x , TypeVer y , TypeEdge w) {
    int u = find(x) , v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点！\n\n";
        return;
    }
    EdgeNode *tmp = VerList[u].head;
    while (tmp) {
        if (v == tmp-> end) {
            cout<<"边 "<<x<<"->"<<y<<" 已存在！\n\n";
            return;
        }
        tmp = tmp-> next;
    }

    tmp = new EdgeNode(v , w);
    tmp-> next = VerList[u].head;
    VerList[u].head = tmp;
    cout<<"插入成功！\n\n";
    ++this-> edge;
}

template<class TypeVer , class TypeEdge>
void BiLinkGraph<TypeVer , TypeEdge>::remove(TypeVer x , TypeVer y) {
    int u = find(x) , v = find(y);
    if (-1 == u || -1 == v) {
        cout<<"未查找到顶点呀！\n\n";
        return;
    }

    EdgeNode *tmp , *tmp0;
    tmp = VerList[u].head;
    if (!tmp) {
        cout<<"该边不存在！\n\n";
        return;
    }
    if (v == tmp-> end) {
        VerList[u].head = tmp-> next;
        delete tmp;
        cout<<"删除成功！\n\n";
        --this-> edge;
        return;
    }

    while (tmp-> next) {
        if (v == tmp-> next-> end) {
            tmp0 = tmp-> next;
            tmp-> next = tmp0-> next;
            delete tmp0;
            cout<<"删除成功！\n\n";
            --this-> edge;
            return;
        }
        tmp = tmp-> next;
    }
    cout<<"该边不存在！\n\n";
}

template<class TypeVer , class TypeEdge>
void BiLinkGraph<TypeVer , TypeEdge>::dfs() const {
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
void BiLinkGraph<TypeVer , TypeEdge>::bfs() const {
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

template <class TypeVer ,class TypeEdge>
bool BiLinkGraph<TypeVer ,  TypeEdge>::loop_check() const {
    bool *visit = new bool [this-> ver] , *check = new bool [this-> ver];
    EdgeNode *tmpEdge;
    stack<int> sequence;
    for (int i = 0 ; i < this-> ver ; ++i)
        check[i] = false;

    for (int i = 0 ; i < this-> ver ; ++i) {
        if (!check[i]) {
            for (int j = 0 ; j < this-> ver ; ++j)
                visit[i] = false;
            sequence.push(i);

        }
    }

    delete [] visit;
    delete [] check;
}
#endif //LINK_GRAPH_LINKGRAPH_DIRECTED_H