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
		bool, u8, s8, u16, s16, u32, s32, u64, s64, const wchar*, wchar, object
	>::type
> value;

typedef array_<value> values;

struct object
{
	object();
	object(machine &_machine);
	~object();

	inline uint ID() const { return m_ID; }

	bool is_valid() const;

	object operator () ();

private:
	machine &m_machine;
	uint m_ID;
};