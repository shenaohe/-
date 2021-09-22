#pragma once
#include"cstddef"

class Graphic;

template <class T>
struct LinkNode
{
	T data;   //������
	LinkNode<T>* rLink, * lLink;  //��������ָ��
	LinkNode() :rLink(NULL), lLink(NULL) {}  //�޲γ�ʼ��
	LinkNode(T& x) :rLink(NULL), lLink(NULL) { data = x; }  //���γ�ʼ��
};

template <class T>
class LinkList
{
protected:
	LinkNode<T>* head ;  //ͷָ��
	LinkNode<T>* current;  //����ָ��
	LinkNode<T>* Insert(T& data);  //�������в�������,�������½����ĵ�ַ
public:
	LinkNode<T>* GetNext();  //�����һ������ַ
	LinkList();  //�޲γ�ʼ��
	LinkList(LinkList<T>& list);  //�������캯��
	~LinkList();  //��������
	void InsertData(T& data);   //������������
	void Remove(T& data);  //�Ƴ�ָ������
	void Remove(LinkNode<T>* location);  //�Ƴ�ָ��λ������
	bool GetNodepos(T& data, LinkNode<T>*& data_pos);  //��ȡdata�������еĵ�ַ
	bool IsEmpty();  //�ж������Ƿ�Ϊ��
	void MakeEmpty();  //���
	LinkList& operator=(LinkList<T>& list);  //���ظ�ֵ�����
	bool GetNext(T& data);        /* �����һ�ڵ������ */
	void ResetCurrent();           //�����α�
	friend class Graphic;         //��������ͼΪ��Ԫ����Ϊͼ��Ҫ���ñ�����Ա����
};

template <class T>
LinkList<T>::LinkList()
{
	head = new LinkNode<T>;  //��ͷ��������
	head->rLink = NULL;
	current = head;    //����ָ���ʼ��
}

template <class T>
LinkList<T>::LinkList(LinkList<T>& list)
{
	MakeEmpty();
	LinkNode<T>* cpNode, * cur1 = head, * cur2 = list.head->rLink;   //cpNode�����ݴ��½���㣬cur1��cur2�ֱ�Ϊ����λ�õı��
	while (cur2)  //��cur2ָ���Ƶ���������ʱ�˳�ѭ��
	{
		cpNode = new LinkNode<T>(cur2->data);
		cpNode->lLink = cur1;  //�½ڵ���ָ��ָ��ǰһ�����
		cpNode->rLink = cur1->rLink;    //�½ڵ���ָ��ָ��ǰһ��������ָ��
		cur1->rLink = cpNode;   //�ý����ָ��ָ���½ڵ�
		cur1 = cur1->rLink;   //cur1����ǰ����ָ���������
		cur2 = cur2->rLink;   //cur2����ǰ����ָ����һ�ڵ�
	}
	current = head;  //����ָ���ʼ��
}

template <class T>
LinkList<T>::~LinkList()
{
	MakeEmpty();  //���
	if (head)  //��head��Ϊ�գ�ɾ��ͷ���
	{
		delete head;
		head = NULL;
	}
}

template <class T>
LinkNode<T>* LinkList<T>::Insert(T& data)
{
	LinkNode<T>* newNode = new LinkNode<T>(data);  //ͷ�巨
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
	LinkNode<T>* dele, * curp = head->rLink;  //dele�����ݴ�Ҫɾ���Ľ�㣬curpΪ����ָ��
	while (curp)
	{
		if (curp->data == data)
		{
			dele = curp;
			curp = curp->lLink;
			curp->rLink = dele->rLink;
			if (dele->rLink)
				dele->rLink->lLink = curp;   //����ɾ������������ɾ��
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
	if (location)  //�ж�location��ָ�Ľ����������������Ϊ��
	{
		if (location->lLink)
		{
			LinkNode<T>* curp = location->lLink;
			curp->rLink = location->rLink;
			if (location->rLink)
				location->rLink->lLink = curp;   //����ɾ������������ժ��
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
	LinkNode<T>* cur = head->rLink;  //curΪ����ָ��
	while (cur)  //δ������ĩβ
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
	return head->rLink ? false : true;  //ͷ�����ҽ��Ϊ��������Ϊ��
}

template <class T>
void LinkList<T>::MakeEmpty()
{
	LinkNode<T>* dele = head->rLink;  //de�ݴ��ɾ�����
	while (dele)
	{
		head->rLink = dele->rLink;
		if (dele->rLink)
			dele->rLink->lLink = head;  //����ɾ�����ժ��
		delete dele;
		dele = head->rLink;
	}
	dele = NULL;
}

template <class T>
LinkList<T>& LinkList<T>::operator=(LinkList<T>& list)
{
	MakeEmpty();
	LinkNode<T>* copyNode, * cur1 = head, * cur2 = list.head->rLink;   //copyNode�����ݴ��½���㣬cur1��һ����cur2ǰһ��λ��
	while (cur2)  //��cur2ָ���Ƶ���������ʱ
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
	if (current)     //��current��Ϊ�գ�����ǰ��
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
	if (current)     //��current��Ϊ�գ�����ǰ��
	{
		current = current->rLink;
	}
	return current;      //���ص�ǰ���λ��
}

template<class T>
void LinkList<T>::ResetCurrent()
{
	current = head;   //�����α�
}

template<class T>
void LinkList<T>::InsertData(T& data)
{
	LinkNode<T>* newNode = new LinkNode<T>(data);  //ͷ�巨
	newNode->rLink = head->rLink;
	newNode->lLink = head;
	if (head->rLink)
		head->rLink->lLink = newNode;
	head->rLink = newNode;
}