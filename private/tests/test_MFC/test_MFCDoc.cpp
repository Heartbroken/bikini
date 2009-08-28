// test_MFCDoc.cpp : implementation of the Ctest_MFCDoc class
//

#include "stdafx.h"
#include "test_MFC.h"

#include "test_MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest_MFCDoc

IMPLEMENT_DYNCREATE(Ctest_MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(Ctest_MFCDoc, CDocument)
END_MESSAGE_MAP()


// Ctest_MFCDoc construction/destruction

Ctest_MFCDoc::Ctest_MFCDoc()
{
	// TODO: add one-time construction code here

}

Ctest_MFCDoc::~Ctest_MFCDoc()
{
}

BOOL Ctest_MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Ctest_MFCDoc serialization

void Ctest_MFCDoc::Serialize(CArchive& ar)
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


// Ctest_MFCDoc diagnostics

#ifdef _DEBUG
void Ctest_MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ctest_MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ctest_MFCDoc commands
