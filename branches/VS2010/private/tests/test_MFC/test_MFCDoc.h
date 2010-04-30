// test_MFCDoc.h : interface of the Ctest_MFCDoc class
//


#pragma once


class Ctest_MFCDoc : public CDocument
{
protected: // create from serialization only
	Ctest_MFCDoc();
	DECLARE_DYNCREATE(Ctest_MFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Ctest_MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


