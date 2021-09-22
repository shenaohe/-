#pragma once
#include<limits>
#include<iostream>
using namespace std;
const float maxV = FLT_MAX;
struct MSTEdgeNode
{
	int tail, head;//������λ�ü����ϵ�Ȩֵ
	int key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	bool operator <= (MSTEdgeNode& R) { return key <= R.key; }
	bool operator > (MSTEdgeNode& R) { return key > R.key; }
};
class MinSpantree
{
public:
	MSTEdgeNode* edgevalue;//�ñ�ֵ�����ʾ��
	int maxSize, n;//��������Ԫ�ظ����͵�ǰ����
	MinSpantree(int sz =100001 - 1) :maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[sz];
	}
	int Insert(MSTEdgeNode& item);
	bool IsEmpty() { return n == 0; }   //�ж��Ƿ�Ϊ��
	bool IsFull() { return n == maxSize; }  //�ж��Ƿ�����
	bool getTree(MSTEdgeNode* tree);   //��������Ԫ������
};
