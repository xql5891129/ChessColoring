// Bishop.cpp: 实现文件
//

#include "pch.h"
#include "ChessColoring.h"
#include "Bishop.h"
#include "afxdialogex.h"
//定义CFont对象操作字体
CFont bishop_staticFont1, bishop_staticFont2, bishop_staticFont3, bishop_staticFont4, bishop_staticFont5, bishop_staticFont6, bishop_editFont1, bishop_editFont2;
// Bishop 对话框

IMPLEMENT_DYNAMIC(Bishop, CDialogEx)

Bishop::Bishop(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Bishop_DIALOG, pParent)
	, n(0)
	, min_color(0)
{

}

Bishop::~Bishop()
{
	//释放CFont对象
    bishop_staticFont1.DeleteObject();
    bishop_staticFont2.DeleteObject();
    bishop_staticFont3.DeleteObject();
    bishop_staticFont4.DeleteObject();
    bishop_staticFont5.DeleteObject();
    bishop_staticFont6.DeleteObject();
    bishop_editFont1.DeleteObject();
    bishop_editFont2.DeleteObject();
}

void Bishop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN2, m_Spin);
	DDX_Text(pDX, IDC_EDIT1, n);
	DDX_Control(pDX, IDC_BUTTON1, bt1);
	DDX_Control(pDX, IDC_BUTTON2, bt2);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT2, min_color);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
}


BEGIN_MESSAGE_MAP(Bishop, CDialogEx)
    ON_WM_PAINT()
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &Bishop::OnDeltaposSpin2)
    ON_BN_CLICKED(IDC_BUTTON1, &Bishop::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &Bishop::OnBnClickedButton2)
END_MESSAGE_MAP()


BOOL Bishop::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    // 初始化为编辑框的边长n值赋初始值
    n = 9;
    UpdateData(false);

    //初始化绑定spin控件与edit控件
    m_Spin.SetBuddy(GetDlgItem(n));
    m_Spin.SetRange(2, 12);

    //设置静态文本框的字体格式

    bishop_staticFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_static1.SetFont(&bishop_staticFont1, true);
    bishop_staticFont3.CreatePointFont(120, _T("仿宋"), NULL);
    m_static3.SetFont(&bishop_staticFont3, true);
    bishop_staticFont5.CreatePointFont(120, _T("仿宋"), NULL);
    m_static5.SetFont(&bishop_staticFont5, true);
    bishop_staticFont6.CreatePointFont(120, _T("仿宋"), NULL);
    m_static6.SetFont(&bishop_staticFont6, true);
    bishop_staticFont2.CreatePointFont(250, _T("仿宋"), NULL);
    m_static2.SetFont(&bishop_staticFont2, true);
    bishop_staticFont4.CreatePointFont(150, _T("楷体"), NULL);
    m_static4.SetFont(&bishop_staticFont4, true);
    m_static4.SetWindowText(_T("棋盘中的主教是威胁同一对角线上任何正方形的人。现在，由于主对角线上有 N 个正方形，因此至少需要 N 种颜色来为对角线上的正方形着色，这样对角线上的主教就不会相互威胁。为了将这种颜色扩展到整个板，我们可以用与位于主对角线上的正方形相同的颜色为列或行着色。这样，所有的对角线都会有不同的颜色的方块，所以躺在两个同色正方形上的两个主教不会互相威胁。"));
    bishop_editFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit1.SetFont(&bishop_editFont1, true);
    bishop_editFont2.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit2.SetFont(&bishop_editFont2, true);

    //初始化进度条控件
    //设置进度条的范围
    m_progress.SetRange(0, 100);
    //设置进度条当前的位置
    m_progress.SetPos(0);
    //设置进度条每次步进的长度
    m_progress.SetStep(1);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void Bishop::OnPaint()//绘制棋盘
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CDialogEx::OnPaint()

    CDC* pdc;
    pdc = GetDC();
    Draw(n, pdc);
}

void Bishop::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)//spin控件响应函数
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(true);
    int ss;
    if (pNMUpDown->iDelta == -1) // 如果此值为-1 , 说明点击了Spin的往下的箭头
    {
        int a;
        a = n - 1;
        ss = a;
    }
    else if (pNMUpDown->iDelta == 1) // 如果此值为1, 说明点击了Spin的往上的箭头
    {
        int a;
        a = n + 1;
        ss = a;
    }
    if (ss >= 2 && ss <= 12) //限制边长n在2-12之间
    {
        n = ss;
        UpdateData(false);
    }
    else
    {
        AfxMessageBox(_T("请将边长n设置在2-12之间！"));
    }

    *pResult = 0;
}






void Bishop::Draw(int n, CDC* pdc)//绘制边长为n的棋盘
{
    //绘制棋盘
    CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
    CPen* pOldpen = pdc->SelectObject(&pen);//获取指针
    int Ox = 100;
    int Oy = 100;
    int numx = n;//行数
    int numy = n;//列数
    for (int i = 0; i <= numx; i++)//画列线
    {
        pdc->MoveTo(Ox + 30 * i, Oy);
        pdc->LineTo(Ox + 30 * i, 100 + 30 * n);
    }
    for (int j = 0; j <= numy; j++)//画行线
    {
        pdc->MoveTo(100, Oy + 30 * j);
        pdc->LineTo(100 + 30 * n, Oy + 30 * j);
    }
    //颜色填充
    CBrush brush1(RGB(0, 0, 0));
    for (int n = 0; n < numy; n = n + 2)
    {

        for (int m = 0; m < numx; m = m + 2)
        {
            CRect rc(Ox + 30 * m, Oy + n * 30, Ox + 30 + 30 * m, Oy + 30 + n * 30);
            pdc->FillRect(rc, &brush1);
        }
    }
    CBrush brush2(RGB(0, 0, 0));
    for (int p = 1; p <= numy - 1; p = p + 2)
    {
        for (int q = 1; q <= numx - 1; q = q + 2)
        {
            CRect rc(Ox + 30 * q, Oy + p * 30, Ox + 30 + 30 * q, Oy + 30 + p * 30);
            pdc->FillRect(rc, &brush2);

        }
    }
}


void Bishop::OnBnClickedButton1()//绘制棋盘事件
{
    // 清空绘制区域(若不清空旧棋盘依然存在)
    CRect rectDlg;
    GetClientRect(rectDlg);			// 获得窗体的大小
    int pointWidth = rectDlg.Width();		// 获取窗体宽度
    int pointHeight = rectDlg.Height();		// 获取窗体高度
    RedrawWindow(CRect(0, 0, pointWidth, pointHeight));

    //开始重绘
    OnPaint();
}


void Bishop::OnBnClickedButton2()
{
    min_color = 0;//将使用颜色种类初始化为0
    CDC* pdc;
    pdc = GetDC();
    //定义着色所需的颜色
    int color[12][3] = { {204,0,51},{0,51,153},{255,255,0},{0,51,0},{255,255,204},{204,255,255},{102,51,0},{204,153,204},{0,204,0},{255,204,153},{112,128,144},{60,179,113} };
    //开始染色
    //主教棋盘的威胁范围为斜线，对角线上的颜色必须不同，以颜色1、颜色2......颜色n以此斜着涂色
    for (int i = 0; i < n; i++) 
    {
        if (i > 0)
        {
            int x = i;
            int j = 0;
            for (int k = 0; k <= i; k++)
            { 
                CBrush brush(RGB(color[k][0], color[k][1], color[k][2]));
                CRect rc(100 + 30 * j, 100 + x * 30, 100 + 30 + 30 * j, 100 + 30 + x * 30);
                pdc->FillRect(rc, &brush);
                //若新用了一种颜色，则min_color记录加一
                (k > min_color) ? min_color = k : min_color = min_color;
                Sleep(80);
                x -= 1; j += 1;//向右上斜对角线移动
            }
        }
        else
        {
            //最左上角的格子直接用第一种颜色涂一次
            CBrush brush(RGB(color[0][0], color[0][1], color[0][2]));
            CRect rc(100, 100, 100 + 30, 100 + 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        } 
        //进度条增加
        m_progress.SetPos(100 / n * (i + 1)/2);
        CString str;
        str.Format(_T("%d%%"), 100 / n * (i + 1)/2); //百分比
        (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
    }
    for (int j = 1; j < n; j++)
    {
        if (j < n-1)
        {
            int x = n - 1;
            int y = j;
            for (int k = 0; k < n-j; k++)
            {
                
                CBrush brush(RGB(color[k][0], color[k][1], color[k][2]));
                CRect rc(100 + 30 * y, 100 + x * 30, 100 + 30 + 30 * y, 100 + 30 + x * 30);
                pdc->FillRect(rc, &brush);
                //若新用了一种颜色，则min_color记录加一
                (k > min_color) ? min_color = k : min_color = min_color;
                Sleep(80);
                x -= 1; y += 1;//向右上斜对角线移动
            }
        }
        else
        {
            //最右上角的格子直接用第一种颜色涂一次
            CBrush brush(RGB(color[0][0], color[0][1], color[0][2]));
            CRect rc(100 + 30 * (n-1), 100 + (n - 1) * 30, 100 + 30 + 30 * (n - 1), 100 + 30 + (n - 1) * 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        }
        //进度条增加
        m_progress.SetPos(50+100 / n * (j + 1)/2);
        CString str;
        str.Format(_T("%d%%"), 50 + 100 / n * (j + 1) / 2); //百分比
        (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
    }
    //涂色完成，进度条增至100%
    m_progress.SetPos(100);
    CString str;
    str.Format(_T("%d%%"), 100); //百分比
    (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
    min_color += 1;//由于颜色数组是从0开始，所以使用的颜色种类最后要+1
    UpdateData(false);
    CString temp = _T("");
    temp.Format(_T("染色完成！使用颜色种类：%d"), min_color);
    MessageBox(temp);;
}

