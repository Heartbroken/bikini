/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if defined(XBOX)

//#include <assert.h>

#elif defined(WIN32)

#ifdef halt
#	undef halt
#endif
#ifdef assert
#	undef assert
#endif

bool ARI(wchar const* _expression, wchar const* _file, int _line, wchar const* _function, wchar const* _message = 0);

#define halt { Sleep(1); __debugbreak(); }
#define __T(x) L ## x

#ifdef _DEBUG
#	define assert(E)	while(!(E)) { Sleep(1); if(bk::ARI(_CRT_WIDE(#E), _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(__FUNCTION__))) break; halt; }
#else
#	define assert(E)
#endif

#endif

template<bool> struct compile_time_assert;
template<> struct compile_time_assert<true> {};

#define c_assert(E)	{ bk::compile_time_assert<((E) != 0)> COMPILE_TIME_ERROR; COMPILE_TIME_ERROR; }


void run_unit_tests();