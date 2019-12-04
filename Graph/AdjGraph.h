//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_ADJGRAPH_H
#define WORKPLACE_ADJGRAPH_H

#include "init.h"
#include "Edge.h"
#include <math.h>

namespace nGraph {


    template<class EdgeType>
    class AdjGraph : public Graph<EdgeType> {
    private:
        int **matrix;
    public:

        AdjGraph(int vertexNum);

        virtual ~AdjGraph();

        Edge<EdgeType> FirstEdge(int oneVertex);

        Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge);

        void setEdge(int start, int end, EdgeType weight);

        void delEdge(int start, int end);

    };

    template<class EdgeType>
    AdjGraph<EdgeType>::AdjGraph(int vertexNum) : Graph<EdgeType>(vertexNum) {
        matrix = (int **) new int *[vertexNum];
        for (int i = 0; i < vertexNum; ++i) {
            matrix[i] = new int[vertexNum];
        }
        for (int i = 0; i < vertexNum; ++i) {
            for (int j = 0; j < vertexNum; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    template<class EdgeType>
    AdjGraph<EdgeType>::~AdjGraph() {
        {
            for (int i = 0; i < this->vertexNum; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

    template<class EdgeType>
    Edge<EdgeType> AdjGraph<EdgeType>::FirstEdge(VERTEXE oneVertex) {
        Edge<EdgeType> tmpEdge;
        tmpEdge.start = oneVertex;
        tmpEdge.end = -1;
        tmpEdge.weight = MYINFINITY;
        for (int i = 0; i < this->vertexNum; ++i) {
            if (matrix[oneVertex][i] != 0) {
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneVertex][i];
                return tmpEdge;
            }
        }
        return tmpEdge;
    }

    template<class EdgeType>
    Edge<EdgeType> AdjGraph<EdgeType>::NextEdge(Edge<EdgeType> oneEdge) {
        Edge<EdgeType> tmpEdge;
        tmpEdge.start = oneEdge.start;
        tmpEdge.end = -1;
        tmpEdge.weight = MYINFINITY;
        for (int i = (oneEdge.end + 1); i < this->vertexNum; ++i) {
            if (matrix[oneEdge.start][i] != 0) {
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneEdge.start][i];
                return tmpEdge;
            }
        }
        return tmpEdge;
    }

    template<class EdgeType>
    void AdjGraph<EdgeType>::setEdge(int start, int end, EdgeType weight) {
        if (matrix[start][end] == 0) {
            this->vertexNum++;
        }
        matrix[start][end] = weight;
    }

    template<class EdgeType>
    void AdjGraph<EdgeType>::delEdge(int start, int end) {
        if (matrix[start][end] != 0) {
            this->vertexNum--;
        }
        matrix[start][end] = 0;
    }
}
#endif //WORKPLACE_ADJGRAPH_H
