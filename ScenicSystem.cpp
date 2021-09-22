#include"pch.h"
#include"ScenicSystem.h"
//��³˹�����㷨
int Kruskal(Graphic& G, MinSpantree& MST, int V[]) {
	MSTEdgeNode ed; int count, u, v, w;//�߽�㸨������
	int sum_w = 0;   //��¼��Ȩֵ
	int n = G.vertexCount();  //��ö�����
	int m = G.edgeCount();   //��ñߵĸ���
	MinHeap<MSTEdgeNode>H(m); //��С��
	UFSets F(n); //���鼯
	//������ʼ��С��
	for (int i = 0; i < n; i++)
	{
		Neighbors a; int k = 0;
		G.getNeighbors(V[i], a);//��ȡ��ǰ������ھ�
		//��ȡ��ǰ�ڽӶ���Ķ����
		while (a.neighborList.GetNext(k)) {
			a.weightList.GetNext(w);
			ed.tail = i;
			ed.head = k;
			ed.key = w;
			H.Insert(ed);  //�����
		}
		a.weightList.ResetCurrent();
		a.neighborList.ResetCurrent();
	}
	count = 1;   //��С�����������������
	while (count < n)  
	{
		H.RemoveMin(ed);   //�Ӷ����˳���СȨֵ�ı�
		u = F.Find(ed.tail);
		v = F.Find(ed.head);  
		if (u != v)
		{
			F.Union(u, v);  //�ϲ�
			MST.Insert(ed);  //�ñߴ�����С������
			sum_w += ed.key;   //������Ȩֵ
			count++;
		}
	}
	return sum_w;
}

//�Ͻ�˹�����㷨
bool Dijkstra(Graphic& G, int dist[], int path[], int v[], int startV, int maxValue = INT_MAX,int end = 0) {
	int startpos, endpos, n = G.vertexCount();    //startposΪ��ʼ���ڶ��������е�λ�ã�endposΪ�յ��ڶ��������е�λ��
	int w;    //�ݴ洢Ȩֵ
	int top;//��
	EHash  ehash;
	MinHeap<EHash> HE(n);
	MinHeap<int> H(n);//��С�Ѵ洢�����ţ��Ѷ��Ǵӵ�ǰ�㵽����������С�ĵ�
	bool* S = new bool[n];      //�ж��Ƿ�Ϊ�յ������
	if (!G.isVertex(startV))     //�ж���ʼ���Ƿ�Ϊͼ�еĵ�
		return false;
	if (end == 0)        //��endΪĬ��ֵ
	{
		endpos = -1;    //Ѱ����㵽���е�����·��
		startpos = G.getVerPos(startV);   //�����λ��
	}
	else {
		if (!G.isVertex(end))    //�����յ�ʱ���ж��յ��Ƿ���ͼ��
			return false;
		startpos = G.getVerPos(startV);   //�����λ��
		endpos = G.getVerPos(end);   //���յ�λ��
		ehash.v[0] = startpos;
		ehash.v[1] = startpos;
		ehash.key = G.weight(startV, end);
	}
	for (int i = 0; i < n; i++)    //��ʼ��
	{
		S[i] = false;      
		dist[i] = INT_MAX;
		path[i] = -1;
	}
	H.Insert(startpos); dist[startpos] = 0;
	HE.Insert(ehash);//��С�ߵ���������
	int k = 0;
	while (!HE.IsEmpty()) {//����ѷǿ�
		Neighbors a;//��������
		HE.RemoveMin1(top);//�õ���Сֵ
		int u = top;
		if (S[u]) {//�Ѿ����ʹ��Ĳ��ڷ���
			continue;
		}
		if (endpos != -1 && S[endpos])
			return true;
		S[u] = true;//����С�߱��Ϊ���ʹ�
		G.getNeighbors(v[u], a);//��ȡ��ǰ�ڽӶ���Ķ����
		while (a.neighborList.GetNext(k)) {
			a.weightList.GetNext(w);//��Ӧȡ��Ȩֵ
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k])//û�б����ʹ��Ҿ���k�������̾���    
			{
				dist[k] = dist[u] + w;//������̾���
				path[k] = u;//��¼����
				EHash  ehash1(u,k,dist[k]);//����һ���±�       
				HE.Insert(ehash1);//������С��
			}
		}
		a.weightList.ResetCurrent();//����
		a.neighborList.ResetCurrent();
	}
	return true;
}

//������·��
void OutputPath(Graphic& G, int dist[], int path[], int v[], int start, int end,int &alldist,LinkList<int>&list)
{
	int n = G.vertexCount();
	int endpos;   //�յ��������е�λ��
	endpos = G.getVerPos(end);
	int curpos = endpos;
	while (!(v[curpos] == start) && path[curpos] != -1)    //�������
	{
		list.InsertData(curpos);
		curpos = path[curpos];
	}
	alldist = dist[endpos];
}

//������һϵ�ж������С������
void Kru_knownV(Graphic& G, MinSpantree& MST, int& distance, int V[], int n)  //v1Ϊ���������飬nΪ��ĸ���,distance��¼�����������ĳ���
{
	MSTEdgeNode ed; int u, v, count;  //�߽��
	int m = n * (n - 1) / 2;  //������
	int sum_n = G.vertexCount();
	int* dist = new int[sum_n];  //����
	int* v_all = new int[sum_n];//ȫ����������
	int* path = new int[sum_n]; //·��
	G.getVertices(v_all);
	int end = 0; 
	MinHeap<MSTEdgeNode>H(m);  //��С��
	UFSets F(n);   //���鼯
	for (u = 0; u < n; u++) {
		for (v = u+1; v < n; v++)
		{
				Dijkstra(G, dist, path, v_all,V[u], intmax, V[v]);   //������֮�����·��
				end = G.getVerPos(V[v]);//�ж�
				if (dist[end]!=INT_MAX)
				{
					ed.tail = u;
					ed.head = v;
					ed.key = dist[end];
					H.Insert(ed);   //���ñ߲������
				}
		}
	}
	count = 1;    //��С��������������
	while (count < n)    
	{
		H.RemoveMin(ed);   //����С�����˳�������СȨֵ�ı�ed
		u = F.Find(ed.tail);
		v = F.Find(ed.head);    //ȡ�����㼯�ϵı�
		if (u != v)      //����ͬһ����˵������ͨ
		{
			F.Union(u, v);   //�ϲ���ͨ
			MST.Insert(ed);  //�ñߴ�����С������
			distance += ed.key;//��̾��볤��
			count++;
		}
	}
	delete[] dist;
	delete[] path;
	delete[] v_all;
}

//��ѯ���о���
void SearchSecnic(Graphic& G,int *v )    //��ѯ���о���
{
	int n = G.vertexCount();
	int num = 1;
	v = G.getVertices();//�������ж��������
}

//��ѯĳ����һ����Χ�ڵ����о���
void SearchSurrSecnic(Graphic& G, int curSecnic, int surround, LinkList<int>& list,LinkList<int> &listd,int &numv){
	int n = G.vertexCount();
	int* dist = new int[n];//��������
	int* path = new int[n];//��������
	int* v = new int[n];   //Ϊ��Χ�ھ��㿪������
	v = G.getVertices();
	if (!G.isVertex(curSecnic))
	{
		MessageBox(NULL, _T("ͼ��û�о���"), _T("��ʾ"), MB_OK);
		return;
	}
	Dijkstra(G, dist, path, v, curSecnic, surround);   //��ѯ�Ե�ǰ��Ϊ���ģ�һ����Χ�ڵ����о���
	//���������Ϣ
	for (int i = 0; i < n; i++)
	{
		if (dist[i] <= surround) {
			list.InsertData(v[i]);
			listd.InsertData(dist[i]);
			numv++;
		}
	}
	delete[] dist;   
	delete[] path;
	delete[] v;
}

//�������֮������·��
void FindPath(Graphic& G,int curSecnic,int endSecnic,int&alldist, LinkList<int> &list,int v[],int n)   //��ѯ·��
{
	int* dist = new int[n];
	int* path = new int[n];
	if (!G.isVertex(curSecnic))
	{
		MessageBox(NULL, _T("ͼ��û�о���1"), _T("��ʾ"), MB_OK);
		return;
	}
	if (!G.isVertex(endSecnic))
	{
		MessageBox(NULL, _T("ͼ��û�о���2"), _T("��ʾ"), MB_OK);
		return;
	}
	Dijkstra(G, dist, path, v, curSecnic, intmax, endSecnic);   //��ѯ��������·��
	OutputPath(G, dist, path, v, curSecnic, endSecnic,alldist,list);    //���·��
	delete[] dist;  
	delete[] path;
}

//��ѯһϵ�ж������С������
void SearchsSetSecnic(Graphic& G, int num, int* visitSecnic, int& distance, int (*a)[3])
{
	MinSpantree mst(num);
	Kru_knownV(G, mst, distance, visitSecnic, num);
	MSTEdgeNode* tree = new MSTEdgeNode[num];   //���ڻ�ø�������ĵ�·
	bool tag = mst.getTree(tree);
	if (!tag) {
		MessageBox(NULL, _T("����֮�䲻��ͨ��"), _T("��ʾ"), MB_OK);
		return;
	}
	for (int i = 0; i < num - 1; i++)
	{
		a[i][0]= visitSecnic[tree[i].tail];
		a[i][1]= visitSecnic[tree[i].head];
		a[i][2] = tree[i].key;
	}
	delete[] tree;  
}

//���һ������
void AddSecnic(Graphic& G, int name)   //���Ӿ���
{
	if (G.isVertex(name))
	{
		MessageBox(NULL, _T("�����Ѿ�����"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.addVertex(name))
		MessageBox(NULL, _T("�������ɹ�"), _T("��ʾ"), MB_OK);
	else
	{
		MessageBox(NULL, _T("�������ʧ��"), _T("��ʾ"), MB_OK);
		exit(0);
	}
}

//ɾ��һ������
void DeleteSecnic(Graphic& G,int name )    //ɾ������
{
	if (!G.isVertex(name))
	{
		MessageBox(NULL, _T("���㲻����"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.removeVertex(name))
		MessageBox(NULL, _T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
	else {
		MessageBox(NULL, _T("ɾ��ʧ��"), _T("��ʾ"), MB_OK);
		return;
	}
}

//�޸�һ������
void ReSecnic(Graphic& G,int oldname,int newname)   //�޸ľ���
{
	if (!G.isVertex(oldname))
	{
		MessageBox(NULL, _T("�ɶ��㲻����"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.updateVertex(oldname, newname))
		MessageBox(NULL, _T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
	else
	{
		MessageBox(NULL, _T("�޸�ʧ��"), _T("��ʾ"), MB_OK);
		exit(1);
	}
}

//����һ��·
void AddRoad(Graphic& G,int start,int end,int weight)    //���ӵ�·
{
	if (G.isEdge(start, end))
	{
		MessageBox(NULL, _T("��·�Ѿ�����"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.addEdge(start, end, weight, false))
		MessageBox(NULL, _T("�½��ɹ�"), _T("��ʾ"), MB_OK);
	else
	{
		MessageBox(NULL, _T("�½�ʧ��"), _T("��ʾ"), MB_OK);
		return;
	}
}

//ɾ��һ��·
void DeleRoad(Graphic& G, int start, int end)    //ɾ����·
{
	if (!G.isEdge(start, end))
	{
		MessageBox(NULL, _T("��·������"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.removeEdge(start, end))
		MessageBox(NULL, _T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
	else {
		MessageBox(NULL, _T("ɾ��ʧ��"), _T("��ʾ"), MB_OK);
		return;
	}
}

//�޸ĵ�·
void ReRoad(Graphic& G, int start, int end, int weight)    //���µ�·
{
	if (!G.isEdge(start, end))
	{
		MessageBox(NULL, _T("��·������"), _T("��ʾ"), MB_OK);
		return;
	}
	if (G.updateEdge(start, end, weight)) {
		MessageBox(NULL, _T("���³ɹ�"), _T("��ʾ"), MB_OK);
	}
	else {
		MessageBox(NULL, _T("����ʧ��"), _T("��ʾ"), MB_OK);
		return;
	}
}

