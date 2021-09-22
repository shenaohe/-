#pragma once


// hhh 对话框

class hhh : public CDialogEx
{
	DECLARE_DYNAMIC(hhh)

public:
	hhh(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~hhh();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int addsec;
	afx_msg void OnBnClickedButton1();
private:
	int oldv;
	int newv;	
public:
	afx_msg void OnBnClickedButton3();
private:
	int V1;
public:
	int V2;
private:
	// 边的权值
	int weight;
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton2();
};
