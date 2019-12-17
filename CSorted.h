//
// Created by ThinkPad on 2019/12/10.
//

#ifndef WORKPLACE_CSORTED_H
#define WORKPLACE_CSORTED_H


template<class T>
bool lt(T a, T b) {
    return a < b;
}

template<class T>
bool gt(T a, T b) {
    return a > b;
}

template<class T>
void swap(T *a, T *b) {
    T tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
    return;
}

template <class T>
void initArr(T Arr[],int n){
    for (int i = 0; i < n; ++i) {
        Arr[i] = 0;
    }
}

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
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (cmp(Arr[j], Arr[j + 1])) {
                swap(&Arr[j], &Arr[j + 1]);
            }
        }
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
    while (low <= high) {
        while (low < high && !cmp(pivot, Arr[high]))
            high--;
        if (low >= high) break;         //当low和high相遇时退出
        Arr[low] = Arr[high];
        low++;
        while (low < high && cmp(pivot, Arr[low]))
            low++;
        if (low >= high) break;         // 当low和high相遇时退出
        Arr[high] = Arr[low];
        --high;
    }
    Arr[low] = pivot;
    return low;
}

template<class T>
void QuickSort1(T Arr[], int low, int high, bool (*cmp)(T, T)) {
    int piovt;
    if (low < high) {
        piovt = Partition1(Arr, low, high, cmp);
        QuickSort1(Arr, low, piovt, cmp);
        QuickSort1(Arr, piovt + 1, high, cmp);
    }
}

template <class T>
void QuickSort2(T Arr[], int left, int right, bool (*cmp)(T, T)) {
    if(right<=left){     //子序列只有0个或一个记录
        return;
    }
    int pivot =left;
    pivot = Partition2(Arr,left,right,cmp);
    QuickSort2(Arr,left,pivot,cmp);
    QuickSort2(Arr,pivot+1,right,cmp);
}

template <class T>
void SelectSort(T Arr[],int length,bool (*cmp)(T,T)) {
    for (int i = 0; i < length-1; ++i) {
        int anchor = i;
        for (int j = i+1; j < length; ++j) {
            if(cmp(Arr[anchor], Arr[j])) anchor=j;
        }
        if(anchor != i) swap(&Arr[anchor], &Arr[i]);
    }
}

template <class T>
void MergeSort(T Arr[],T sideArr[],int left,int right,bool (*cmp)(T,T)) {
    if(right-left>2){
        int mid = (right+left)/2;
        int leftlength = mid-left;
        int rightlength = right-mid;
        T leftArr[leftlength];
        T rightArr[rightlength];
        initArr(leftArr,leftlength);
        initArr(rightArr,rightlength);
        MergeSort(Arr,leftArr,left,mid,cmp);
        MergeSort(Arr,rightArr,mid,right,cmp);

        int m = 0,i=0,j=0;
        while(i<leftlength&&j<rightlength){
            sideArr[m++] = cmp(leftArr[i],rightArr[j])?rightArr[j++]:leftArr[i++];
        }
        while(i<leftlength){
            sideArr[m++] = leftArr[i++];
        }
        while(j<rightlength){
            sideArr[m++] = rightArr[j++];
        }
    } else if (right-left==2){
        if(!cmp(Arr[--right],Arr[left]))        //right>left
        {
            sideArr[0] = Arr[right];
            sideArr[1] = Arr[left];
            return;
        }else{
            sideArr[0] = Arr[left];
            sideArr[1] = Arr[right];
        }

    }else{
        sideArr[0] = Arr[left];
        return;
    }
}
#endif //WORKPLACE_CSORTED_H
