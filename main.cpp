#include "binarytree.h"
#include "Dlist.h"
#include "singleList.h"
#include "CircleList.h"
#include <stdlib.h>
#include <cstring>
#include "CircleQueue.h"
#include "CircleDoubleList.h"
#include "ACircleQueue.h"

using namespace std;

int Tran(int value, int base) {
    if (value / base == 0) {
        return value % base;
    }
    return Tran(value / base, base) * 10 + value % base;
}
char getInteracte(char s) {
    switch (s) {
        case ']':
            return '[';
        case ')':
            return '(';
        case '}':
            return '{';
        default:
            throw "error";
    }
}
bool isMatched(const char* str) {
    int len = strlen(str);
    stack<char> stack;
    bool noMatched = false;
    for (int i = 0; i < len; ++i) {
        if(str[i]=='('||str[i]=='['||str[i]=='{'){
            stack.push(str[i]);
        }if(str[i]==')'||str[i]==']'||str[i]=='}') {
            if(stack.empty()) {
                noMatched = true;
                break;
            } else{
                char top = stack.top();
                stack.pop();
                if(top!=getInteracte(str[i])) {
                    noMatched = true;
                    break;
                }
            }
        }
    }
    if(!stack.empty()) noMatched = true;
    return !noMatched;
}

void userInput() {
    queue<int> Queue[10];

    while(true) {
        int input = 0;
        cin>>input;

        if(input<0||input>9) { break;}

        switch(input) {
            case 0:Queue[0].push(input);
                break;
            case 1:Queue[1].push(input);
                break;
            case 2:Queue[2].push(input);
                break;
            case 3:Queue[3].push(input);
                break;
            case 4:Queue[4].push(input);
                break;
            case 5:Queue[5].push(input);
                break;
            case 6:Queue[6].push(input);
                break;
            case 7:Queue[7].push(input);
                break;
            case 8:Queue[8].push(input);
                break;
            case 9:Queue[9].push(input);
                break;
        }
    }
    queue<int> ret;
    for (int i = 0; i < 10; ++i) {
        for (;!Queue[i].empty(); ret.push(Queue[i].front()),cout<<Queue[i].front()<<endl,Queue[i].pop());
    }
}
int main() {
//    BinaryTree<int> tree;
//    string filepath = "E:\\C++project\\workplace\\test.txt"; //将测试文件放到D盘根目录下
//    vector<int> data = loaddata(filepath); //加载测试文件中的数据加载到data中
//    int index = 0; //设置开始的下标
//    tree.root = tree.buildTree(data, index); //根据data数据建立一棵二叉树
//    tree.inorder(tree.root);
//    cout<<endl;
//    tree.preorder(tree.root);
//    cout<<endl;
//    tree.postorder(tree.root);
//    //system("pause");
//    cout<<endl;
//    DList<int> list;
//    //list.showList();
//    return 0;

//    singleList sl;
//    sl.createList();
//    sl.display();
//    sl.invert();
//    cout<<endl;
//    cout<<sl.getMax();
//    cout<<'\n'<<sl.getcurlen()<<endl;
//    cout<<"\n"<<sl.getaverage()<<endl;

//    CircleList cl;
//    while (true) {
//        int i = 0;
//        cin >> i;
//        if (i <= 0) {
//            break;
//        } else {
//            cl.createList(i);
//        }
//    }
//    cl.display();
//    cout << endl;
//    cl.Delete(3);
//    cout << endl;
//    cl.display();

//    cout << isMatched("[")<<endl;
//    cout<<isMatched("[A+B]")<<endl;
//    cout<<isMatched("[A+B+{c+d+()}]")<<endl;
//    userInput();

//    CircleQueue<int> cq(5);
//    if(cq.empty()) {
//        cout<<"empty queue"<<endl;
//    }
//    cq.push(1);
//    cq.push(2);
//    if(cq.empty()) {
//        cout<<"empty queue"<<endl;
//    }
//    cq.push(3);
//    cq.push(4);
//    cq.push(5);
//    if(cq.empty()) {
//        cout<<"empty queue"<<endl;
//    }
//    cq.push(6);
//    cout<<"length "<<cq.length()<<endl;
//    cout<<cq.Front()<<endl;
//    cq.pop();
//    cout<<cq.Front()<<endl;
//    cq.pop();
//    cq.pop();
//    cout<<cq.Front()<<endl;
//    cout<<cq.Front()<<endl;
//    cq.pop();
//    cout<<cq.Front()<<endl;
//    cq.pop();
//    try {
//        cout<<cq.Front()<<endl;
//        cq.pop();
//    }catch (const char* e) {
//        cout<<e<<endl;
//    }
//    if(cq.empty()) {
//        cout<<"empty queue"<<endl;
//    }


//    CircleDoubleList<int> cdl;
//    cdl.insert(0);
//    cdl.insert(1);
//    cdl.insert(2);
//    cdl.insert(3);
//    cdl.display();
//    cdl.Delete(0);
//    cout<<endl;
//    cdl.display();
//    cdl.Delete(1);
//    cdl.Delete(2);
//    cdl.Delete(3);
//    cout<<endl;
//    cdl.display();
//    cdl.Delete(4);
//    cout<<endl;
//    cdl.display();

    ACircleQueue<int> acq(5);
    if(acq.empty()){
        cout<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"full queue"<<endl;
    }
    acq.push(0);
    cout<<"0\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"0\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"0\t"<<"full queue"<<endl;
    }

    acq.push(1);
    cout<<"1\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"1\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"1\t"<<"full queue"<<endl;
    }

    acq.push(2);
    cout<<"2\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"2\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"2\t"<<"full queue"<<endl;
    }

    acq.push(3);
    cout<<"3\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"3\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"3\t"<<"full queue"<<endl;
    }

    acq.push(4);
    cout<<"4\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"4\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"4\t"<<"full queue"<<endl;
    }

    acq.push(5);
    cout<<"5\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"5\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"5\t"<<"full queue"<<endl;
    }

    acq.push(6);
    cout<<"6\t"<<acq.len()<<endl;
    if(acq.empty()){
        cout<<"6\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"6\t"<<"full queue"<<endl;
    }

    cout<<"\n\n\n"<<endl;
    cout<<"current front:\t"<<acq.Front()<<endl;
    acq.pop();
    if(acq.empty()){
        cout<<"0\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"0\t"<<"full queue"<<endl;
    }
    cout<<"current front:\t"<<acq.Front()<<endl;
    acq.pop();
    cout<<"current front:\t"<<acq.Front()<<endl;
    acq.pop();
    cout<<"current front:\t"<<acq.Front()<<endl;
    acq.pop();
    cout<<"current front:\t"<<acq.Front()<<endl;
    acq.pop();
    try {
        cout<<"current front:\t"<<acq.Front()<<endl;
        acq.pop();
    }catch (const char* e) {
        cout<<e<<endl;
    }

    if(acq.empty()){
        cout<<"0\t"<<"empty queue"<<endl;
    }
    if(acq.full()) {
        cout<<"0\t"<<"full queue"<<endl;
    }
}