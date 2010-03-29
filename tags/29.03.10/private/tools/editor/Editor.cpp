
// editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "editor.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "GameDoc.h"
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorApp

BEGIN_MESSAGE_MAP(CEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CEditorApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CEditorApp construction

CEditorApp::CEditorApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CEditorApp object

CEditorApp theApp;


// CEditorApp initialization

BOOL CEditorApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("bikini-iii"));
	LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_gameTYPE,
		RUNTIME_CLASS(CGameDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGameView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// bikini
	bk::thread::set_thread_name(GetCurrentThreadId(), "bikini-iii main");
	m_video.create();
	m_time = bk::sys_time();

	return TRUE;
}

BOOL CEditorApp::OnIdle(LONG lCount)
{
	// TODO: Add your specialized code here and/or call the base class
	update_video();

	return CWinAppEx::OnIdle(lCount);
}

//int CEditorApp::Run()
//{
//	bool l_run = true;
//	while (l_run)
//	{
//		MSG l_message;
//		while (PeekMessage(&l_message, NULL, 0U, 0U, PM_REMOVE)) {
//			if (l_message.message == WM_QUIT)
//			{
//				l_run = false;
//				break;
//			}
//			if (!PreTranslateMessage(&l_message))
//			{
//				TranslateMessage(&l_message);
//				DispatchMessage(&l_message);
//			}
//		}
//		if (l_run)
//		{
//			update_video();
//			//m_ticker.sync();
//		}
//	}
//
//	return 0;
//}

int CEditorApp::ExitInstance()
{
	// bikini
	m_video.destroy();

	return CWinAppEx::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEditorApp customization load/save methods

void CEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CEditorApp::LoadCustomState()
{
}

void CEditorApp::SaveCustomState()
{
}

// CEditorApp message handlers


// bikini

bk::video& CEditorApp::get_video()
{
	return m_video;
}
void CEditorApp::update_video()
{
	bk::rbig l_time = bk::sys_time();
	bk::real l_dt = bk::real(l_time - m_time);
	if (l_dt > (1.0/60.0))
	{
		m_video.update(l_dt);
		m_time = l_time;
		//theApp.console_output(L"Update\n");
	}
}

void CEditorApp::console_output(const bk::wstring &_string)
{
	CMainFrame &l_mainframe = *(CMainFrame*)GetMainWnd();
	l_mainframe.console_output(_string);
}

