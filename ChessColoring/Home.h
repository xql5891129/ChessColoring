#pragma once
#include "Button.h"

// home 对话框

class Home : public CDialogEx
{
	DECLARE_DYNAMIC(Home)

public:
	Home(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Home();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Home_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	CFont m_font;
	CStatic m_static;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	virtual BOOL OnInitDialog();
	
	COwerButton bt1;
	COwerButton bt2;
	COwerButton bt3;
	COwerButton bt4;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
