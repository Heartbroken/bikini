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


} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
