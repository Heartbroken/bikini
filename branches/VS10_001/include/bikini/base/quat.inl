/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// quat

template<typename _T>
inline quat_<_T>::quat_()
{}
template<typename _T>
inline quat_<_T>::quat_(_T _i, _T _j, _T _k, _T _r)
:
	i(_i), j(_j), k(_k), r(_r)
{}
