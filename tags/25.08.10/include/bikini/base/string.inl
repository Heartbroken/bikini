/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _string

inline _string::_string()
{}
inline _string::_string(const _string & _s)
	:
	astr(_s.astr), wstr(_s.wstr)
{}
inline _string::_string(const astring & _s)
	:
	astr(_s), wstr(utf8(_s))
{}
inline _string::_string(const wstring & _s)
	:
	astr(utf8(_s)), wstr(_s)
{}
inline _string::_string(const achar * _s)
	:
	astr(_s), wstr(utf8(_s))
{}
inline _string::_string(const wchar * _s)
	:
	astr(utf8(_s)), wstr(_s)
{}
inline _string & _string::operator = (const _string & _s)
{
	astr = _s.astr; wstr = _s.wstr;
	return *this;
}
inline _string & _string::operator = (const astring & _s)
{
	astr = _s; wstr = utf8(_s);
	return *this;
}
inline _string & _string::operator = (const wstring & _s)
{
	astr = utf8(_s); wstr = _s;
	return *this;
}
inline _string & _string::operator = (const achar * _s)
{
	astr = _s; wstr = utf8(_s);
	return *this;
}
inline _string & _string::operator = (const wchar * _s)
{
	astr = utf8(_s); wstr = _s;
	return *this;
}
inline _string::operator astring&()
{
	return astr;
}
inline _string::operator wstring&()
{
	return wstr;
}
inline _string::operator const achar*()
{
	return astr.c_str();
}
inline _string::operator const wchar*()
{
	return wstr.c_str();
}

// format
_string format(wchar const * _f, ...);
_string format(achar const * _f, ...);

//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11, typename _A12>
//inline astring format(const achar* _f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A10 &_a10, const _A11 &_a11, const _A12 &_a12)
//{
//	return _format(_f, _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11, typename _A12>
//inline wstring format(const wchar* _f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A10 &_a10, const _A11 &_a11, const _A12 &_a12)
//{
//	return _format(_f, _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12);
//}

//////
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11, typename _A12>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A10 &_a10, const _A11 &_a11, const _A12 &_a12)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10, typename _A11>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A10 &_a10, const _A11 &_a11)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9, typename _A10>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9, const _A10 &_a10)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8, typename _A9>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8, const _A9 &_a9)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7, typename _A8>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7, const _A8 &_a8)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6, typename _A7>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6, const _A7 &_a7)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5, typename _A6>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5, const _A6 &_a6)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5, _a6);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4, const _A5 &_a5)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4, _a5);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3, const _A4 &_a4)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3, _a4);
//}
//template<typename _A0, typename _A1, typename _A2, typename _A3>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2, const _A3 &_a3)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2, _a3);
//}
//template<typename _A0, typename _A1, typename _A2>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1, const _A2 &_a2)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1, _a2);
//}
//template<typename _A0, typename _A1>
//inline _string format(const _string &_f, const _A0 &_a0, const _A1 &_a1)
//{
//	return _format(_f.wstr.c_str(), _a0, _a1);
//}
//template<typename _A0>
//inline _string format(const _string &_f, const _A0 &_a0)
//{
//	return _format(_f.wstr.c_str(), _a0);
//}
