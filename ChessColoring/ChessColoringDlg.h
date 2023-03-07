
// ChessColoringDlg.h: 头文件
//
#pragma once
#include "Button.h"

// CChessColoringDlg 对话框
class CChessColoringDlg : public CDialogEx
{
// 构造
public:
	CChessColoringDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHESSCOLORING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
//	CBrush m_normalBrush;
//	CPen m_Pen;
//	CBrush m_activeBrush;
public:
	COwerButton bt1;
	COwerButton bt2;
	afx_msg void OnBnClickedCancel();
};
