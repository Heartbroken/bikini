/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// create random GUID
inline GUID random_GUID(random &_random = random_0);

inline const achar* format(const GUID &_g)
{
	return format("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", _g.Data1, _g.Data2, _g.Data3, _g.Data4[0], _g.Data4[1], _g.Data4[2], _g.Data4[3], _g.Data4[4], _g.Data4[5], _g.Data4[6], _g.Data4[7]);
}

/// bad GUID
const GUID bad_GUID = { 0xffffffff, 0xffff, 0xffff, { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } };

inline GUID scan_GUID(const astring &_s)
{
	byte l_buff[18]; GUID &l_g = *(GUID*)l_buff;
	if (sscanf_s(_s.c_str(), "{%lx-%hx-%hx-%hx-%llx}", &l_g.Data1, &l_g.Data2, &l_g.Data3, &l_g.Data4[0], &l_g.Data4[2]) != 5) return bad_GUID;
	swap(l_g.Data4[0], l_g.Data4[1]);
	swap(l_g.Data4[2], l_g.Data4[7]);
	swap(l_g.Data4[3], l_g.Data4[6]);
	swap(l_g.Data4[4], l_g.Data4[5]);
	return l_g;
}
inline GUID scan_GUID(const wstring &_s)
{
	byte l_buff[18]; GUID &l_g = *(GUID*)l_buff;
	if (swscanf_s(_s.c_str(), L"{%lx-%hx-%hx-%hx-%llx}", &l_g.Data1, &l_g.Data2, &l_g.Data3, &l_g.Data4[0], &l_g.Data4[2]) != 5) return bad_GUID;
	swap(l_g.Data4[0], l_g.Data4[1]);
	swap(l_g.Data4[2], l_g.Data4[7]);
	swap(l_g.Data4[3], l_g.Data4[6]);
	swap(l_g.Data4[4], l_g.Data4[5]);
	return l_g;
}

#include "GUID.inl"
