//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_EDGE_H
#define WORKPLACE_EDGE_H
namespace nGraph{
    template <class EdgeType>
    class Edge{
    public:
        int start,end;
        EdgeType weight;
        Edge();

        Edge(int st,int ed,int w);

        bool operator>(Edge<EdgeType> oneEdge);

        bool operator<(Edge<EdgeType> oneEdge);
    };

    template<class EdgeType>
    Edge<EdgeType>::Edge() {
        start = end= weight = 0;
    }

    template<class EdgeType>
    Edge<EdgeType>::Edge(int st, int ed, int w) {
        start = st;
        end = ed;
        weight = w;
    }

    template<class EdgeType>
    bool Edge<EdgeType>::operator>(Edge<EdgeType> oneEdge) {
        return this->weight>oneEdge.weight;
    }

    template<class EdgeType>
    bool Edge<EdgeType>::operator<(Edge<EdgeType> oneEdge) {
        return this->weight<oneEdge.weight;
    }
}


#endif //WORKPLACE_EDGE_H
