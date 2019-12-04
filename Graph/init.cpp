//
// Created by ThinkPad on 2019/11/30.
//


#include "init.h"
#include "ListGraph.h"
#include "AdjGraph.h"

namespace nGraph{
    void ListGraphTest() {
        ListGraph<int> lg(5);
        lg.setEdge(0,1,5);
        lg.setEdge(0,2,4);
        lg.setEdge(0,3,4);
        lg.setEdge(0,4,8);
        lg.setEdge(0,5,9);
        lg.setEdge(1,0,5);
        lg.setEdge(1,2,4);
        lg.setEdge(1,3,4);
        lg.setEdge(1,4,8);
        lg.setEdge(1,5,9);
        lg.setEdge(2,1,5);
        lg.setEdge(2,0,4);
        lg.setEdge(2,3,4);
        lg.setEdge(2,4,8);
        lg.setEdge(2,5,9);
        lg.setEdge(3,1,5);
        lg.setEdge(3,2,4);
        lg.setEdge(3,0,4);
        lg.setEdge(3,4,8);
        lg.setEdge(3,5,9);
        lg.setEdge(4,1,5);
        lg.setEdge(4,2,4);
        lg.setEdge(4,3,4);
        lg.setEdge(4,0,8);
        lg.setEdge(4,5,9);

        using std::cout;
        using std::endl;

        cout<<endl;

        lg.BFS();

    }
}
