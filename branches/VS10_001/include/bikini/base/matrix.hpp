/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///
template
<
	typename _Matrix,
    typename _Element,
    uint _Columns, uint _Rows,
    uint _Rowstride = sizeof(_Element) * _Columns
>
struct _matrix_
{
	typedef _Matrix matrix;
	typedef _Element element;
	static const uint columns = _Columns;
	static const uint rows = _Rows;

	inline _matrix_& operator - ();
	inline _matrix_& operator = (const _matrix_ &_m);
	inline _matrix_& operator += (const _matrix_ &_m);
	inline _matrix_& operator -= (const _matrix_ &_m);
	inline _matrix_& operator *= (const _matrix_ &_m);
	inline _matrix_& operator /= (const _matrix_ &_m);
	inline _matrix_& operator *= (const _Element & _s);
	inline _matrix_& operator /= (const _Element & _s);

	inline const _Matrix operator + (const _matrix_ &_m) const;
	inline const _Matrix operator - (const _matrix_ &_m) const;
	inline const _Matrix operator * (const _matrix_ &_m) const;
	inline const _Matrix operator / (const _matrix_ &_m) const;
	inline const _Matrix operator * (const _Element & _s) const;
	inline const _Matrix operator / (const _Element & _s) const;

	inline bool operator == (const _matrix_ &_m) const;
	inline bool operator != (const _matrix_ &_m) const;

	template <uint _I, uint _J> inline _Element & cell_();
	template <uint _I, uint _J> inline const _Element & cell_() const;

	struct _row;

	inline const _row & operator [] (uint _i) const;
	inline _row & operator [] (uint _i);

	inline operator _Matrix& ();
	inline operator const _Matrix& () const;

	//inline _matrix_() {}
	//template <typename _M1>
	//explicit inline _matrix_(const _M1 &_m)
	//{
	//	c_assert(_M1::columns >= _C && _M1::rows >= _R);
	//	*this = (_matrix_&)_m;
	//}

	//template <typename _M1, typename _E1, uint _C1, uint _R1, uint _Rs1>
	//inline operator const typename _matrix_<_M1, _E1, _C1, _R1, _Rs1>::matrix () const;

	//template <typename _Matrix1>
	//inline operator _Matrix1 () const;
};

template <typename _Type, uint _Columns, uint _Rows, uint _Extra = 0>
struct matrix_
	:
	_matrix_<matrix_<_Type, _Columns, _Rows>, _Type, _Columns, _Rows, sizeof(_Type) * (_Columns + _Extra)>
{
    _Type m[_Rows][_Columns + _Extra];
};

template <typename _Type>
struct matrix_<_Type, 1, 1>
	:
	_matrix_<matrix_<_Type, 1, 1>, _Type, 1, 1>
{
	_Type m11;

	inline matrix_();
	inline matrix_(_Type _m11);
};

template <typename _Type>
struct matrix_<_Type, 2, 2>
	:
	_matrix_<matrix_<_Type, 2, 2>, _Type, 2, 2>
{
	_Type m11, m12,
	      m21, m22;

	inline matrix_();
	inline matrix_(_Type _m11, _Type _m12,
	               _Type _m21, _Type _m22);
};

template <typename _Type>
struct matrix_<_Type, 3, 3>
	:
	_matrix_<matrix_<_Type, 3, 3>, _Type, 3, 3>
{
	_Type m11, m12, m13,
	      m21, m22, m23,
	      m31, m32, m33;

	inline matrix_();
	inline matrix_(_Type _m11, _Type _m12, _Type _m13,
	               _Type _m21, _Type _m22, _Type _m23,
	               _Type _m31, _Type _m32, _Type _m33);
};

template <typename _Type>
struct matrix_<_Type, 3, 2>
	:
	_matrix_<matrix_<_Type, 3, 2>, _Type, 3, 2>
{
	_Type m11, m12, m13,
	      m21, m22, m23;

	inline matrix_();
	inline matrix_(_Type _m11, _Type _m12, _Type _m13,
	               _Type _m21, _Type _m22, _Type _m23);
};

template <typename _Type>
struct matrix_<_Type, 4, 4>
	:
	_matrix_<matrix_<_Type, 4, 4>, _Type, 4, 4>
{
	_Type m11, m12, m13, m14,
	      m21, m22, m23, m24,
	      m31, m32, m33, m34,
	      m41, m42, m43, m44;

	inline matrix_();
	inline matrix_(_Type _m11, _Type _m12, _Type _m13, _Type _m14,
	               _Type _m21, _Type _m22, _Type _m23, _Type _m24,
	               _Type _m31, _Type _m32, _Type _m33, _Type _m34,
	               _Type _m41, _Type _m42, _Type _m43, _Type _m44);
};

template <typename _Type>
struct matrix_<_Type, 4, 2>
	:
	_matrix_<matrix_<_Type, 4, 2>, _Type, 4, 2>
{
	_Type m11, m12, m13, m14,
	      m21, m22, m23, m24;

	inline matrix_();
	inline matrix_(_Type _m11, _Type _m12, _Type _m13, _Type _m14,
	               _Type _m21, _Type _m22, _Type _m23, _Type _m24);
};

template <typename _T, uint _C, uint _R, uint _E>
inline const matrix_<_T, _R, _C> transpose(const matrix_<_T, _C, _R, _E> &_m);

template <uint _C, uint _R, typename _T, uint _S, uint _E>
inline matrix_<_T, _S - 1, _S - 1> minor_(const matrix_<_T, _S, _S, _E> &_m);

template <typename _T, uint _S, uint _E>
inline const _T determinant(const matrix_<_T, _S, _S, _E> &_m);

template <typename _T, uint _S, uint _E>
inline bool inverse(const matrix_<_T, _S, _S, _E> &_m, matrix_<_T, _S, _S, _E> &_im);

template <typename _T, uint _S, uint _E>
inline const matrix_<_T, _S, _S, _E> inverse(const matrix_<_T, _S, _S, _E> &_m);

template <typename _T, uint _C, uint _M, uint _R, uint _Ea, uint _Eb>
inline const matrix_<_T, _C, _R> mul(matrix_<_T, _M, _R, _Ea> &_a, matrix_<_T, _C, _M, _Eb> &_b);

//
typedef matrix_<float, 3, 3> f3x3, float3x3;
typedef matrix_<float, 3, 2> f3x2, float3x2;
typedef matrix_<float, 4, 4> f4x4, float4x4;
typedef matrix_<float, 4, 2> f4x2, float4x2;
typedef matrix_<real, 3, 3> r3x3, real3x3;
typedef matrix_<real, 3, 2> r3x2, real3x2;
typedef matrix_<real, 4, 4> r4x4, real4x4;
typedef matrix_<real, 4, 2> r4x2, real4x2;

/// zero 3x3 matrix of float
const f3x3 f3x3_0(f_0, f_0, f_0,
                  f_0, f_0, f_0,
                  f_0, f_0, f_0);
/// unit 3x3 matrix of float
const f3x3 f3x3_1(f_1, f_0, f_0,
                  f_0, f_1, f_0,
                  f_0, f_0, f_1);
/// zero 4x4 matrix of float
const f4x4 f4x4_0(f_0, f_0, f_0, f_0,
                  f_0, f_0, f_0, f_0,
                  f_0, f_0, f_0, f_0,
                  f_0, f_0, f_0, f_0);
/// unit 4x4 matrix of float
const f4x4 f4x4_1(f_1, f_0, f_0, f_0,
                  f_0, f_1, f_0, f_0,
                  f_0, f_0, f_1, f_0,
                  f_0, f_0, f_0, f_1);
/// zero 3x3 matrix of real
const r3x3 r3x3_0(r_0, r_0, r_0,
                  r_0, r_0, r_0,
                  r_0, r_0, r_0);
/// unit 3x3 matrix of real
const r3x3 r3x3_1(r_1, r_0, r_0,
                  r_0, r_1, r_0,
                  r_0, r_0, r_1);
/// zero 4x4 matrix of real
const r4x4 r4x4_0(r_0, r_0, r_0, r_0,
                  r_0, r_0, r_0, r_0,
                  r_0, r_0, r_0, r_0,
                  r_0, r_0, r_0, r_0);
/// unit 4x4 matrix of real
const r4x4 r4x4_1(r_1, r_0, r_0, r_0,
                  r_0, r_1, r_0, r_0,
                  r_0, r_0, r_1, r_0,
                  r_0, r_0, r_0, r_1);


#include "matrix.inl"

DECLARE_UTEST(matrix);
