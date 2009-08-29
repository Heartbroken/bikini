
// editor.h : main header file for the editor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEditorApp:
// See editor.cpp for the implementation of this class
//

class CEditorApp : public CWinAppEx
{
public:
	CEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
//	virtual int Run();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

// bikini
public:
	bk::video& get_video();
	void update_video();
	void console_output(const bk::wstring &_string);

private:
	bk::video m_video;
	bk::real m_time;
public:
};

extern CEditorApp theApp;
