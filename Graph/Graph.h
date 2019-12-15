//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_GRAPH_H
#define WORKPLACE_GRAPH_H

#include "init.h"
#include "Edge.h"
#include "UFSets.h"
#include <stack>
#include <queue>
#include "../BinaryTree/Heap.h"
#include <iostream>

namespace nGraph {

    template<class WeightType>
    class Graph {
    protected:
        int vertexNum;
        int edgeNum;
        int *Mark;
    public:

        static const bool VISITED;
        static const bool UNVISITED;

        Graph(int vertecesNum);

        ~Graph();

        virtual Edge<WeightType> FirstEdge(VERTEXE oneVertex) = 0;

        virtual Edge<WeightType> NextEdge(Edge<WeightType> oneEdge) = 0;

        int VertexNum();

        int EdgeNum();

        bool IsEdge(Edge<WeightType> oneEdge);

        int StartVertex(Edge<WeightType> oneEdge);

        WeightType Weight(Edge<WeightType> oneEdge);

        virtual void setEdge(VERTEXE start, VERTEXE end, WeightType weight) = 0;

        virtual void delEdge(VERTEXE start, VERTEXE end) = 0;

        virtual Edge<WeightType> getEdge(VERTEXE start, VERTEXE end) = 0;

        void DFS(int v);

        void DFSNoReverse();

        void BFS();

        Edge<WeightType> *Prim();

        Edge<WeightType> *Kruskal();

        void Dijkstra(VERTEXE s, WeightType D[], VERTEXE Path[]);

        void Floyd(WeightType **Adj, int **Path);
    };

    template<class WeightType>
    const bool Graph<WeightType>::VISITED = true;

    template<class WeightType>
    const bool Graph<WeightType>::UNVISITED = false;

    template<class WeightType>
    Graph<WeightType>::Graph(int vertecesNum) {
        vertexNum = vertecesNum;
        edgeNum = 0;
        Mark = new int[vertexNum];
        for (int i = 0; i < vertexNum; Mark[i] = UNVISITED, ++i);
    }

    template<class WeightType>
    Graph<WeightType>::~Graph() {
        delete[] this->Mark;
    }

    template<class WeightType>
    int Graph<WeightType>::VertexNum() {
        return vertexNum;
    }

    template<class WeightType>
    int Graph<WeightType>::EdgeNum() {
        return this->edgeNum;
    }


    template<class WeightType>
    bool Graph<WeightType>::IsEdge(Edge<WeightType> oneEdge) {
        return oneEdge.weight > 0 && oneEdge.weight < MYINFINITY && oneEdge.weight > 0 && oneEdge.end >= 0;
    }

    template<class WeightType>
    int Graph<WeightType>::StartVertex(Edge<WeightType> oneEdge) {
        return oneEdge.start;
    }

    template<class WeightType>
    WeightType Graph<WeightType>::Weight(Edge<WeightType> oneEdge) {
        return oneEdge.weight;
    }

    template<class WeightType>
    void Graph<WeightType>::DFS(VERTEXE v) {
        using std::cout;
        using std::endl;
        if (Mark[v] == UNVISITED) {
            Mark[v] = VISITED;
            cout << v << endl;
        }
        for (Edge<WeightType> e = FirstEdge(v); IsEdge(e); e = NextEdge(e)) {
            if (Mark[e.end] == UNVISITED) {
                DFS(e.end);
            }
        }
    }


    template<class WeightType>
    void Graph<WeightType>::DFSNoReverse() {
        using std::stack;
        using std::cout;
        using std::endl;

        VERTEXE v, u;

        stack<int> s;
        for (VERTEXE j = 0; j < this->vertexNum; ++j) {
            Mark[j] = UNVISITED;
        }

        for (VERTEXE i = 0; i < this->vertexNum; ++i) {
            if (Mark[i] == UNVISITED) {
                s.push(i);
                while (!s.empty()) {
                    v = s.top();
                    s.pop();
                    if (Mark[v] == UNVISITED) {
                        cout << v << endl;
                        Mark[v] = VISITED;
                    }

                    for (Edge<WeightType> e = FirstEdge(v); IsEdge(e); e = NextEdge(e)) {
                        u = e.end;
                        if (Mark[u] == UNVISITED) {
                            s.push(u);
                        }

                    }
                }
            }
        }
    }


    template<class WeightType>
    void Graph<WeightType>::BFS() {
        using std::queue;
        using std::cout;
        using std::endl;

        queue<int> Q;

        Q.push(0);
        while (!Q.empty()) {
            VERTEXE u = Q.front();
            Q.pop();
            if (Mark[u] == UNVISITED) {
                cout << u << endl;
                Mark[u] = VISITED;
            }
            for (Edge<WeightType> e = FirstEdge(u); IsEdge(e); e = NextEdge(e)) {
                int k = e.end;
                if (Mark[k] == UNVISITED) {
                    Q.push(k);
                }

            }
        }

    }

    template<class WeightType>
    Edge<WeightType> *Graph<WeightType>::Prim() {
        // 引用prim算法从顶点s出发得到最小生成树
        const bool IN = true;
        const bool OUT = false;
        VERTEXE neighbor[this->vertexNum];      // 生成树中的节点
        VERTEXE nearest[this->vertexNum];       //还未在生成树中的节点
        auto *MST = new Edge<WeightType>[this->vertexNum - 1];

        for (int i = 0; i < this->vertexNum; ++i) {
            neighbor[i] = OUT;
            nearest[i] = IN;
        }

        neighbor[0] = IN;
        nearest[0] = OUT;

        for (int count = 0; count < this->vertexNum - 1; ++count) {
            WeightType weight = 1000;
            Edge<WeightType> maybe;
            for (VERTEXE i = 0; i < this->vertexNum; ++i) {
                if (neighbor[i]) {
                    for (Edge<WeightType> e = FirstEdge(i); IsEdge(e); e = NextEdge(e)) {
                        if (nearest[e.end] && e.weight < weight) {
                            weight = e.weight;
                            maybe.start = e.start;
                            maybe.end = e.end;
                            maybe.weight = weight;
                        }
                    }
                }
            }
            MST[count] = maybe;
            neighbor[maybe.end] = IN;
            nearest[maybe.end] = OUT;
        }
        return MST;

    }

    template<class WeightType>
    Edge<WeightType> *Graph<WeightType>::Kruskal() {
        using BinaryTree::MinHeap;
        int n = this->vertexNum;

        UFSets set(n);
        Edge<WeightType> *MST = new Edge<WeightType>[this->vertexNum - 1];
        MinHeap<Edge<WeightType>> H(MST, 0, 1000);
        Edge<WeightType> edge;
        for (VERTEXE i = 0; i < this->vertexNum; ++i) {
            for (edge = this->FirstEdge(i); IsEdge(edge); edge = NextEdge(edge)) {
                if (edge.start < edge.end) {
                    H.insert(edge);
                }
            }
        }
        int edgeNum = 0;
        while (edgeNum < n - 1) {
            try {
                if (!H.empty()) {
                    edge = H.removeMin();
                    VERTEXE v = edge.start;
                    VERTEXE u = edge.end;
                    if (set.Find(v) != set.Find(u)) {
                        set.Union(v, u);
                        MST[edgeNum++] = edge;
                    }
                } else {
                    std::cout << "不存在最小生成树" << std::endl;
                    exit(0);
                }
            } catch (const char *) {
                continue;
            }

        }
        return MST;
    }

    template<class WeightType>
    void Graph<WeightType>::Dijkstra(VERTEXE s, WeightType *D, VERTEXE *Path) {
        int n = this->vertexNum;

        //第一步将除与s节点有关的所有节点的边的权值记录，并且Path设置为s
        for (VERTEXE i = 0; i < n; ++i) {
            if (i != s) {
                this->Mark[i] = UNVISITED;
                D[i] = this->getEdge(s, i).weight;       //s相连的所有路径权值入数组
                Path[i] = s;            //与s相连的所有点的前驱为s
            }
        }
        this->Mark[s] = VISITED;
        D[s] = 0;
        for (VERTEXE i = 0; i < n; ++i) {
            if (i != s) {
                //找到最短路径
                //start
                WeightType min = MYINFINITY;
                int k = i;
                for (int j = 0; j < n; ++j) {
                    if (this->Mark[j] == UNVISITED && min > D[j]) {
                        min = D[j];
                        k = j;
                    }
                }
                this->Mark[k] = VISITED;
                // end

                // 更新与此时最短路径有关的所有的边
                // start
                for (Edge<WeightType> e = this->FirstEdge(k); IsEdge(e); e = this->NextEdge(e)) {
                    VERTEXE endVertex = e.end;
                    if (this->Mark[endVertex] == UNVISITED && D[endVertex] > (D[k] + e.weight)) {
                        D[endVertex] = D[k] + e.weight;
                        Path[endVertex] = k;
                    }
                }
                // end
            }

        }

        for (int l = 0; l < n; ++l) {
            if (this->Mark[l] == UNVISITED) {
                D[l] = MYINFINITY;
            }
        }

        return;

    }

    template<class WeightType>
    void Graph<WeightType>::Floyd(WeightType **Adj, int **Path) {

        //adj,path数组进行初始化
        for (VERTEXE i = 0; i < this->vertexNum; ++i) {
            for (VERTEXE j = 0; j < this->vertexNum; ++j) {
                if (i == j) {
                    Adj[i][j] = 0;
                    Path[i][j] = i;
                } else {
                    Adj[i][j] = this->getEdge(i, j).weight;
                    Path[i][j] = i;
                }
            }
        }

        // 如果两个顶点 i,j间的最短路径经过顶点v,且有adj[i][j]>(adj[i][k]+adj[k][j]),
        // 则更新adj[i][j],path[i][j]
        for (VERTEXE k = 0; k < this->vertexNum; ++k) {
            for (VERTEXE i = 0; i < this->vertexNum; ++i) {
                for (VERTEXE j = 0; j < this->vertexNum; ++j) {
                    if (i != j) {
                        if (Adj[i][j] > (Adj[i][k] + Adj[k][j])) {
                            Adj[i][j] = Adj[i][k] + Adj[k][j];
                            Path[i][j] = k;
                        }
                    }

                }
            }

        }

    }

}
#endif //WORKPLACE_GRAPH_H
