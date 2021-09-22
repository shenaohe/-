#pragma once
#include<iostream>
#include"math.h"
#include"fstream"
#include<limits.h>
#include<string>
using namespace std;

#include"MinHeap.h"
#include"UFSets.h"
#include"Graph.h"
#include"MSTEdgeTree.h"

extern	void SearchSecnic(Graphic &G,int *v);    //查询所有景点
extern	void SearchSurrSecnic(Graphic& G, int curSecnic, int surround, LinkList<int>& list, LinkList<int>& listd,int& numv);   //查询所在位置的周围景点
extern	void FindPath(Graphic& G, int curSecnic, int endSecnic,int &alldist, LinkList<int>&list,int v[],int n);     //查询路径
extern	void SearchsSetSecnic(Graphic& G, int num, int* visitSecnic, int& distance, int (*a)[3]);   //查询一系列顶点
extern	void AddSecnic(Graphic& G,int name);   //增加景点
extern	void ReSecnic(Graphic& G,int oldname,int newname);   //修改景点
extern	void DeleteSecnic(Graphic& G, int name);    //删除景点
extern	void AddRoad(Graphic& G,int start,int end,int weight);    //增加道路
extern	void ReRoad(Graphic& G, int start, int end, int weight);    //更新道路
extern	void DeleRoad(Graphic& G, int start, int end);    //删除道路
extern	int Kruskal(Graphic& G, MinSpantree& MST, int V[]);//克鲁斯卡算法
extern	void Kru_knownV(Graphic& G, MinSpantree& MST, int& distance, int v1[], int n);
extern	bool Dijkstra(Graphic& G, int dist[], int path[], int v[], int startV, int maxValue,int end);//迪杰斯特拉算法
extern	void OutputPath(Graphic& G, int dist[], int path[], int v[], int start, int end, int& alldist, LinkList<int>& list);//输出最短路径
