//author 软1803 徐志

#include <iostream>
#include "Graph/init.h"
#include "BinaryTree/Binary.h"
#include "SortedTest.h"
#include <time.h>
int main() {
    int arr[10] = {8, 4, 3, 2, 1, 9, 7, 5, 10, 6};
    visit(arr,10);

    cout<<"Shell sort"<<endl;
    ShellSortTest();
    cout<<"Insert sort"<<endl;
    InsertSortTest();
    cout<<"Binary insert sort"<<endl;
    BinaryInsertSortTest();
    cout<<"Bubble sort"<<endl;
    BubbleSortTest();
    cout<<"Quick sort 1"<<endl;
    QuickSortTest1();
    cout<<"Quick sort 2"<<endl;
    QuickSortTest2();
    cout<<"Select sort"<<endl;
    SelectSortTest();
    cout<<"Merge sort"<<endl;
    MergeSortTest();
    cout<<"Radix sort"<<endl;
    RadixSortTest();
}