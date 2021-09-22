#pragma once
#include"iostream"
#include"math.h"
using namespace std;
const int DefaultSize = 122000;
enum KindOfStatus { Active, Empty, Deleted };//元素分类 (活动/空/删)

template<class T>
class HashTable {		     //散列表类定义//k是关键码类型，E是元素类型
public:
    HashTable(const int d, int sz = DefaultSize); 	//构造函数
    ~HashTable() { delete[]ht;  delete[]info; } 	//析构函数
    bool Search(int k1,T& e1);	       //搜索k1,e1是可以拿到该元素
    int Search1(int x1,int x2);	       //搜索k1
    bool Insert(const int k1,T& e1);		       //插入e1，k1是该元素关键码
    bool Insert1(int v1,int v2,T&e1);//插入x1,x2
    bool Remove(const T& e1);	       	       //删除e1
    bool Remove1(const T& e1);
    void makeEmpty();			       //置表空
    int FindPos2(int x1,int  x2);//
    int FindPos1(int v1,int v2);		//散列函数
private:
    int divitor;			//散列函数的除数
    int CurrentSize, TableSize;			//当前桶数及最大桶数
    T* ht;				//散列表存储数组
    KindOfStatus* info;		//状态数组
    int FindPos(int k1) const;		//真正的散列函数 
    int Nextprime(int n1);
    bool isPrime(int num);
    int operator == (T& e1) { return *this == e1; } 	//重载函数：元素判等
    int operator != (T& e1) { return *this != e1; } //重载函数：元素判不等
};

template<class T>
HashTable<T>::HashTable(const int d, int sz)
{
    divitor = d;				//除数
    TableSize = sz;  CurrentSize = 0;		//表长
    ht = new T[TableSize];		//表存储空间
    info = new KindOfStatus[TableSize];
    for (int i = 0; i < TableSize; i++) info[i] = Empty;
}

template<class T>
bool HashTable<T>::Search(int k1, T& e1)
{
    int i = FindPos(k1);  		//搜索
    if (info[i] != Active || ht[i].key != k1) return false;
    e1 = ht[i];
    return true;
}

template<class T>
int HashTable<T>::Search1(int x1, int x2)
{
    int i = FindPos2(x1,x2);  		//搜索
    if (info[i] == Empty) {
        i = FindPos2(x2, x1);
    }
    if (info[i] != Active || (ht[i].v[0]!=x1&&ht[i].v[1]!=x2)&&(ht[i].v[0]!=x2 && ht[i].v[1]!=x1)) {
        return INT_MAX;
        exit(1);
    }
    else {
        return i;
    }
}

template<class T>
bool HashTable<T>::Insert(const int k1, T& e1)
{
    int i = FindPos(k1);	    //计算桶号
    if (info[i] != Active) {	    //该桶空,存放新元素
        ht[i] = e1;   info[i] = Active;
        CurrentSize++;   return true;
    }
    if (info[i] == Active && ht[i].key == k1)
    {
        MessageBox(NULL, _T("hash表中已经有这个元素，插入失败"), _T("提示"), MB_OK);
        return false;
    }
    else {
        MessageBox(NULL, _T("hash表已满，插入失败"), _T("提示"), MB_OK);
    }
    return false;
}

//判断是否为质数
template <class T>
bool HashTable<T>::isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    }
    // 不在6的倍数两侧的一定不是质数
    if (num % 6 != 1 && num % 6 != 5) {
        return false;
    }
    int sqrt1 = sqrt(num);
    for (int i = 5; i <= sqrt1; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

template <class T>
int HashTable<T>::Nextprime(int n1) {
    if (n1 % 2 == 0)n1++;
    for (; !isPrime(n1); n1 += 2);
    return n1;
}

template<class T>
inline bool HashTable<T>::Insert1(int v1,int v2,T&e1)
{
    int key = FindPos1(v1, v2);//计算key值
    e1.key = key;//更新e1的key值
    int i = key;
    if (info[i] != Active) {	    //该桶空,存放新元素
        ht[i] = e1; info[i] = Active;
        CurrentSize++;   return true;
    }
    if (info[i] == Active && ht[i] == key)
    {
        MessageBox(NULL, _T("表中已经有这个元素，插入失败"), _T("提示"), MB_OK);
        exit(1);
        
    }
    else {
        MessageBox(NULL, _T("hash表已满，插入失败"), _T("提示"), MB_OK);
    }
    return false;
}

template<class T>
inline bool HashTable<T>::Remove(const T& e1)
{
    int i = FindPos(e1.key);
    if (info[i] == Active) {
        //找到要删元素, 且是活动元素
        info[i] = Deleted;  CurrentSize--;
        //做逻辑删除标志, 并不真正物理删除
        return true;
    }
    else return false;
}

template<class T>
inline bool HashTable<T>::Remove1(const T& e1)
{
    int i = FindPos(e1.key);
    if (info[i] == Active) {
        //找到要删元素, 且是活动元素
        info[i] = Deleted;  CurrentSize--;
        //做逻辑删除标志, 并不真正物理删除
        return true;
    }
    else return false;
}


template<class T>
void HashTable<T>::makeEmpty()
{
    for (int i = 0; i < TableSize; i++) {
        info[i] = Empty;     //只需将info表清空
    }
    CurrentSize = 0;
}

template<class T>
int HashTable<T>::FindPos(int k1) const
{
    int i = k1 % divitor;	        //计算初始桶号
    int j = i;			        //j是检测下一空桶下标
    do {
        if (info[j] == Empty || info[j] == Active && ht[j].key == k1)return j; 		//找到初始桶号
        j = (j + 1) % TableSize;		//找下一个空桶 
    } while (j != i);
    return j;	         //转一圈回到开始点, 表已满, 失败
}

//计算v1,v2的key值
template<class T>
inline int HashTable<T>::FindPos1(int v1,int v2){
    int k1 = v1*10 + v2%10;
    int i = k1 % divitor;	        //计算初始桶号
    int j = i;			        //j是检测下一空桶下标
    do {
        if (info[j] == Empty)return j; 		//找到初始桶号
        else 
        { 
            j = (j + 1) % TableSize; 
        }	//找下一个空桶 
    } while (j != i);
    return j;	         //转一圈回到开始点, 表已满, 失败
}

template<class T>
inline int HashTable<T>::FindPos2(int x1,int x2)
{
    int i = (x1*10+x2%10) % divitor;	        //计算初始桶号
    int j = i;			        //j是检测下一空桶下标
    do {
        if (info[j] == Empty || (info[j]==Active&&((ht[j].v[0]==x1&&ht[j].v[1]==x2)||(ht[j].v[0] == x2 && ht[j].v[1] == x1))))
            return j; 		//找到初始桶号
        j = (j + 1) % TableSize;		//找下一个空桶 
    } while (j != i);
    return j;	         //转一圈回到开始点, 表已满, 失败
}


