/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace script { /*----------------------------------------------------------------------------*/

static pool_<HSQOBJECT> sg_objects;

void compiler_error_handler(HSQUIRRELVM, const SQChar* _desc, const SQChar* _source, SQInteger _line, SQInteger _column)
{
	wprintf(L"%s(%d) : error: %s\n", _source, _line, _desc);
}
SQInteger runtime_error_handler(HSQUIRRELVM _vm)
{
	const wchar* l_desc = 0; sq_getstring(_vm, -1, &l_desc);
	SQStackInfos l_si; sq_stackinfos(_vm, 1, &l_si);

	wprintf(L"%s(%d) : error: %s\n", l_si.source, l_si.line, l_desc);

	return 0;
}
static void print_function(HSQUIRRELVM, const SQChar* _format, ...)
{
	va_list l_args;
	va_start(l_args, _format);

	vwprintf(_format, l_args);

	va_end(l_args);
}

static void push(HSQUIRRELVM _vm, const value &_v)
{
	switch(_v.type())
	{
	case value::types::type_<bool>::index :
		sq_pushbool(_vm, _v.get_<bool>());
		break;
	case value::types::type_<u8>::index :
		sq_pushinteger(_vm, _v.get_<u8>());
		break;
	case value::types::type_<s8>::index :
		sq_pushinteger(_vm, _v.get_<s8>());
		break;
	case value::types::type_<u16>::index :
		sq_pushinteger(_vm, _v.get_<u16>());
		break;
	case value::types::type_<s16>::index :
		sq_pushinteger(_vm, _v.get_<s16>());
		break;
	case value::types::type_<u32>::index :
		sq_pushinteger(_vm, _v.get_<u32>());
		break;
	case value::types::type_<s32>::index :
		sq_pushinteger(_vm, _v.get_<s32>());
		break;
	//case value::types::type_<u64>::index :
	//	sq_pushinteger(_vm, _v.get_<u64>());
	//	break;
	//case value::types::type_<s64>::index :
	//	sq_pushinteger(_vm, _v.get_<s64>());
	//	break;
	case value::types::type_<float>::index :
		sq_pushfloat(_vm, _v.get_<float>());
		break;
	case value::types::type_<const wchar*>::index :
		sq_pushstring(_vm, _v.get_<const wchar*>(), wcslen(_v.get_<const wchar*>()));
		break;
	case value::types::type_<wchar*>::index :
		sq_pushstring(_vm, _v.get_<wchar*>(), wcslen(_v.get_<wchar*>()));
		break;
	case value::types::type_<object>::index :
		sq_pushobject(_vm, sg_objects.get(_v.get_<object>().ID()));
		break;
	default:
		sq_pushnull(_vm);
	}
}

machine::machine(uint _stacksize)
:
	m_handle(sq_open(_stacksize))
{
	HSQUIRRELVM l_vm = (HSQUIRRELVM)m_handle;

	sq_setprintfunc(l_vm, &print_function, &print_function);

	sq_notifyallexceptions(l_vm, true);
	sq_setcompilererrorhandler(l_vm, &compiler_error_handler);

	sq_newclosure(l_vm, &runtime_error_handler, 0);
	sq_seterrorhandler(l_vm);

}
machine::~machine()
{
	sq_close((HSQUIRRELVM)m_handle);
}

object machine::compile(const wchar* _code, const wchar* _name)
{
	//struct _l { static SQInteger read(SQUserPointer _code)
	//{
	//	wchar* &l_code = *(wchar**)_code;
	//	return *(l_code++);
	//}};

	//if (SQ_SUCCEEDED(sq_compile((HSQUIRRELVM)m_handle, &_l::read, &_code, _name, true)))
	//	return object(*this);

	HSQUIRRELVM l_vm = (HSQUIRRELVM)m_handle;

	sq_enabledebuginfo(l_vm, true);

	if (SQ_SUCCEEDED(sq_compilebuffer((HSQUIRRELVM)m_handle, _code, wcslen(_code), _name, true)))
		return object(*this);

	return object();
}

object machine::root()
{
	sq_pushroottable((HSQUIRRELVM)m_handle);
	return object(*this);
}

uint machine::make_reference()
{
	HSQOBJECT l_object;
	sq_resetobject(&l_object);
	sq_getstackobj((HSQUIRRELVM)m_handle, -1, &l_object);
	sq_addref((HSQUIRRELVM)m_handle, &l_object);
	sq_pop((HSQUIRRELVM)m_handle, 1);

	return sg_objects.add(l_object);
}
uint machine::add_reference(uint _ID)
{
	if (sg_objects.exists(_ID))
		sq_addref((HSQUIRRELVM)m_handle, &sg_objects.get(_ID));

	return _ID;
}
void machine::free_reference(uint _ID)
{
	if (sg_objects.exists(_ID))
		if (sq_release((HSQUIRRELVM)m_handle, &sg_objects.get(_ID)))
			sg_objects.remove(_ID);
}

bool machine::is_null(const object &_v) const
{
	HSQUIRRELVM l_vm = (HSQUIRRELVM)m_handle;

	push(l_vm, _v);
	SQObjectType l_type = sq_gettype(l_vm, -1);
	sq_pop(l_vm, 1);

	return l_type == OT_NULL;
}

object machine::index(const object &_table, const wchar* _key)
{
	if (sg_objects.exists(_table.ID()))
	{
		HSQUIRRELVM l_vm = (HSQUIRRELVM)m_handle;

		uint l_top = sq_gettop(l_vm);

		push(l_vm, _table);
		sq_pushstring(l_vm, _key, wcslen(_key));

		if (SQ_SUCCEEDED(sq_get(l_vm, -2)))
		{
			object l_result(*this);
			sq_pop(l_vm, 1);
			return l_result;
		}

		sq_settop(l_vm, l_top);
	}

	return object();
}
object machine::call(const object &_closure, const values &_args)
{
	if (sg_objects.exists(_closure.ID()))
	{
		HSQUIRRELVM l_vm = (HSQUIRRELVM)m_handle;

		uint l_top = sq_gettop(l_vm);

		push(l_vm, _closure);

		sq_pushroottable(l_vm); // push 'this'
		
		for (uint i = 0, s = _args.size(); i < s; ++i)
			push(l_vm, _args[i]);

		if (SQ_SUCCEEDED(sq_call(l_vm, _args.size() + 1, true, true)))
		{
			object l_result(*this);
			sq_pop(l_vm, 1);

			return l_result;
		}
		//else
		//{
		//	sq_getlasterror(l_vm);
		//	const wchar* l_error = 0;
		//	sq_getstring(l_vm, -1, &l_error);

		//	if (l_error != 0)
		//		wprintf(L"%s\n", l_error);
		//}

		sq_settop(l_vm, l_top);
	}

	return object();
}

} /* namespace script ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
