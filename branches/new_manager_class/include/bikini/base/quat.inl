/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// quat
template<typename _T>
inline quat_<_T>::quat_()
{}
template<typename _T>
inline quat_<_T>::quat_(_T _i, _T _j, _T _k, _T _r) :
	matrix_<1, 4, _T>(_i, _j, _k, _r)
{}
template<typename _T>
inline const _T quat_<_T>::i() const {
	return x();
}
template<typename _T>
inline _T& quat_<_T>::i() {
	return x();
}
template<typename _T>
inline const _T quat_<_T>::j() const {
	return y();
}
template<typename _T>
inline _T& quat_<_T>::j() {
	return y();
}
template<typename _T>
inline const _T quat_<_T>::k() const {
	return z();
}
template<typename _T>
inline _T& quat_<_T>::k() {
	return z();
}
template<typename _T>
inline const _T quat_<_T>::r() const {
	return w();
}
template<typename _T>
inline _T& quat_<_T>::r() {
	return w();
}
