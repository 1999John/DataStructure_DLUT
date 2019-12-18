//
// Created by ThinkPad on 2019/12/10.
//

#ifndef WORKPLACE_CSORTED_H
#define WORKPLACE_CSORTED_H

#include <queue>
#include <cmath>

template<class T>
bool lt(T a, T b) {             //降序排列
    return a < b;
}

template<class T>
bool gt(T a, T b) {             //升序排列
    return a > b;
}

template<class T>
void swap(T *a, T *b) {
    T tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
    return;
}

template<class T>
void initArr(T Arr[], int n) {
    for (int i = 0; i < n; ++i) {
        Arr[i] = 0;
    }
}

//希尔排序
template<class T>
void ShellSort(T Arr[], int len, bool (*cmp)(T, T)) {
    int gap = len / 2;

    while (gap >= 1) {
        for (int k = 0; k < gap; ++k) {
            for (int i = k + gap; i < len; i += gap) {
                T temp = Arr[i];
                int j = 0;
                for (j = i - gap; j >= k && cmp(Arr[j], temp); Arr[j + gap] = Arr[j], j -= gap);
                Arr[j + gap] = temp;
            }
        }
        gap /= 2;
    }
}

//直接插入
template<class T>
void InsertSort(T Arr[], int len, bool (*cmp)(T, T)) {
    for (int i = 1; i < len; ++i) {
        if (!cmp(Arr[i], Arr[i - 1])) {
            int j = i - 1;
            T tmp = Arr[i];
            for (; j >= 0 && !cmp(tmp, Arr[j]); Arr[j + 1] = Arr[j], --j);
            Arr[j + 1] = tmp;
        }

    }
}


//二分插入
template<class T>
void BinaryInsertSort(T Arr[], int len, bool (*cmp)(T, T)) {
    for (int i = 1; i < len; ++i) {
        T tmp = Arr[i];
        int low = 0, high = i - 1;
        for (int mid = (low + high) / 2; low <= high; mid = (low + high) / 2) {
            if (cmp(Arr[mid], tmp)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        int j = i - 1;
        for (; j >= high + 1; --j) {
            Arr[j + 1] = Arr[j];
        }
        Arr[j + 1] = tmp;
    }

}

template<class T>
void BubbleSort(T Arr[], int len, bool (*cmp)(T, T)) {
    int flag = true;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (cmp(Arr[j], Arr[j + 1])) {
                swap(&Arr[j], &Arr[j + 1]);
                flag = false;
            }
        }
        if (flag) {           //已经稳定就可以跳转
            return;
        }
        flag = true;
    }
}

template<class T>
int Partition1(T Arr[], int first, int last, bool (*cmp)(T, T)) {     //划分方法一是选定第一个为轴
    int low = first + 1, high = last - 1;
    T pivot = Arr[first];
    while (low <= high) {
        while (low <= high && cmp(pivot, Arr[low]))
            low++;
        while (low <= high && !cmp(pivot, Arr[high]))
            high--;
        if (low < high) swap(&Arr[low], &Arr[high]);
    }
    swap(&Arr[first], &Arr[high]);
    return high;
}

template<class T>
int Partition2(T Arr[], int first, int last, bool (*cmp)(T, T)) {
    int low = first, high = last - 1;
    T pivot = Arr[low];
    while (low < high) {
        while (low < high && !cmp(pivot, Arr[high]))
            high--;
        Arr[low] = Arr[high];
        while (low < high && cmp(pivot, Arr[low]))
            low++;
        Arr[high] = Arr[low];
    }
    Arr[low] = pivot;
    return low;
}

// 基于第一种分割策略的快速排序
template<class T>
void QuickSort1(T Arr[], int low, int high, bool (*cmp)(T, T)) {
    int piovt;
    if (low < high) {
        piovt = Partition1(Arr, low, high, cmp);
        QuickSort1(Arr, low, piovt, cmp);
        QuickSort1(Arr, piovt + 1, high, cmp);
    }
}


//基于第二种分割策略的快速排序
template<class T>
void QuickSort2(T Arr[], int left, int right, bool (*cmp)(T, T)) {
    if (right <= left) {     //子序列只有0个或一个记录
        return;
    }
    int pivot = left;
    pivot = Partition2(Arr, left, right, cmp);
    QuickSort2(Arr, left, pivot, cmp);
    QuickSort2(Arr, pivot + 1, right, cmp);
}


//选择排序
template<class T>
void SelectSort(T Arr[], int length, bool (*cmp)(T, T)) {
    for (int i = 0; i < length - 1; ++i) {
        int anchor = i;
        for (int j = i + 1; j < length; ++j) {
            if (cmp(Arr[anchor], Arr[j])) anchor = j;
        }
        if (anchor != i) swap(&Arr[anchor], &Arr[i]);
    }
}


//合并排序
template<class T>
void Merge(T arr[], T arr1[], T arr2[], int length1, int length2, bool (*cmp)(T, T)) {
    int m = 0, i = 0, j = 0;
    while (i < length1 && j < length2) {
        arr[m++] = cmp(arr1[i], arr2[j]) ? arr2[j++] : arr1[i++];
    }
    while (i < length1) {
        arr[m++] = arr1[i++];
    }
    while (j < length2) {
        arr[m++] = arr2[j++];
    }
}

//合并排序
template<class T>
void MergeSort(T Arr[], T sideArr[], int left, int right, bool (*cmp)(T, T)) {
    if (right - left > 2) {
        int mid = (right + left) / 2;
        int leftlength = mid - left;
        int rightlength = right - mid;
        T leftArr[leftlength];
        T rightArr[rightlength];
        initArr(leftArr, leftlength);
        initArr(rightArr, rightlength);
        MergeSort(Arr, leftArr, left, mid, cmp);
        MergeSort(Arr, rightArr, mid, right, cmp);
        Merge(sideArr, leftArr, rightArr, leftlength, rightlength, cmp);

    } else if (right - left == 2) {
        if (!cmp(Arr[--right], Arr[left]))        //right>left
        {
            sideArr[0] = Arr[right];
            sideArr[1] = Arr[left];
            return;
        } else {
            sideArr[0] = Arr[left];
            sideArr[1] = Arr[right];
            return;
        }
    } else {
        sideArr[0] = Arr[left];
        return;
    }
}


//基数排序部分
template<class T>
int maxd(T Arr[], int n) {            //求最大的位数
    int d = 1;
    int p = 1;
    int pre = 0;
    for (int i = 0; i < n; ++i) {
        while (Arr[i] > p) {
            p *= 10;
            pre++;
        }
        if (pre > d) {
            d = pre;
        }
        pre = 0;
    }
    return d;
}


template<class T>
void mergeArrAndQueue(T Arr[], std::queue<T> QList[], int length) {
    int m = 0;
    for (int i = 0; i < length; ++i) {
        while (!QList[i].empty()) {
            Arr[m++] = QList[i].front();
            QList[i].pop();
        }
    }
}

template<class T>
void RadixSort(T Arr[], int length) {
    using std::queue;
    queue<int> Qlist[10];
    int d = maxd(Arr, length);
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < length; ++j) {
            Qlist[(Arr[j] / int(pow(10, i + 1))) % 10].push(Arr[j]);
        }
        mergeArrAndQueue(Arr, Qlist, length);
    }
}

#endif //WORKPLACE_CSORTED_H
