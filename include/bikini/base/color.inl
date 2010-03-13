/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// color
template<typename _T>
inline color_<_T>::color_()
{}
template<typename _T>
inline color_<_T>::color_(_T _r, _T _g, _T _b, _T _a)
:
	r(_r), g(_g), b(_b), a(_a)
{}
template<typename _T>
inline color_<_T>::color_(u8 _r, u8 _g, u8 _b, u8 _a)
:
	r(_T(_r)/_T(255)), g(_T(_g)/_T(255)), b(_T(_b)/_T(255)), a(_T(_a)/_T(255))
{}
template<typename _T>
inline color_<_T>::color_(u32 _c)
:
	r(_T((_c>>16)&0xff)/_T(255)), g(_T((_c>>8)&0xff)/_T(255)), b(_T((_c>>0)&0xff)/_T(255)), a(_T((_c>>24)&0xff)/_T(255))
{
}
//template<typename _T>
//inline const _T color_<_T>::r() const
//{
//	return x();
//}
//template<typename _T>
//inline _T& color_<_T>::r()
//{
//	return x();
//}
//template<typename _T>
//inline const _T color_<_T>::g() const
//{
//	return y();
//}
//template<typename _T>
//inline _T& color_<_T>::g()
//{
//	return y();
//}
//template<typename _T>
//inline const _T color_<_T>::b() const
//{
//	return z();
//}
//template<typename _T>
//inline _T& color_<_T>::b()
//{
//	return z();
//}
//template<typename _T>
//inline const _T color_<_T>::a() const
//{
//	return w();
//}
//template<typename _T>
//inline _T& color_<_T>::a()
//{
//	return w();
//}
template<typename _T>
inline color_<_T>::operator u32 () const
{
	return
	(
		((0xff & u32(a * _T(255))) << 24)|
		((0xff & u32(r * _T(255))) << 16)|
		((0xff & u32(g * _T(255))) <<  8)|
		((0xff & u32(b * _T(255))) <<  0)
	);
}

// cxform
template<typename _T>
inline cxform_<_T>::cxform_()
:
	m_mul(white), m_add(black)
{
}
template<typename _T>
inline cxform_<_T>::cxform_(const color &_mul, const color &_add)
:
	m_mul(_mul), m_add(_add)
{
}
template<typename _T>
inline const typename cxform_<_T>::color cxform_<_T>::transform(const color &_c) const
{
	return color
	(
		clamp(_c.r() * m_mul.r() + m_add.r(), _Type(0), _Type(1)),
		clamp(_c.g() * m_mul.g() + m_add.g(), _Type(0), _Type(1)),
		clamp(_c.b() * m_mul.b() + m_add.b(), _Type(0), _Type(1)),
		clamp(_c.a() * m_mul.a() + m_add.a(), _Type(0), _Type(1))
	);
}
