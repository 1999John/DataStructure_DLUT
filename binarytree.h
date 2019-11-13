#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<fstream>
#include<vector>
#include<cstdlib>

using namespace std;

template<typename T>
struct TreeNode {
    T value;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(T value, TreeNode<T> *leftChild = NULL, TreeNode<T> *rightChild = NULL) : value(value),
                                                                                       leftChild(leftChild),
                                                                                       rightChild(rightChild) {}
};

template<typename T>
struct BinaryTree {
    TreeNode<T> *root;

    BinaryTree() : root(NULL) {}
    /*
    先序建立一棵二叉树
        1
       / \
      2   3
     /   /
    4   5
    如果建立上述一个二叉树，则输入顺序为：1，2，4，0，0，0，3，5，0，0，0
    即：
            1
          /   \
         2     3
        / \   / \
       4   0 5   0
      / \   / \
     0   0 0   0
    */
    //手动建立一棵二叉树
    TreeNode<T> *buildTree() {
        T value;
        cin >> value;
        if (!value)
            return NULL;
        else {
            TreeNode<T> *newnode = new TreeNode<T>(value);
            newnode->leftChild = buildTree();
            newnode->rightChild = buildTree();
            return newnode;
        }
    }

    //从数组数据中建立一棵二叉树
    TreeNode<T> *buildTree(vector<T> data, int &index) {
        if (!data[index])
            return NULL;
        else {
            TreeNode<T> *newnode = new TreeNode<T>(data[index]);
            newnode->leftChild = buildTree(data, ++index);
            newnode->rightChild = buildTree(data, ++index);
            return newnode;
        }
    }

    //访问二叉树节点的数据
    void visit(TreeNode<T> *node) {
        cout << node->value << endl;
    }

    //递归遍历先序遍历二叉树
    void preorder(TreeNode<T> *node) {
        if (node) {
            visit(node);
            preorder(node->leftChild);
            preorder(node->rightChild);
        }
    }

    //递归中序遍历二叉树
    void inorder(TreeNode<T> *node) {
        if (node) {
            inorder(node->leftChild);
            visit(node);
            inorder(node->rightChild);
        }
    }

    //递归后序遍历二叉树
    void postorder(TreeNode<T> *node) {
        if (node) {
            postorder(node->leftChild);
            postorder(node->rightChild);
            visit(node);
        }
    }
};

//从文件中加载数据
vector<int> loaddata(string filepath) {
    vector<int> result;
    ifstream ifs(filepath.c_str(), ios::in);
    int temp = 0;
    while (ifs >> temp)
        result.push_back(temp);
    ifs.close();
    return result;
}

//int main() {
//    BinaryTree<int> tree;
//    string filepath = "test.txt"; //将测试文件放到D盘根目录下
//    vector<int> data = loaddata(filepath); //加载测试文件中的数据加载到data中
//    int index = 0; //设置开始的下标
//    tree.root = tree.buildTree(data, index); //根据data数据建立一棵二叉树
//    tree.inorder(tree.root);
//    //tree.preorder(tree.root);
//    //tree.postorder(tree.root);
//    //system("pause");
//    return 0;
//}
