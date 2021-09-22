// hhh1.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "hhh1.h"
#include "afxdialogex.h"
#include"MFCApplication1Dlg.h"

// hhh1 对话框

IMPLEMENT_DYNAMIC(hhh1, CDialogEx)

hhh1::hhh1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, numV(0)
	, numE(0)
	, V1(0)
	, V2(0)
	, weight(0)
	, v3(0)
	, Yes_no(_T(""))
	, surroundNum(0)
	, allsurroundV(_T(""))
{
	numV = G.vertexCount();
	numE = G.edgeCount();
}

hhh1::~hhh1()
{
}

void hhh1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, numV);
	DDX_Text(pDX, IDC_EDIT2, numE);
	DDX_Text(pDX, IDC_EDIT4, V1);
	DDX_Text(pDX, IDC_EDIT5, V2);
	DDX_Text(pDX, IDC_EDIT3, weight);
	DDX_Text(pDX, IDC_EDIT6, v3);
	DDX_Text(pDX, IDC_EDIT8, Yes_no);
	DDX_Text(pDX, IDC_EDIT7, surroundNum);
	DDX_Text(pDX, IDC_EDIT9, allsurroundV);
}


BEGIN_MESSAGE_MAP(hhh1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &hhh1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &hhh1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &hhh1::OnBnClickedButton3)
END_MESSAGE_MAP()


// hhh1 消息处理程序


void hhh1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (G.isEdge(V1, V2) ){
		MessageBox(_T("v1与v2之间有边"));
		return;
	}
	else {
		MessageBox(_T("v1与v2之间没有边"));
		return;
	}
}


void hhh1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	weight = G.weight(V1, V2);
	UpdateData(FALSE);
}


void hhh1::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	allsurroundV = "";
	if (G.isVertex(v3)) {
		Yes_no.Format(_T("是"));
	}
	else {
		Yes_no.Format(_T("否"));
	}
	surroundNum = G.getneighborCount(v3);
	Neighbors* a;
	Neighbors b;
	a=G.getNeighbors1(v3,b);
	int xv;
	CString cstr(_T(""));
	while (a->neighborList.GetNext(xv)) {//有问题
		cstr.Format(_T("%d\r\n"),xv);
		allsurroundV += cstr;
	}
	a->neighborList.ResetCurrent();
	UpdateData(FALSE);
}
