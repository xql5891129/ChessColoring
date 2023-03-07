#include "pch.h"
#include "Button.h"
IMPLEMENT_DYNAMIC(COwerButton, CButton)

COwerButton::COwerButton()
{
	m_bgColor = RGB(39, 58, 91);
	m_textColor = RGB(255, 255, 255);
	m_bPressed = FALSE;
	SwitchDlgMouseMoveState = 0;
}

COwerButton::~COwerButton()
{
}


BEGIN_MESSAGE_MAP(COwerButton, CButton)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()



// COwerButton 消息处理程序

void COwerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString btnCaption = L"";
	//设置标题
	CFont font;
	CWnd* pItemCWnd = FromHandle(lpDrawItemStruct->hwndItem);
	pItemCWnd->GetWindowText(btnCaption);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect drawRect;
	CBrush pBrush;
	CRect rect = lpDrawItemStruct->rcItem;//空间选择
	//获得绘图DC
	//得到原Button的矩形大小
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	//绘制控件框架 
	pDC->DrawFrameControl(&drawRect, DFC_BUTTON, lpDrawItemStruct->CtlType);

	if (ODS_SELECTED & lpDrawItemStruct->itemState)
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"黑体");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(102, 204, 255));
	}
	else if (SwitchDlgMouseMoveState == 1)
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"黑体");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(30, 144, 255));
	}
	else
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"黑体");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(39, 58, 91));
	}
	//画矩形 
	pDC->FillRect(drawRect, &pBrush);

	//定义一个CRect用于绘制文本 
	CRect textRect;
	//拷贝矩形区域 
	textRect.CopyRect(&drawRect);
	//获得字符串尺寸
	CSize sz = pDC->GetTextExtent(btnCaption);
	//调整文本位置 居中 
	textRect.top += (textRect.Height() - sz.cy) / 2;
	//设置文本背景透明 
	pDC->SetBkMode(TRANSPARENT);
	//设置文本颜色
	pDC->SetTextColor(RGB(255, 255, 255));
	//绘制文本内容
	pDC->DrawText(btnCaption, &textRect, DT_RIGHT | DT_CENTER | DT_BOTTOM);
}

//设置按钮背景的颜色 
void COwerButton::SetButtonBgColor(COLORREF color)
{
	m_bgColor = color;
}

//设置按钮字体的颜色
void COwerButton::SetButtonTextColor(COLORREF color)
{
	m_textColor = color;
}

void COwerButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		SwitchDlgMouseMoveState = 1;
		// 重画按钮
		Invalidate(TRUE);
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	CButton::OnMouseMove(nFlags, point);
}

LRESULT COwerButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	SwitchDlgMouseMoveState = 0;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

