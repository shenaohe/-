#include"pch.h"
#include"MSTEdgeTree.h"
int MinSpantree::Insert(MSTEdgeNode& item)
{
	if (n == maxSize - 1)
	{
		cout << "已超出数组的存储范围！" << endl;
		return false;
	}
	edgevalue[n] = item;
	n++;
	return true;
}

bool MinSpantree::getTree(MSTEdgeNode* tree)
{
	if (IsEmpty())
		return false;
	for (int i = 0; i < n; i++)
	{
		tree[i] = edgevalue[i];             //把edgevalue数组的内容复制到返回变量上
	}
	return true;
}

