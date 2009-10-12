
// GameDoc.h : interface of the CGameDoc class
//


#pragma once


class CGameDoc : public CDocument
{
protected: // create from serialization only
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
};


