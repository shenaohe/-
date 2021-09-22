// hhh.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "hhh.h"
#include "afxdialogex.h"
#include"MFCApplication1Dlg.h"
// hhh 对话框

IMPLEMENT_DYNAMIC(hhh, CDialogEx)

hhh::hhh(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, addsec(0)
	, oldv(0)
	, newv(0)
	, V1(0)
	, V2(0)
	, weight(0)
{

}

hhh::~hhh()
{
}

void hhh::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, addsec);
	DDX_Text(pDX, IDC_EDIT2, oldv);
	DDX_Text(pDX, IDC_EDIT3, newv);
	DDX_Text(pDX, IDC_EDIT4, V1);
	DDX_Text(pDX, IDC_EDIT5, V2);
	DDX_Text(pDX, IDC_EDIT6, weight);
}


BEGIN_MESSAGE_MAP(hhh, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &hhh::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &hhh::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &hhh::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &hhh::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &hhh::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &hhh::OnBnClickedButton2)
END_MESSAGE_MAP()


// hhh 消息处理程序


void hhh::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	AddSecnic(G, addsec);
}


void hhh::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ReSecnic(G, oldv, newv);
	oldv = newv = 0;
	UpdateData(FALSE);
}


void hhh::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	AddRoad(G, V1, V2, weight);
	V1 = V2 = weight = 0;
	UpdateData(FALSE);
}


void hhh::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ReRoad(G, V1, V2,weight);
	V1 = V2 = weight = 0;
	UpdateData(FALSE);
}


void hhh::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DeleRoad(G, V1, V2);
	V1 = V2 = 0;
	UpdateData(FALSE);
}


void hhh::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DeleteSecnic(G, addsec);
	addsec = 0;
	UpdateData(FALSE);
}
