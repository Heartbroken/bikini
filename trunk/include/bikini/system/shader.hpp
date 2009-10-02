/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once


#define make_a_string(_ARG) #_ARG

#if defined _XBOX
#	define compiled_shader(_NAME) make_a_string(_NAME.xbox 360.h)
#elif defined _WIN64
#	define compiled_shader(_NAME) make_a_string(_NAME.x64.h)
#elif defined _WIN32
#	define compiled_shader(_NAME) make_a_string(_NAME.win32.h)
#endif

namespace shader { /*----------------------------------------------------------------------------*/

#include "shader.shh"

} /* namespace shader ---------------------------------------------------------------------------*/
