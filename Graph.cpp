#include"pch.h"
#include"Graph.h"



//���ݶ���ؼ����ж��Ƿ��Ƕ���
LinkNode<Vertex>* Graphic::getVertex(int key)
{
	VHash temp;
	if (vhash.Search(key,temp))
		return temp.p_v;    //���ҳɹ����ض�����λ��
	else
		return NULL;   //ʧ�ܷ���NULL
}

//�õ�һ����
LinkNode<Edge>* Graphic::getEdge(int& vertex1, int& vertex2)
{
	EHash temp; //�洢��ϣ�߱���
	int key = findkey(vertex1, vertex2);
	if (ehash.Search(key, temp)!=NULL)
	{
		if ((temp.v[0] == vertex1 && temp.v[1] == vertex2)||(temp.v[0]==vertex2&&temp.v[1]==vertex1)) {
			return temp.p_e;  //�ɹ����ظñ����ڽ�������һ���߽���λ��
		}
	}
	return NULL;  //ʧ�ܷ���NULL
}

//���������
int Graphic::vertexCount()
{
	return numofVertices;
}

//�ߵ�����
int Graphic::edgeCount()
{
	return numofEdge;
}

//���ذ������ж�������飬����int* vertex��
bool Graphic::getVertices(int* vertices)
{
	LinkNode<Vertex>* v;
	if (numofVertices != 0)
	{
		for (int i = 0; (v = vList.GetNext())!= NULL; i++)
		{
			vertices[i] = v->data.data;  //���ض����������Ϣ
		}
		vList.ResetCurrent();
		return true;
	}
	else 
		return false;
}

//���ذ������ж�������飬������ȫ��ȷ�Ĵ����
int* Graphic::getVertices()
{
	LinkNode<Vertex>* v;
	int* vertexs=new int[100000];
	if (numofVertices != 0) {
		for (int i = 0; (v=vList.GetNext()) != NULL; i++) {
			vertexs[i] = v->data.data;
		}
		vList.ResetCurrent();//��ȷ�ĺ���
		return vertexs;
	}
	else return NULL;
}

//���һ������
bool Graphic::addVertex(int& key)
{
	if (isVertex(key))//�����Ƕ��㣬����ʧ��
	{
		MessageBox(NULL, _T("�����Ѿ����ڣ�����ʧ��"), _T("��ʾ"), MB_OK);
		exit(1);
		return false;
	}      
	LinkNode<Vertex>* newNode;
	Vertex v(key);
	newNode = vList.Insert(v);//���붥���б�,���ظö����ڶ����б��λ��
	VHash newHashNode(key, newNode);  //�½������ϣ��ڵ�
	if (!vhash.Insert(newHashNode.key, newHashNode))   //���붥��hash��,����ʧ�ܷ���false
	{
		MessageBox(NULL, _T("����hash��ʧ��"), _T("��ʾ"), MB_OK);
		return false;
	}
	else//����ɹ�
	{
		IsEdited = true;//�Ѿ��޸Ĺ���
		numofVertices++;//������+1
		return true;
	}
}

//ɾ������
bool Graphic::removeVertex(int& key)
{
	if (isVertex(key)) {//����Ƕ���
		IsEdited = true;
		LinkNode<Edge>* e1, * e2;  //��ɾ�����ָ��,����ָ�롢����ָ��,�붥������ı�
		LinkNode<Vertex>* v1, * v2;//�ڶ����б��е�ָ��
		EHash e;    //��ϣ��ı����ݽṹ�壬����ɾ����
		v1 = getVertex(key);//cur_v1ָ���ɾ���Ķ���
		int keye = 0;
		e1 = v1->data.edgList.GetNext();
		while (e1) //ɾ���ö��������ڽӶ���,cure1��һ�����
		{
			//����һ�������ڹ�ϣ����ɾ��
			v2 = e1->data.next_v;  //v2Ϊ�ñ���һ�����λ��
			keye = findkey(key,v2->data.data);   //����Ե�key  
			e.v[0] = key;//���
			e.v[1] = v2->data.data;//�յ�
			e.key = keye;  
			KEY.Remove1(e);       
			ehash.Remove(e);    //ɾ����ϣ��,��������ɾ��
			//ɾ����һ���
			e2 = e1->data.part;   //e2�ñߵ���һ���
			if (e2)
			{
				v2->data.edgList.Remove(e2);//��v2�ڽ�������ɾ����رߵ���һ���
				v2->data.degree--;//v2�Ķȼ�һ
			}
			numofEdge--;
			e1 = v1->data.edgList.GetNext();
		}
		v1->data.edgList.ResetCurrent();
		VHash  temp(key);
		vhash.Remove(temp);  //ɾ����ϣ���������ϢΪkey�Ķ���
		vList.Remove(v1); //�ڶ���������ɾ���ö���
		numofVertices--;
		return true;
	}
	else {
		MessageBox(NULL, _T("����"), _T("��ʾ"), MB_OK);
		return false;
	}
}

//��ǰ����Ķ�
int Graphic::degree(int& key)
{
	LinkNode<Vertex>* temp;  //��ö�����λ
	if (temp = getVertex(key))return temp->data.degree;  //���ض�
	return -1;
}


//�ж��Ƿ�Ϊ����
bool Graphic::isVertex(int& key)
{
	VHash temp;
	if (vhash.Search(key, temp))
		return true;    //���ҳɹ����ض�����λ��
	else
		return NULL;   //ʧ�ܷ���NULL
}

//��ȡ��ǰ������ھ�
bool Graphic::getNeighbors(int& key, Neighbors& neighbor)
{
	int tempV;       //tempV�ݴ涥����Ϣ
	int tempW;       //wtempW�ݴ�Ȩֵ��Ϣ
	LinkNode<Vertex>* vp1, * vp2;   //vp1�洢���ҵĶ���λ��
	LinkNode<Edge>* ep;    //ep���ڴ洢������ڽӶ���λ��
	vp1 = getVertex(key);
	if (!vp1)
	{
		cout << "���㲻����" << endl;
		return false;
	}    //vp1Ϊ�մ����㲻����
	while (ep = vp1->data.edgList.GetNext())   //��ep��Ϊ�գ�������δ��ĩβ����������
	{
		vp2 = ep->data.next_v;
		tempV = vp2->data.locat;
		tempW = ep->data.weight;             //��ö�����Ϣ
		neighbor.neighborList.Insert(tempV);//����
		neighbor.weightList.Insert(tempW);//����
	}
	vp1->data.edgList.ResetCurrent();
	return true;
}

//neighbor����һ����ʽ
Neighbors* Graphic::getNeighbors1(int v, Neighbors &Neighbor)
{
	int key = v;    //����keyֵ
	int tempV;       //vtemp�ݴ涥����Ϣ
	int tempW;       //wtemp�ݴ�Ȩֵ��Ϣ
	//Neighbors Neighbor;    //Neighbors����temp�����ݴ�data���ڽӶ�����Ϣ
	LinkNode<Vertex>* vp1, * vp2;   //vp2�洢���ҵĶ���λ��
	LinkNode<Edge>* ep;    //ep���ڴ洢������ڽӶ���λ��
	vp1 = getVertex(key);
	if (!vp1)//vp1Ϊ�մ����㲻����
	{
		cout << "���㲻����" << endl;
		exit(0);
	}    
	while (ep = vp1->data.edgList.GetNext())   //��ep��Ϊ�գ�������δ��ĩβ����������
	{
		vp2 = ep->data.next_v;
		tempV = vp2->data.data;
		tempW = ep->data.weight;             //��ö�����Ϣ
		Neighbor.neighborList.Insert(tempV);//����
		Neighbor.weightList.Insert(tempW);//����
	}
	vp1->data.edgList.ResetCurrent();   //����ָ��
	return &Neighbor;
}

//���һ����
bool Graphic::addEdge(int& v1, int& v2, int weight,bool tag)
{
	if (isEdge(v1, v2))
	{
		MessageBox(NULL, _T("���Ѿ����ڲ���ʧ��"), _T("��ʾ"), MB_OK);
		return false;
		exit(0);
	}
	if (!isVertex(v1)) {
		addVertex(v1);
	}
	if (!isVertex(v2)) {
		addVertex(v2);
	}
	if (isVertex(v1) && isVertex(v2)) 
	{
		EHash  ehashNode; //��ϣ��
		LinkNode<Edge>* edgeNode1, * edgeNode2;
		LinkNode<Vertex>* pv1, *pv2; 
		Edge edge(NULL, weight, NULL);
		pv1 = getVertex(v1);//���v1��λ��
		edgeNode1 = pv1->data.edgList.Insert(edge);//v1�ı������м���ð��
		pv1->data.degree++;
		pv2 = getVertex(v2);  //���v2�Ķ���,���ص���hash���еĵ�ַ
		edgeNode1->data.next_v = pv2;  //ʹedge��next_vָ��ñߵ�һ������V2
		edgeNode2 = pv2->data.edgList.Insert(edge);//v2�ı��������ð��
		edgeNode2->data.next_v = pv1;  //�޸�edgeָ��ñߵ���һ������v1
		pv2->data.degree++;
		//ָ����һ���
		edgeNode1->data.part = edgeNode2;
		edgeNode2->data.part = edgeNode1; 
		//hash���м���ñ�
		ehashNode.v[0] = v1;  //�󶥵�
		ehashNode.v[1] = v2;   //�Ҷ���
		if (tag==false) {
			KEY.Insert1(v1, v2, ehashNode);
		}
		int key = findkey(v1, v2);
		ehashNode.key = key;
		ehashNode.p_e = edgeNode2;  //ָ����Ӧ���ڽӱ�
		ehash.Insert(key, ehashNode); //�ڹ�ϣ�߱��в�����
		//��tagΪTrueʱ�����޸�KEY�е�����
		numofEdge++;
		return true;
	}
	return false;
}

//ɾ��һ����
bool Graphic::removeEdge(int& v1, int& v2)
{
	LinkNode<Edge>* epart1, * epart2;    //�߽�����etemp1��etemp2�����ݴ���λ��
	LinkNode<Vertex>* vtemp1, * vtemp2;   //���������vtemp1��vtemp2�����ݴ涥��λ��
	epart1 = getEdge(v1, v2);        //ȡ�����1λ��
	if (!epart1)
		return false;    //�߽��ΪNULL��߲����ڣ�����false
	epart2 = epart1->data.part;    //etemp2�洢�ñ߽�����һ���
	if (epart2)
	{
		vtemp1 = epart2->data.next_v;    //�洢���1�����Ķ���1��λ�ã��ɰ��2ָ��
		vtemp2 = epart1->data.next_v;    //�洢���2�����Ķ���2��λ�ã��ɰ��1ָ��
		vtemp1->data.edgList.Remove(epart1);   //����v1���������Ƴ��ñ�
		vtemp1->data.degree--;//����һ�Ķȼ�һ
		vtemp2->data.edgList.Remove(epart2);   //����v2���������Ƴ��ñ�
		vtemp2->data.degree--;//������Ķȼ�һ
	}
	else
	{
		vtemp1 = epart1->data.next_v;       //�洢��1�����Ķ���1��λ��
		vtemp1->data.edgList.Remove(epart1);   //ֱ���Ƴ��ñ�
		vtemp1->data.degree -= 2;
	}
	////�ڹ�ϣ����ɾ���ñ�
	EHash e(v1, v2);
	ehash.Remove(e);
	KEY.Remove(e);
	numofEdge--;
	return true;
}

//�ж��Ƿ��б�
bool Graphic::isEdge(int& v1, int& v2)
{
	return (getEdge(v1, v2) == NULL) ? false : true;  //�жϷ��ص��Ƿ�Ϊ�գ�Ϊ�շ���false�����򷵻�ture
}

//��Ȩֵ
int Graphic::weight(int& v1, int& v2)
{
	if (v1 == v2)return 0;
	int key = findkey(v1, v2);
	LinkNode<Edge>* etemp;  //�ݴ�߽��λ��
	if (key == INT_MAX) {
		return key;
	}
	etemp = getEdge(v1, v2);
	if (!etemp)
		return INT_MAX;    //�����ڱߣ�ȨֵΪ�����
	else
		return etemp->data.weight;
}

//����һ��λ��
bool Graphic::updateVerPos()
{
	if (!vList.IsEmpty())
	{
		LinkNode<Vertex>* cur;  //��������ı���ָ��
		cur = vList.head->rLink;
		int pos = 0;    //λ�ñ���
		while (cur != NULL)
		{
			cur->data.locat = pos;
			pos++;
			cur = cur->rLink;
		}
		IsEdited = false;
		return true;
	}
	return false;
}

//���ظõ��ڶ��������λ��
int Graphic::getVerPos(int& key)//���չؼ������
{
	if (IsEdited)
		updateVerPos();
	VHash vhashNode;   //reΪ���صĹ�ϣ����
	LinkNode<Vertex>* cur;
	vhash.Search(key, vhashNode);
	cur = vhashNode.p_v;
	return cur->data.locat;
}

//���¶���ģ����֣��ؼ���
bool Graphic::updateVertex(int& key, int& newkey)
{
	//�޸�hash���е�����
	LinkNode<Vertex>* vtemp = getVertex(key);    //��øö����λ��
	VHash vhashNode1(key), vhashNode2(newkey);
	vhash.Remove(vhashNode1);//ɾ��ԭ��������
	vhashNode2.p_v = vtemp;
	vhash.Insert(newkey,vhashNode2);
	//�޸ı������е�����
	if (!vtemp)
		return false;
	vtemp->data.data = newkey;
	return true;
}

//���±ߵ�Ȩֵ
bool Graphic::updateEdge(int& v1, int& v2,int newweight)
{
	//�޸�hash���е�����
	LinkNode<Edge>* etemp = getEdge(v1,v2);    //��øñߵ�λ��
	if (!etemp)
		return false; 
	etemp->data.weight = newweight;    //����
	etemp = etemp->data.part;    //�ֵܱ߸���
	if (etemp)
		etemp->data.weight = newweight;
	return true;
}

//��ȡ�ھ�����
int Graphic::getneighborCount(int& v)
{
	int count=0;
	LinkNode<Vertex>* vp;   //vp1�洢���ҵĶ���λ��
	LinkNode<Edge>* ep;    //ep���ڴ洢������ڽӶ���λ��
	vp = getVertex(v);
	if (!vp)
	{
		MessageBox(NULL, _T("���㲻����"), _T("��ʾ"), MB_OK);
		return false;
	}    //vp1Ϊ�մ����㲻����
	while (vp->data.edgList.GetNext())   //��ep��Ϊ�գ�������δ��ĩβ����������
	{
		count++;
	}
	vp->data.edgList.ResetCurrent();
	return count;
}
