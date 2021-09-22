#include"pch.h"
#include"Key.h"
HashTable<EHash> KEY(123000, 123000);
//HashTable<Verxx> HH(100000, 100000);
Graphic G;

void init() {
	fstream openfile("Edge1.txt");
	int v1, v2,w;
	if (!openfile.is_open()) {
		cout << "���ļ�����" << endl;
		exit(1);
	}
	for (int i = 0; i < 121592; i++) {
		openfile >> v1 >> v2>>w;
		EHash e(v1, v2);
		KEY.Insert1(v1, v2,e);
	}
	openfile.close();
	fstream open("Dingdian.txt");
	if (!open.is_open()) {
		cout << "���ļ�����" << endl;
		exit(1);
	}
	openfile.close();
}
int findkey(int v1, int v2) {
	return KEY.Search1(v1, v2);
}
void Initialization(Graphic& G)   //��ʼ������ͼ
{
	fstream openfile("Dingdian.txt");
	if (!openfile.is_open())
	{
		MessageBox(NULL, _T("�ļ�����ʧ��"), _T("��ʾ"), MB_OK);
		exit(0);
	}
	int vertex, a, b;
	int v1, v2;    //�ļ��ж���ľ�����
	int w;     //����ĵ�·Ȩֵ
	for (int k = 0; k <87574; k++) { //���ļ��ж�ȡ�������
		openfile >> vertex >> a >> b;
		G.addVertex(vertex);
	}
	openfile.close();
	openfile.open("Edge1.txt");
	if (!openfile.is_open())
	{
		MessageBox(NULL, _T("�ļ�����ʧ��"), _T("��ʾ"), MB_OK);
		exit(0);
	}
	for (int i = 0; i < 121592; i++) {
		openfile >> v1 >> v2 >> w;
		G.addEdge(v1, v2, w);
	}
	openfile.close();
}