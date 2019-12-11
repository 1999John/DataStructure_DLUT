//
// Created by ThinkPad on 2019/11/23.
//

#ifndef WORKPLACE_INIT_H
#define WORKPLACE_INIT_H


namespace nGraph{

    static int MYINFINITY = 1000;

    typedef int VERTEXE;

    template <class WeightType>
    class Edge;

    template <class WeightType>
    class AdjGraph;

    template <class WeightType>
    class Graph;

    template <class WeightType>
    class ListGraph;

    class UFSets;

    void ListGraphTest();

    void AdjGraphTest();

    void FloydTest();

    void DijkstraTest();
}


#endif //WORKPLACE_INIT_H
