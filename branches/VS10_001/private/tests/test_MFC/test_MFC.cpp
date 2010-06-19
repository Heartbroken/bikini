// test_MFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "test_MFC.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "test_MFCDoc.h"
#include "test_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest_MFCApp

BEGIN_MESSAGE_MAP(Ctest_MFCApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Ctest_MFCApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Ctest_MFCApp construction

Ctest_MFCApp::Ctest_MFCApp() :
	m_update_task(*this, &Ctest_MFCApp::update)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Ctest_MFCApp object

Ctest_MFCApp theApp;


// Ctest_MFCApp initialization

BOOL Ctest_MFCApp::InitInstance()
{
	m_run = true;
	m_update_task.run();

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_TEXT("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_test_MFCTYPE,
		RUNTIME_CLASS(Ctest_MFCDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(Ctest_MFCView));
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

	return TRUE;
}

void Ctest_MFCApp::update() {
	bk::thread::flag l_event(false, false, "video_update");
	m_video.create(true);
	bk::ticker l_ticker(1.f / 30.f);
	bk::rbig l_time = bk::sys_time();
	l_event.set();
	while(m_run) {
		l_event.wait();
		m_video.update(bk::sys_time() - l_time);
		l_time = bk::sys_time();
		l_ticker.sync();
		l_event.set();
	}
	l_event.wait();
	m_video.destroy();
	l_event.set();
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
void Ctest_MFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// Ctest_MFCApp message handlers


BOOL Ctest_MFCApp::OnIdle(LONG lCount)
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::OnIdle(lCount);
	//return TRUE;
}

int Ctest_MFCApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	m_run = false;
	m_update_task.wait();

	return CWinApp::ExitInstance();
}
