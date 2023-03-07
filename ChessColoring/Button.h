#pragma once
#include <afxwin.h>
class COwerButton :
	public CButton
{
	DECLARE_DYNAMIC(COwerButton)
public:
	COwerButton();
	virtual ~COwerButton();
	void SetButtonBgColor(COLORREF color);
	void SetButtonTextColor(COLORREF color);
	int SwitchDlgMouseMoveState;

private:
	COLORREF m_bgColor;
	COLORREF m_textColor;
	COLORREF m_DownColor;
	BOOL m_bPressed;

protected:
	DECLARE_MESSAGE_MAP()
	BOOL m_bTracking; //在鼠标按下没有释放时该值为true
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
};


