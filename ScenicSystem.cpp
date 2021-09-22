#include"pch.h"
#include"ScenicSystem.h"
//克鲁斯卡尔算法
int Kruskal(Graphic& G, MinSpantree& MST, int V[]) {
	MSTEdgeNode ed; int count, u, v, w;//边结点辅助变量
	int sum_w = 0;   //记录总权值
	int n = G.vertexCount();  //获得顶点数
	int m = G.edgeCount();   //获得边的个数
	MinHeap<MSTEdgeNode>H(m); //最小堆
	UFSets F(n); //并查集
	//建立初始最小堆
	for (int i = 0; i < n; i++)
	{
		Neighbors a; int k = 0;
		G.getNeighbors(V[i], a);//获取当前顶点的邻居
		//获取当前邻接顶点的顶点表
		while (a.neighborList.GetNext(k)) {
			a.weightList.GetNext(w);
			ed.tail = i;
			ed.head = k;
			ed.key = w;
			H.Insert(ed);  //插入堆
		}
		a.weightList.ResetCurrent();
		a.neighborList.ResetCurrent();
	}
	count = 1;   //最小生成树加入边数计数
	while (count < n)  
	{
		H.RemoveMin(ed);   //从堆中退出最小权值的边
		u = F.Find(ed.tail);
		v = F.Find(ed.head);  
		if (u != v)
		{
			F.Union(u, v);  //合并
			MST.Insert(ed);  //该边存入最小生成树
			sum_w += ed.key;   //更新总权值
			count++;
		}
	}
	return sum_w;
}

//迪杰斯特拉算法
bool Dijkstra(Graphic& G, int dist[], int path[], int v[], int startV, int maxValue = INT_MAX,int end = 0) {
	int startpos, endpos, n = G.vertexCount();    //startpos为起始点在顶点数组中的位置，endpos为终点在顶点数组中的位置
	int w;    //暂存储权值
	int top;//顶
	EHash  ehash;
	MinHeap<EHash> HE(n);
	MinHeap<int> H(n);//最小堆存储点的序号，堆顶是从当前点到这个点距离最小的点
	bool* S = new bool[n];      //判断是否为终点的数组
	if (!G.isVertex(startV))     //判断起始点是否为图中的点
		return false;
	if (end == 0)        //当end为默认值
	{
		endpos = -1;    //寻找起点到所有点的最短路径
		startpos = G.getVerPos(startV);   //找起点位置
	}
	else {
		if (!G.isVertex(end))    //当有终点时，判读终点是否在图内
			return false;
		startpos = G.getVerPos(startV);   //找起点位置
		endpos = G.getVerPos(end);   //找终点位置
		ehash.v[0] = startpos;
		ehash.v[1] = startpos;
		ehash.key = G.weight(startV, end);
	}
	for (int i = 0; i < n; i++)    //初始化
	{
		S[i] = false;      
		dist[i] = INT_MAX;
		path[i] = -1;
	}
	H.Insert(startpos); dist[startpos] = 0;
	HE.Insert(ehash);//最小边的生成树堆
	int k = 0;
	while (!HE.IsEmpty()) {//如果堆非空
		Neighbors a;//辅助变量
		HE.RemoveMin1(top);//拿到最小值
		int u = top;
		if (S[u]) {//已经访问过的不在访问
			continue;
		}
		if (endpos != -1 && S[endpos])
			return true;
		S[u] = true;//将最小边标记为访问过
		G.getNeighbors(v[u], a);//获取当前邻接顶点的顶点表
		while (a.neighborList.GetNext(k)) {
			a.weightList.GetNext(w);//对应取得权值
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k])//没有被访问过且经过k可以缩短距离    
			{
				dist[k] = dist[u] + w;//更新最短距离
				path[k] = u;//记录顶点
				EHash  ehash1(u,k,dist[k]);//构造一个新边       
				HE.Insert(ehash1);//插入最小堆
			}
		}
		a.weightList.ResetCurrent();//重置
		a.neighborList.ResetCurrent();
	}
	return true;
}

//输出最短路径
void OutputPath(Graphic& G, int dist[], int path[], int v[], int start, int end,int &alldist,LinkList<int>&list)
{
	int n = G.vertexCount();
	int endpos;   //终点在数组中的位置
	endpos = G.getVerPos(end);
	int curpos = endpos;
	while (!(v[curpos] == start) && path[curpos] != -1)    //反向查找
	{
		list.InsertData(curpos);
		curpos = path[curpos];
	}
	alldist = dist[endpos];
}

//求解给定一系列顶点的最小生成树
void Kru_knownV(Graphic& G, MinSpantree& MST, int& distance, int V[], int n)  //v1为输入点的数组，n为点的个数,distance记录最终生成树的长度
{
	MSTEdgeNode ed; int u, v, count;  //边结点
	int m = n * (n - 1) / 2;  //最大边数
	int sum_n = G.vertexCount();
	int* dist = new int[sum_n];  //距离
	int* v_all = new int[sum_n];//全部顶点数组
	int* path = new int[sum_n]; //路径
	G.getVertices(v_all);
	int end = 0; 
	MinHeap<MSTEdgeNode>H(m);  //最小堆
	UFSets F(n);   //并查集
	for (u = 0; u < n; u++) {
		for (v = u+1; v < n; v++)
		{
				Dijkstra(G, dist, path, v_all,V[u], intmax, V[v]);   //找两点之间最短路径
				end = G.getVerPos(V[v]);//判断
				if (dist[end]!=INT_MAX)
				{
					ed.tail = u;
					ed.head = v;
					ed.key = dist[end];
					H.Insert(ed);   //将该边插入堆中
				}
		}
	}
	count = 1;    //最小生成树边数计数
	while (count < n)    
	{
		H.RemoveMin(ed);   //从最小堆中退出具有最小权值的边ed
		u = F.Find(ed.tail);
		v = F.Find(ed.head);    //取两顶点集合的边
		if (u != v)      //不是同一集合说明不连通
		{
			F.Union(u, v);   //合并连通
			MST.Insert(ed);  //该边存入最小生成树
			distance += ed.key;//最短距离长度
			count++;
		}
	}
	delete[] dist;
	delete[] path;
	delete[] v_all;
}

//查询所有景点
void SearchSecnic(Graphic& G,int *v )    //查询所有景点
{
	int n = G.vertexCount();
	int num = 1;
	v = G.getVertices();//包含所有顶点的数组
}

//查询某顶点一定范围内的所有景点
void SearchSurrSecnic(Graphic& G, int curSecnic, int surround, LinkList<int>& list,LinkList<int> &listd,int &numv){
	int n = G.vertexCount();
	int* dist = new int[n];//距离数组
	int* path = new int[n];//景点数组
	int* v = new int[n];   //为求范围内景点开辟数组
	v = G.getVertices();
	if (!G.isVertex(curSecnic))
	{
		MessageBox(NULL, _T("图中没有景点"), _T("提示"), MB_OK);
		return;
	}
	Dijkstra(G, dist, path, v, curSecnic, surround);   //查询以当前点为中心，一定范围内的所有景点
	//输出景点信息
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

//两顶点的之间的最短路径
void FindPath(Graphic& G,int curSecnic,int endSecnic,int&alldist, LinkList<int> &list,int v[],int n)   //查询路径
{
	int* dist = new int[n];
	int* path = new int[n];
	if (!G.isVertex(curSecnic))
	{
		MessageBox(NULL, _T("图中没有景点1"), _T("提示"), MB_OK);
		return;
	}
	if (!G.isVertex(endSecnic))
	{
		MessageBox(NULL, _T("图中没有景点2"), _T("提示"), MB_OK);
		return;
	}
	Dijkstra(G, dist, path, v, curSecnic, intmax, endSecnic);   //查询两点间最短路径
	OutputPath(G, dist, path, v, curSecnic, endSecnic,alldist,list);    //输出路径
	delete[] dist;  
	delete[] path;
}

//查询一系列顶点的最小生成树
void SearchsSetSecnic(Graphic& G, int num, int* visitSecnic, int& distance, int (*a)[3])
{
	MinSpantree mst(num);
	Kru_knownV(G, mst, distance, visitSecnic, num);
	MSTEdgeNode* tree = new MSTEdgeNode[num];   //用于获得各个景点的道路
	bool tag = mst.getTree(tree);
	if (!tag) {
		MessageBox(NULL, _T("景点之间不连通啊"), _T("提示"), MB_OK);
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

//添加一个景点
void AddSecnic(Graphic& G, int name)   //增加景点
{
	if (G.isVertex(name))
	{
		MessageBox(NULL, _T("顶点已经存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.addVertex(name))
		MessageBox(NULL, _T("顶点插入成功"), _T("提示"), MB_OK);
	else
	{
		MessageBox(NULL, _T("顶点插入失败"), _T("提示"), MB_OK);
		exit(0);
	}
}

//删除一个景点
void DeleteSecnic(Graphic& G,int name )    //删除景点
{
	if (!G.isVertex(name))
	{
		MessageBox(NULL, _T("景点不存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.removeVertex(name))
		MessageBox(NULL, _T("删除成功"), _T("提示"), MB_OK);
	else {
		MessageBox(NULL, _T("删除失败"), _T("提示"), MB_OK);
		return;
	}
}

//修改一个景点
void ReSecnic(Graphic& G,int oldname,int newname)   //修改景点
{
	if (!G.isVertex(oldname))
	{
		MessageBox(NULL, _T("旧顶点不存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.updateVertex(oldname, newname))
		MessageBox(NULL, _T("修改成功"), _T("提示"), MB_OK);
	else
	{
		MessageBox(NULL, _T("修改失败"), _T("提示"), MB_OK);
		exit(1);
	}
}

//增加一条路
void AddRoad(Graphic& G,int start,int end,int weight)    //增加道路
{
	if (G.isEdge(start, end))
	{
		MessageBox(NULL, _T("道路已经存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.addEdge(start, end, weight, false))
		MessageBox(NULL, _T("新建成功"), _T("提示"), MB_OK);
	else
	{
		MessageBox(NULL, _T("新建失败"), _T("提示"), MB_OK);
		return;
	}
}

//删除一条路
void DeleRoad(Graphic& G, int start, int end)    //删除道路
{
	if (!G.isEdge(start, end))
	{
		MessageBox(NULL, _T("道路不存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.removeEdge(start, end))
		MessageBox(NULL, _T("删除成功"), _T("提示"), MB_OK);
	else {
		MessageBox(NULL, _T("删除失败"), _T("提示"), MB_OK);
		return;
	}
}

//修改道路
void ReRoad(Graphic& G, int start, int end, int weight)    //更新道路
{
	if (!G.isEdge(start, end))
	{
		MessageBox(NULL, _T("道路不存在"), _T("提示"), MB_OK);
		return;
	}
	if (G.updateEdge(start, end, weight)) {
		MessageBox(NULL, _T("更新成功"), _T("提示"), MB_OK);
	}
	else {
		MessageBox(NULL, _T("更新失败"), _T("提示"), MB_OK);
		return;
	}
}

