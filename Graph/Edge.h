//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_EDGE_H
#define WORKPLACE_EDGE_H
namespace nGraph{
    template <class WeightType>
    class Edge{
    public:
        int start,end;
        WeightType weight;
        Edge();

        Edge(int st, int ed, WeightType w=MYINFINITY);

        bool operator>(Edge<WeightType> oneEdge);

        bool operator<(Edge<WeightType> oneEdge);

        bool operator>=(Edge<WeightType> oneEdge);

        bool operator<=(Edge<WeightType> oneEdge);

        bool operator==(Edge<WeightType> oneEdge);

    };

    template<class WeightType>
    Edge<WeightType>::Edge() {
        start = 0;
        weight = MYINFINITY;
        end = -1;
    }

    template<class WeightType>
    Edge<WeightType>::Edge(int st, int ed, WeightType w) {
        start = st;
        end = ed;
        weight = w;
    }

    template<class WeightType>
    bool Edge<WeightType>::operator>(Edge<WeightType> oneEdge) {
        return this->weight>oneEdge.weight;
    }

    template<class WeightType>
    bool Edge<WeightType>::operator<(Edge<WeightType> oneEdge) {
        return this->weight<oneEdge.weight;
    }

    template<class WeightType>
    bool Edge<WeightType>::operator>=(Edge<WeightType> oneEdge) {
        return this->weight>=oneEdge.weight;
    }

    template<class WeightType>
    bool Edge<WeightType>::operator<=(Edge<WeightType> oneEdge) {
        return this->weight<=oneEdge.weight;
    }

    template<class WeightType>
    bool Edge<WeightType>::operator==(Edge<WeightType> oneEdge) {
        return this->weight==oneEdge.weight;
    }
}


#endif //WORKPLACE_EDGE_H
