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

//�߽ṹ��
struct Edge{//�߽ṹ
	LinkNode<Vertex>* next_v;  //ָ����һ�����ָ��
	int weight;                       //Ȩֵ
	LinkNode<Edge>* part;    //ָ����һ��ߵ�ָ��
	Edge(LinkNode<Vertex>* p = NULL, int w = INT_MAX, LinkNode<Edge>* q = NULL) :next_v(p), weight(w), part(q) {}
};

//����ṹ��
struct Vertex {//����ṹ
	int data;//���������򼴹ؼ���
	int degree;//����Ķ�
	int locat;//�����ڶ��������е�λ��
	LinkList<Edge> edgList;//����ı�����
	Vertex() {}
	Vertex(int& x) :data(x), degree(0),locat(-1){}
};

//�ھӽṹ��
struct Neighbors   //�ڽӶ���ṹ��
{
	LinkList<int> neighborList;   //�洢�ڽӶ���
	LinkList<int> weightList;    //�洢��ӦȨֵ
};

//����hash
struct VHash  //�����ڹ�ϣ���д洢����Ľṹ��
{
	int key;  //���ڲ����ϣ���keyֵ
	LinkNode<Vertex>* p_v;   //ָ��ǰ�����ָ��
	VHash() { }   //key��data���ļ��е����
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
//��hash
 struct EHash  //�����ڹ�ϣ���д洢һ�Զ���ıߵĽṹ��
{
	int key;   //���ڲ����ϣ���keyֵ
	int v[2];  //�����
	LinkNode<Edge>* p_e;   //ָ��ö���Ե�һ���ߵ�ĳ������ָ��
	EHash() {}    //keyֵ��������������ݻ�ã����������ظ�
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

 //ͼ��
class Graphic{
protected:
	LinkList<Vertex> vList;//���ж�������
	HashTable<VHash> vhash;//����hash��
	HashTable<EHash> ehash;//����Լ��ߵ�hash��
	int numofVertices;//������
	int numofEdge;//����
	
	bool IsEdited;//�ж϶��������Ƿ񱻱༭��������Ҫ���¶����position
public:
	Graphic(int max_V = 100000, int max_E =122000) :vhash(max_V,max_V), ehash(max_E, max_E), numofVertices(0), numofEdge(0), IsEdited(false) {}  //��ʼ��
	int vertexCount();  //��ö������
	int edgeCount();//��ñ���
	LinkNode<Edge>* getEdge(int& vertex1, int& vertex2); //�ж��Ƿ�Ϊ�ߣ��Ƿ��ر�λ�ã����Ƿ���NULL
	bool getVertices(int* vertices);//��ö����б�
	int* getVertices();//���ذ������ж��������
	bool addVertex(int& key);//��Ӷ���
	bool removeVertex(int& key);//ɾ������
	bool isVertex(int& key);//�ж��Ƿ�Ϊ����
	int degree(int& key);	//����Ķ�
	bool getNeighbors(int& data, Neighbors & neighbor);	//����ڽӶ����
	Neighbors* getNeighbors1(int v,Neighbors &neighbor);//���ص�һ���ڽӶ���
	bool addEdge(int& v1, int& v2, int weight,bool tag=true);	//��ͼ�в����
	bool removeEdge(int& v1, int& v2);//�Ƴ���
	bool isEdge(int& v1, int& v2);//�ж�������Ƿ��б�
	int weight(int& v1, int& v2);//���Ȩֵ
	bool updateVerPos(); //���¶����������е�λ��
	int getVerPos(int& data);  //��ö����λ��
	bool updateVertex(int& data, int& newdata);  //���¶�����Ϣ
	bool updateEdge(int& v1, int& v2,int newweight); //���±�Ȩֵ��Ϣ
	int getneighborCount(int& v);//��ȡ�ھ�����
	LinkNode<Vertex>* getVertex(int key);//�ж��Ƿ�Ϊ���㣬�Ƿ��ض���λ�ã����Ƿ���NULL
};
