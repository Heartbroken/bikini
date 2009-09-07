/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// Configuration and platform

#ifdef _DEBUG
#	define _CONFIGURATION_ "debug"
#elif NDEBUG
#	define _CONFIGURATION_ "release"
#endif
#ifdef _XBOX
#	define _PLATFORM_ "xbox 360"
#elif _WIN64
#	define _PLATFORM_ "x64"
#elif _WIN32
#	define _PLATFORM_ "win32"
#endif

//	Math

/// If this is defined type bk::real is double, else float
//#define BIKINI_REAL_IS_DOUBLE

