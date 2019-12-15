//
// Created by ThinkPad on 2019/11/30.
//

#ifndef WORKPLACE_LISTDATA_H
#define WORKPLACE_LISTDATA_H

#include <iostream>
#include "Graph.h"
#include "Edge.h"

namespace nGraph {
    template<class WeightType>
    class ListData {         // element
    public:
        VERTEXE vertex;
        WeightType weight=MYINFINITY;
    };

    template<class Elem>
    class ListNode {     // 邻接表每一行的节点
    public:
        Elem element;
        ListNode<Elem> *next;

        ListNode(const Elem &elemval, ListNode<Elem> *nextval = NULL);

        ListNode(ListNode<Elem> *nextval = NULL);


    };

    template<class Elem>
    ListNode<Elem>::ListNode(const Elem &elemval, ListNode<Elem> *nextval) {
        element = elemval;
        next = nextval;
    }

    template<class Elem>
    ListNode<Elem>::ListNode(ListNode<Elem> *nextval) {
        next = nextval;
    }

    template<class Elem>
    class EdgeList {     // 邻接表的一行
    public:
        ListNode<Elem> *head;

        EdgeList() {
            head = new ListNode<Elem>();
        }

        void removeAll();

        ~EdgeList();
    };

    template<class Elem>
    void EdgeList<Elem>::removeAll() {
        ListNode<Elem> *cur;
        while (!head) {
            cur = head;
            head = head->next;
            delete cur;
        }
    }

    template<class Elem>
    EdgeList<Elem>::~EdgeList() {
        removeAll();
    }

    template<class WeightType>
    class ListGraph : public Graph<WeightType> {
    private:
        EdgeList<ListData<WeightType>> *graList;
    public:
        ListGraph(int verticesNum);

        ~ListGraph();

        Edge<WeightType> FirstEdge(VERTEXE oneVertex);

        Edge<WeightType> NextEdge(Edge<WeightType> oneEdge);

        void setEdge(VERTEXE start, VERTEXE end, WeightType weight);

        void delEdge(VERTEXE start, VERTEXE end);

        Edge<WeightType> getEdge(VERTEXE start, VERTEXE end) override;
    };

    template<class WeightType>
    ListGraph<WeightType>::ListGraph(int verticesNum):Graph<WeightType>(verticesNum) {
        graList = new EdgeList<ListData<WeightType>>[this->vertexNum];
        for (VERTEXE i = 0; i < this->vertexNum; i++) {
            graList[i].head->element.vertex = i;
        }
    }

    template<class WeightType>
    ListGraph<WeightType>::~ListGraph() {
        delete[] graList;
    }

    template<class WeightType>
    Edge<WeightType> ListGraph<WeightType>::FirstEdge(VERTEXE oneVertex) {
        Edge<WeightType> tmpEdge;
        tmpEdge.start = oneVertex;
        ListNode<ListData<WeightType>> *temp = graList[oneVertex].head;
        if (temp->next != NULL) {
            tmpEdge.end = temp->next->element.vertex;
            tmpEdge.weight = temp->next->element.weight;
        }
        return tmpEdge;
    }

    template<class WeightType>
    Edge<WeightType> ListGraph<WeightType>::NextEdge(Edge<WeightType> oneEdge) {
        Edge<WeightType> tmpEdge;
        tmpEdge.start = oneEdge.start;
        ListNode<ListData<WeightType>> *temp = graList[oneEdge.start].head;
        while (temp->next != NULL && temp->next->element.vertex <= oneEdge.end) {
            temp = temp->next;
        }

        if (temp->next != NULL) {
            tmpEdge.end = temp->next->element.vertex;
            tmpEdge.weight = temp->next->element.weight;
            return tmpEdge;
        }
        return tmpEdge;
    }

    template<class WeightType>
    void ListGraph<WeightType>::setEdge(VERTEXE start, VERTEXE end, WeightType weight) {
        ListNode<ListData<WeightType>> *temp = graList[start].head;
        while (temp->next != NULL && temp->next->element.vertex < end) {
            temp = temp->next;
        }
        if (temp->next == NULL) {
            temp->next = new ListNode<ListData<WeightType>>();
            temp->next->element.vertex = end;
            temp->next->element.weight = weight;
            this->edgeNum++;
            return;
        }
        if (temp->next->element.vertex == end) {
            temp->next->element.weight = weight;
            return;
        }
        if (temp->next->element.vertex > end) {
            ListNode<ListData<WeightType>> *other = temp->next;
            temp->next = new ListNode<ListData<WeightType>>();
            temp->next->element.vertex = end;
            temp->next->element.weight = weight;
            temp->next->next = other;
            this->edgeNum++;
        }
    }

    template<class WeightType>
    void ListGraph<WeightType>::delEdge(VERTEXE start, VERTEXE end) {
        ListNode<ListData<WeightType>> *temp = graList[start].head;
        while (temp->next != NULL && temp->next->element.vertex < end) {
            temp = temp->next;
        }
        if (temp->next == NULL) return;
        if (temp->next->element.vertex == end) {
            ListNode<ListData<WeightType>> *other = temp->next->next;
            delete temp->next;
            temp->next = other;
            this->edgeNum--;
        }
    }

    template<class WeightType>
    Edge<WeightType> ListGraph<WeightType>::getEdge(VERTEXE start, VERTEXE end) {
        Edge<WeightType> ret;
        ret.start = start;
        ret.end = end;
        for (Edge<WeightType> e=FirstEdge(start) ; this->IsEdge(e) ; e=NextEdge(e)) {
            if(e.end==end){
                ret.weight = e.weight;
                return ret;
            }
        }
    }
}


#endif //WORKPLACE_LISTDATA_H
