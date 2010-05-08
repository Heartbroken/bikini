#include "stdafx.h"

#include <sys/stat.h>

static bk::random sg_GUID_random(GetTickCount());
// project

project::project()
{}

bool project::create(const bk::wstring &_path, const bk::wstring &_name)
{
	destroy();

	m_name = _name;
	m_path = _path;

	if (!m_path.empty())
	{
		while (m_path[m_path.size() - 1] == L'\\' || m_path[m_path.size() - 1] == L'/')
		{
			m_path.resize(m_path.size() - 1);
		}

		m_path += L"\\";
	}
	m_path += m_name;

	m_GUID = bk::random_GUID(sg_GUID_random);

	return save();
}
void project::destroy()
{
	clear();
}

bool project::save()
{
	struct _stat64 l_st;
	if (_wstat64(m_path.c_str(), &l_st) != 0 && _wmkdir(m_path.c_str()) != 0)
	{
		std::cerr << "ERROR: Cant save project. Can't create folder";
		return false;
	}

	bk::wstring l_path = m_path + L"\\" + m_name + L".bkproj";

	std::fstream l_stream(l_path.c_str(), std::ios_base::out);

	if (l_stream.good())
	{
		pugi::xml_document l_document;

		pugi::xml_node l_project = l_document.append_child();
		l_project.set_name("project");
		l_project.append_attribute("Name") = bk::utf8(m_name).c_str();
		l_project.append_attribute("GUID") = bk::print_GUID(m_GUID);
		{
			pugi::xml_node l_package = l_project.append_child();
			l_package.set_name("package");
			l_package.append_attribute("Name") = "Fake Package";
			l_package.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(sg_GUID_random));
		}

		pugi::xml_writer_stream l_writer(l_stream);
		l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);
	}

	return true;
}
