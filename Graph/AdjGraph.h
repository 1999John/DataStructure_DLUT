//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_ADJGRAPH_H
#define WORKPLACE_ADJGRAPH_H

#include "init.h"
#include "Edge.h"
#include <math.h>

namespace nGraph {


    struct vertexTuple {
        VERTEXE start;
        VERTEXE end;

        vertexTuple(VERTEXE s=-1, VERTEXE e=-1) {
            start = s;
            end = e;
        }
    };

    template<class WeightType>
    class AdjGraph : public Graph<WeightType> {
    private:
        int **matrix;

        bool _find(vertexTuple* vtArr,VERTEXE s,VERTEXE e,int curlen);

    public:

        AdjGraph(int vertexNum);

        AdjGraph(const AdjGraph<WeightType> &ag);

        virtual ~AdjGraph();

        Edge <WeightType> FirstEdge(int oneVertex);

        Edge <WeightType> NextEdge(Edge <WeightType> oneEdge);

        void setEdge(int start, int end, WeightType weight);

        void delEdge(int start, int end);

        Edge<WeightType> getEdge(VERTEXE start, VERTEXE end) override;

    };

    template<class WeightType>
    AdjGraph<WeightType>::AdjGraph(int vertexNum) : Graph<WeightType>(vertexNum) {
        matrix = (int **) new int *[vertexNum];
        for (int i = 0; i < vertexNum; ++i) {
            matrix[i] = new int[vertexNum];
        }
        for (int i = 0; i < vertexNum; ++i) {
            for (int j = 0; j < vertexNum; ++j) {
                matrix[i][j] = MYINFINITY;
            }
        }
    }

    template<class WeightType>
    AdjGraph<WeightType>::AdjGraph(const AdjGraph<WeightType> &ag):Graph<WeightType>(ag.vertexNum) {
        for (int i = 0; i < this->vertexNum; ++i) {
            for (int j = 0; j < this->vertexNum; ++j) {
                this->matrix[i][j] = ag.matrix[i][j];
            }
        }
    }

    template<class WeightType>
    AdjGraph<WeightType>::~AdjGraph() {
        {
            for (int i = 0; i < this->vertexNum; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

    template<class WeightType>
    Edge <WeightType> AdjGraph<WeightType>::FirstEdge(VERTEXE oneVertex) {
        Edge<WeightType> tmpEdge;
        tmpEdge.start = oneVertex;
        tmpEdge.end = -1;
        tmpEdge.weight = MYINFINITY;
        for (int i = 0; i < this->vertexNum; ++i) {
            if (matrix[oneVertex][i] != MYINFINITY) {
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneVertex][i];
                return tmpEdge;
            }
        }
        return tmpEdge;
    }

    template<class WeightType>
    Edge <WeightType> AdjGraph<WeightType>::NextEdge(Edge <WeightType> oneEdge) {
        Edge<WeightType> tmpEdge;
        tmpEdge.start = oneEdge.start;
        tmpEdge.end = -1;
        tmpEdge.weight = MYINFINITY;
        for (int i = (oneEdge.end + 1); i < this->vertexNum; ++i) {
            if (matrix[oneEdge.start][i] != MYINFINITY) {
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneEdge.start][i];
                return tmpEdge;
            }
        }
        return tmpEdge;
    }

    template<class WeightType>
    void AdjGraph<WeightType>::setEdge(int start, int end, WeightType weight) {
        matrix[start][end] = weight;
    }

    template<class WeightType>
    void AdjGraph<WeightType>::delEdge(int start, int end) {
        matrix[start][end] = MYINFINITY;
    }


    template<class WeightType>
    bool AdjGraph<WeightType>::_find(vertexTuple *vtArr, VERTEXE s, VERTEXE e, int curlen) {
        for (int i = 0; i < curlen; ++i) {
            if ((vtArr[i].start ==s&&vtArr[i].end == e)||(vtArr[i].end==s&&vtArr[i].start==e)){
                return true;
            }
        }
        return false;
    }

    template<class WeightType>
    Edge<WeightType> AdjGraph<WeightType>::getEdge(VERTEXE start, VERTEXE end) {
        Edge<WeightType> ret(start, end, this->matrix[start][end]);
        return ret;
    }

}
#endif //WORKPLACE_ADJGRAPH_H
