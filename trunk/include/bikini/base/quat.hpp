/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// quaternion template
template<typename _Type>
struct quat_
:
	_vector_<quat_<_Type>, _Type, 4>
{
	_Type i, j, k, r;

	inline quat_();
	//{}
	inline quat_(_Type _i, _Type _j, _Type _k, _Type _r);
	//:
	//	i(_i), j(_j), k(_k), r(_r)
	//{}
};

//template<typename _Type>
//struct quat_ : matrix_<1, 4, _Type> {
//	inline quat_();
//	inline quat_(_Type _i, _Type _j, _Type _k, _Type _r);
//	inline const _Type i() const;
//	inline _Type& i();
//	inline const _Type j() const;
//	inline _Type& j();
//	inline const _Type k() const;
//	inline _Type& k();
//	inline const _Type r() const;
//	inline _Type& r();
//};
typedef quat_<real> quat;

/// unit quaternion
const quat_<real> quat_1(r_0, r_0, r_0, r_1);

#include "quat.inl"
