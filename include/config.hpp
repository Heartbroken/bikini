/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// Configuration and platform

#if defined(_PROFILE)
#	define _CONFIGURATION_ "profile"
#elif defined(_DEBUG)
#	define _CONFIGURATION_ "debug"
#else
#	define _CONFIGURATION_ "release"
#endif

#if defined(_XBOX)
#	define _PLATFORM_ "xbox 360"
#elif defined(_WIN64)
#	define _PLATFORM_ "x64"
#else
#	define _PLATFORM_ "win32"
#endif

//	Math

/// If this is defined type bk::real is double, else float
//#define BIKINI_REAL_IS_DOUBLE

