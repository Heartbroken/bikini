/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// folder

folder bad_folder;

folder::folder()
:
	m_parent(*(folder*)0)
{}
folder::folder(const folder &_folder)
:
	m_parent(*(_folder.is_root() ? (folder*)0 : new folder(_folder.parent()))),
	m_name(_folder.name())
{}
static wstring _check_path(const wstring &_path)
{
	if (_path.empty()) return L"";

	wstring l_path = _path;

	wstring::size_type l_pos;
	while ((l_pos = l_path.find(L'\\')) != wstring::npos)
		l_path.replace(l_pos, 1, L"/");

	while (l_path[l_path.size() - 1] == L'/')
		l_path.resize(l_path.size() - 1);

	return l_path;
}
static folder& _folder_parent(const wstring &_path)
{
	wstring l_path = _check_path(_path);

	wstring::size_type l_pos;
	if ((l_pos = l_path.rfind(L'/')) != wstring::npos)
		l_path = l_path.substr(0, l_pos);
	else
		return *(folder*)0;

	if (_path.empty()) return *(folder*)0;
	return * new folder(l_path);
}
static wstring _folder_name(const wstring &_path)
{
	wstring l_name = _check_path(_path);

	wstring::size_type l_pos;
	if ((l_pos = l_name.rfind(L'/')) != wstring::npos)
		l_name = l_name.substr(l_pos + 1);

	return l_name;
}
folder::folder(const wstring &_path)
:
	m_parent(_folder_parent(_path)),
	m_name(_folder_name(_path))
{}
folder::~folder()
{
	delete &m_parent;
}

folder& folder::operator = (const folder &_folder)
{
	this->~folder(); new(this) folder(_folder);
	return *this;
}

const wstring& folder::name() const
{
	return m_name;
}
bool folder::is_root() const
{
	return &m_parent == 0;
}
const folder& folder::parent() const
{
	return is_root() ? bad_folder : m_parent;
}
wstring folder::path() const
{
	return is_root() ? name() : parent().path() + L"/" + name();
}
bool folder::exists() const
{
	struct _stat64 l_st;
	return _wstat64(path().c_str(), &l_st) == 0;
}
bool folder::create() const
{
	if (!is_root())
	{
		if (!parent().exists() && !parent().create())
			return false;
	}

	return _wmkdir(path().c_str()) == 0;
}
bool folder::empty() const
{
	wstring l_pattern = path() + L"/*.*";

	WIN32_FIND_DATAW l_finddata;
	HANDLE l_find = FindFirstFileW(l_pattern.c_str(), &l_finddata);

	if (l_find != INVALID_HANDLE_VALUE)
	{
		FindClose(l_find);
		return false;
	}

	return true;
}
bool folder::rename(const wstring &_name)
{
	if (!exists()) return false;

	wstring l_oldpath = path();
	wstring l_newpath = is_root() ? _name : parent().path() + L"/" + _name;

	if (_wrename(l_oldpath.c_str(), l_newpath.c_str()) != 0) return false;

	m_name = _name;

	return true;
}
bool folder::move(const folder &_to)
{
	if (!exists()) return false;

	wstring l_oldpath = path();
	wstring l_newpath = _to.is_root() ? m_name : _to.path() + L"/" + m_name;

	if (!MoveFileW(l_oldpath.c_str(), l_newpath.c_str())) return false;

	m_parent = _to;

	return true;
}
bool folder::remove()
{
	if (!exists()) return false;

	wstring l_pattern = path() + L"/*.*";

	WIN32_FIND_DATAW l_finddata;
	HANDLE l_find = FindFirstFileW(l_pattern.c_str(), &l_finddata);

	if (l_find != INVALID_HANDLE_VALUE)
	{
		do
		{
			wstring l_filename(l_finddata.cFileName);

			if (l_filename == L"." || l_filename == L"..")
			{
				continue;
			}

			wstring l_filepath(path() + L"/" + l_filename);

			if (l_finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				folder subfolder(l_filepath);
				subfolder.remove();
			}
			else
			{
				DeleteFileW(l_filepath.c_str());
			}
		}
		while (FindNextFileW(l_find, &l_finddata));
		FindClose(l_find);
	}

	wstring l_path = path();

	if (_wrmdir(l_path.c_str()) != 0) return false;

	return true;
}

// file

folder::file::file()
:
	m_parent(*(folder*)0)
{}

} /* namespace bk -------------------------------------------------------------------------------*/
