#include "stdafx.h"

#include <sys/stat.h>

static bk::random sg_GUID_random(GetTickCount());
// workspace

workspace::workspace()
{}

bool workspace::create()
{
	destroy();

	commands::add("NewProject", bk::functor_<const bk::GUID&, const bk::wstring&, const bk::wstring&>(*this, &workspace::new_project));
	commands::add("NewPackage", bk::functor_<const bk::GUID&, const bk::GUID&, const bk::wstring&>(*this, &workspace::new_package));
	commands::add("ObjectStructure", bk::functor_<bk::astring, const bk::GUID&>(*this, &workspace::object_structure));
	commands::add("RenameObject", bk::functor_<bool, const bk::GUID&, const bk::wstring&>(*this, &workspace::rename_object));
	commands::add("RemoveObject", bk::functor_<bool, const bk::GUID&>(*this, &workspace::remove_object));

	return true;
}
void workspace::destroy()
{
	commands::remove("RemoveObject");
	commands::remove("RenameObject");
	commands::remove("ObjectStructure");
	commands::remove("NewPackage");
	commands::remove("NewProject");

	clear();
}

const bk::GUID& workspace::new_project(const bk::wstring &_location, const bk::wstring &_name)
{
	static wo::project::info sl_project;

	bk::uint l_ID = spawn(sl_project, _location, _name);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
const bk::GUID& workspace::new_package(const bk::GUID &_parent, const bk::wstring &_name)
{
	static wo::package::info sl_package;

	bk::uint l_parent_ID = find_object(_parent);

	if (l_parent_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't add new package. Parent object not found\n";
		return bk::bad_GUID;
	}

	bk::uint l_ID = spawn(sl_package, l_parent_ID, _name);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
bk::astring workspace::object_structure(const bk::GUID& _object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't get object's structure. Object not found";
		return false;
	}

	return get_<object>(l_ID).structure();
}
bool workspace::rename_object(const bk::GUID &_object, const bk::wstring &_name)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't rename object. Object not found";
		return false;
	}

	return get_<object>(l_ID).rename(_name);
}
bool workspace::remove_object(const bk::GUID &_object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't remove object. Object not found";
		return false;
	}

	kill(l_ID);

	return true;
}

bk::uint workspace::find_object(const bk::GUID &_object) const
{
	for (bk::uint l_ID = get_first_ID(); l_ID != bk::bad_ID; l_ID = get_next_ID(l_ID))
	{
		if (get_<object>(l_ID).GUID() == _object)
			return l_ID;
	}
	return bk::bad_ID;
}

// workspace::object

workspace::object::object(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name)
:
	bk::manager::object(_info, _workspace),
	m_GUID(bk::random_GUID(sg_GUID_random)),
	m_parent_ID(_parent_ID),
	m_name(_name),
	m_valid(false)
{}


namespace wo { // workspace objects ---------------------------------------------------------------

// project

project::project(const info &_info, workspace &_workspace, const bk::wstring& _location, const bk::wstring& _name)
:
	workspace::object(_info, _workspace, bk::bad_ID, _name)
{
	m_folder = bk::folder(_location + L"/" + name());

	if (m_folder.exists())
	{
		if (!m_folder.empty())
		{
			std::wcerr << "ERROR: Can't create project. Folder '" << m_folder.path() << "' already exists and isn't empty\n";
			m_folder = bk::bad_folder;
			return;
		}
	}
	else
	{
		if(!m_folder.create())
		{
			std::wcerr << "ERROR: Can't create project. Can't create folder '" << m_folder.path() << "'\n";
			m_folder = bk::bad_folder;
			return;
		}
	}

	if (!save()) return;

	set_valid();
}

bool project::add_child(bk::uint _child)
{
	if (get_workspace().get(_child).type() != workspace::ot::package)
		return false;

	return super::add_child(_child);
}
bool project::rename(const bk::wstring &_name)
{
	if (!m_folder.rename(_name))
	{
		std::wcerr << "ERROR: Can't rename project folder\n";
		return false;
	}

	bk::wstring l_oldpath = m_folder.path() + L"/" + name() + L".bkproj";
	bk::wstring l_newpath = m_folder.path() + L"/" + _name + L".bkproj";

	if (_wrename(l_oldpath.c_str(), l_newpath.c_str()) != 0)
	{
		std::wcerr << "ERROR: Can't rename project file\n";
		m_folder.rename(name());
		return false;
	}

	return super::rename(_name);
}
bk::astring project::structure() const
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

	bk::wstring l_path = m_folder.path() + L"/" + name() + L".bkproj";

	std::fstream l_stream(l_path.c_str(), std::ios_base::out);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't save workspace. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_writer_stream l_writer(l_stream);

	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);

	return true;
}

void project::write_structure(pugi::xml_node &_root) const
{
	pugi::xml_node l_project = _root.append_child();
	l_project.set_name("project");
	l_project.append_attribute("Name") = bk::utf8(name()).c_str();
	l_project.append_attribute("GUID") = bk::print_GUID(GUID());
	{
		for (bk::uint l_ID = first_relation(); l_ID != bk::bad_ID; l_ID = next_relation(l_ID))
		{
			if (!get_workspace().exists(get_relation(l_ID))) continue;

			object &l_object = get_workspace().get_<object>(get_relation(l_ID));
			switch (l_object.type())
			{
				case workspace::ot::package :
				{
					pugi::xml_node l_package = l_project.append_child();
					l_package.set_name("package");
					l_package.append_attribute("Name") = bk::utf8(l_object.name()).c_str();
					l_package.append_attribute("GUID") = bk::print_GUID(l_object.GUID());
				}
				break;
			}
		}
	}
}

// package

package::package(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring& _name)
:
	workspace::object(_info, _workspace, _parent_ID, _name)
{
	if (!get_workspace().exists(_parent_ID) ||
		get_workspace().get(_parent_ID).type() != workspace::ot::project)
	{
		std::wcerr << "ERROR: Can't create package. Bad parent ID\n";
		return;
	}

	get_workspace().get_<object>(_parent_ID).add_child(ID());
	set_valid();
}

} // namespace wo ---------------------------------------------------------------------------------