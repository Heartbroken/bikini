
// GameView.cpp : implementation of the CGameView class
//

#include "stdafx.h"
#include "editor.h"

#include "GameDoc.h"
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CGameView construction/destruction

CGameView::CGameView()
{
	// TODO: add construction code here

}

CGameView::~CGameView()
{
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGameView drawing

void CGameView::OnDraw(CDC* /*pDC*/)
{
//	theApp.get_video().get_<bk::vo::window>(m_window_ID).set_invalid();

	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CGameView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGameView diagnostics

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameView message handlers

int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_window_ID = theApp.get_video().spawn(m_window_info, m_hWnd);

	//SetTimer(0, 10, NULL);

	return 0;
}

void CGameView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	theApp.get_video().kill(m_window_ID);
	m_window_ID = bk::bad_ID;
}

BOOL CGameView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
		case WM_TIMER :
		{
			//Invalidate(FALSE);
			break;
		}
		case WM_PAINT :
		{
			//theApp.update_video();
			//theApp.console_output(L"PAINT\n");
			break;
		}
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}

void CGameView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class
	//theApp.get_video().get_<bk::vo::window>(m_window_ID).set_active(bActivate == TRUE);

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
