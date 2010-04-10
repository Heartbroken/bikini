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

	object root();

private:
	handle m_handle;

	friend object;

	uint make_reference();
	uint add_reference(uint _ID);
	void free_reference(uint _ID);

	bool is_null(const object &_v) const;

	object call(const object &_closure, const values &_args);
};