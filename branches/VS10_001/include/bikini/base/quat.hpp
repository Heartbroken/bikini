/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// quaternion template
template <typename _Type>
struct quat_
:
	_vector_<quat_<_Type>, _Type, 4>
{
	_Type i, j, k, r;

	inline quat_();
	inline quat_(_Type _i, _Type _j, _Type _k, _Type _r);
};

typedef quat_<real> quat;

/// unit quaternion
const quat_<real> quat_1(r_0, r_0, r_0, r_1);

DECLARE_UTEST(quat);

#include "quat.inl"
