
// gameDoc.cpp : implementation of the CGameDoc class
//

#include "stdafx.h"
#include "editor.h"

#include "GameDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGameDoc *theGameDoc = NULL;

// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
END_MESSAGE_MAP()


// CGameDoc construction/destruction

CGameDoc::CGameDoc()
:
	m_selected(bk::bad_GUID)
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
	assert(theGameDoc == NULL);
	theGameDoc = this;


	bk::random l_random(GetTickCount());

	pugi::xml_node l_game = m_document.append_child();
	l_game.set_name("game");
	l_game.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(l_random));
	{
		pugi::xml_node l_prop = l_game.append_child();
		l_prop.set_name("property");
		l_prop.append_attribute("name") = "Name";
		l_prop.append_attribute("value") = "New Game";
	}
	{
		pugi::xml_node l_prop = l_game.append_child();
		l_prop.set_name("property");
		l_prop.append_attribute("name") = "Resources";
		l_prop.append_attribute("value") = "";
	}
	{
		pugi::xml_node l_stage = l_game.append_child();
		l_stage.set_name("stage");
		l_stage.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(l_random));
		{
			pugi::xml_node l_prop = l_stage.append_child();
			l_prop.set_name("property");
			l_prop.append_attribute("name") = "Name";
			l_prop.append_attribute("value") = "Main Stage";
		}
	}
	{
		pugi::xml_node l_folder = l_game.append_child();
		l_folder.set_name("folder");
		l_folder.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(l_random));
		{
			pugi::xml_node l_prop = l_folder.append_child();
			l_prop.set_name("property");
			l_prop.append_attribute("name") = "Name";
			l_prop.append_attribute("value") = "Levels";
		}
		{
			pugi::xml_node l_stage = l_folder.append_child();
			l_stage.set_name("stage");
			l_stage.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(l_random));
			{
				pugi::xml_node l_prop = l_stage.append_child();
				l_prop.set_name("property");
				l_prop.append_attribute("name") = "Name";
				l_prop.append_attribute("value") = "Level 001";
			}
		}
		{
			pugi::xml_node l_stage = l_folder.append_child();
			l_stage.set_name("stage");
			l_stage.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(l_random));
			{
				pugi::xml_node l_prop = l_stage.append_child();
				l_prop.set_name("property");
				l_prop.append_attribute("name") = "Name";
				l_prop.append_attribute("value") = "Level 002";
			}
		}
	}

	CMainFrame* l_MainFrame = (CMainFrame*)theApp.GetMainWnd();
	l_MainFrame->GetClassView().FillClassView();

	return TRUE;
}

// CGameDoc commands

BOOL CGameDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	if (theGameDoc) theGameDoc->OnCloseDocument();
	assert(theGameDoc == NULL);
	theGameDoc = this;

	CMainFrame* l_MainFrame = (CMainFrame*)theApp.GetMainWnd();
	l_MainFrame->GetClassView().FillClassView();

	return TRUE;
}

void CGameDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	if (theGameDoc == this) theGameDoc = NULL;

	CMainFrame* l_MainFrame = (CMainFrame*)theApp.GetMainWnd();
	l_MainFrame->GetClassView().FillClassView();
	l_MainFrame->GetPropertiesWnd().InitPropList();

	CDocument::OnCloseDocument();
}




// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		std::ostringstream l_stream;
		pugi::xml_writer_stream l_writer(l_stream);
		m_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);

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

		m_document.load(l_XML.c_str());
	}
}

// bikini game xml
const GUID& CGameDoc::SelectedNode()
{
	return m_selected;
}
void CGameDoc::SetSelectedNode(const GUID &_g)
{
	m_selected = _g;
	CMainFrame* l_MainFrame = (CMainFrame*)theApp.GetMainWnd();
	l_MainFrame->GetPropertiesWnd().InitPropList();
}
pugi::xml_node CGameDoc::GetNodeByGUID(const GUID &_g)
{
	struct _by_GUID
	{
		bk::astring s;
		_by_GUID(const GUID &_g) : s(bk::print_GUID(_g)) {}
		bool operator () (const pugi::xml_node &_n)
		{
			return s == _n.attribute("GUID").value();
		}
	};

	return m_document.find_node(_by_GUID(_g));
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


void CGameDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetPathName(lpszPathName, bAddToMRU);

	pugi::xml_node l_game_node = m_document.child("game");
	bk::_string l_game_name = l_game_node.find_child_by_attribute("property", "name", "Name").attribute("value").value();
	SetTitle(l_game_name);

}
