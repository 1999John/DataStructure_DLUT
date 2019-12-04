//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_GRAPH_H
#define WORKPLACE_GRAPH_H

#include "init.h"
#include "Edge.h"
#include <stack>
#include <queue>

namespace nGraph {

    template<class EdgeType>
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

        virtual Edge<EdgeType> FirstEdge(VERTEXE oneVertex) = 0;

        virtual Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge) = 0;

        int VertexNum();

        int EdgeNum();

        bool IsEdge(Edge<EdgeType> oneEdge);

        int StartVertex(Edge<EdgeType> oneEdge);

        EdgeType Weight(Edge<EdgeType> oneEdge);

        virtual void setEdge(VERTEXE start, VERTEXE end, EdgeType weight) = 0;

        virtual void delEdge(VERTEXE start, VERTEXE end) = 0;

        void DFS(int v);

        void DFSNoReverse();

        void BFS();
    };

    template<class EdgeType>
    const bool Graph<EdgeType>::VISITED = true;

    template<class EdgeType>
    const bool Graph<EdgeType>::UNVISITED = false;

    template<class EdgeType>
    Graph<EdgeType>::Graph(int vertecesNum) {
        vertexNum = vertecesNum;
        edgeNum = 0;
        Mark = new int[vertexNum];
        for (int i = 0; i < vertexNum; Mark[i] = UNVISITED, ++i);
    }

    template<class EdgeType>
    Graph<EdgeType>::~Graph() {
        delete[] this->Mark;
    }

    template<class EdgeType>
    int Graph<EdgeType>::VertexNum() {
        return vertexNum;
    }

    template<class EdgeType>
    int Graph<EdgeType>::EdgeNum() {
        return this->edgeNum;
    }


    template<class EdgeType>
    bool Graph<EdgeType>::IsEdge(Edge<EdgeType> oneEdge) {
        return oneEdge.weight > 0 && oneEdge.weight < MYINFINITY && oneEdge.end >= 0;
    }

    template<class EdgeType>
    int Graph<EdgeType>::StartVertex(Edge<EdgeType> oneEdge) {
        return oneEdge.start;
    }

    template<class EdgeType>
    EdgeType Graph<EdgeType>::Weight(Edge<EdgeType> oneEdge) {
        return oneEdge.weight;
    }

    template<class EdgeType>
    void Graph<EdgeType>::DFS(VERTEXE v) {
        using std::cout;
        using std::endl;
        if(Mark[v]==UNVISITED){
            Mark[v] = VISITED;
            cout << v << endl;
        }
        for (Edge<EdgeType> e = FirstEdge(v); IsEdge(e); e = NextEdge(e)) {
            if(Mark[e.end]==UNVISITED){
                DFS(e.end);
            }
        }
    }


    template<class EdgeType>
    void Graph<EdgeType>::DFSNoReverse() {
        using std::stack;
        using std::cout;
        using std::endl;

        VERTEXE v,u;

        stack<int> s;
        for (VERTEXE j = 0; j < this->vertexNum; ++j) {
            Mark[j] = UNVISITED;
        }

        for (VERTEXE i = 0; i < this->vertexNum; ++i) {
            if(Mark[i]==UNVISITED){
                s.push(i);
                while(!s.empty()){
                    v = s.top();
                    s.pop();
                    if(Mark[v]==UNVISITED){
                        cout<<v<<endl;
                        Mark[v]=VISITED;
                    }

                    for (Edge<EdgeType> e = FirstEdge(v); IsEdge(e) ; e = NextEdge(e)) {
                        u = e.end;
                        if(Mark[u]==UNVISITED){
                            s.push(u);
                        }

                    }
                }
            }
        }
    }


    template<class EdgeType>
    void Graph<EdgeType>::BFS() {
        using std::queue;
        using std::cout;
        using std::endl;

        queue<int> Q;

        Q.push(0);
        while(!Q.empty()){
            VERTEXE u = Q.front();
            Q.pop();
            if(Mark[u]==UNVISITED){
                cout<<u<<endl;
                Mark[u]=VISITED;
            }
            for (Edge<EdgeType> e = FirstEdge(u); IsEdge(e); e = NextEdge(e)) {
                int k = e.end;
                if(Mark[k]==UNVISITED){
                    Q.push(k);
                }

            }
        }


    }
}




#endif //WORKPLACE_GRAPH_H
