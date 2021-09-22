#include"pch.h"
#include "UFSets.h"
#include"iostream"
using namespace std;
UFSets::UFSets(int sz)
{
    size = sz;			  //����Ԫ�ظ���
    parent = new int[size];  //����˫������
    for (int i = 0; i < size; i++)
        parent[i] = -1;               //ÿ���Գɵ�Ԫ�ؼ���
}

void UFSets::Union(int Root1, int Root2)
{
    int r1 = Find(Root1), r2 = Find(Root2), temp;
    if (r1 != r2)
    {
        temp = parent[r1] + parent[r2];
        if (parent[r2] < parent[r1]) {
            parent[r1] = r2;     //r2�н������(��ֵ)
            parent[r2] = temp;      //r1ָ��r2
        }
        else {
            parent[r2] = r1;    //r1�н������(��ֵ)
            parent[r1] = temp;      //r2ָ��r1
        }
    }
}

int UFSets::Find(int i)
{
    if (parent[i] < 0)       //��x�Ǹ���ʱ�򷵻ظ���ֵ
        return i;
    else
        return Find(parent[i]);   //����ݹ�Ѱ�Ҹ��ĸ�
}
