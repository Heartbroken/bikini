/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if !defined(XBOX)
#	error Wrong system include!!!
#endif

#define _XBOX_CRT_DEPRECATE_INSECURE

#include "xtl.h"

#ifdef min
#	undef min
#endif

#ifdef max
#	undef max
#endif

#ifdef _T
#	undef _T
#endif

#ifdef UNICODE
#	undef UNICODE
#endif
