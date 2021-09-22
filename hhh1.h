#pragma once


// hhh1 对话框

class hhh1 : public CDialogEx
{
	DECLARE_DYNAMIC(hhh1)

public:
	hhh1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~hhh1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int numV;
	int numE;
	int V1;
	int V2;
public:
	afx_msg void OnBnClickedButton2();
private:
	int weight;
public:
	afx_msg void OnBnClickedButton1();
private:
	int v3;
	CString Yes_no;
	int surroundNum;
public:
	afx_msg void OnBnClickedButton3();
private:
	CString allsurroundV;
};
