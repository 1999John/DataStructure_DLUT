//
// Created by ThinkPad on 2019/12/10.
//

#ifndef WORKPLACE_SORTEDTEST_H
#define WORKPLACE_SORTEDTEST_H

#include <iostream>
#include "CSorted.h"

using std::cout;
using std::endl;

template<class T>
void visit(T *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void ShellSortTest() {
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    ShellSort(arr, 10, lt);
    visit(arr,10);
}

void InsertSortTest() {
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    InsertSort(arr, 10, lt);
    visit(arr,10);
}

void BinaryInsertSortTest(){
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    BinaryInsertSort(arr,10,lt);
    visit(arr,10);
}

void BubbleSortTest(){
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    BubbleSort(arr,10,lt);
    visit(arr,10);
}

void QuickSortTest1(){
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    QuickSort1(arr,0,10,lt);
    visit(arr,10);
}

void QuickSortTest2(){
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    QuickSort2(arr,0,10,lt);
    visit(arr,10);
}

void SelectSortTest() {
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    SelectSort(arr,10,lt);
    visit(arr,10);
}

void MergeSortTest() {
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    int ans[10];
    initArr(ans,10);
    MergeSort(arr,ans,0,10,lt);
    visit(ans,10);
}


#endif //WORKPLACE_SORTEDTEST_H
