#pragma once


// hhh3 对话框

class hhh3 : public CDialogEx
{
	DECLARE_DYNAMIC(hhh3)

public:
	hhh3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~hhh3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int V1;
	int V2;
	int mindist;
	CString minPath;
public:
	afx_msg void OnBnClickedButton1();
private:
	int V3;
	int Raidus;
	int count;
	CString allsecnic;
public:
	afx_msg void OnBnClickedButton2();
};
