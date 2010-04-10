/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine;

struct object
{
	object();
	object(machine &_machine);
	~object();

	inline bool valid() const { return &m_machine == 0; }

private:
	machine &m_machine;
	uint m_reference;
};