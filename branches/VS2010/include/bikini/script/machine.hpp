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

	object new_null();
	object new_integer(sint _v = 0);
	object new_float(real _v = 0);
	object new_string(const wchar* _v = L"");
	object new_table();
	object new_array();

private:
	handle m_handle;

	friend object;

	uint make_reference();
	uint add_reference(uint _ID);
	void free_reference(uint _ID);

	bool is_null(const object &_v) const;
	bool is_integer(const object &_v) const;
	bool is_float(const object &_v) const;
	bool is_bool(const object &_v) const;
	bool is_string(const object &_v) const;
	bool is_table(const object &_v) const;
	bool is_array(const object &_v) const;
	bool is_userdata(const object &_v) const;
	bool is_closure(const object &_v) const;
	bool is_nativeclosure(const object &_v) const;
	bool is_generator(const object &_v) const;
	bool is_userpointer(const object &_v) const;
	bool is_thread(const object &_v) const;
	bool is_class(const object &_v) const;
	bool is_instance(const object &_v) const;
	bool is_weakref(const object &_v) const;

	sint to_integer(const object &_v, sint _default) const;
	real to_float(const object &_v, real _default) const;
	bool to_bool(const object &_v, bool _default) const;
	const wchar* to_string(const object &_v, const wchar* _default) const;

	void set(object &_array, uint _key, const value &_value);
	void set(object &_table, const wchar* _key, const value &_value);

	object get(const object &_array, uint _key);
	object get(const object &_table, const wchar* _key);

	object call(const object &_closure, const values &_args);
};