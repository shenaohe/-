#pragma once
#include<limits>
#include<iostream>
using namespace std;
const float maxV = FLT_MAX;
struct MSTEdgeNode
{
	int tail, head;//两顶点位置及边上的权值
	int key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	bool operator <= (MSTEdgeNode& R) { return key <= R.key; }
	bool operator > (MSTEdgeNode& R) { return key > R.key; }
};
class MinSpantree
{
public:
	MSTEdgeNode* edgevalue;//用边值数组表示树
	int maxSize, n;//数组的最大元素个数和当前个数
	MinSpantree(int sz =100001 - 1) :maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[sz];
	}
	int Insert(MSTEdgeNode& item);
	bool IsEmpty() { return n == 0; }   //判断是否为空
	bool IsFull() { return n == maxSize; }  //判断是否已满
	bool getTree(MSTEdgeNode* tree);   //返回树的元素数组
};
