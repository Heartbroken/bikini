/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ game programming library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// Configuration and platform

#ifdef _DEBUG
#	define _CONFIGURATION "debug"
#elif NDEBUG
#	define _CONFIGURATION "release"
#endif
#ifdef _XBOX
#	define _PLATFORM "xbox 360"
#elif _WIN32
#	define _PLATFORM "win32"
#endif

//	Math

/// If this is defined type bk::real is double, else float
//#define BIKINI_REAL_IS_DOUBLE

