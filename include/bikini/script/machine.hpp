/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine
{
	machine(uint _stacksize = 1024);
	~machine();

	object compile(const wchar* _code, const wchar* _name);

	uint make_reference();
	void free_reference(uint _ID);

private:
	handle m_handle;
};