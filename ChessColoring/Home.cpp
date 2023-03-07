// home.cpp: 实现文件
//

#include "pch.h"
#include "ChessColoring.h"
#include "Home.h"
#include "afxdialogex.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"

// home 对话框

IMPLEMENT_DYNAMIC(Home, CDialogEx)

Home::Home(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Home_DIALOG, pParent)
{

}

Home::~Home()
{
}

void Home::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, bt1);
	DDX_Control(pDX, IDC_BUTTON2, bt2);
	DDX_Control(pDX, IDC_BUTTON3, bt3);
	DDX_Control(pDX, IDC_BUTTON4, bt4);
}


BOOL Home::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 
	//设置静态文本框的字体格式
	m_static.SubclassDlgItem(IDC_STATIC1, this);
	m_font.CreatePointFont(180, _T("楷体"));
	m_static.SetFont(&m_font);
	m_static.SetWindowText(_T("问题说明：对于以下每个棋子，找到为 N x N 棋盘着色所需的最小颜色数，这样放置在相同颜色的两个棋盘格子上的一对棋子都不会相互威胁。骑士、主教、国王、车的威胁范围如下图"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// home 消息处理程序
BEGIN_MESSAGE_MAP(Home, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Home::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Home::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Home::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Home::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &Home::OnBnClickedButton6)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void Home::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//打开骑士棋盘
	Knight knight;
	knight.DoModal();
}


void Home::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//打开主教棋盘
	Bishop bishop;
	bishop.DoModal();
}


void Home::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//打开国王棋盘
	King king;
	king.DoModal();
}


void Home::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//打开车棋盘
	Rook rook;
	rook.DoModal();
}


void Home::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}





HBRUSH Home::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(135, 206, 235));//修改静态文本字体颜色
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}




