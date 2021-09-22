// hhh3.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "hhh3.h"
#include "afxdialogex.h"
#include"MFCApplication1Dlg.h"
#include<string>
// hhh3 对话框

IMPLEMENT_DYNAMIC(hhh3, CDialogEx)

hhh3::hhh3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, V1(0)
	, V2(0)
	, mindist(0)
	, minPath(_T(""))
	, V3(0)
	, Raidus(0)
	, count(0)
	, allsecnic(_T(""))
{

}

hhh3::~hhh3()
{
}

void hhh3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, V1);
	DDX_Text(pDX, IDC_EDIT2, V2);
	DDX_Text(pDX, IDC_EDIT3, mindist);
	DDX_Text(pDX, IDC_EDIT4, minPath);
	DDX_Text(pDX, IDC_EDIT5, V3);
	DDX_Text(pDX, IDC_EDIT6, Raidus);
	DDX_Text(pDX, IDC_EDIT8, count);
	DDX_Text(pDX, IDC_EDIT7, allsecnic);
}


BEGIN_MESSAGE_MAP(hhh3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &hhh3::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &hhh3::OnBnClickedButton2)
END_MESSAGE_MAP()


// hhh3 消息处理程序


void hhh3::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	minPath = "";
	LinkList<int> list;
	int n = G.vertexCount();
	int *v = new int[n];
	G.getVertices(v);
	FindPath(G, V1, V2, mindist, list,v,n);
	int temp;    //暂存结点
	CString cstr(_T(""));
	minPath.Format(_T("%d\r\n"), V1);
	string str("->");
	CString cs;
	cs = str.c_str();
	while (list.GetNext(temp)) {//有问题
		cstr.Format(_T("%s%d\r\n"),cs,v[temp]);
		minPath += cstr;
	}
	list.ResetCurrent();
	delete[] v;
	UpdateData(FALSE);
}


void hhh3::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	count = 0;
	allsecnic = "";
	LinkList<int> list;
	LinkList<int> listd;
	SearchSurrSecnic(G, V3, Raidus, list, listd,count);
	int temp, distance;;    //暂存结点
	CString cstr(_T(""));
	allsecnic.Format(_T("%d"), V1);
	string str(" ");
	CString cs;
	cs = str.c_str();
	while (list.GetNext(temp)) {
		listd.GetNext(distance);
		cstr.Format(_T("%s%d%s%s%d\r\n"), cs,temp,cs,cs,distance);
		allsecnic += cstr;
	}
	list.ResetCurrent();
	listd.ResetCurrent();
	UpdateData(FALSE);
}
