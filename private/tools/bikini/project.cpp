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

	if (!save()) return false;

	commands::add("GetProjectStructure", bk::functor_<bk::astring>(*this, &project::get_structure));
	commands::add("RenameObject", bk::functor_<bool, GUID, const bk::wstring&>(*this, &project::rename_object));

	return true;
}
void project::destroy()
{
	commands::remove("GetProjectStructure");
	commands::remove("RenameObject");

	m_folder = bk::bad_folder;
	m_name = L"";
	m_GUID = bk::bad_GUID;

	clear();
}

bool project::rename_object(GUID _GUID, const bk::wstring &_name)
{
	if (_GUID == m_GUID)
	{
		if (!m_folder.rename(_name))
		{
			std::wcerr << "ERROR: Can't rename project folder\n";
			return false;
		}

		bk::wstring l_oldpath = m_folder.path() + L"/" + m_name + L".bkproj";
		bk::wstring l_newpath = m_folder.path() + L"/" + _name + L".bkproj";

		if (_wrename(l_oldpath.c_str(), l_newpath.c_str()) != 0)
		{
			std::wcerr << "ERROR: Can't rename project file\n";
			m_folder.rename(m_name);
			return false;
		}

		m_name = _name;

		save();
	}
	else
		return false;

	return true;
}

void project::write_structure(pugi::xml_node &_root) const
{
	pugi::xml_node l_project = _root.append_child();
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
}
bk::astring project::get_structure() const
{
	std::ostringstream l_stream;
	pugi::xml_writer_stream l_writer(l_stream);
	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_no_declaration);

	return l_stream.str();
}
bool project::save() const
{
	if (!m_folder.exists())
	{
		std::wcerr << "ERROR: Can't save project. Folder '" << m_folder.path() << "' doesn't exist\n";
		return false;
	}

	bk::wstring l_path = m_folder.path() + L"/" + m_name + L".bkproj";

	std::fstream l_stream(l_path.c_str(), std::ios_base::out);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't save project. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_writer_stream l_writer(l_stream);

	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);

	return true;
}
