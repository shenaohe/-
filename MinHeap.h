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
	E* heap;   //存放最小堆元素的数组
	int maxSize;    //元素数目上限
	int currentSize;    //当前元素个数
	void SiftDown(int start, int m);    //从start下滑到m形成最小堆
	void SiftUp(int start);      //从start上滑到0形成最小堆
public:
	MinHeap(int sz = defaultSize);    //初始化一个空的最小堆
	MinHeap(E arr[], int n);    //通过一个数组建立最小堆
	~MinHeap() { delete[] heap; }     //析构
	bool Insert(E &d);      //插入一个元素
	bool RemoveMin(E &d);        //移除堆中最小的元素并用变量rev返回
	bool RemoveMin1(int& d);
	bool IsEmpty() const{ return currentSize ? false : true; }   //判断堆是否为空
	bool IsFull()const { return (currentSize == maxSize) ? true : false; }   //判断堆是否已满
	void MakeEmpty() { currentSize = 0; }       //清空堆
};

template<class E>
MinHeap<E>::MinHeap(int sz)
{
	maxSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new E[maxSize];  	//创建堆空间
	if (heap == NULL) {
		cerr << "堆存储分配失败！" << endl;  
		exit(1);
	}
	currentSize = 0;				//建立当前大小
}

template<class E>
void MinHeap<E>::SiftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;  			//j是i的左子女位置
	E temp = heap[i];
	while (j <= m) {				//检查是否到最后位置
		if (j < m && heap[j] > heap[j + 1]) j++;     	//让j指向两子女中的小者
		if (temp <= heap[j]) break;		//小则不做调整
		else { 		//否则小者上移, i, j下降
			heap[i] = heap[j];  i = j; j = 2 * j + 1;
		}
	}
	heap[i] = temp;	      	//回放temp中暂存的元素
}

template<class E>
void MinHeap<E>::SiftUp(int start)
{
	int j = start, i = (j - 1) / 2;   E temp = heap[j];
	while (j > 0) {		//沿父结点路径向上直达根
		if (heap[i] <= temp) break;	//父结点值小, 不调整
		else {		//父结点结点值大, 调整
			heap[j] = heap[i];  j = i;  i = (i - 1) / 2;
		}
	}
	heap[j] = temp;				//回送
}


template<class E>
MinHeap<E>::MinHeap(E arr[], int sz)
{
	maxSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new E[maxSize];
	if (heap == NULL) {
		cerr << "堆存储分配失败！"<< endl; 
		exit(1);
	}
	for (int i = 0; i < sz; i++)    heap[i] = arr[i];
	currentSize = sz;	       		//复制堆数组, 建立当前大小
	int currentPos = (currentSize - 2) / 2;        	//找最初调整位置:最后分支结点
	while (currentPos >= 0) {	    	//逐步向上扩大堆
		siftDown(currentPos, currentSize - 1);      //局部自上向下下滑调整
		currentPos--;
	}
}

template<class E>
bool MinHeap<E>::Insert(E &d)
{
	if (currentSize == maxSize) { 	//堆满
		cerr << "Heap Full" << endl;  return false;
	}
	heap[currentSize] = d;  		//插入
	SiftUp(currentSize);			//向上调整
	currentSize++;				//堆计数加1
	return true;
}

template<class E>
bool MinHeap<E>::RemoveMin(E &x)
{
	if (!currentSize) {		//堆空, 返回false
		cout << "Heap empty" << endl;  return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	SiftDown(0, currentSize - 1);    	//自上向下调整为堆
	return true;			//返回最小元素
}

template<class E>
inline bool MinHeap<E>::RemoveMin1(int& d)
{
	if (!currentSize) {		//堆空, 返回false
		cout << "Heap empty" << endl;  return false;
	}
	d = heap[0].v[1];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	SiftDown(0, currentSize - 1);    	//自上向下调整为堆
	return true;			//返回最小元素
}



