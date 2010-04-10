/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace script { /*----------------------------------------------------------------------------*/

object::object()
:
	m_machine(*(machine*)0),
	m_ID(bad_ID)
{
}
object::object(machine &_machine)
:
	m_machine(_machine),
	m_ID(m_machine.make_reference())
{
}
object::~object()
{
	if (&m_machine != 0)
	{
		m_machine.free_reference(m_ID);
	}
}

bool object::is_valid() const
{
	return &m_machine != 0;
}

object object::operator () (const value &_a0, const value &_a1, const value &_a2, const value &_a3, const value &_a4)
{
	struct _l { static void push(values &_args, const value &_a0, const value &_a1, const value &_a2, const value &_a3, const value &_a4)
	{
		if (_a0.is_nothing()) return;

		_args.push_back(_a0);
		push(_args, _a1, _a2, _a3, _a4, value());
	}};

	values l_args;
	_l::push(l_args, _a0, _a1, _a2, _a3, _a4);

	return m_machine.call(*this, l_args);
}

} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
