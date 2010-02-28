/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// create random GUID
inline GUID random_GUID(random &_random = random_0);

_string print_GUID(const GUID &_g);
GUID scan_GUID(const _string &_s);
//GUID scan_GUID(const wstring &_s);

/// bad GUID
const GUID bad_GUID = { 0xffffffff, 0xffff, 0xffff, { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } };

#include "GUID.inl"
