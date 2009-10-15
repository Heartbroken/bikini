
#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "editor.h"

#include "GameDoc.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClassView::CClassView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	// Load images:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillClassView();

	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::FillClassView()
{

	// Delete items and their data
	HTREEITEM hDeleteItem = m_wndClassView.GetChildItem(TVI_ROOT);
	while (hDeleteItem)
	{
		HTREEITEM hNextItem = m_wndClassView.GetNextItem(hDeleteItem, TVGN_CHILD);

		if (hNextItem == NULL)
		{
			hNextItem = m_wndClassView.GetNextItem(hDeleteItem, TVGN_NEXT);
			if (hNextItem == NULL) hNextItem = m_wndClassView.GetNextItem(hDeleteItem, TVGN_PARENT);

			GUID &l_GUID = *(GUID*)m_wndClassView.GetItemData(hDeleteItem);
			m_wndClassView.SetItemData(hDeleteItem, NULL);
			if (&l_GUID) delete &l_GUID;

			m_wndClassView.DeleteItem(hDeleteItem);
		}

		hDeleteItem = hNextItem;
	}

	// Fill the tree with new items
	if (theGameDoc != NULL)
	{
		pugi::xml_document &l_document = theGameDoc->m_document;

		pugi::xml_node l_game_node = l_document.child("game");

		GUID l_game_GUID = bk::scan_GUID(l_game_node.attribute("GUID").value());
		bk::wstring l_game_name = bk::utf8(l_game_node.find_child_by_attribute("property", "name", "Name").attribute("value").value());
		//l_game_name = bk::format(L"Game '%s'", l_game_name.c_str());

		//bk::wstring l_game_name = bk::format(L"Game '%s'", bk::utf8(l_game_node.attribute("name").value()));
		//GUID l_game_GUID = bk::scan_GUID(l_game_node.attribute("GUID").value());

		HTREEITEM hGame = m_wndClassView.InsertItem(l_game_name.c_str(), 0, 0);
		m_wndClassView.SetItemData(hGame, (DWORD_PTR) new GUID(l_game_GUID));
		//m_wndClassView.SetItemState(hGame, TVIS_BOLD, TVIS_BOLD);

		struct _l { static void AddChildren(CViewTree &_tree, HTREEITEM _hFolder, pugi::xml_node _folder)
		{
			for (pugi::xml_node l_child = _folder.first_child(); l_child; l_child = l_child.next_sibling())
			{
				bk::wstring l_type = bk::utf8(l_child.name());

				if (l_type == L"property") continue;

				GUID l_GUID = bk::scan_GUID(l_child.attribute("GUID").value());
				bk::wstring l_name = bk::utf8(l_child.find_child_by_attribute("property", "name", "Name").attribute("value").value());

				if (l_type == L"folder")
				{
					HTREEITEM hFolder = _tree.InsertItem(l_name.c_str(), 2, 2, _hFolder);
					_tree.SetItemData(hFolder, (DWORD_PTR) new GUID(l_GUID));
					AddChildren(_tree, hFolder, l_child);
				}
				else if (l_type == L"stage")
				{
					HTREEITEM hStage = _tree.InsertItem(l_name.c_str(), 3, 3, _hFolder);
					_tree.SetItemData(hStage, (DWORD_PTR) new GUID(l_GUID));
				}
			}
		}};

		_l::AddChildren(m_wndClassView, hGame, l_game_node);

		//HTREEITEM hFolder = hGame;

		//for (pugi::xml_node l_stage_node = l_game_node.child(); l_stage_node; l_stage_node = l_stage_node.next_sibling())
		//{
		//	bk::wstring l_type = bk::utf8(l_stage_node.name());
		//	bk::wstring l_name = bk::utf8(l_stage_node.attribute("name").value());

		//	if (l_folder != l_last_folder)
		//	{
		//		hFolder = m_wndClassView.InsertItem(l_folder.c_str(), 2, 2, hGame);
		//		l_last_folder = l_folder;
		//	}

		//	m_wndClassView.InsertItem(l_name.c_str(), 3, 3, hFolder);
		//}

		//for (bk::uint i = 0, s = theGameDoc->m_stages.size(); i < s; ++i)
		//{
		//	const CGameDoc::stage &l_stage = theGameDoc->m_stages[i];

		//	if (l_folder != l_stage.folder)
		//	{
		//		hFolder = m_wndClassView.InsertItem(l_stage.folder.c_str(), 2, 2, hGame);
		//		l_folder = l_stage.folder;
		//	}

		//	m_wndClassView.InsertItem(l_stage.name.c_str(), 3, 3, hFolder);
		//}

		m_wndClassView.Expand(hGame, TVE_EXPAND);
		m_wndClassView.SelectItem(hGame);
	}

	//HTREEITEM hFolder;

	//hFolder = m_wndClassView.InsertItem(_T("Levels"), 2, 2, hGame);

	//hFolder = m_wndClassView.InsertItem(_T("Menus"), 2, 2, hGame);

	//hFolder = m_wndClassView.InsertItem(_T("Resources"), 2, 2, hGame);

	//m_wndClassView.Expand(hGame, TVE_EXPAND);

	//HTREEITEM hRoot = m_wndClassView.InsertItem(_T("Game 'game1'"), 0, 0);
	//m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	//HTREEITEM hClass = m_wndClassView.InsertItem(_T("CFakeAboutDlg"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAboutDlg()"), 3, 3, hClass);

	//m_wndClassView.Expand(hRoot, TVE_EXPAND);

	//hClass = m_wndClassView.InsertItem(_T("CFakeApp"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeApp()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("InitInstance()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("OnAppAbout()"), 3, 3, hClass);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppDoc"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppDoc()"), 4, 4, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppDoc()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("OnNewDocument()"), 3, 3, hClass);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppView"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppView()"), 4, 4, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppView()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("GetDocument()"), 3, 3, hClass);
	//m_wndClassView.Expand(hClass, TVE_EXPAND);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppFrame"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppFrame()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppFrame()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("m_wndMenuBar"), 6, 6, hClass);
	//m_wndClassView.InsertItem(_T("m_wndToolBar"), 6, 6, hClass);
	//m_wndClassView.InsertItem(_T("m_wndStatusBar"), 6, 6, hClass);

	//hClass = m_wndClassView.InsertItem(_T("Globals"), 2, 2, hRoot);
	//m_wndClassView.InsertItem(_T("theFakeApp"), 5, 5, hClass);
	//m_wndClassView.Expand(hClass, TVE_EXPAND);
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CClassView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}

void CClassView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}

void CClassView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}

void CClassView::OnClassProperties()
{
	// TODO: Add your command handler code here
}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("New Folder..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}

void CClassView::Clear()
{
	m_wndClassView.DeleteAllItems();
}

//void CClassView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
//	ASSERT_VALID(pWndTree);
//
//	if (pWnd != pWndTree)
//	{
//		CDockablePane::OnContextMenu(pWnd, point);
//		return;
//	}
//
//	if (point != CPoint(-1, -1))
//	{
//		// Select clicked item:
//		CPoint ptTree = point;
//		pWndTree->ScreenToClient(&ptTree);
//
//		UINT flags = 0;
//		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
//		if (hTreeItem != NULL)
//		{
//			const GUID &l_GUID = *(GUID*)pWndTree->GetItemData(hTreeItem);
//			if (&l_GUID != 0)
//			{
//			}
//		}
//	}
//
//	CDockablePane::OnLButtonUp(nFlags, point);
//}

BOOL CClassView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint point;
	LPNMTREEVIEW tv = (LPNMTREEVIEW)lParam;
	switch (tv->hdr.code)
	{
		case TVN_SELCHANGED :
		{
			if (theGameDoc)
			{
				theGameDoc->SetSelectedNode(bk::bad_GUID);

				HTREEITEM hSelectedItem = tv->itemNew.hItem;//m_wndClassView.GetNextItem(TVI_ROOT, TVGN_CARET);
				if (hSelectedItem == NULL) break;

				const GUID &l_GUID = *(GUID*)m_wndClassView.GetItemData(hSelectedItem);
				if (&l_GUID == 0) break;

				theGameDoc->SetSelectedNode(l_GUID);
			}
			break;
		}
		//case TVN_SELCHANGED:
		//	if ( tv->action == TVC_UNKNOWN )
		//	OnSelchanged(( NMHDR *)lParam, pResult );
		//	break;

		//case TVN_BEGINDRAG:
		//	OnBegindrag(( NMHDR *)lParam, pResult );
		//	break;
	}


	return CDockablePane::OnNotify(wParam, lParam, pResult);
}
