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

extern	void SearchSecnic(Graphic &G,int *v);    //��ѯ���о���
extern	void SearchSurrSecnic(Graphic& G, int curSecnic, int surround, LinkList<int>& list, LinkList<int>& listd,int& numv);   //��ѯ����λ�õ���Χ����
extern	void FindPath(Graphic& G, int curSecnic, int endSecnic,int &alldist, LinkList<int>&list,int v[],int n);     //��ѯ·��
extern	void SearchsSetSecnic(Graphic& G, int num, int* visitSecnic, int& distance, int (*a)[3]);   //��ѯһϵ�ж���
extern	void AddSecnic(Graphic& G,int name);   //���Ӿ���
extern	void ReSecnic(Graphic& G,int oldname,int newname);   //�޸ľ���
extern	void DeleteSecnic(Graphic& G, int name);    //ɾ������
extern	void AddRoad(Graphic& G,int start,int end,int weight);    //���ӵ�·
extern	void ReRoad(Graphic& G, int start, int end, int weight);    //���µ�·
extern	void DeleRoad(Graphic& G, int start, int end);    //ɾ����·
extern	int Kruskal(Graphic& G, MinSpantree& MST, int V[]);//��³˹���㷨
extern	void Kru_knownV(Graphic& G, MinSpantree& MST, int& distance, int v1[], int n);
extern	bool Dijkstra(Graphic& G, int dist[], int path[], int v[], int startV, int maxValue,int end);//�Ͻ�˹�����㷨
extern	void OutputPath(Graphic& G, int dist[], int path[], int v[], int start, int end, int& alldist, LinkList<int>& list);//������·��
