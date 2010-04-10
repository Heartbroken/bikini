/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace script { /*----------------------------------------------------------------------------*/

static void print_function(HSQUIRRELVM, const SQChar* _format, ...)
{
	va_list l_args;
	va_start(l_args, _format);

	vwprintf(_format, l_args);

	va_end(l_args);
}

machine::machine(uint _stacksize)
:
	m_handle(sq_open(_stacksize))
{
	sq_setprintfunc((HSQUIRRELVM)m_handle, &print_function, &print_function);
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

object machine::call(const object &_closure, const values &_args)
{
	if (sg_objects.exists(_closure.ID()))
	{
		uint l_top = sq_gettop((HSQUIRRELVM)m_handle);

		sq_pushobject((HSQUIRRELVM)m_handle, sg_objects.get(_closure.ID()));
		sq_pushroottable((HSQUIRRELVM)m_handle);
		// push arguments

		if (SQ_SUCCEEDED(sq_call((HSQUIRRELVM)m_handle, 1, true, true)))
		{
			object l_result(*this);
			sq_pop((HSQUIRRELVM)m_handle, 1);

			return l_result;
		}

		sq_settop((HSQUIRRELVM)m_handle, l_top);
	}

	return object();
}

} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
