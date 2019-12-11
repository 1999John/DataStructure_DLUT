//
// Created by ThinkPad on 2019/12/5.
//

#ifndef WORKPLACE_UFSETS_H
#define WORKPLACE_UFSETS_H


#include "init.h"

namespace nGraph {
    class UFSets {
    private:
        int n;      //等价类中元素个数
        VERTEXE *root;      //root[i]表示元素i所在的等价类的代表元素编号
        VERTEXE *next;      //next[i]表示在等价类中，i的后面的元素编号
        int *length;        //length[i]表示i所代表的的等价类的元素个数
    public:
        UFSets(int size)  {
            n = size;
            root = new VERTEXE[n];
            next = new VERTEXE[n];
            length = new int[n];
            for (VERTEXE i = 0; i < n; ++i) {
                root[i] = i;
                next[i] = i;
                length[i] = 1;
            }
        }

        int Find(VERTEXE v);

        void Union(VERTEXE v, VERTEXE u);
    };

    int UFSets::Find(VERTEXE v) {
        return root[v];
    }

    void UFSets::Union(VERTEXE v, VERTEXE u) {
        if (root[v] == root[u])
            return;
        else if (length[root[v]] < length[root[u]]) {
            VERTEXE rt = root[v];
            length[root[u]]+=length[rt];

            root[rt] = root[u];
            for(VERTEXE j = next[rt];j!=rt;j = next[j]){
                root[j] = root[u];
            }
            VERTEXE tmp = next[rt];
            next[rt] = next[u];
            next[u] = tmp;
        }
        else{
            VERTEXE rt = root[u];
            length[root[v]]+=length[rt];

            root[rt] = root[v];
            for(VERTEXE j = next[rt];j!=rt;j = next[j]){
                root[j] = root[v];
            }
            VERTEXE tmp = next[rt];
            next[rt] = next[v];
            next[v] = tmp;
        }

    }

}

#endif //WORKPLACE_UFSETS_H
