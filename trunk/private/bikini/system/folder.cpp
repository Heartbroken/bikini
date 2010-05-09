/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

folder folder::find(const wstring &_path, bool _create)
{
	wstring l_path = _path;

	return folder(l_path);
}

folder::folder()
{}

folder::folder(const wstring &_path)
:
	m_path(_path)
{}


} /* namespace bk -------------------------------------------------------------------------------*/
