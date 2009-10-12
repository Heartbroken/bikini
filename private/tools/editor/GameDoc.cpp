
// gameDoc.cpp : implementation of the CGameDoc class
//

#include "stdafx.h"
#include "editor.h"

#include "GameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CGameDoc *theGameDoc = NULL;

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
	if (theGameDoc) theGameDoc->OnCloseDocument();
	theGameDoc = this;

	return TRUE;
}

// CGameDoc commands

BOOL CGameDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	if (theGameDoc) theGameDoc->OnCloseDocument();
	theGameDoc = this;

	return TRUE;
}




// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		pugi::xml_document l_document;
		pugi::xml_node l_game = l_document.append_child();
		l_game.set_name("game");
		l_game.append_attribute("name") = pugi::as_utf8(GetTitle()).c_str();
		pugi::xml_node l_levels = l_game.append_child();
		l_levels.set_name("levels");
		pugi::xml_node l_level_001 = l_levels.append_child();
		l_level_001.set_name("level_001");
		l_level_001.append_attribute("description") = pugi::as_utf8(L"Тестовый уровень").c_str();

		std::ostringstream l_stream;
		pugi::xml_writer_stream l_writer(l_stream);
		l_document.save(l_writer, "\x09", pugi::format_default|pugi::format_write_bom_utf8);

		std::string l_XML = l_stream.str();
		size_t l_pos = l_XML.find("\n");
		while (l_pos != std::string::npos)
		{
			l_XML.replace(l_pos, 1, "\r\n");
			l_pos = l_XML.find("\n", l_pos + 2);
		}

		ar.Write(l_XML.c_str(), l_XML.length());
	}
	else
	{
		// TODO: add loading code here
		const UINT l_buffer_max = 512;
		bk::achar l_buffer[l_buffer_max];
		bk::astring l_XML;
		while (true)
		{
			UINT l_read = ar.Read(l_buffer, l_buffer_max);
			l_XML.append(l_buffer, l_read);
			if (l_read < l_buffer_max) break;
		}

		pugi::xml_document l_document;
		l_document.load(l_XML.c_str());

		pugi::xml_node l_game = l_document.child("game");
		pugi::xml_node l_levels = l_game.child("levels");
		pugi::xml_node l_level_001 = l_levels.child("level_001");
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

