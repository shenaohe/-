#include"pch.h"
#include"MSTEdgeTree.h"
int MinSpantree::Insert(MSTEdgeNode& item)
{
	if (n == maxSize - 1)
	{
		cout << "�ѳ�������Ĵ洢��Χ��" << endl;
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
		tree[i] = edgevalue[i];             //��edgevalue��������ݸ��Ƶ����ر�����
	}
	return true;
}

