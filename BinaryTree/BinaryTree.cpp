//
// Created by ThinkPad on 2019/11/15.
//
#include "SearchTree.h"
namespace BinaryTree{

    void SearchTreeTest(){
        SearchTree<int> st(10);
        st.insert(8);
        st.insert(11);
        st.insert(7);
        st.insert(9);
//        st.insert(7);
//        st.insert(9);
//        st.insert(12);
//        st.insert(1);
//        st.insert(13);
//        st.insert(11);
        int leaf = 0;
        int oneChild = 0;
        int twoChild = 0;
        st.noChild(st.getRoot(),&leaf);
        st.oneChild(st.getRoot(),&oneChild);
        st.twoChild(st.getRoot(),&twoChild);

        std::cout<<"leaf\t"<<leaf<<"\toneChild\t"<<oneChild<<"\ttwoChild\t"<<twoChild<<std::endl;

        int height = 0;

        st.getHeight(st.getRoot(),&height);
        std::cout<<"height\t"<<height<<std::endl;

        int width = 0;
        st.getWidth(st.getRoot(),&width);
        std::cout<<"width\t"<<width<<std::endl;

        int maxValue = 0;
        st.getMax(st.getRoot(),&maxValue);
        std::cout<<"max value\t"<<maxValue<<std::endl;

//        st.exchange(st.getRoot());
        st.inOrder(st.getRoot());

       // st.deleteCurrentLeaf(st.getRoot(),NULL);

        if(st.isCompleteBinaryTree()) {
            std::cout<<"complete binary tree!"<<std::endl;
        }
    }
}
