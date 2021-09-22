#pragma once
#include"cstddef"

class Graphic;

template <class T>
struct LinkNode
{
	T data;   //数据域
	LinkNode<T>* rLink, * lLink;  //左右连接指针
	LinkNode() :rLink(NULL), lLink(NULL) {}  //无参初始化
	LinkNode(T& x) :rLink(NULL), lLink(NULL) { data = x; }  //带参初始化
};

template <class T>
class LinkList
{
protected:
	LinkNode<T>* head ;  //头指针
	LinkNode<T>* current;  //遍历指针
	LinkNode<T>* Insert(T& data);  //向链表中插入数据,并返回新建结点的地址
public:
	LinkNode<T>* GetNext();  //获得下一个结点地址
	LinkList();  //无参初始化
	LinkList(LinkList<T>& list);  //拷贝构造函数
	~LinkList();  //析构函数
	void InsertData(T& data);   //单纯插入数据
	void Remove(T& data);  //移除指定数据
	void Remove(LinkNode<T>* location);  //移除指定位置数据
	bool GetNodepos(T& data, LinkNode<T>*& data_pos);  //获取data在链表中的地址
	bool IsEmpty();  //判断链表是否为空
	void MakeEmpty();  //清空
	LinkList& operator=(LinkList<T>& list);  //重载赋值运算符
	bool GetNext(T& data);        /* 获得下一节点的数据 */
	void ResetCurrent();           //重置游标
	friend class Graphic;         //声明无向图为友元，因为图内要调用保护成员函数
};

template <class T>
LinkList<T>::LinkList()
{
	head = new LinkNode<T>;  //带头结点的链表
	head->rLink = NULL;
	current = head;    //遍历指针初始化
}

template <class T>
LinkList<T>::LinkList(LinkList<T>& list)
{
	MakeEmpty();
	LinkNode<T>* cpNode, * cur1 = head, * cur2 = list.head->rLink;   //cpNode用于暂存新建结点，cur1与cur2分别为链表位置的标记
	while (cur2)  //当cur2指向复制的链表的最后时退出循环
	{
		cpNode = new LinkNode<T>(cur2->data);
		cpNode->lLink = cur1;  //新节点左指针指向前一个结点
		cpNode->rLink = cur1->rLink;    //新节点右指针指向前一个结点的右指针
		cur1->rLink = cpNode;   //该结点右指针指向新节点
		cur1 = cur1->rLink;   //cur1向右前进，指向链表最后
		cur2 = cur2->rLink;   //cur2向右前进，指向下一节点
	}
	current = head;  //遍历指针初始化
}

template <class T>
LinkList<T>::~LinkList()
{
	MakeEmpty();  //清空
	if (head)  //若head不为空，删除头结点
	{
		delete head;
		head = NULL;
	}
}

template <class T>
LinkNode<T>* LinkList<T>::Insert(T& data)
{
	LinkNode<T>* newNode = new LinkNode<T>(data);  //头插法
	newNode->rLink = head->rLink;
	newNode->lLink = head;
	if (head->rLink)
		head->rLink->lLink = newNode;
	head->rLink = newNode;
	return newNode;
}

template <class T>
void LinkList<T>::Remove(T& data)
{
	LinkNode<T>* dele, * curp = head->rLink;  //dele用于暂存要删除的结点，curp为遍历指针
	while (curp)
	{
		if (curp->data == data)
		{
			dele = curp;
			curp = curp->lLink;
			curp->rLink = dele->rLink;
			if (dele->rLink)
				dele->rLink->lLink = curp;   //将待删除结点从链表中删除
			if (dele)
			{
				delete dele;
				dele = NULL;
			}
			return;
		}
		curp = curp->rLink;
	}
}

template <class T>
void LinkList<T>::Remove(LinkNode<T>* location)
{
	if (location)  //判断location所指的结点在链表中且链表不为空
	{
		if (location->lLink)
		{
			LinkNode<T>* curp = location->lLink;
			curp->rLink = location->rLink;
			if (location->rLink)
				location->rLink->lLink = curp;   //将待删除结点从链表中摘除
			if (location)
			{
				delete location;
				location = NULL;
			}
		}
	}
}

template<class T>
bool LinkList<T>::GetNodepos(T& data, LinkNode<T>*& data_pos)
{
	LinkNode<T>* cur = head->rLink;  //cur为遍历指针
	while (cur)  //未到链表末尾
	{
		if (cur->data == data) 
		{
			data_pos = cur;
			return true;
		}
		cur = cur->rLink;
	}
	return false; 
}

template <class T>
bool LinkList<T>::IsEmpty()
{
	return head->rLink ? false : true;  //头结点的右结点为空则链表为空
}

template <class T>
void LinkList<T>::MakeEmpty()
{
	LinkNode<T>* dele = head->rLink;  //de暂存待删除结点
	while (dele)
	{
		head->rLink = dele->rLink;
		if (dele->rLink)
			dele->rLink->lLink = head;  //将待删除结点摘除
		delete dele;
		dele = head->rLink;
	}
	dele = NULL;
}

template <class T>
LinkList<T>& LinkList<T>::operator=(LinkList<T>& list)
{
	MakeEmpty();
	LinkNode<T>* copyNode, * cur1 = head, * cur2 = list.head->rLink;   //copyNode用于暂存新建结点，cur1后一个，cur2前一个位置
	while (cur2)  //当cur2指向复制的链表的最后时
	{
		copyNode = new LinkNode<T>(cur2->data);
		copyNode->lLink = cur1;  
		copyNode->rLink = cur1->rLink;   
		cur1->rLink = copyNode;  
		cur1 = cur1->rLink;   
		cur2 = cur2->rLink;   
	}
	return *this;
}

template<class T>
bool LinkList<T>::GetNext(T& data)    
{
	if (current)     //当current不为空，继续前进
	{
		current = current->rLink;
		if (current)  
		{
			data = current->data;
			return true;
		}
		else
			return false;
	}
	else
		return false;

}

template<class T>
LinkNode<T>* LinkList<T>::GetNext()    
{
	if (current)     //当current不为空，继续前进
	{
		current = current->rLink;
	}
	return current;      //返回当前结点位置
}

template<class T>
void LinkList<T>::ResetCurrent()
{
	current = head;   //重置游标
}

template<class T>
void LinkList<T>::InsertData(T& data)
{
	LinkNode<T>* newNode = new LinkNode<T>(data);  //头插法
	newNode->rLink = head->rLink;
	newNode->lLink = head;
	if (head->rLink)
		head->rLink->lLink = newNode;
	head->rLink = newNode;
}