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



// COwerButton ��Ϣ�������

void COwerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString btnCaption = L"";
	//���ñ���
	CFont font;
	CWnd* pItemCWnd = FromHandle(lpDrawItemStruct->hwndItem);
	pItemCWnd->GetWindowText(btnCaption);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect drawRect;
	CBrush pBrush;
	CRect rect = lpDrawItemStruct->rcItem;//�ռ�ѡ��
	//��û�ͼDC
	//�õ�ԭButton�ľ��δ�С
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	//���ƿؼ���� 
	pDC->DrawFrameControl(&drawRect, DFC_BUTTON, lpDrawItemStruct->CtlType);

	if (ODS_SELECTED & lpDrawItemStruct->itemState)
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"����");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(102, 204, 255));
	}
	else if (SwitchDlgMouseMoveState == 1)
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"����");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(30, 144, 255));
	}
	else
	{
		font.CreateFontW(0, 0, 0, 0, 400, NULL, NULL, NULL, DEFAULT_CHARSET, 0, 0, 0, 0, L"����");
		pDC->SelectObject(&font);
		pBrush.CreateSolidBrush(RGB(39, 58, 91));
	}
	//������ 
	pDC->FillRect(drawRect, &pBrush);

	//����һ��CRect���ڻ����ı� 
	CRect textRect;
	//������������ 
	textRect.CopyRect(&drawRect);
	//����ַ����ߴ�
	CSize sz = pDC->GetTextExtent(btnCaption);
	//�����ı�λ�� ���� 
	textRect.top += (textRect.Height() - sz.cy) / 2;
	//�����ı�����͸�� 
	pDC->SetBkMode(TRANSPARENT);
	//�����ı���ɫ
	pDC->SetTextColor(RGB(255, 255, 255));
	//�����ı�����
	pDC->DrawText(btnCaption, &textRect, DT_RIGHT | DT_CENTER | DT_BOTTOM);
}

//���ð�ť��������ɫ 
void COwerButton::SetButtonBgColor(COLORREF color)
{
	m_bgColor = color;
}

//���ð�ť�������ɫ
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
		// �ػ���ť
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

