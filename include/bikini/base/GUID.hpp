/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// create random GUID
inline GUID random_GUID(random &_random = random_0);

inline const achar* format(const GUID &_GUID)
{
	return format("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", _GUID.Data1, _GUID.Data2, _GUID.Data3, _GUID.Data4[0], _GUID.Data4[1], _GUID.Data4[2], _GUID.Data4[3], _GUID.Data4[4], _GUID.Data4[5], _GUID.Data4[6], _GUID.Data4[7]);
}

/// bad GUID
const GUID bad_GUID = { 0xffffffff, 0xffff, 0xffff, { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } };

#include "GUID.inl"
