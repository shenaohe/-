#pragma once
#include"LinkList.h"
#include"Key.h"
#include"limits.h"
#include"Hash.h"
#include <cstddef>

struct Edge;
struct Vertex;
struct EHash;
template<class T>
struct LinkNode;

//边结构体
struct Edge{//边结构
	LinkNode<Vertex>* next_v;  //指向另一顶点的指针
	int weight;                       //权值
	LinkNode<Edge>* part;    //指向另一半边的指针
	Edge(LinkNode<Vertex>* p = NULL, int w = INT_MAX, LinkNode<Edge>* q = NULL) :next_v(p), weight(w), part(q) {}
};

//顶点结构体
struct Vertex {//顶点结构
	int data;//顶点数据域即关键码
	int degree;//顶点的度
	int locat;//顶点在顶点数组中的位置
	LinkList<Edge> edgList;//顶点的边链表
	Vertex() {}
	Vertex(int& x) :data(x), degree(0),locat(-1){}
};

//邻居结构体
struct Neighbors   //邻接顶点结构体
{
	LinkList<int> neighborList;   //存储邻接顶点
	LinkList<int> weightList;    //存储对应权值
};

//顶点hash
struct VHash  //用于在哈希表中存储顶点的结构体
{
	int key;  //用于插入哈希表的key值
	LinkNode<Vertex>* p_v;   //指向当前顶点的指针
	VHash() { }   //key即data即文件中的序号
	VHash(int& x, LinkNode<Vertex>* pv=NULL)
	{
		key = x;
		p_v = pv;
		
	}
	bool operator==(const int& k)const
	{
		return (key == k) ? true : false;
	}
	bool operator==(const VHash& v)const
	{
		return (this->key == v.key) ? true : false;
	}
};
//边hash
 struct EHash  //用于在哈希表中存储一对顶点的边的结构体
{
	int key;   //用于插入哈希表的key值
	int v[2];  //顶点对
	LinkNode<Edge>* p_e;   //指向该顶点对的一条边的某个结点的指针
	EHash() {}    //key值由两个顶点的数据获得，尽量避免重复
	EHash(int& v1, int& v2, LinkNode<Edge>* p_e = NULL)
	{
		v[0] = v1;
		v[1] = v2;
		p_e = NULL;
		key = v[0]*10 + v[1]%10;
	}
	EHash(int& v1, int& v2, int key1, LinkNode<Edge>* p_e = NULL)
	{
	v[0] = v1;
	v[1] = v2;
	p_e = NULL;
	key = key1;
	}
	bool operator==(const int& k)const
	{
		return (key == k) ? true : false;
	}
	bool operator==(const EHash& edge)const
	{
		if ((this->v[0] == edge.v[0] && this->v[1] == edge.v[1]) || (this->v[0] == edge.v[1] && this->v[1] == edge.v[0]))
			return true;
		else return false;
	}
	bool operator<(const EHash& edge)const
	{
		if (this->key<edge.key)
			return true;
		else return false;
	}
	bool operator<=(const EHash& edge)const
	{
		if (this->key <=edge.key)
			return true;
		else return false;
	}
	bool operator>(const EHash& edge)const
	{
		if (this->key > edge.key)
			return true;
		else return false;
	}
};

 //图类
class Graphic{
protected:
	LinkList<Vertex> vList;//所有顶点链表
	HashTable<VHash> vhash;//顶点hash表
	HashTable<EHash> ehash;//顶点对即边的hash表
	int numofVertices;//顶点数
	int numofEdge;//边数
	
	bool IsEdited;//判断顶点链表是否被编辑过，是则要更新顶点的position
public:
	Graphic(int max_V = 100000, int max_E =122000) :vhash(max_V,max_V), ehash(max_E, max_E), numofVertices(0), numofEdge(0), IsEdited(false) {}  //初始化
	int vertexCount();  //获得顶点个数
	int edgeCount();//获得边数
	LinkNode<Edge>* getEdge(int& vertex1, int& vertex2); //判断是否为边，是返回边位置，不是返回NULL
	bool getVertices(int* vertices);//获得顶点列表
	int* getVertices();//返回包含所有顶点的数组
	bool addVertex(int& key);//添加顶点
	bool removeVertex(int& key);//删除顶点
	bool isVertex(int& key);//判断是否为顶点
	int degree(int& key);	//顶点的度
	bool getNeighbors(int& data, Neighbors & neighbor);	//获得邻接顶点表
	Neighbors* getNeighbors1(int v,Neighbors &neighbor);//返回第一个邻接顶点
	bool addEdge(int& v1, int& v2, int weight,bool tag=true);	//往图中插入边
	bool removeEdge(int& v1, int& v2);//移除边
	bool isEdge(int& v1, int& v2);//判断两点间是否有边
	int weight(int& v1, int& v2);//获得权值
	bool updateVerPos(); //更新顶点在数组中的位置
	int getVerPos(int& data);  //获得顶点的位置
	bool updateVertex(int& data, int& newdata);  //更新顶点信息
	bool updateEdge(int& v1, int& v2,int newweight); //更新边权值信息
	int getneighborCount(int& v);//获取邻居数量
	LinkNode<Vertex>* getVertex(int key);//判断是否为顶点，是返回顶点位置，不是返回NULL
};
