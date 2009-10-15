
// GameDoc.h : interface of the CGameDoc class
//


#pragma once


class CGameDoc : public CDocument
{

public:

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

// bikini game xml
public:
	pugi::xml_document m_document;

	// Selected node
	GUID m_selected;
	const GUID& SelectedNode();
	void SetSelectedNode(const GUID &_g);
	pugi::xml_node GetNodeByGUID(const GUID &_g);

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
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
};

extern CGameDoc *theGameDoc;

