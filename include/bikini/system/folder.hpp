/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct folder
{
	static folder find(const wstring &_path, bool _create = true);

	folder();

private:
	folder(const wstring &_path);
	wstring m_path;
};