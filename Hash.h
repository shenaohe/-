#pragma once
#include"iostream"
#include"math.h"
using namespace std;
const int DefaultSize = 122000;
enum KindOfStatus { Active, Empty, Deleted };//Ԫ�ط��� (�/��/ɾ)

template<class T>
class HashTable {		     //ɢ�б��ඨ��//k�ǹؼ������ͣ�E��Ԫ������
public:
    HashTable(const int d, int sz = DefaultSize); 	//���캯��
    ~HashTable() { delete[]ht;  delete[]info; } 	//��������
    bool Search(int k1,T& e1);	       //����k1,e1�ǿ����õ���Ԫ��
    int Search1(int x1,int x2);	       //����k1
    bool Insert(const int k1,T& e1);		       //����e1��k1�Ǹ�Ԫ�عؼ���
    bool Insert1(int v1,int v2,T&e1);//����x1,x2
    bool Remove(const T& e1);	       	       //ɾ��e1
    bool Remove1(const T& e1);
    void makeEmpty();			       //�ñ��
    int FindPos2(int x1,int  x2);//
    int FindPos1(int v1,int v2);		//ɢ�к���
private:
    int divitor;			//ɢ�к����ĳ���
    int CurrentSize, TableSize;			//��ǰͰ�������Ͱ��
    T* ht;				//ɢ�б�洢����
    KindOfStatus* info;		//״̬����
    int FindPos(int k1) const;		//������ɢ�к��� 
    int Nextprime(int n1);
    bool isPrime(int num);
    int operator == (T& e1) { return *this == e1; } 	//���غ�����Ԫ���е�
    int operator != (T& e1) { return *this != e1; } //���غ�����Ԫ���в���
};

template<class T>
HashTable<T>::HashTable(const int d, int sz)
{
    divitor = d;				//����
    TableSize = sz;  CurrentSize = 0;		//��
    ht = new T[TableSize];		//��洢�ռ�
    info = new KindOfStatus[TableSize];
    for (int i = 0; i < TableSize; i++) info[i] = Empty;
}

template<class T>
bool HashTable<T>::Search(int k1, T& e1)
{
    int i = FindPos(k1);  		//����
    if (info[i] != Active || ht[i].key != k1) return false;
    e1 = ht[i];
    return true;
}

template<class T>
int HashTable<T>::Search1(int x1, int x2)
{
    int i = FindPos2(x1,x2);  		//����
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
    int i = FindPos(k1);	    //����Ͱ��
    if (info[i] != Active) {	    //��Ͱ��,�����Ԫ��
        ht[i] = e1;   info[i] = Active;
        CurrentSize++;   return true;
    }
    if (info[i] == Active && ht[i].key == k1)
    {
        MessageBox(NULL, _T("hash�����Ѿ������Ԫ�أ�����ʧ��"), _T("��ʾ"), MB_OK);
        return false;
    }
    else {
        MessageBox(NULL, _T("hash������������ʧ��"), _T("��ʾ"), MB_OK);
    }
    return false;
}

//�ж��Ƿ�Ϊ����
template <class T>
bool HashTable<T>::isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    }
    // ����6�ı��������һ����������
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
    int key = FindPos1(v1, v2);//����keyֵ
    e1.key = key;//����e1��keyֵ
    int i = key;
    if (info[i] != Active) {	    //��Ͱ��,�����Ԫ��
        ht[i] = e1; info[i] = Active;
        CurrentSize++;   return true;
    }
    if (info[i] == Active && ht[i] == key)
    {
        MessageBox(NULL, _T("�����Ѿ������Ԫ�أ�����ʧ��"), _T("��ʾ"), MB_OK);
        exit(1);
        
    }
    else {
        MessageBox(NULL, _T("hash������������ʧ��"), _T("��ʾ"), MB_OK);
    }
    return false;
}

template<class T>
inline bool HashTable<T>::Remove(const T& e1)
{
    int i = FindPos(e1.key);
    if (info[i] == Active) {
        //�ҵ�ҪɾԪ��, ���ǻԪ��
        info[i] = Deleted;  CurrentSize--;
        //���߼�ɾ����־, ������������ɾ��
        return true;
    }
    else return false;
}

template<class T>
inline bool HashTable<T>::Remove1(const T& e1)
{
    int i = FindPos(e1.key);
    if (info[i] == Active) {
        //�ҵ�ҪɾԪ��, ���ǻԪ��
        info[i] = Deleted;  CurrentSize--;
        //���߼�ɾ����־, ������������ɾ��
        return true;
    }
    else return false;
}


template<class T>
void HashTable<T>::makeEmpty()
{
    for (int i = 0; i < TableSize; i++) {
        info[i] = Empty;     //ֻ�轫info�����
    }
    CurrentSize = 0;
}

template<class T>
int HashTable<T>::FindPos(int k1) const
{
    int i = k1 % divitor;	        //�����ʼͰ��
    int j = i;			        //j�Ǽ����һ��Ͱ�±�
    do {
        if (info[j] == Empty || info[j] == Active && ht[j].key == k1)return j; 		//�ҵ���ʼͰ��
        j = (j + 1) % TableSize;		//����һ����Ͱ 
    } while (j != i);
    return j;	         //תһȦ�ص���ʼ��, ������, ʧ��
}

//����v1,v2��keyֵ
template<class T>
inline int HashTable<T>::FindPos1(int v1,int v2){
    int k1 = v1*10 + v2%10;
    int i = k1 % divitor;	        //�����ʼͰ��
    int j = i;			        //j�Ǽ����һ��Ͱ�±�
    do {
        if (info[j] == Empty)return j; 		//�ҵ���ʼͰ��
        else 
        { 
            j = (j + 1) % TableSize; 
        }	//����һ����Ͱ 
    } while (j != i);
    return j;	         //תһȦ�ص���ʼ��, ������, ʧ��
}

template<class T>
inline int HashTable<T>::FindPos2(int x1,int x2)
{
    int i = (x1*10+x2%10) % divitor;	        //�����ʼͰ��
    int j = i;			        //j�Ǽ����һ��Ͱ�±�
    do {
        if (info[j] == Empty || (info[j]==Active&&((ht[j].v[0]==x1&&ht[j].v[1]==x2)||(ht[j].v[0] == x2 && ht[j].v[1] == x1))))
            return j; 		//�ҵ���ʼͰ��
        j = (j + 1) % TableSize;		//����һ����Ͱ 
    } while (j != i);
    return j;	         //תһȦ�ص���ʼ��, ������, ʧ��
}


