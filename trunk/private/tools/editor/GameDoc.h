
// GameDoc.h : interface of the CGameDoc class
//


#pragma once


class CGameDoc : public CDocument
{
public:
	struct stage
	{
		bk::wstring name;
		bk::wstring folder;
	};
	bk::array_<stage> m_stages;

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
	virtual void OnCloseDocument();
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


