/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

astring utf8(const wstring &_s)
{
	uint l_wlength = _s.length();
	uint l_alength = WideCharToMultiByte(CP_UTF8, 0, _s.c_str(), l_wlength, 0, 0, 0, 0);

	astring l_s; l_s.resize(l_alength);
	WideCharToMultiByte(CP_UTF8, 0, _s.c_str(), l_wlength, &l_s[0], l_alength, 0, 0);

	return l_s;
}
wstring utf8(const astring &_s)
{
	uint l_alength = _s.length();
	uint l_wlength = MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), l_alength, 0, 0);

	wstring l_s; l_s.resize(l_wlength);
	MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), l_alength, &l_s[0], l_wlength);

	return l_s;
}
//_string format(const _string &_format, ...)
//{
//	va_list l_args;
//	va_start(l_args, _format);
//
//	const uint l_buffer_max = 1024;
//	achar l_buffer[l_buffer_max];
//
//	sint l_length = vsprintf_s(l_buffer, _format, l_args);
//	
//	if (l_length <= 0) return "";
//
//	l_buffer[l_length] = 0;
//
//	static achar_array l_data;
//	l_data.assign(l_buffer, l_buffer + l_length + 1);
//
//	va_end(l_args);
//
//	return &l_data[0];
//}
_string _format(const wchar* _f, ...)
{
	va_list l_args;
	va_start(l_args, _f);

	const uint l_buffer_max = 1024;
	wchar l_buffer[l_buffer_max];

	sint l_length = vswprintf_s(l_buffer, _f, l_args);
	
	if (l_length <= 0) return L"";

	l_buffer[l_length] = 0;

	static wchar_array l_data;
	l_data.assign(l_buffer, l_buffer + l_length + 1);

	va_end(l_args);

	return &l_data[0];
}
_string print_GUID(const GUID &_g)
{
	return format("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", _g.Data1, _g.Data2, _g.Data3, _g.Data4[0], _g.Data4[1], _g.Data4[2], _g.Data4[3], _g.Data4[4], _g.Data4[5], _g.Data4[6], _g.Data4[7]);
}
//GUID scan_GUID(const astring &_s)
//{
//	byte l_buff[18]; GUID &l_g = *(GUID*)l_buff;
//	if (sscanf_s(_s.c_str(), "{%lx-%hx-%hx-%hx-%llx}", &l_g.Data1, &l_g.Data2, &l_g.Data3, &l_g.Data4[0], &l_g.Data4[2]) != 5) return bad_GUID;
//	swap(l_g.Data4[0], l_g.Data4[1]);
//	swap(l_g.Data4[2], l_g.Data4[7]);
//	swap(l_g.Data4[3], l_g.Data4[6]);
//	swap(l_g.Data4[4], l_g.Data4[5]);
//	return l_g;
//}

GUID scan_GUID(const _string &_s)
{
	byte l_buff[18]; GUID &l_g = *(GUID*)l_buff;
	if (swscanf_s(_s.wstr.c_str(), L"{%lx-%hx-%hx-%hx-%llx}", &l_g.Data1, &l_g.Data2, &l_g.Data3, &l_g.Data4[0], &l_g.Data4[2]) != 5) return bad_GUID;
	swap(l_g.Data4[0], l_g.Data4[1]);
	swap(l_g.Data4[2], l_g.Data4[7]);
	swap(l_g.Data4[3], l_g.Data4[6]);
	swap(l_g.Data4[4], l_g.Data4[5]);
	return l_g;
}

} /* namespace bk -------------------------------------------------------------------------------*/
