#include"pch.h"
#include"Graph.h"



//根据顶点关键码判断是否是顶点
LinkNode<Vertex>* Graphic::getVertex(int key)
{
	VHash temp;
	if (vhash.Search(key,temp))
		return temp.p_v;    //查找成功返回顶点结点位置
	else
		return NULL;   //失败返回NULL
}

//拿到一条边
LinkNode<Edge>* Graphic::getEdge(int& vertex1, int& vertex2)
{
	EHash temp; //存储哈希边表结点
	int key = findkey(vertex1, vertex2);
	if (ehash.Search(key, temp)!=NULL)
	{
		if ((temp.v[0] == vertex1 && temp.v[1] == vertex2)||(temp.v[0]==vertex2&&temp.v[1]==vertex1)) {
			return temp.p_e;  //成功返回该边在邻接链表中一个边结点的位置
		}
	}
	return NULL;  //失败返回NULL
}

//顶点的数量
int Graphic::vertexCount()
{
	return numofVertices;
}

//边的数量
int Graphic::edgeCount()
{
	return numofEdge;
}

//返回包含所有顶点的数组，存在int* vertex中
bool Graphic::getVertices(int* vertices)
{
	LinkNode<Vertex>* v;
	if (numofVertices != 0)
	{
		for (int i = 0; (v = vList.GetNext())!= NULL; i++)
		{
			vertices[i] = v->data.data;  //返回顶点的数据信息
		}
		vList.ResetCurrent();
		return true;
	}
	else 
		return false;
}

//返回包含所有顶点的数组，这是完全正确的代码段
int* Graphic::getVertices()
{
	LinkNode<Vertex>* v;
	int* vertexs=new int[100000];
	if (numofVertices != 0) {
		for (int i = 0; (v=vList.GetNext()) != NULL; i++) {
			vertexs[i] = v->data.data;
		}
		vList.ResetCurrent();//正确的函数
		return vertexs;
	}
	else return NULL;
}

//添加一个顶点
bool Graphic::addVertex(int& key)
{
	if (isVertex(key))//假如是顶点，插入失败
	{
		MessageBox(NULL, _T("顶点已经存在，插入失败"), _T("提示"), MB_OK);
		exit(1);
		return false;
	}      
	LinkNode<Vertex>* newNode;
	Vertex v(key);
	newNode = vList.Insert(v);//插入顶点列表,返回该顶点在顶点列表的位置
	VHash newHashNode(key, newNode);  //新建顶点哈希表节点
	if (!vhash.Insert(newHashNode.key, newHashNode))   //插入顶点hash表,插入失败返回false
	{
		MessageBox(NULL, _T("插入hash表失败"), _T("提示"), MB_OK);
		return false;
	}
	else//插入成功
	{
		IsEdited = true;//已经修改过了
		numofVertices++;//顶点数+1
		return true;
	}
}

//删除顶点
bool Graphic::removeVertex(int& key)
{
	if (isVertex(key)) {//如果是顶点
		IsEdited = true;
		LinkNode<Edge>* e1, * e2;  //待删除结点指针,遍历指针、过渡指针,与顶点关联的边
		LinkNode<Vertex>* v1, * v2;//在顶点列表中的指针
		EHash e;    //哈希表的边数据结构体，用于删除边
		v1 = getVertex(key);//cur_v1指向待删除的顶点
		int keye = 0;
		e1 = v1->data.edgList.GetNext();
		while (e1) //删除该顶点所有邻接顶点,cure1是一个半边
		{
			//构造一个边用于哈希表中删除
			v2 = e1->data.next_v;  //v2为该边另一顶点的位置
			keye = findkey(key,v2->data.data);   //顶点对的key  
			e.v[0] = key;//起点
			e.v[1] = v2->data.data;//终点
			e.key = keye;  
			KEY.Remove1(e);       
			ehash.Remove(e);    //删除哈希边,不做物理删除
			//删除另一半边
			e2 = e1->data.part;   //e2该边的另一半边
			if (e2)
			{
				v2->data.edgList.Remove(e2);//在v2邻接链表中删除相关边的另一半边
				v2->data.degree--;//v2的度减一
			}
			numofEdge--;
			e1 = v1->data.edgList.GetNext();
		}
		v1->data.edgList.ResetCurrent();
		VHash  temp(key);
		vhash.Remove(temp);  //删除哈希顶点表中信息为key的顶点
		vList.Remove(v1); //在顶点链表中删除该顶点
		numofVertices--;
		return true;
	}
	else {
		MessageBox(NULL, _T("错误"), _T("提示"), MB_OK);
		return false;
	}
}

//当前顶点的度
int Graphic::degree(int& key)
{
	LinkNode<Vertex>* temp;  //获得顶点结点位
	if (temp = getVertex(key))return temp->data.degree;  //返回度
	return -1;
}


//判断是否为顶点
bool Graphic::isVertex(int& key)
{
	VHash temp;
	if (vhash.Search(key, temp))
		return true;    //查找成功返回顶点结点位置
	else
		return NULL;   //失败返回NULL
}

//获取当前顶点的邻居
bool Graphic::getNeighbors(int& key, Neighbors& neighbor)
{
	int tempV;       //tempV暂存顶点信息
	int tempW;       //wtempW暂存权值信息
	LinkNode<Vertex>* vp1, * vp2;   //vp1存储查找的顶点位置
	LinkNode<Edge>* ep;    //ep用于存储顶点的邻接顶点位置
	vp1 = getVertex(key);
	if (!vp1)
	{
		cout << "顶点不存在" << endl;
		return false;
	}    //vp1为空代表顶点不存在
	while (ep = vp1->data.edgList.GetNext())   //当ep不为空，边链表未到末尾，继续遍历
	{
		vp2 = ep->data.next_v;
		tempV = vp2->data.locat;
		tempW = ep->data.weight;             //获得顶点信息
		neighbor.neighborList.Insert(tempV);//复制
		neighbor.weightList.Insert(tempW);//复制
	}
	vp1->data.edgList.ResetCurrent();
	return true;
}

//neighbor的另一种形式
Neighbors* Graphic::getNeighbors1(int v, Neighbors &Neighbor)
{
	int key = v;    //计算key值
	int tempV;       //vtemp暂存顶点信息
	int tempW;       //wtemp暂存权值信息
	//Neighbors Neighbor;    //Neighbors对象temp用于暂存data的邻接顶点信息
	LinkNode<Vertex>* vp1, * vp2;   //vp2存储查找的顶点位置
	LinkNode<Edge>* ep;    //ep用于存储顶点的邻接顶点位置
	vp1 = getVertex(key);
	if (!vp1)//vp1为空代表顶点不存在
	{
		cout << "顶点不存在" << endl;
		exit(0);
	}    
	while (ep = vp1->data.edgList.GetNext())   //当ep不为空，边链表未到末尾，继续遍历
	{
		vp2 = ep->data.next_v;
		tempV = vp2->data.data;
		tempW = ep->data.weight;             //获得顶点信息
		Neighbor.neighborList.Insert(tempV);//复制
		Neighbor.weightList.Insert(tempW);//复制
	}
	vp1->data.edgList.ResetCurrent();   //重置指针
	return &Neighbor;
}

//添加一条边
bool Graphic::addEdge(int& v1, int& v2, int weight,bool tag)
{
	if (isEdge(v1, v2))
	{
		MessageBox(NULL, _T("边已经存在插入失败"), _T("提示"), MB_OK);
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
		EHash  ehashNode; //哈希边
		LinkNode<Edge>* edgeNode1, * edgeNode2;
		LinkNode<Vertex>* pv1, *pv2; 
		Edge edge(NULL, weight, NULL);
		pv1 = getVertex(v1);//获得v1的位置
		edgeNode1 = pv1->data.edgList.Insert(edge);//v1的边链表中加入该半边
		pv1->data.degree++;
		pv2 = getVertex(v2);  //获得v2的顶点,返回的是hash表中的地址
		edgeNode1->data.next_v = pv2;  //使edge的next_v指向该边的一个顶点V2
		edgeNode2 = pv2->data.edgList.Insert(edge);//v2的边链表加入该半边
		edgeNode2->data.next_v = pv1;  //修改edge指向该边的另一个顶点v1
		pv2->data.degree++;
		//指向另一半边
		edgeNode1->data.part = edgeNode2;
		edgeNode2->data.part = edgeNode1; 
		//hash表中加入该边
		ehashNode.v[0] = v1;  //左顶点
		ehashNode.v[1] = v2;   //右顶点
		if (tag==false) {
			KEY.Insert1(v1, v2, ehashNode);
		}
		int key = findkey(v1, v2);
		ehashNode.key = key;
		ehashNode.p_e = edgeNode2;  //指向相应的邻接边
		ehash.Insert(key, ehashNode); //在哈希边表中插入结点
		//当tag为True时，不修改KEY中的内容
		numofEdge++;
		return true;
	}
	return false;
}

//删除一条边
bool Graphic::removeEdge(int& v1, int& v2)
{
	LinkNode<Edge>* epart1, * epart2;    //边结点变量etemp1和etemp2用于暂存半边位置
	LinkNode<Vertex>* vtemp1, * vtemp2;   //顶点结点变量vtemp1和vtemp2用于暂存顶点位置
	epart1 = getEdge(v1, v2);        //取出半边1位置
	if (!epart1)
		return false;    //边结点为NULL则边不存在，返回false
	epart2 = epart1->data.part;    //etemp2存储该边结点的另一半边
	if (epart2)
	{
		vtemp1 = epart2->data.next_v;    //存储半边1所属的顶点1的位置，由半边2指向
		vtemp2 = epart1->data.next_v;    //存储半边2所属的顶点2的位置，由半边1指向
		vtemp1->data.edgList.Remove(epart1);   //顶点v1边链表中移除该边
		vtemp1->data.degree--;//顶点一的度减一
		vtemp2->data.edgList.Remove(epart2);   //顶点v2边链表中移除该边
		vtemp2->data.degree--;//顶点二的度减一
	}
	else
	{
		vtemp1 = epart1->data.next_v;       //存储边1所属的顶点1的位置
		vtemp1->data.edgList.Remove(epart1);   //直接移除该边
		vtemp1->data.degree -= 2;
	}
	////在哈希表中删除该边
	EHash e(v1, v2);
	ehash.Remove(e);
	KEY.Remove(e);
	numofEdge--;
	return true;
}

//判断是否有边
bool Graphic::isEdge(int& v1, int& v2)
{
	return (getEdge(v1, v2) == NULL) ? false : true;  //判断返回的是否为空，为空返回false，否则返回ture
}

//求权值
int Graphic::weight(int& v1, int& v2)
{
	if (v1 == v2)return 0;
	int key = findkey(v1, v2);
	LinkNode<Edge>* etemp;  //暂存边结点位置
	if (key == INT_MAX) {
		return key;
	}
	etemp = getEdge(v1, v2);
	if (!etemp)
		return INT_MAX;    //不存在边，权值为无穷大
	else
		return etemp->data.weight;
}

//更新一下位置
bool Graphic::updateVerPos()
{
	if (!vList.IsEmpty())
	{
		LinkNode<Vertex>* cur;  //顶点链表的遍历指针
		cur = vList.head->rLink;
		int pos = 0;    //位置变量
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

//返回该点在顶点数组的位置
int Graphic::getVerPos(int& key)//按照关键码查找
{
	if (IsEdited)
		updateVerPos();
	VHash vhashNode;   //re为返回的哈希顶点
	LinkNode<Vertex>* cur;
	vhash.Search(key, vhashNode);
	cur = vhashNode.p_v;
	return cur->data.locat;
}

//更新顶点的（名字）关键码
bool Graphic::updateVertex(int& key, int& newkey)
{
	//修改hash表中的内容
	LinkNode<Vertex>* vtemp = getVertex(key);    //获得该顶点的位置
	VHash vhashNode1(key), vhashNode2(newkey);
	vhash.Remove(vhashNode1);//删除原来的内容
	vhashNode2.p_v = vtemp;
	vhash.Insert(newkey,vhashNode2);
	//修改边链表中的内容
	if (!vtemp)
		return false;
	vtemp->data.data = newkey;
	return true;
}

//更新边的权值
bool Graphic::updateEdge(int& v1, int& v2,int newweight)
{
	//修改hash表中的内容
	LinkNode<Edge>* etemp = getEdge(v1,v2);    //获得该边的位置
	if (!etemp)
		return false; 
	etemp->data.weight = newweight;    //更新
	etemp = etemp->data.part;    //兄弟边更新
	if (etemp)
		etemp->data.weight = newweight;
	return true;
}

//获取邻居数量
int Graphic::getneighborCount(int& v)
{
	int count=0;
	LinkNode<Vertex>* vp;   //vp1存储查找的顶点位置
	LinkNode<Edge>* ep;    //ep用于存储顶点的邻接顶点位置
	vp = getVertex(v);
	if (!vp)
	{
		MessageBox(NULL, _T("顶点不存在"), _T("提示"), MB_OK);
		return false;
	}    //vp1为空代表顶点不存在
	while (vp->data.edgList.GetNext())   //当ep不为空，边链表未到末尾，继续遍历
	{
		count++;
	}
	vp->data.edgList.ResetCurrent();
	return count;
}
