/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine;
struct object;

typedef variant_<
	make_typelist_<
		bool, u8, s8, u16, s16, u32, s32, /*u64, s64,*/ float, const wchar*, wchar*, object
	>::type
> value;

typedef array_<value> values;

struct object
{
	object();
	object(machine &_machine);
	object(const object &_object);
	~object();

	object& operator = (const object &_object);

	inline machine& get_machine() const { return m_machine; }
	inline uint ID() const { return m_ID; }

	bool is_valid() const;
	bool is_null() const;
	bool is_integer() const;
	bool is_float() const;
	bool is_bool() const;
	bool is_string() const;
	bool is_table() const;
	bool is_array() const;
	bool is_userdata() const;
	bool is_closure() const;
	bool is_nativeclosure() const;
	bool is_generator() const;
	bool is_userpointer() const;
	bool is_thread() const;
	bool is_class() const;
	bool is_instance() const;
	bool is_weakref() const;

	object get(uint _key) const;
	object get(const wchar* _key) const;
	void set(uint _key, const value &_v);
	void set(const wchar* _key, const value &_v);

	object operator [] (uint _key) const;
	object operator [] (const wchar* _key) const;

	object operator () (const value &_a0 = value(), const value &_a1 = value(), const value &_a2 = value(), const value &_a3 = value(), const value &_a4 = value());

private:
	machine &m_machine;
	uint m_ID;
};