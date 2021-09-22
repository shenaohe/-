#include"pch.h"
#include "UFSets.h"
#include"iostream"
using namespace std;
UFSets::UFSets(int sz)
{
    size = sz;			  //集合元素个数
    parent = new int[size];  //创建双亲数组
    for (int i = 0; i < size; i++)
        parent[i] = -1;               //每个自成单元素集合
}

void UFSets::Union(int Root1, int Root2)
{
    int r1 = Find(Root1), r2 = Find(Root2), temp;
    if (r1 != r2)
    {
        temp = parent[r1] + parent[r2];
        if (parent[r2] < parent[r1]) {
            parent[r1] = r2;     //r2中结点数多(负值)
            parent[r2] = temp;      //r1指向r2
        }
        else {
            parent[r2] = r1;    //r1中结点数多(负值)
            parent[r1] = temp;      //r2指向r1
        }
    }
}

int UFSets::Find(int i)
{
    if (parent[i] < 0)       //当x是根的时候返回根的值
        return i;
    else
        return Find(parent[i]);   //否则递归寻找父的根
}
