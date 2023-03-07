// Knight.cpp: 实现文件
//

#include "pch.h"
#include "ChessColoring.h"
#include "Knight.h"
#include "afxdialogex.h"
#include "knightType.h"
//定义CFont对象操作字体

CFont knight_staticFont1, knight_staticFont2, knight_staticFont3, knight_staticFont4, knight_staticFont5, knight_staticFont6, knight_editFont1, knight_editFont2;
// Rook 对话框

IMPLEMENT_DYNAMIC(Knight, CDialogEx)

Knight::Knight(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_Knight_DIALOG, pParent)
    , n(0)
    , min_color(0)
{

}

Knight::~Knight()
{
    //释放CFont对象
    knight_staticFont1.DeleteObject();
    knight_staticFont2.DeleteObject();
    knight_staticFont3.DeleteObject();
    knight_staticFont4.DeleteObject();
    knight_staticFont5.DeleteObject();
    knight_staticFont6.DeleteObject();
    knight_editFont1.DeleteObject();
    knight_editFont2.DeleteObject();
}

void Knight::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(Knight, CDialogEx)
    ON_WM_PAINT()
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &Knight::OnDeltaposSpin2)
    ON_BN_CLICKED(IDC_BUTTON1, &Knight::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &Knight::OnBnClickedButton2)
END_MESSAGE_MAP()


// Rook 消息处理程序


BOOL Knight::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    // 初始化为编辑框的边长n值赋初始值
    n = 9;
    UpdateData(false);

    //初始化绑定spin控件与edit控件
    m_Spin.SetBuddy(GetDlgItem(n));
    m_Spin.SetRange(5, 12);

    //设置静态文本框的字体格式

    knight_staticFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_static1.SetFont(&knight_staticFont1, true);
    knight_staticFont3.CreatePointFont(120, _T("仿宋"), NULL);
    m_static3.SetFont(&knight_staticFont3, true);
    knight_staticFont5.CreatePointFont(120, _T("仿宋"), NULL);
    m_static5.SetFont(&knight_staticFont5, true);
    knight_staticFont6.CreatePointFont(120, _T("仿宋"), NULL);
    m_static6.SetFont(&knight_staticFont6, true);
    knight_staticFont2.CreatePointFont(250, _T("仿宋"), NULL);
    m_static2.SetFont(&knight_staticFont2, true);
    knight_staticFont4.CreatePointFont(150, _T("楷体"), NULL);
    m_static4.SetFont(&knight_staticFont4, true);
    m_static4.SetWindowText(_T("棋盘中的骑士威胁任何水平两个正方形和垂直一个正方形的正方形，或垂直两个正方形和水平两个正方形的正方形。因此，对于骑士来说，当N > 2 时最小颜色数是2。当N = 2最小颜色数是1，因为没有两个骑士可以在这么小的棋盘上互相威胁。"));
    knight_editFont1.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit1.SetFont(&knight_editFont1, true);
    knight_editFont2.CreatePointFont(120, _T("仿宋"), NULL);
    m_edit2.SetFont(&knight_editFont2, true);

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


void Knight::OnPaint()//绘制棋盘
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CDialogEx::OnPaint()

    CDC* pdc;
    pdc = GetDC();
    Draw(n, pdc);
}

void Knight::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)//spin控件响应函数
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
    if (ss >= 5 && ss <= 12) //限制边长n在2-12之间
    {
        n = ss;
        UpdateData(false);
    }
    else
    {
        AfxMessageBox(_T("请将边长n设置在5-12之间！"));
    }

    *pResult = 0;
}






void Knight::Draw(int n, CDC* pdc)//绘制边长为n的棋盘
{
    //绘制棋盘
    CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
    CPen* pOldpen = pdc->SelectObject(&pen);//获取指针
    int Ox = 100;
    int Oy = 100;
    int numx = n;//行数
    int numy = n;//列数
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


void Knight::OnBnClickedButton1()//绘制棋盘事件
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


void Knight::OnBnClickedButton2()
{
    min_color = 0;//将使用颜色种类初始化为0
    CDC* pdc;
    pdc = GetDC();
    //定义着色所需的颜色
    int color[12][3] = { {204,0,51},{0,51,153},{255,255,0},{0,51,0},{255,255,204},{204,255,255},{102,51,0},{204,153,204},{0,204,0},{255,204,153},{112,128,144},{60,179,113} };
    //开始染色
    //对于骑士棋盘来说，当 N > 2时最小颜色数是2，当N = 2时最小颜色数是1，因为没有两个骑士可以在这么小的棋盘上互相威胁。
    //所以我们可以利用骑士游历算法来涂色
    //骑士游历算法即用骑士走完整个棋盘且不重复
    //我们只需在骑士游历过程中切换2种颜色即可
    knightType* tour =new knightType(n);//初始化knightType对象
    if (tour->knightTour(0, 0))//以(左上角为起点开始执行骑士遍历)
    {
        for (int k = 1; k <= n*n; k++)
        {
            //找到序号为k的坐标位置
            int x=tour->outputx(k);
            int y=tour->outputy(k);
            //绘图
            CBrush brush(RGB(color[k%2][0], color[k % 2][1], color[k % 2][2]));
            CRect rc(100 + 30 * y, 100 + x * 30, 100 + 30 + 30 * y, 100 + 30 + x * 30);
            pdc->FillRect(rc, &brush);
            min_color = 2;
            Sleep(80);

            //进度条增加
            m_progress.SetPos(100 / n /n* k);
            CString str;
            str.Format(_T("%d%%"), 100 / n / n * k); //百分比
            (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
        }  
    }
    //涂色完成，进度条增至100%
    m_progress.SetPos(100);
    CString str;
    str.Format(_T("%d%%"), 100); //百分比
    (GetDlgItem(IDC_STATIC6))->SetWindowText(str);
    UpdateData(false);
    CString temp = _T("");
    temp.Format(_T("染色完成！使用颜色种类：%d"), min_color);
    MessageBox(temp);

}
