/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2011 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct object
{
	friend struct simulator;

	struct UID
	{
		u32 type : 5, index : 16, counter : 11;
		inline UID(uint _ID = bad_ID) { *(u32*)this = (u32)_ID; }
		inline operator uint () const { return *(uint*)this; }
	};

	inline object();
	inline object(const object &_o);
	inline object& operator = (const object &_o);

	inline simulator& get_simulator() const;
	inline uint ID() const;

	inline bool is_valid() const;

protected:
	object(const simulator &_simulator);

private:
	simulator &m_simulator;
	UID m_ID;
};

DECLARE_UTEST(dyne_object);

#include "object.inl"