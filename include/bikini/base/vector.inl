/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _vector_

template <typename _V, typename _E, uint _S, uint _P>
const _E & _vector_<_V, _E, _S, _P>::operator [] (uint _i) const
{
	return super::operator [] (0)[_i];
}
template <typename _V, typename _E, uint _S, uint _P>
_E & _vector_<_V, _E, _S, _P>::operator [] (uint _i)
{
	return super::operator [] (0)[_i];
}

// vector_

template <typename _T>
inline vector_<_T, 1>::vector_()
{}
template <typename _T>
inline vector_<_T, 1>::vector_(_T _x)
	:
	x(_x)
{}

template <typename _T>
inline vector_<_T, 2>::vector_()
{}
template <typename _T>
inline vector_<_T, 2>::vector_(_T _x, _T _y)
	:
	x(_x), y(_y)
{}

template <typename _T>
inline vector_<_T, 3>::vector_()
{}
template <typename _T>
inline vector_<_T, 3>::vector_(_T _x, _T _y, _T _z)
	:
	x(_x), y(_y), z(_z)
{}

template <typename _T>
inline vector_<_T, 4>::vector_()
{}
template <typename _T>
inline vector_<_T, 4>::vector_(_T _x, _T _y, _T _z, _T _w)
	:
	x(_x), y(_y), z(_z), w(_w)
{}

// vector_ function

template <typename _T, uint _S, uint _E, uint _I = _S>
struct _vector_dot_helper_
{
	static inline const _T get(const vector_<_T, _S, _E> &_a, const vector_<_T, _S, _E> &_b)
	{
		return _vector_dot_helper_<_T, _S, _E, _I - 1>::get(_a, _b) + _a.cell_<_I - 1, 0>() * _b.cell_<_I - 1, 0>();
	}
};
template <typename _T, uint _S, uint _E>
struct _vector_dot_helper_<_T, _S, _E, 0>
{
	static inline const _T get(const vector_<_T, _S, _E> &_a, const vector_<_T, _S, _E> &_b)
	{
		return 0;
	}
};
template <typename _T, uint _S, uint _E>
inline const _T dot(const vector_<_T, _S, _E> &_a, const vector_<_T, _S, _E> &_b)
{
	return _vector_dot_helper_<_T, _S, _E>::get(_a, _b);
}

template <typename _T, uint _S, uint _E>
inline const _T length(const vector_<_T, _S, _E> &_a)
{
	return sqrt(dot(_a, _a));
}
template <typename _T, uint _S, uint _E>
inline const _T length2(const vector_<_T, _S, _E> &_a)
{
	return dot(_a, _a);
}

template <typename _T, uint _S, uint _E>
inline const vector_<_T, _S, _E> normalize(const vector_<_T, _S, _E> &_a)
{
	_T l_length = length(_a);
	return l_length > eps ? _a * (_T(1) / l_length) : _a;
}

template <typename _T, uint _E>
inline const vector_<_T, 2, _E> cross(const vector_<_T, 2, _E> &_a)
{
	return vector_<_T, 2, _E>(_a.y, -_a.x);
}
template <typename _T, uint _E>
inline const _T cross(const vector_<_T, 2, _E> &_a, const vector_<_T, 2, _E> &_b)
{
	return _a.x * _b.y - _a.y * _b.x;
}
template <typename _T, uint _E>
inline const vector_<_T, 3, _E> cross(const vector_<_T, 3, _E> &_a, const vector_<_T, 3, _E> &_b)
{
	return vector_<_T, 3, _E>(_a.y * _b.z - _a.z * _b.y, _a.z * _b.x - _a.x * _b.z, _a.x * _b.y - _a.y * _b.x);
}
template <typename _T, uint _E>
inline const _T cross(const vector_<_T, 3, _E> &_a, const vector_<_T, 3, _E> &_b, const vector_<_T, 3, _E> &_c)
{
	return dot(cross(_a, _b), _c);
}

template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector_<_T, _C> mul(const vector_<_T, _R, _Ea> &_a, const matrix_<_T, _C, _R, _Eb> &_b)
{
	vector_<_T, _C> l_v; mul(_a, _b, l_v);
	return l_v;
}
template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector_<_T, _R> mul(const matrix_<_T, _C, _R, _Eb> &_a, const vector_<_T, _C, _Ea> &_b)
{
	vector_<_T, _R> l_v; mul(_b, transpose(_a), l_v);
	return l_v;
}
