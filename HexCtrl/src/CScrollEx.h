/****************************************************************************************
* Copyright (C) 2018-2019, Jovibor: https://github.com/jovibor/						    *
* This code is available under the "MIT License modified with The Commons Clause"		*
* Scroll bar control class for MFC apps.												*
* The main creation purpose of this control is the innate 32-bit range limitation		*
* of the standard Windows' scrollbars.													*
* This control works with unsigned long long data representation and thus can operate	*
* with numbers in full 64-bit range.													*
****************************************************************************************/
#pragma once
#include <afxwin.h>

namespace HEXCTRL {
	namespace SCROLLEX {
		//Forward declaration.
		enum class ENSTATE : DWORD;

		class CScrollEx : public CWnd
		{
		public:
			CScrollEx() {}
			~CScrollEx() {}
			bool Create(CWnd* pWnd, int iScrollType, ULONGLONG ullScrolline, ULONGLONG ullScrollPage, ULONGLONG ullScrollSizeMax);
			void AddSibling(CScrollEx* pSibling);
			bool IsVisible()const;
			CWnd* GetParent()const;
			void SetScrollSizes(ULONGLONG ullScrolline, ULONGLONG ullScrollPage, ULONGLONG ullScrollSizeMax);
			ULONGLONG SetScrollPos(ULONGLONG);
			void ScrollLineUp();
			void ScrollLineDown();
			void ScrollLineLeft();
			void ScrollLineRight();
			void ScrollPageUp();
			void ScrollPageDown();
			void ScrollPageLeft();
			void ScrollPageRight();
			void ScrollHome();
			void ScrollEnd();
			ULONGLONG GetScrollPos()const;
			LONGLONG GetScrollPosDelta()const;
			ULONGLONG GetScrollLineSize()const;
			ULONGLONG GetScrollPageSize()const;
			void SetScrollPageSize(ULONGLONG ullSize);
			BOOL OnNcActivate(BOOL bActive)const;
			void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
			void OnNcPaint()const;
			void OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
			void OnMouseMove(UINT nFlags, CPoint point);
			void OnLButtonUp(UINT nFlags, CPoint point);
		protected:
			DECLARE_MESSAGE_MAP()
			void DrawScrollBar()const;
			void DrawArrows(CDC* pDC)const;
			void DrawThumb(CDC* pDC)const;
			CRect GetScrollRect(bool fWithNCArea = false)const;			//Scroll's whole rect.
			CRect GetScrollWorkAreaRect(bool fClientCoord = false)const;//Rect without arrows.
			UINT GetScrollSizeWH()const;								//Scroll size in pixels, width or height.
			UINT GetScrollWorkAreaSizeWH()const;						//Scroll size (WH) without arrows.
			CRect GetThumbRect(bool fClientCoord = false)const;
			UINT GetThumbSizeWH()const;
			UINT GetThumbPos()const;
			void SetThumbPos(int iPos);
			long double GetThumbScrollingSize()const;
			CRect GetFirstArrowRect(bool fClientCoord = false)const;
			CRect GetLastArrowRect(bool fClientCoord = false)const;
			CRect GetFirstChannelRect(bool fClientCoord = false)const;
			CRect GetLastChannelRect(bool fClientCoord = false)const;
			CRect GetParentRect(bool fClient = true)const;
			int GetTopDelta()const;	//Difference between parent window's Window and Client area. Very important in hit testing.
			int GetLeftDelta()const;
			bool IsVert()const;
			bool IsThumbDragging()const;
			bool IsSiblingVisible()const;
			void SendParentScrollMsg()const;
			afx_msg void OnTimer(UINT_PTR nIDEvent);
		protected:
			CWnd* m_pwndParent { };
			CScrollEx* m_pSibling { };
			UINT m_uiScrollBarSizeWH { };
			int m_iScrollType { };
			ENSTATE m_enState { };
			const COLORREF m_clrBkNC { GetSysColor(COLOR_3DFACE) };
			const COLORREF m_clrBkScrollBar { RGB(241, 241, 241) };
			const COLORREF m_clrThumb { RGB(192, 192, 192) };
			CPoint m_ptCursorCur { };
			ULONGLONG m_ullScrollPosCur { 0 };
			ULONGLONG m_ullScrollPosPrev { };
			ULONGLONG m_ullScrollLine { };
			ULONGLONG m_ullScrollPage { };
			ULONGLONG m_ullScrollSizeMax { };
			const unsigned m_uiThumbSizeMin { 15 };
			const int m_iTimerFirstClick { 200 };
			const int m_iTimerRepeat { 50 };
			CBitmap m_bmpArrows;
			const unsigned m_uiFirstArrowOffset { 0 };
			const unsigned m_uiLastArrowOffset { 18 };
			const unsigned m_uiArrowSize { 17 };
			bool m_fCreated { false };						//Is created or not.
			bool m_fVisible { false };						//Is visible at the moment or not.
		};
	};
};