#pragma once
#include <limits.h>
#include <cfloat>
using namespace std;
const float maxValue = FLT_MAX;
const int defaultSize = 122000;
const int intmax = INT_MAX;

template<class E>
class MinHeap
{
protected:
	E* heap;   //�����С��Ԫ�ص�����
	int maxSize;    //Ԫ����Ŀ����
	int currentSize;    //��ǰԪ�ظ���
	void SiftDown(int start, int m);    //��start�»���m�γ���С��
	void SiftUp(int start);      //��start�ϻ���0�γ���С��
public:
	MinHeap(int sz = defaultSize);    //��ʼ��һ���յ���С��
	MinHeap(E arr[], int n);    //ͨ��һ�����齨����С��
	~MinHeap() { delete[] heap; }     //����
	bool Insert(E &d);      //����һ��Ԫ��
	bool RemoveMin(E &d);        //�Ƴ�������С��Ԫ�ز��ñ���rev����
	bool RemoveMin1(int& d);
	bool IsEmpty() const{ return currentSize ? false : true; }   //�ж϶��Ƿ�Ϊ��
	bool IsFull()const { return (currentSize == maxSize) ? true : false; }   //�ж϶��Ƿ�����
	void MakeEmpty() { currentSize = 0; }       //��ն�
};

template<class E>
MinHeap<E>::MinHeap(int sz)
{
	maxSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new E[maxSize];  	//�����ѿռ�
	if (heap == NULL) {
		cerr << "�Ѵ洢����ʧ�ܣ�" << endl;  
		exit(1);
	}
	currentSize = 0;				//������ǰ��С
}

template<class E>
void MinHeap<E>::SiftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;  			//j��i������Ůλ��
	E temp = heap[i];
	while (j <= m) {				//����Ƿ����λ��
		if (j < m && heap[j] > heap[j + 1]) j++;     	//��jָ������Ů�е�С��
		if (temp <= heap[j]) break;		//С��������
		else { 		//����С������, i, j�½�
			heap[i] = heap[j];  i = j; j = 2 * j + 1;
		}
	}
	heap[i] = temp;	      	//�ط�temp���ݴ��Ԫ��
}

template<class E>
void MinHeap<E>::SiftUp(int start)
{
	int j = start, i = (j - 1) / 2;   E temp = heap[j];
	while (j > 0) {		//�ظ����·������ֱ���
		if (heap[i] <= temp) break;	//�����ֵС, ������
		else {		//�������ֵ��, ����
			heap[j] = heap[i];  j = i;  i = (i - 1) / 2;
		}
	}
	heap[j] = temp;				//����
}


template<class E>
MinHeap<E>::MinHeap(E arr[], int sz)
{
	maxSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new E[maxSize];
	if (heap == NULL) {
		cerr << "�Ѵ洢����ʧ�ܣ�"<< endl; 
		exit(1);
	}
	for (int i = 0; i < sz; i++)    heap[i] = arr[i];
	currentSize = sz;	       		//���ƶ�����, ������ǰ��С
	int currentPos = (currentSize - 2) / 2;        	//���������λ��:����֧���
	while (currentPos >= 0) {	    	//�����������
		siftDown(currentPos, currentSize - 1);      //�ֲ����������»�����
		currentPos--;
	}
}

template<class E>
bool MinHeap<E>::Insert(E &d)
{
	if (currentSize == maxSize) { 	//����
		cerr << "Heap Full" << endl;  return false;
	}
	heap[currentSize] = d;  		//����
	SiftUp(currentSize);			//���ϵ���
	currentSize++;				//�Ѽ�����1
	return true;
}

template<class E>
bool MinHeap<E>::RemoveMin(E &x)
{
	if (!currentSize) {		//�ѿ�, ����false
		cout << "Heap empty" << endl;  return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	SiftDown(0, currentSize - 1);    	//�������µ���Ϊ��
	return true;			//������СԪ��
}

template<class E>
inline bool MinHeap<E>::RemoveMin1(int& d)
{
	if (!currentSize) {		//�ѿ�, ����false
		cout << "Heap empty" << endl;  return false;
	}
	d = heap[0].v[1];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	SiftDown(0, currentSize - 1);    	//�������µ���Ϊ��
	return true;			//������СԪ��
}



