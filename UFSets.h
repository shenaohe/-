#pragma once
const int DefaultSize1 = 100000;
class UFSets {	//�����еĸ����Ӽ��ϻ����ཻ
public:
    UFSets(int sz = DefaultSize1);	//���캯��
    ~UFSets() { delete[]parent; }	//��������
    //UFSets& operator = (UFSets& R);    //���ϸ�ֵ
    void Union(int Root1, int Root2);	     //�Ӽ��ϲ�
    int Find(int x);				//����x�ĸ�
private:
    int* parent;		  //����Ԫ������(˫�ױ�ʾ)
    int size;			  //����Ԫ�ص���Ŀ
};

