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
	commands::add("OpenProject", bk::functor_<const bk::GUID&, const bk::wstring&>(*this, &workspace::open_project));
	commands::add("NewPackage", bk::functor_<const bk::GUID&, const bk::GUID&, const bk::wstring&>(*this, &workspace::new_package));
	commands::add("NewFolder", bk::functor_<const bk::GUID&, const bk::GUID&, const bk::wstring&>(*this, &workspace::new_folder));
	commands::add("NewStage", bk::functor_<const bk::GUID&, const bk::GUID&, const bk::wstring&>(*this, &workspace::new_stage));
	commands::add("ObjectStructure", bk::functor_<bk::astring, const bk::GUID&>(*this, &workspace::object_structure));
	commands::add("ObjectPath", bk::functor_<bk::astring, const bk::GUID&>(*this, &workspace::object_path));
	commands::add("ObjectName", bk::functor_<bk::astring, const bk::GUID&>(*this, &workspace::object_name));
	commands::add("RenameObject", bk::functor_<bool, const bk::GUID&, const bk::wstring&>(*this, &workspace::rename_object));
	commands::add("MoveObject", bk::functor_<bool, const bk::GUID&, const bk::GUID&>(*this, &workspace::move_object));
	commands::add("RemoveObject", bk::functor_<bool, const bk::GUID&>(*this, &workspace::remove_object));
	commands::add("SaveAll", bk::functor_<bool>(*this, &workspace::save_all));

	return true;
}
void workspace::destroy()
{
	commands::remove("SaveAll");
	commands::remove("RemoveObject");
	commands::remove("MoveObject");
	commands::remove("RenameObject");
	commands::remove("ObjectName");
	commands::remove("ObjectPath");
	commands::remove("ObjectStructure");
	commands::remove("NewStage");
	commands::remove("NewFolder");
	commands::remove("NewPackage");
	commands::remove("OpenProject");
	commands::remove("NewProject");

	clear();
}

static wo::project::info& project_info() { static wo::project::info sl_project; return sl_project; }
static wo::package::info& package_info() { static wo::package::info sl_package; return sl_package; }
static wo::folder::info& folder_info() { static wo::folder::info sl_folder; return sl_folder; }
static wo::stage::info& stage_info() { static wo::stage::info sl_stage; return sl_stage; }

const bk::GUID& workspace::new_project(const bk::wstring &_location, const bk::wstring &_name)
{
	m_location = _location;

	bk::uint l_ID = spawn(project_info(), _name, true);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
const bk::GUID& workspace::open_project(const bk::wstring &_path)
{
	m_location = _path;
	if (m_location.rfind(wo::project::extension) != m_location.size() - bk::wstring(wo::project::extension).size())
	{
		std::wcerr << "ERROR: Can't open project. Bad file path\n";
		return bk::bad_GUID;
	}

	m_location.resize(m_location.size() - wcslen(wo::project::extension));

	bk::folder l_folder(m_location);

	m_location = l_folder.parent().path();

	bk::uint l_ID = spawn(project_info(), l_folder.name(), false);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
const bk::GUID& workspace::new_package(const bk::GUID &_parent, const bk::wstring &_name)
{
	bk::uint l_parent_ID = find_object(_parent);

	if (l_parent_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't add new package. Parent object not found\n";
		return bk::bad_GUID;
	}

	bk::uint l_ID = spawn(package_info(), l_parent_ID, _name, true);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
const bk::GUID& workspace::new_folder(const bk::GUID &_parent, const bk::wstring &_name)
{
	bk::uint l_parent_ID = find_object(_parent);

	if (l_parent_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't add new folder. Parent object not found\n";
		return bk::bad_GUID;
	}

	bk::uint l_ID = spawn(folder_info(), l_parent_ID, _name, true);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
const bk::GUID& workspace::new_stage(const bk::GUID &_parent, const bk::wstring &_name)
{
	bk::uint l_parent_ID = find_object(_parent);

	if (l_parent_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't add new stage. Parent object not found\n";
		return bk::bad_GUID;
	}

	bk::uint l_ID = spawn(stage_info(), l_parent_ID, _name, true);

	if (!get_<object>(l_ID).valid())
	{
		kill(l_ID);
		return bk::bad_GUID;
	}

	return get_<object>(l_ID).GUID();
}
bk::astring workspace::object_structure(const bk::GUID &_object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't get object's structure. Object not found";
		return false;
	}

	return get_<object>(l_ID).structure();
}
bk::astring workspace::object_path(const bk::GUID &_object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't get object's path. Object not found";
		return false;
	}

	return bk::utf8(get_<object>(l_ID).path());
}
bk::astring workspace::object_name(const bk::GUID &_object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't get object's name. Object not found";
		return false;
	}

	return bk::utf8(get_<object>(l_ID).name());
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
bool workspace::move_object(const bk::GUID &_object, const bk::GUID &_new_parent)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't move object. Object not found";
		return false;
	}

	bk::uint l_new_parent_ID = find_object(_new_parent);

	if (l_new_parent_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't move object. New parent object not found";
		return false;
	}

	return get_<object>(l_ID).move(l_new_parent_ID);
}
bool workspace::remove_object(const bk::GUID &_object)
{
	bk::uint l_ID = find_object(_object);

	if (l_ID == bk::bad_ID)
	{
		std::wcerr << "ERROR: Can't remove object. Object not found";
		return false;
	}

	if (!get_<object>(l_ID).remove()) return false;

	kill(l_ID);

	return true;
}
bool workspace::save_all()
{
	bool l_result = true;

	for (bk::uint l_ID = get_first_ID(); l_ID != bk::bad_ID; l_ID = get_next_ID(l_ID))
	{
		l_result = get_<object>(l_ID).save() && l_result;
	}

	return l_result;
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

workspace::object::object(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name)
:
	bk::manager::object(_info, _workspace),
	m_GUID(bk::random_GUID(sg_GUID_random)),
	m_parent_ID(_parent_ID),
	m_name(_name),
	m_valid(true)
{
	if (get_workspace().exists(parent_ID()))
	{
		if (!get_workspace().get_<object>(parent_ID()).add_child(ID())) set_valid(false);
	}
}
workspace::object::~object()
{
	if (get_workspace().exists(parent_ID()))
		get_workspace().get_<object>(parent_ID()).remove_child(ID());
}
bk::wstring workspace::object::path() const
{
	if (get_workspace().exists(parent_ID()))
		return get_workspace().get_<object>(parent_ID()).path() + L"/" + name();

	return get_workspace().location() + L"/" + name();
}

// workspace::folder

workspace::folder::folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create)
:
	object(_info, _workspace, _parent_ID, _name)
{
	if (!valid()) return;

	if (_create)
	{
		bk::folder l_folder(path());

		if (l_folder.exists())
		{
			if (!l_folder.empty())
			{
				std::wcerr << "ERROR: Can't create folder. Folder '" << l_folder.path() << "' already exists and isn't empty\n";
				return;
			}
		}
		else
		{
			if(!l_folder.create())
			{
				std::wcerr << "ERROR: Can't create folder. Can't create folder '" << l_folder.path() << "'\n";
				return;
			}
		}
	}
}

bool workspace::folder::rename(const bk::wstring &_name)
{
	bk::folder l_folder(path());

	if (!l_folder.rename(_name))
	{
		std::wcerr << "ERROR: Can't rename folder\n";
		return false;
	}

	return super::rename(_name);
}
bool workspace::folder::move(bk::uint _new_parent_ID)
{
	object &l_old_parent = get_workspace().get_<object>(parent_ID());
	object &l_new_parent = get_workspace().get_<object>(_new_parent_ID);

	if (!l_new_parent.add_child(ID()))
	{
		std::wcerr << "ERROR: Can't move folder. Bad new parent ID\n";
		return false;
	}

	bk::folder l_folder(path());

	if (!l_folder.move(l_new_parent.path()))
	{
		std::wcerr << "ERROR: Can't move folder. I/O error\n";
		l_new_parent.remove_child(ID());
		return false;
	}

	l_old_parent.remove_child(ID());

	return super::move(_new_parent_ID);
}
bool workspace::folder::remove()
{
	bk::folder l_folder(path());

	for (bk::uint l_ID = first_relation(); l_ID != bk::bad_ID; l_ID = next_relation(l_ID))
	{
		get_workspace().get_<object>(get_relation(l_ID)).remove();
		remove_relation(l_ID);
	}

	if (!l_folder.remove())
	{
		std::wcerr << "ERROR: Can't remove folder\n";
		return false;
	}

	return true;
}

namespace wo { // workspace objects ---------------------------------------------------------------

// project

bk::wchar const* project::extension = L".project";

project::project(const info &_info, workspace &_workspace, const bk::wstring &_name, bool _create)
:
	workspace::folder(_info, _workspace, bk::bad_ID, _name, _create)
{
	if (_create)
	{
		if (!save()) set_valid(false);
	}
	else
	{
		if (!load()) set_valid(false);
	}
}

bool project::add_child(bk::uint _child)
{
	if (get_workspace().get(_child).type() != workspace::ot::package &&
		get_workspace().get(_child).type() != workspace::ot::folder)
		return false;

	return super::add_child(_child);
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
	bk::folder l_folder(path());

	if (!l_folder.exists())
	{
		std::wcerr << "ERROR: Can't save project. Folder '" << l_folder.path() << "' doesn't exist\n";
		return false;
	}

	bk::wstring l_path = l_folder.path() + L"/" + extension;

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
bool project::load()
{
	bk::wstring l_path = path() + L"/" + extension;

	std::fstream l_stream(l_path.c_str(), std::ios_base::in);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't load project. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_document l_document;
	l_document.load(l_stream);

	pugi::xml_node l_project = l_document.child("project");
	if (bk::astring("project") != l_project.name()) return false;

	set_GUID(bk::scan_GUID(l_project.attribute("GUID").value()));

	struct _l { static void load_childs(pugi::xml_node _parent, bk::uint _ID, workspace &_w)
	{
		for (pugi::xml_node l_child = _parent.first_child(); l_child; l_child = l_child.next_sibling())
		{
			if (bk::astring("folder") == l_child.name())
			{
				bk::wstring l_name = bk::utf8(l_child.attribute("name").value());
				bk::uint l_ID = _w.spawn(folder_info(), _ID, l_name, false);
				load_childs(l_child, l_ID, _w);
			}
			else if (bk::astring("package") == l_child.name())
			{
				bk::wstring l_name = bk::utf8(l_child.attribute("name").value());
				_w.spawn(package_info(), _ID, l_name, false);
			}
		}
	}};

	_l::load_childs(l_project, ID(), get_workspace());

	return true;
}

void project::write_structure(pugi::xml_node &_root) const
{
	struct _l { static void write_childs(pugi::xml_node &_parent, const workspace::object &_object)
	{
		for (bk::uint l_ID = _object.first_relation(); l_ID != bk::bad_ID; l_ID = _object.next_relation(l_ID))
		{
			if (!_object.get_workspace().exists(_object.get_relation(l_ID))) continue;

			const object &l_child = _object.get_workspace().get_<object>(_object.get_relation(l_ID));
			switch (l_child.type())
			{
				case workspace::ot::package :
				{
					pugi::xml_node l_package = _parent.append_child();
					l_package.set_name("package");
					l_package.append_attribute("name") = bk::utf8(l_child.name()).c_str();
					l_package.append_attribute("GUID") = bk::print_GUID(l_child.GUID());
				}
				break;
				case workspace::ot::folder :
				{
					pugi::xml_node l_folder = _parent.append_child();
					l_folder.set_name("folder");
					l_folder.append_attribute("name") = bk::utf8(l_child.name()).c_str();
					l_folder.append_attribute("GUID") = bk::print_GUID(l_child.GUID());
					write_childs(l_folder, l_child);
				}
				break;
			}
		}
	}};

	pugi::xml_node l_project = _root.append_child();
	l_project.set_name("project");
	l_project.append_attribute("name") = bk::utf8(name()).c_str();
	l_project.append_attribute("GUID") = bk::print_GUID(GUID());

	_l::write_childs(l_project, *this);
}

// package

bk::wchar const* package::extension = L".package";

package::package(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create)
:
	workspace::folder(_info, _workspace, _parent_ID, _name, _create)
{
	if (valid())
	{
		if (_create)
		{
			if (!save()) set_valid(false);
		}
		else
		{
			if (!load()) set_valid(false);
		}
	}
}

bool package::add_child(bk::uint _child)
{
	if (get_workspace().get(_child).type() != workspace::ot::stage)
		return false;

	return super::add_child(_child);
}
bk::astring package::structure() const
{
	std::ostringstream l_stream;
	pugi::xml_writer_stream l_writer(l_stream);
	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_no_declaration);

	return l_stream.str();
}
bool package::save() const
{
	bk::folder l_folder(path());

	if (!l_folder.exists())
	{
		std::wcerr << "ERROR: Can't save package. Folder '" << l_folder.path() << "' doesn't exist\n";
		return false;
	}

	bk::wstring l_path = l_folder.path() + L"/" + extension;

	std::fstream l_stream(l_path.c_str(), std::ios_base::out);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't save package. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_writer_stream l_writer(l_stream);

	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);

	return true;
}
bool package::load()
{
	bk::wstring l_path = path() + L"/" + extension;

	std::fstream l_stream(l_path.c_str(), std::ios_base::in);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't load package. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_document l_document;
	l_document.load(l_stream);

	pugi::xml_node l_package = l_document.child("package");
	if (bk::astring("package") != l_package.name()) return false;

	set_GUID(bk::scan_GUID(l_package.attribute("GUID").value()));

	struct _l { static void load_childs(pugi::xml_node _parent, bk::uint _ID, workspace &_w)
	{
		for (pugi::xml_node l_child = _parent.first_child(); l_child; l_child = l_child.next_sibling())
		{
			if (bk::astring("stage") == l_child.name())
			{
				bk::wstring l_name = bk::utf8(l_child.attribute("name").value());
				bk::uint l_ID = _w.spawn(stage_info(), _ID, l_name, false);
				load_childs(l_child, l_ID, _w);
			}
		}
	}};

	_l::load_childs(l_package, ID(), get_workspace());

	return true;
}

void package::write_structure(pugi::xml_node &_root) const
{
	pugi::xml_node l_package = _root.append_child();
	l_package.set_name("package");
	l_package.append_attribute("name") = bk::utf8(name()).c_str();
	l_package.append_attribute("GUID") = bk::print_GUID(GUID());
	{
		for (bk::uint l_ID = first_relation(); l_ID != bk::bad_ID; l_ID = next_relation(l_ID))
		{
			if (!get_workspace().exists(get_relation(l_ID))) continue;

			object &l_object = get_workspace().get_<object>(get_relation(l_ID));
			switch (l_object.type())
			{
				case workspace::ot::stage :
				{
					pugi::xml_node l_stage = l_package.append_child();
					l_stage.set_name("stage");
					l_stage.append_attribute("name") = bk::utf8(l_object.name()).c_str();
					l_stage.append_attribute("GUID") = bk::print_GUID(l_object.GUID());
				}
				break;
			}
		}
	}
}

// folder

folder::folder(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create)
:
	workspace::folder(_info, _workspace, _parent_ID, _name, _create)
{}

bool folder::add_child(bk::uint _child)
{
	if (get_workspace().get(_child).type() != workspace::ot::package &&
		get_workspace().get(_child).type() != workspace::ot::folder)
		return false;

	return super::add_child(_child);
}

// stage

bk::wchar const* stage::extension = L".stage";

stage::stage(const info &_info, workspace &_workspace, bk::uint _parent_ID, const bk::wstring &_name, bool _create)
:
	workspace::folder(_info, _workspace, _parent_ID, _name, _create)
{
	if (valid())
	{
		if (_create)
		{
			if (!save()) set_valid(false);
		}
		else
		{
			if (!load()) set_valid(false);
		}
	}
}

bool stage::add_child(bk::uint _child)
{
	if (get_workspace().get(_child).type() != workspace::ot::stage)
		return false;

	return super::add_child(_child);
}
bk::astring stage::structure() const
{
	std::ostringstream l_stream;
	pugi::xml_writer_stream l_writer(l_stream);
	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_no_declaration);

	return l_stream.str();
}
bool stage::save() const
{
	bk::folder l_folder(path());

	if (!l_folder.exists())
	{
		std::wcerr << "ERROR: Can't save stage. Folder '" << l_folder.path() << "' doesn't exist\n";
		return false;
	}

	bk::wstring l_path = l_folder.path() + L"/" + extension;

	std::fstream l_stream(l_path.c_str(), std::ios_base::out);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't save stage. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_writer_stream l_writer(l_stream);

	pugi::xml_document l_document; write_structure(l_document);
	l_document.save(l_writer, "    ", pugi::format_default|pugi::format_write_bom_utf8);

	return true;
}
bool stage::load()
{
	bk::wstring l_path = path() + L"/" + extension;

	std::fstream l_stream(l_path.c_str(), std::ios_base::in);

	if (!l_stream.good())
	{
		std::wcerr << "ERROR: Can't load stage. Can't open file '" << l_path << "'\n";
		return false;
	}

	pugi::xml_document l_document;
	l_document.load(l_stream);

	pugi::xml_node l_stage = l_document.child("stage");
	if (bk::astring("stage") != l_stage.name()) return false;

	set_GUID(bk::scan_GUID(l_stage.attribute("GUID").value()));

	struct _l { static void load_childs(pugi::xml_node _parent, bk::uint _ID, workspace &_w)
	{
		for (pugi::xml_node l_child = _parent.first_child(); l_child; l_child = l_child.next_sibling())
		{
			if (bk::astring("stage") == l_child.name())
			{
				bk::wstring l_name = bk::utf8(l_child.attribute("name").value());
				bk::uint l_ID = _w.spawn(stage_info(), _ID, l_name, false);
				load_childs(l_child, l_ID, _w);
			}
		}
	}};

	_l::load_childs(l_stage, ID(), get_workspace());

	return true;
}

void stage::write_structure(pugi::xml_node &_root) const
{
	pugi::xml_node l_stage = _root.append_child();
	l_stage.set_name("stage");
	l_stage.append_attribute("name") = bk::utf8(name()).c_str();
	l_stage.append_attribute("GUID") = bk::print_GUID(GUID());
	{
		for (bk::uint l_ID = first_relation(); l_ID != bk::bad_ID; l_ID = next_relation(l_ID))
		{
			if (!get_workspace().exists(get_relation(l_ID))) continue;

			object &l_object = get_workspace().get_<object>(get_relation(l_ID));
			switch (l_object.type())
			{
				case workspace::ot::stage :
				{
					pugi::xml_node l_stage2 = l_stage.append_child();
					l_stage2.set_name("stage");
					l_stage2.append_attribute("name") = bk::utf8(l_object.name()).c_str();
					l_stage2.append_attribute("GUID") = bk::print_GUID(l_object.GUID());
				}
				break;
			}
		}
	}
}

} // namespace wo ---------------------------------------------------------------------------------