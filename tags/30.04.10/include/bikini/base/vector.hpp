/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///
template
<
	typename _Vector,
	typename _Element,
	uint _Size,
	uint _Extra = 0
>
struct _vector_
:
	_matrix_<_Vector, _Element, _Size, 1, sizeof(_Element) * (_Size + _Extra)>
{
	typedef _Vector vector;

	const _Element& operator [] (uint _i) const;
	_Element& operator [] (uint _i);

	//template <typename _V1, typename _E1, uint _S1, uint _Ex1>
	//inline operator typename _vector_<_V1, _E1, _S1, _Ex1>::vector () const
	//{
	//	return *(_vector_<_V1, _E1, _S1, _Ex1>::vector*)this;
	//}
};

template <typename _Type, uint _Size, uint _Extra = 0>
struct vector_
:
	_vector_<vector_<_Type, _Size>, _Type, _Size>
{
	_Type v[_Size + _Extra];
};

template <typename _Type>
struct vector_<_Type, 1>
:
	_vector_<vector_<_Type, 1>, _Type, 1>
{
	_Type x;

	inline vector_();
	explicit inline vector_(_Type _x);
};

template <typename _Type>
struct vector_<_Type, 2>
:
	_vector_<vector_<_Type, 2>, _Type, 2>
{
	_Type x, y;

	inline vector_();
	inline vector_(_Type _x, _Type _y);
};

template <typename _Type>
struct vector_<_Type, 3>
:
	_vector_<vector_<_Type, 3>, _Type, 3>
{
	_Type x, y, z;

	inline vector_();
	inline vector_(_Type _x, _Type _y, _Type _z);
};

template <typename _Type>
struct vector_<_Type, 4>
:
	_vector_<vector_<_Type, 4>, _Type, 4>
{
	_Type x, y, z, w;

	inline vector_();
	inline vector_(_Type _x, _Type _y, _Type _z, _Type _w);
};

template <typename _T, uint _S, uint _E>
inline const _T dot(const vector_<_T, _S, _E> &_a, const vector_<_T, _S, _E> &_b);

template <typename _T, uint _S, uint _E>
inline const _T length(const vector_<_T, _S, _E> &_a);
template <typename _T, uint _S, uint _E>
inline const _T length2(const vector_<_T, _S, _E> &_a);

template <typename _T, uint _S, uint _E>
inline const vector_<_T, _S, _E> normalize(const vector_<_T, _S, _E> &_a);

template <typename _T, uint _E>
inline const vector_<_T, 2, _E> cross(const vector_<_T, 2, _E> &_a);
template <typename _T, uint _E>
inline const _T cross(const vector_<_T, 2, _E> &_a, const vector_<_T, 2, _E> &_b);
template <typename _T, uint _E>
inline const vector_<_T, 3, _E> cross(const vector_<_T, 3, _E> &_a, const vector_<_T, 3, _E> &_b);
template <typename _T, uint _E>
inline const _T cross(const vector_<_T, 3, _E> &_a, const vector_<_T, 3, _E> &_b, const vector_<_T, 3, _E> &_c);

template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector_<_T, _C> mul(const vector_<_T, _R, _Ea> &_a, const matrix_<_T, _C, _R, _Eb> &_b);
template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector_<_T, _R> mul(const matrix_<_T, _C, _R, _Eb> &_a, const vector_<_T, _C, _Ea> &_b);

typedef vector_<sint, 2> sint2;
typedef vector_<float, 2> float2;
typedef vector_<float, 3> float3;
typedef vector_<float, 4> float4;
typedef vector_<real, 2> real2;
typedef vector_<real, 3> real3;
typedef vector_<real, 4> real4;

const sint2 sint2_0(s_0, s_0);
const sint2 sint2_1(s_1, s_1);
const sint2 sint2_x(s_1, s_0);
const sint2 sint2_y(s_0, s_1);
const float2 float2_0(f_0, f_0);
const float2 float2_x(f_1, f_0);
const float2 float2_y(f_0, f_1);
const float3 float3_0(f_0, f_0, f_0);
const float3 float3_x(f_1, f_0, f_0);
const float3 float3_y(f_0, f_1, f_0);
const float3 float3_z(f_0, f_0, f_1);
const real2 real2_0(r_0, r_0);
const real2 real2_x(r_1, r_0);
const real2 real2_y(r_0, r_1);
const real3 real3_0(r_0, r_0, r_0);
const real3 real3_x(r_1, r_0, r_0);
const real3 real3_y(r_0, r_1, r_0);
const real3 real3_z(r_0, r_0, r_1);

#include "vector.inl"
