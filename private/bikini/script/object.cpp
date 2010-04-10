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
	m_reference(bad_ID)
{
}
object::object(machine &_machine)
:
	m_machine(_machine),
	m_reference(m_machine.make_reference())
{
}
object::~object()
{
	if (&m_machine != 0)
	{
		m_machine.free_reference(m_reference);
	}
}

} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
