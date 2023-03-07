// King.cpp: 实现文件
//

#include "pch.h"
#include "ChessColoring.h"
#include "King.h"
#include "afxdialogex.h"

//定义CFont对象操作字体
CFont king_staticFont1, king_staticFont2, king_staticFont3, king_staticFont4, king_staticFont5, king_staticFont6, king_editFont1, king_editFont2;
// King 对话框

IMPLEMENT_DYNAMIC(King, CDialogEx)

King::King(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_King_DIALOG, pParent)
    , n(0)
    , min_color(0)
{

}

King::~King()
{
    //释放CFont对象
    king_staticFont1.DeleteObject();
    king_staticFont2.DeleteObject();
    king_staticFont3.DeleteObject();
    king_staticFont4.DeleteObject();
    king_staticFont5.DeleteObject();
    king_staticFont6.DeleteObject();
    king_editFont1.DeleteObject();
    king_editFont2.DeleteObject();
}

void King::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, n);
    DDX_Control(pDX, IDC_SPIN2, m_Spin);
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


BEGIN_MESSAGE_MAP(King, CDialogEx)
    ON_WM_PAINT()
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &King::OnDeltaposSpin2)
    ON_BN_CLICKED(IDC_BUTTON1, &King::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &King::OnBnClickedButton2)
END_MESSAGE_MAP()


// King 消息处理程序


BOOL King::OnInitDialog()
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

    king_staticFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_static1.SetFont(&king_staticFont1, true);
    king_staticFont3.CreatePointFont(120, _T("仿宋"), NULL);
    m_static3.SetFont(&king_staticFont3, true);
    king_staticFont5.CreatePointFont(120, _T("仿宋"), NULL);
    m_static5.SetFont(&king_staticFont5, true);
    king_staticFont6.CreatePointFont(120, _T("仿宋"), NULL);
    m_static6.SetFont(&king_staticFont6, true);
    king_staticFont2.CreatePointFont(250, _T("仿宋"), NULL);
    m_static2.SetFont(&king_staticFont2, true);
    king_staticFont4.CreatePointFont(150, _T("楷体"), NULL);
    m_static4.SetFont(&king_staticFont4, true);
    m_static4.SetWindowText(_T("国王威胁周围一圈的棋格。考虑一个 2 x 2 的棋盘，左下角有一个国王。因为这样的国王会威胁到棋盘上所有剩余的方格。因此，需要 4 种颜色才能为 2 x 2 板着色。要为 N x N 棋盘着色，我们可以将其视为由 2 x 2 棋盘组成，并且使用相同的配色方案为每个 2 x 2 棋盘着色，将确保相同颜色的方块上没有两个国王相互威胁。因此，国王的颜色数量为4。"));
    king_editFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit1.SetFont(&king_editFont1, true);
    king_editFont2.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit2.SetFont(&king_editFont2, true);

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


void King::OnPaint()//绘制棋盘
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CDialogEx::OnPaint()

    CDC* pdc;
    pdc = GetDC();
    Draw(n, pdc);
}

void King::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)//spin控件响应函数
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






void King::Draw(int n, CDC* pdc)//绘制边长为n的棋盘
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


void King::OnBnClickedButton1()//绘制棋盘事件
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


void King::OnBnClickedButton2()
{
    min_color = 0;//将使用颜色种类初始化为0
    CDC* pdc;
    pdc = GetDC();
    //定义着色所需的颜色
    int color[12][3] = { {204,0,51},{0,51,153},{255,255,0},{0,51,0},{255,255,204},{204,255,255},{102,51,0},{204,153,204},{0,204,0},{255,204,153},{112,128,144},{60,179,113} };
    //开始染色
    //要为 N x N 棋盘着色，我们可以将其视为由 2 x 2 棋盘组成，
    //并且使用相同的配色方案为每个 2 x 2 棋盘着色，将确保相同颜色的方块上没有两个国王相互威胁
    if(n % 2 == 0)//偶数棋盘格直接为每个2×2棋盘着色
    {
        int num = n * n / 4, nn = 1;//这两个变量用于控制进度条的增长

        for (int i = 0; i < n; i = i + 2)
        {
            for (int j = 0; j < n; j = j + 2)
            {
                //为2×2的小棋盘格着色
                for (int x = 0; x < 2; x++)
                {
                    for (int y = 0; y < 2; y++)
                    {
                        CBrush brush(RGB(color[x + y][0], color[x + y][1], color[x + y][2]));
                        CRect rc(100 + 30 * (j + y), 100 + (i + x) * 30, 100 + 30 + 30 * (j + y), 100 + 30 + (i + x) * 30);
                        pdc->FillRect(rc, &brush);
                        Sleep(80);
                    }
                }

                //进度条增加
                m_progress.SetPos(100 / num * nn);
                CString str;
                str.Format(_T("%d%%"), 100 / num * nn); //百分比
                (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
                nn++;
            }
        }
    }
    else//如果不是偶数，最后一列和最后一行单独着色
    {
        int num = n * n / 4, nn = 1;//这两个变量用于控制进度条的增长

        for (int i = 0; i < n - 1; i = i + 2)
        {
            for (int j = 0; j < n - 1; j = j + 2)
            {
                //为2×2的小棋盘格着色
                for (int x = 0; x < 2; x++)
                {
                    for (int y = 0; y < 2; y++)
                    {
                        CBrush brush(RGB(color[x + y][0], color[x + y][1], color[x + y][2]));
                        CRect rc(100 + 30 * (j + y), 100 + (i + x) * 30, 100 + 30 + 30 * (j + y), 100 + 30 + (i + x) * 30);
                        pdc->FillRect(rc, &brush);
                        Sleep(80);
                    }
                }
                //进度条增加
                m_progress.SetPos(100 / num * nn);
                CString str;
                str.Format(_T("%d%%"), 100 / num * nn); //百分比
                (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
                nn++;
            }
        }
        //为最后一行着色
        for (int y = 0; y < n; y = y + 2)
        {
            CBrush brush(RGB(color[0][0], color[0][1], color[0][2]));
            CRect rc(100 + 30 * y, 100 +  (n - 1) * 30, 100 + 30 + 30 *  y, 100 + 30 + ( n - 1) * 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        }
        for (int y = 1; y < n; y = y + 2)
        {
            CBrush brush(RGB(color[1][0], color[1][1], color[1][2]));
            CRect rc(100 + 30 * (y), 100 + (n - 1) * 30, 100 + 30 + 30 * (y), 100 + 30 + (n - 1) * 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        }
        //为最后一列着色
        for (int x = 0; x < n; x = x + 2)
        {
            CBrush brush(RGB(color[0][0], color[0][1], color[0][2]));
            CRect rc(100 + 30 * (n - 1), 100 + (x) * 30, 100 + 30 + 30 * (n - 1), 100 + 30 + (x) * 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        }
        for (int x = 1; x < n; x = x + 2)
        {
            CBrush brush(RGB(color[1][0], color[1][1], color[1][2]));
            CRect rc(100 + 30 * (n - 1), 100 + (x) * 30, 100 + 30 + 30 * (n - 1), 100 + 30 + (x) * 30);
            pdc->FillRect(rc, &brush);
            Sleep(80);
        }

       
    }
    
    //涂色完成，进度条增至100%
    m_progress.SetPos(100);
    CString str;
    str.Format(_T("%d%%"), 100); //百分比
    (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
    min_color = 4;//国王棋盘使用的最少颜色数量为4。
    UpdateData(false);
    CString temp = _T("");
    temp.Format(_T("染色完成！使用颜色种类：%d"), min_color);
    MessageBox(temp);
}