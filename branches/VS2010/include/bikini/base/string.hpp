/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///
astring utf8(const wstring &_s);
wstring utf8(const astring &_s);

///
struct _string
{
	astring astr;
	wstring wstr;
	inline _string();
	inline _string(const _string &_s);
	inline _string(const astring &_s);
	inline _string(const wstring &_s);
	inline _string(const achar* _s);
	inline _string(const wchar* _s);
	inline _string& operator = (const _string &_s);
	inline _string& operator = (const astring &_s);
	inline _string& operator = (const wstring &_s);
	inline _string& operator = (const achar* _s);
	inline _string& operator = (const wchar* _s);
	inline operator astring();
	inline operator wstring();
	inline operator const achar*();
	inline operator const wchar*();
};

///
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11, typename _A12>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A9 &_a10, const _A9 &_a11, const _A9 &_a12);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A9 &_a10, const _A9 &_a11);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A9 &_a10);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5);
template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4);
template<typename _A0, typename _A1, typename _A2, typename _A3>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3);
template<typename _A0, typename _A1, typename _A2>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2);
template<typename _A0, typename _A1>
inline _string format(const _string &_format, const _A0 &_a0, const _A1 &_a1);
template<typename _A0>
inline _string format(const _string &_format, const _A0 &_a0);

#include "string.inl"
