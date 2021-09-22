// Mysecnicsystem.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Mysecnicsystem.h"
#include "afxdialogex.h"


// Mysecnicsystem 对话框

IMPLEMENT_DYNAMIC(Mysecnicsystem, CDialogEx)

Mysecnicsystem::Mysecnicsystem(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{

}

Mysecnicsystem::~Mysecnicsystem()
{
}

void Mysecnicsystem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Mysecnicsystem, CDialogEx)
END_MESSAGE_MAP()


// Mysecnicsystem 消息处理程序
