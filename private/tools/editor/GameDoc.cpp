
// gameDoc.cpp : implementation of the CGameDoc class
//

#include "stdafx.h"
#include "editor.h"

#include "GameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
END_MESSAGE_MAP()


// CGameDoc construction/destruction

CGameDoc::CGameDoc()
{
	// TODO: add one-time construction code here

}

CGameDoc::~CGameDoc()
{
}

BOOL CGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGameDoc diagnostics

#ifdef _DEBUG
void CGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDoc commands
