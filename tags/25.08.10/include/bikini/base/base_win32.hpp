/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#if !defined(WIN32)
#	error Wrong system include!!!
#endif

#ifndef _WIN32_WINNT
#	define _WIN32_WINNT	0x0501
#endif
#define VC_EXTRALEAN

#ifndef _CRT_SECURE_NO_DEPRECATE
#	define _CRT_SECURE_NO_DEPRECATE
#endif

// this speeds up windows.h processing dramatically...
#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NOMINMAX

#include <windows.h>

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

#ifdef RGB
#	undef RGB
#endif
