#include "stdafx.h"

#include <sys/stat.h>

static bk::random sg_GUID_random(GetTickCount());
// project

project::project()
{}

bool project::create(const bk::wstring &_location, const bk::wstring &_name)
{
	destroy();

	m_folder = bk::folder(_location + L"/" + _name);

	if (m_folder.exists())
	{
		if (!m_folder.empty())
		{
			std::wcerr << "ERROR: Can't create project. Folder '" << m_folder.path() << "' already exists and isn't empty\n";
			m_folder = bk::bad_folder;
			return false;
		}
	}
	else
		m_folder.create();

	m_name = _name;
	m_GUID = bk::random_GUID(sg_GUID_random);

	return save();
}
void project::destroy()
{
	clear();
}

bool project::save()
{
	if (!m_folder.exists())
	{
		std::wcerr << "ERROR: Can't save project. Folder '" << m_folder.path() << "' doesn't exist\n";
		return false;
	}

	bk::wstring l_path = m_folder.path() + L"/" + m_name + L".bkproj";

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
			{
				pugi::xml_node l_stage = l_package.append_child();
				l_stage.set_name("stage");
				l_stage.append_attribute("Name") = "Fake Stage";
				l_stage.append_attribute("GUID") = bk::print_GUID(bk::random_GUID(sg_GUID_random));
			}
		}

		pugi::xml_writer_stream l_writer(l_stream);
		l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);
	}

	return true;
}