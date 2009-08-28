// test_MFCView.cpp : implementation of the Ctest_MFCView class
//

#include "stdafx.h"
#include "test_MFC.h"

#include "test_MFCDoc.h"
#include "test_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest_MFCView

IMPLEMENT_DYNCREATE(Ctest_MFCView, CView)

BEGIN_MESSAGE_MAP(Ctest_MFCView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// Ctest_MFCView construction/destruction

Ctest_MFCView::Ctest_MFCView() :
	m_update_task(*this, &Ctest_MFCView::update)
{
	// TODO: add construction code here

}

Ctest_MFCView::~Ctest_MFCView()
{
}

BOOL Ctest_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctest_MFCView drawing

void Ctest_MFCView::OnDraw(CDC* /*pDC*/)
{
	Ctest_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Ctest_MFCView diagnostics

#ifdef _DEBUG
void Ctest_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void Ctest_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctest_MFCDoc* Ctest_MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctest_MFCDoc)));
	return (Ctest_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Ctest_MFCView message handlers

int Ctest_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//if(!m_window.create(m_hWnd)) return -1;
	m_run = true;
	m_update_task.run();

	return 0;
}

void Ctest_MFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void Ctest_MFCView::OnDestroy()
{
	m_run = false;
	m_update_task.wait();

	CView::OnDestroy();

	// TODO: Add your message handler code here
	//m_window.destroy();
}

void Ctest_MFCView::update() {
	bk::thread::flag l_event(false, false, "video_update");
	bk::window l_window(theApp.m_video);
	l_window.create(m_hWnd);
	bk::gui l_gui;
	l_gui.create("");
	bk::rbig l_time = bk::sys_time();
	while(m_run) {
		l_event.wait();
		bk::real l_dt = bk::sys_time() - l_time;
		l_time = bk::sys_time();
		l_window.update(l_dt);
		l_gui.update(l_dt);
		l_gui.render(l_window);
		l_window.present();
		l_event.set();
	}
	l_event.wait();
	l_gui.destroy();
	l_window.destroy();
	l_event.set();
}

void Ctest_MFCView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
}

void Ctest_MFCView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
}

BOOL Ctest_MFCView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}
