/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace script { /*----------------------------------------------------------------------------*/

machine::machine(uint _stacksize)
:
	m_handle(sq_open(_stacksize))
{
}
machine::~machine()
{
	sq_close((HSQUIRRELVM)m_handle);
}

object machine::compile(const wchar* _code, const wchar* _name)
{
	struct _l { static SQInteger read(SQUserPointer _code)
	{
		wchar* &l_code = *(wchar**)_code;
		return *(l_code++);
	}};

	if (SQ_SUCCEEDED(sq_compile((HSQUIRRELVM)m_handle, &_l::read, &_code, _name, false)))
		return object(*this);

	return object();
}

static pool_<HSQOBJECT> sg_objects;
uint machine::make_reference()
{
	HSQOBJECT l_object;
	sq_resetobject(&l_object);
	sq_getstackobj((HSQUIRRELVM)m_handle, -1, &l_object);
	sq_addref((HSQUIRRELVM)m_handle, &l_object);
	sq_pop((HSQUIRRELVM)m_handle, 1);

	return sg_objects.add(l_object);
}
void machine::free_reference(uint _ID)
{
	if (sg_objects.exists(_ID))
	{
		sq_release((HSQUIRRELVM)m_handle, &sg_objects.get(_ID));
		sg_objects.remove(_ID);
	}
}

} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
