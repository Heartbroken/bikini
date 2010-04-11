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
object::object(const object &_object)
:
	m_machine(_object.get_machine()),
	m_ID(_object.is_valid() ? m_machine.add_reference(_object.ID()) : bad_ID)
{
}
object::~object()
{
	if (is_valid())
		m_machine.free_reference(m_ID);
}

object& object::operator = (const object &_object)
{
	this->~object();
	new(this) object(_object);

	return *this;
}

bool object::is_valid() const
{
	return &m_machine != 0;
}
bool object::is_null() const
{
	return is_valid() && m_machine.is_null(*this);
}
bool object::is_integer() const
{
	return is_valid() && m_machine.is_integer(*this);
}
bool object::is_float() const
{
	return is_valid() && m_machine.is_float(*this);
}
bool object::is_bool() const
{
	return is_valid() && m_machine.is_bool(*this);
}
bool object::is_string() const
{
	return is_valid() && m_machine.is_string(*this);
}
bool object::is_table() const
{
	return is_valid() && m_machine.is_table(*this);
}
bool object::is_array() const
{
	return is_valid() && m_machine.is_array(*this);
}
bool object::is_userdata() const
{
	return is_valid() && m_machine.is_userdata(*this);
}
bool object::is_closure() const
{
	return is_valid() && m_machine.is_closure(*this);
}
bool object::is_nativeclosure() const
{
	return is_valid() && m_machine.is_nativeclosure(*this);
}
bool object::is_generator() const
{
	return is_valid() && m_machine.is_generator(*this);
}
bool object::is_userpointer() const
{
	return is_valid() && m_machine.is_userpointer(*this);
}
bool object::is_thread() const
{
	return is_valid() && m_machine.is_thread(*this);
}
bool object::is_class() const
{
	return is_valid() && m_machine.is_class(*this);
}
bool object::is_instance() const
{
	return is_valid() && m_machine.is_instance(*this);
}
bool object::is_weakref() const
{
	return is_valid() && m_machine.is_weakref(*this);
}

sint object::to_integer(sint _default) const
{
	return is_valid() ? m_machine.to_integer(*this, _default) : _default;
}
real object::to_float(real _default) const
{
	return is_valid() ? m_machine.to_float(*this, _default) : _default;
}
bool object::to_bool(bool _default) const
{
	return is_valid() ? m_machine.to_bool(*this, _default) : _default;
}
const wchar* object::to_string(const wchar* _default) const
{
	return is_valid() ? m_machine.to_string(*this, _default) : _default;
}

object object::get(uint _key) const
{
	return is_valid() ? m_machine.get(*this, _key) : object();
}
object object::get(const wchar* _key) const
{
	return is_valid() ? m_machine.get(*this, _key) : object();
}
void object::set(uint _key, const value &_v)
{
	if (is_valid()) m_machine.set(*this, _key, _v);
}
void object::set(const wchar* _key, const value &_v)
{
	if (is_valid()) m_machine.set(*this, _key, _v);
}

object object::operator [] (uint _key) const
{
	return get(_key);
}
object object::operator [] (const wchar* _key) const
{
	return get(_key);
}

object object::operator () (const value &_a0, const value &_a1, const value &_a2, const value &_a3, const value &_a4)
{
	if (!is_valid()) return object();

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
