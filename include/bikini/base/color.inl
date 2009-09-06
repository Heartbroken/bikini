/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// color
template<typename _T>
inline color_<_T>::color_()
{}
template<typename _T>
inline color_<_T>::color_(_T _r, _T _g, _T _b, _T _a) :
	matrix_<1, 4, _T>(_r, _g, _b, _a)
{}
template<typename _T>
inline color_<_T>::color_(u8 _r, u8 _g, u8 _b, u8 _a) :
	matrix_<1, 4, _T>(_T(_r)/_T(255), _T(_g)/_T(255), _T(_b)/_T(255), _T(_a)/_T(255))
{}
template<typename _T>
inline color_<_T>::color_(u32 _c) :
	matrix_<1, 4, _T>(_T((_c>>16)&0xff)/_T(255), _T((_c>>8)&0xff)/_T(255), _T((_c>>0)&0xff)/_T(255), _T((_c>>24)&0xff)/_T(255))
{}
template<typename _T>
inline const _T color_<_T>::r() const {
	return x();
}
template<typename _T>
inline _T& color_<_T>::r() {
	return x();
}
template<typename _T>
inline const _T color_<_T>::g() const {
	return y();
}
template<typename _T>
inline _T& color_<_T>::g() {
	return y();
}
template<typename _T>
inline const _T color_<_T>::b() const {
	return z();
}
template<typename _T>
inline _T& color_<_T>::b() {
	return z();
}
template<typename _T>
inline const _T color_<_T>::a() const {
	return w();
}
template<typename _T>
inline _T& color_<_T>::a() {
	return w();
}
template<typename _T>
inline color_<_T>::operator u32 () const {
	return (u32(a()*_T(255))<<24)|(u32(r()*_T(255))<<16)|(u32(g()*_T(255))<<8)|(u32(b()*_T(255))<<0);
}
