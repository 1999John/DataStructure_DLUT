#include<iostream>
using namespace std;

//节点类的定义
template <typename T>
struct ListNode
{
	T value;
	ListNode<T>* next;
	ListNode<T>* pre;
	ListNode(T value, ListNode<T>* next = NULL, ListNode<T>* pre = NULL) : value(value), next(next), pre(pre){}
};

//双向循环链表类的定义
template <typename T>
struct DList
{
	ListNode<T>* head;
	ListNode<T>* tail;
	DList() : head(NULL), tail(NULL){}

	//访问节点中的数据域
	void visit(ListNode<T>* current){
		cout << current->value << endl;
	}
	//显示双向链表
	void showList()
	{
		ListNode<T>* current = head;
		if (!current)
			return;
		do
		{
			visit(current);
			current = current->next;
		} while (current && current != head);
	}
};
//int main(void)
//{
//	DList<int> list;
//	//list.showList();
//	return 0;
//}