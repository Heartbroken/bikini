#include "stdafx.h"

// project

project::project()
{}

bool project::create(const bk::wstring &_path, const bk::wstring &_name)
{
	destroy();

	m_name = _name;
	m_path = _path;

	return true;
}
void project::destroy()
{
	clear();
}
