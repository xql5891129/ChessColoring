#pragma once
#include "Button.h"

// Bishop 对话框

class Bishop : public CDialogEx
{
	DECLARE_DYNAMIC(Bishop)

public:
	Bishop(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Bishop();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Bishop_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int n;
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
	COwerButton bt1;
	COwerButton bt2;
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic m_static1;
	CStatic m_static2;
	CStatic m_static3;
	CStatic m_static4;
	CEdit m_edit1;
	CStatic m_static5;
	CEdit m_edit2;
	void Draw(int n, CDC* pdc);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int min_color;
	CProgressCtrl m_progress;
	CStatic m_static6;
};
