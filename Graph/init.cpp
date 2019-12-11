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

    void AdjGraphTest(){
        AdjGraph<int> ag(5);

        ag.setEdge(0,1,2);
        ag.setEdge(0,2,3);
        ag.setEdge(0,3,5);
        ag.setEdge(0,4,7);
        ag.setEdge(1,0,2);
        ag.setEdge(1,2,2);
        ag.setEdge(1,3,3);
        ag.setEdge(1,4,4);
        ag.setEdge(2,1,2);
        ag.setEdge(2,0,3);
        ag.setEdge(2,3,3);
        ag.setEdge(2,4,2);
        ag.setEdge(3,1,3);
        ag.setEdge(3,2,3);
        ag.setEdge(3,0,5);
        ag.setEdge(3,4,4);
        ag.setEdge(4,1,4);
        ag.setEdge(4,2,2);
        ag.setEdge(4,3,4);
        ag.setEdge(4,0,7);


        int D[5]={0,0,0,0,0};
        int Path[5] = {0};



        Edge<int> *e=ag.Kruskal();

        int i;
        std::cin>>i;
    }

    void DijkstraTest(){
        using std::cout;
        using std::endl;

        AdjGraph<int> ag(5);

        ag.setEdge(0,1,2);
        ag.setEdge(0,2,3);
        ag.setEdge(0,3,5);
        ag.setEdge(0,4,7);
        ag.setEdge(1,0,2);
        ag.setEdge(1,2,2);
        ag.setEdge(1,3,3);
        ag.setEdge(1,4,4);
        ag.setEdge(2,1,2);
        ag.setEdge(2,0,3);
        ag.setEdge(2,3,3);
        ag.setEdge(2,4,2);
        ag.setEdge(3,1,3);
        ag.setEdge(3,2,3);
        ag.setEdge(3,0,5);
        ag.setEdge(3,4,4);
        ag.setEdge(4,1,4);
        ag.setEdge(4,2,2);
        ag.setEdge(4,3,4);
        ag.setEdge(4,0,7);


        int D[5]={0,0,0,0,0};
        int Path[5] = {0};

        for (int i = 0; i < 5; ++i) {
            cout<<D[i]<<" ";
        }
        cout<<endl;
        for (int i = 0; i < 5; ++i) {
            cout<<Path[i]<<" ";
        }
        cout<<endl;
    }

    void FloydTest(){
        AdjGraph<int> ag(3);

        ag.setEdge(0,1,10);
        ag.setEdge(0,2,5);
        ag.setEdge(1,0,9);
        ag.setEdge(1,2,6);
        ag.setEdge(2,0,2);
        ag.setEdge(2,1,13);

        int **Adj;
        int **Path;
        Adj = new int*[ag.VertexNum()];
        Path = new int*[ag.VertexNum()];
        for (int i = 0; i < ag.VertexNum(); ++i) {
            Adj[i] = new int[ag.VertexNum()];
            Path[i] = new int[ag.VertexNum()];
        }


        ag.Floyd(Adj,Path);

        for (int j = 0; j < ag.VertexNum(); ++j) {
            for (int i = 0; i < ag.VertexNum(); ++i) {
                std::cout<<Adj[j][i]<<" ";
            }
            std::cout<<std::endl;
        }

        std::cout<<std::endl;

        for (int j = 0; j < ag.VertexNum(); ++j) {
            for (int i = 0; i < ag.VertexNum(); ++i) {
                std::cout<<Path[j][i]<<" ";
            }
            std::cout<<std::endl;
        }
    }
}
