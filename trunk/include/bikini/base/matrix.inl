/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _matrix_helper_

template <typename _M, uint _C, uint _R>
struct _matrix_helper_
{
	typedef _matrix_helper_<_M, _C - 1, _R> _next;
	typedef typename _M::element _E;

	static inline void neg(_M &_a) { _next::neg(_a); _a.cell_<_C - 1, _R - 1>() = -_a.cell_<_C - 1, _R - 1>(); }
	static inline void set(_M &_a, const _M &_b) { _next::set(_a, _b); _a.cell_<_C - 1, _R - 1>() = _b.cell_<_C - 1, _R - 1>(); }
	static inline void get(const _M &_a, _M &_b) { _next::get(_a, _b); _b.cell_<_C - 1, _R - 1>() = _a.cell_<_C - 1, _R - 1>(); }
	static inline void add(_M &_a, const _M &_b) { _next::add(_a, _b); _a.cell_<_C - 1, _R - 1>() += _b.cell_<_C - 1, _R - 1>(); }
	static inline void sub(_M &_a, const _M &_b) { _next::sub(_a, _b); _a.cell_<_C - 1, _R - 1>() -= _b.cell_<_C - 1, _R - 1>(); }
	static inline void mul(_M &_a, const _M &_b) { _next::mul(_a, _b); _a.cell_<_C - 1, _R - 1>() *= _b.cell_<_C - 1, _R - 1>(); }
	static inline void div(_M &_a, const _M &_b) { _next::div(_a, _b); _a.cell_<_C - 1, _R - 1>() /= _b.cell_<_C - 1, _R - 1>(); }
	static inline void mul(_M &_a, const _E &_b) { _next::mul(_a, _b); _a.cell_<_C - 1, _R - 1>() *= _b; }
	static inline void div(_M &_a, const _E &_b) { _next::div(_a, _b); _a.cell_<_C - 1, _R - 1>() /= _b; }
	static inline bool equ(const _M &_a, const _M &_b) { return _a.cell_<_C - 1, _R - 1>() == _b.cell_<_C - 1, _R - 1>() && _next::equ(_a, _b); }
};
template <typename _M, uint _R>
struct _matrix_helper_<_M, 0, _R>
{
	typedef _matrix_helper_<_M, _M::columns, _R - 1> _next;
	typedef typename _M::element _E;

	static inline void neg(_M &_a) { _next::neg(_a); }
	static inline void set(_M &_a, const _M &_b) { _next::set(_a, _b); }
	static inline void get(const _M &_a, _M &_b) { _next::get(_a, _b); }
	static inline void add(_M &_a, const _M &_b) { _next::add(_a, _b); }
	static inline void sub(_M &_a, const _M &_b) { _next::sub(_a, _b); }
	static inline void mul(_M &_a, const _M &_b) { _next::mul(_a, _b); }
	static inline void div(_M &_a, const _M &_b) { _next::div(_a, _b); }
	static inline void mul(_M &_a, const _E &_b) { _next::mul(_a, _b); }
	static inline void div(_M &_a, const _E &_b) { _next::div(_a, _b); }
	static inline bool equ(const _M &_a, const _M &_b) { return _next::equ(_a, _b); }
};
template <typename _M, uint _C>
struct _matrix_helper_<_M, _C, 0>
{
	typedef typename _M::element _E;

	static inline void neg(_M &_a) {}
	static inline void set(_M &_a, const _M &_b) {}
	static inline void get(const _M &_a, _M &_b) {}
	static inline void add(_M &_a, const _M &_b) {}
	static inline void sub(_M &_a, const _M &_b) {}
	static inline void mul(_M &_a, const _M &_b) {}
	static inline void div(_M &_a, const _M &_b) {}
	static inline void mul(_M &_a, const _E &_b) {}
	static inline void div(_M &_a, const _E &_b) {}
	static inline bool equ(const _M &_a, const _M &_b) { return true; }
};

// _matrix_

template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator - ()
{
	_matrix_helper_<matrix, _C, _R>::neg(*this);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator = (const _matrix_ &_m)
{
	_matrix_helper_<matrix, _C, _R>::set(*this, _m);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator += (const _matrix_ &_m)
{
	_matrix_helper_<matrix, _C, _R>::add(*this, _m);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator -= (const _matrix_ &_m)
{
	_matrix_helper_<matrix, _C, _R>::sub(*this, _m);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator *= (const _matrix_ &_m)
{
	_matrix_helper_<matrix, _C, _R>::mul(*this, _m);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator /= (const _matrix_ &_m)
{
	_matrix_helper_<matrix, _C, _R>::div(*this, _m);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator *= (const _E &_s)
{
	_matrix_helper_<matrix, _C, _R>::mul(*this, _s);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>& _matrix_<_M, _E, _C, _R, _Rs>::operator /= (const _E &_s)
{
	_matrix_helper_<matrix, _C, _R>::div(*this, _s);
	return *this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator + (const _matrix_ &_m) const
{
	return _M(*this) += _m;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator - (const _matrix_ &_m) const
{
	return _M(*this) -= _m;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator * (const _matrix_ &_m) const
{
	return _M(*this) *= _m;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator / (const _matrix_ &_m) const
{
	return _M(*this) /= _m;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator * (const _E &_s) const
{
	return _M(*this) *= _s;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const _M _matrix_<_M, _E, _C, _R, _Rs>::operator / (const _E &_s) const
{
	return _M(*this) /= _s;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline bool _matrix_<_M, _E, _C, _R, _Rs>::operator == (const _matrix_ &_m) const
{
	return _matrix_helper_<matrix, _C, _R>::equ(*this, _m);
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs> template <uint _I, uint _J>
inline _E& _matrix_<_M, _E, _C, _R, _Rs>::cell_()
{
	return ((_E*)this)[_J * _C + _I];
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs> template <uint _I, uint _J>
inline const _E& _matrix_<_M, _E, _C, _R, _Rs>::cell_() const
{
	return ((const _E*)this)[_J * _C + _I];
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
struct _matrix_<_M, _E, _C, _R, _Rs>::_row
{
	inline _E& operator [] (uint _i) { return ((_E*)this)[_i]; }
	inline const _E& operator [] (uint _i) const { return ((const _E*)this)[_i]; }
};
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline const typename _matrix_<_M, _E, _C, _R, _Rs>::_row& _matrix_<_M, _E, _C, _R, _Rs>::operator [] (uint _i) const
{
	assert(_i < _R);
	return *(const _row*)((const byte*)this + _Rs * _i);
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline typename _matrix_<_M, _E, _C, _R, _Rs>::_row& _matrix_<_M, _E, _C, _R, _Rs>::operator [] (uint _i)
{
	assert(_i < _R);
	return *(_row*)((byte*)this + _Rs * _i);
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>::operator _M& ()
{
	return *(_M*)this;
}
template <typename _M, typename _E, uint _C, uint _R, uint _Rs>
inline _matrix_<_M, _E, _C, _R, _Rs>::operator const _M& () const
{
	return *(const _M*)this;
}

// _matrix_ multiply

template <typename _Ma, typename _Mb, typename _Mc, uint _C, uint _R, uint _I = _Ma::columns>
struct _matrix_mul_dot_helper_ { static void dot(const _Ma &_a, const _Mb &_b, _Mc &_c)
{
	_matrix_mul_dot_helper_<_Ma, _Mb, _Mc, _C, _R, _I - 1>::dot(_a, _b, _c);
	_c.cell_<_C, _R>() += _a.cell_<_I - 1, _R>() * _b.cell_<_C, _I - 1>();
}};
template <typename _Ma, typename _Mb, typename _Mc, uint _C, uint _R>
struct _matrix_mul_dot_helper_<_Ma, _Mb, _Mc, _C, _R, 0> { static void dot(const _Ma &_a, const _Mb &_b, _Mc &_c)
{
	_c.cell_<_C, _R>() = 0;
}};
template <typename _Ma, typename _Mb, typename _Mc, uint _I = _Mb::columns, uint _J = _Ma::rows>
struct _matrix_mul_helper_ { static void mul(const _Ma &_a, const _Mb &_b, _Mc &_c)
{
	_matrix_mul_helper_<_Ma, _Mb, _Mc, _I - 1, _J>::mul(_a, _b, _c);
	_matrix_mul_dot_helper_<_Ma, _Mb, _Mc, _I - 1, _J - 1>::dot(_a, _b, _c);
}};
template <typename _Ma, typename _Mb, typename _Mc, uint _J>
struct _matrix_mul_helper_<_Ma, _Mb, _Mc, 0, _J> { static void mul(const _Ma &_a, const _Mb &_b, _Mc &_c)
{
	_matrix_mul_helper_<_Ma, _Mb, _Mc, _Ma::columns, _J - 1>::mul(_a, _b, _c);
}};
template <typename _Ma, typename _Mb, typename _Mc, uint _I>
struct _matrix_mul_helper_<_Ma, _Mb, _Mc, _I, 0> { static void mul(const _Ma &_a, const _Mb &_b, _Mc &_c)
{}};

template <typename _Ma, typename _Mb, typename _Mc>
void mul(const _Ma &_a, const _Mb &_b, _Mc &_c)
{
	c_assert(_Ma::columns == _Mb::rows && _Ma::rows == _Mc::rows && _Mb::columns == _Mc::columns);
	_matrix_mul_helper_<_Ma, _Mb, _Mc>::mul(_a, _b, _c);
}

// matrix_

template <typename _T>
inline matrix_<_T, 1, 1>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 1, 1>::matrix_(_T _m11)
:
	m11(_m11)
{}

template <typename _T>
inline matrix_<_T, 2, 2>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 2, 2>::matrix_(_T _m11, _T _m12,
								  _T _m21, _T _m22)
:
	m11(_m11), m12(_m12),
	m21(_m21), m22(_m22)
{}

template <typename _T>
inline matrix_<_T, 3, 3>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 3, 3>::matrix_(_T _m11, _T _m12, _T _m13,
								  _T _m21, _T _m22, _T _m23,
								  _T _m31, _T _m32, _T _m33)
:
	m11(_m11), m12(_m12), m13(_m13),
	m21(_m21), m22(_m22), m23(_m23),
	m31(_m31), m32(_m32), m33(_m33)
{}

template <typename _T>
inline matrix_<_T, 3, 2>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 3, 2>::matrix_(_T _m11, _T _m12, _T _m13,
								  _T _m21, _T _m22, _T _m23)
:
	m11(_m11), m12(_m12), m13(_m13),
	m21(_m21), m22(_m22), m23(_m23)
{}

template <typename _T>
inline matrix_<_T, 4, 4>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 4, 4>::matrix_(_T _m11, _T _m12, _T _m13, _T _m14,
								  _T _m21, _T _m22, _T _m23, _T _m24,
								  _T _m31, _T _m32, _T _m33, _T _m34,
								  _T _m41, _T _m42, _T _m43, _T _m44)
:
	m11(_m11), m12(_m12), m13(_m13), m14(_m14),
	m21(_m21), m22(_m22), m23(_m23), m24(_m24),
	m31(_m31), m32(_m32), m33(_m33), m34(_m34),
	m41(_m41), m42(_m42), m43(_m43), m44(_m44)
{}

template <typename _T>
inline matrix_<_T, 4, 2>::matrix_()
{}
template <typename _T>
inline matrix_<_T, 4, 2>::matrix_(_T _m11, _T _m12, _T _m13, _T _m14,
								  _T _m21, _T _m22, _T _m23, _T _m24)
:
	m11(_m11), m12(_m12), m13(_m13), m14(_m14),
	m21(_m21), m22(_m22), m23(_m23), m24(_m24)
{}

// matrix_ transpose

template <typename _Ma, typename _Mt, uint _I = _Ma::columns, uint _J = _Ma::rows>
struct _matrix_transpose_helper_ { static void get(const _Ma &_a, _Mt &_b)
{
	_matrix_transpose_helper_<_Ma, _Mt, _I - 1, _J>::get(_a, _b);
	_b.cell_<_J - 1, _I - 1>() = _a.cell_<_I - 1, _J - 1>();
}};
template <typename _Ma, typename _Mt, uint _J>
struct _matrix_transpose_helper_<_Ma, _Mt, 0, _J> { static void get(const _Ma &_a, _Mt &_b)
{
	_matrix_transpose_helper_<_Ma, _Mt, _Ma::columns, _J - 1>::get(_a, _b);
}};
template <typename _Ma, typename _Mt, uint _I>
struct _matrix_transpose_helper_<_Ma, _Mt, _I, 0> { static void get(const _Ma &_a, _Mt &_b)
{}};
template <typename _T, uint _C, uint _R, uint _E>
inline const matrix_<_T, _R, _C> transpose(const matrix_<_T, _C, _R, _E> &_m)
{
	typedef matrix_<_T, _C, _R> matrix0;
	typedef matrix_<_T, _R, _C> matrix1;
	matrix_<_T, _R, _C> l_m;
	_matrix_transpose_helper_<matrix0, matrix1>::get(_m, l_m);
	return l_m;
}

// matrix_ minor, determinant, inverse

template <typename _Ma, typename _Mi, uint _C, uint _R, uint _I, uint _J>
struct _matrix_minor_helper_ { static inline void get(const _Ma &_a, _Mi &_b)
{
	_matrix_minor_helper_<_Ma,_Mi, _C, _R, _I - 1, _J>::get(_a, _b);
	_b.cell_<_I - 1, _J - 1>() = _a.cell_<(_I > _C ? _I : _I - 1), (_J > _R ? _J : _J - 1)>();
}};
template <typename _Ma, typename _Mi, uint _C, uint _R, uint _J>
struct _matrix_minor_helper_<_Ma, _Mi, _C, _R, 0, _J> { static inline void get(const _Ma &_a, _Mi &_b)
{
	_matrix_minor_helper_<_Ma,_Mi, _C, _R, _Ma::columns - 1, _J - 1>::get(_a, _b);
}};
template <typename _Ma, typename _Mi, uint _C, uint _R, uint _I>
struct _matrix_minor_helper_<_Ma, _Mi, _C, _R, _I, 0> { static inline void get(const _Ma &_a, _Mi &_b)
{}};
template <uint _C, uint _R, typename _T, uint _S, uint _E>
inline matrix_<_T, _S - 1, _S - 1> minor_(const matrix_<_T, _S, _S, _E> &_m)
{
	typedef matrix_<_T, _S, _S, _E> matrix;
	typedef matrix_<_T, _S - 1, _S - 1> minor;
	minor l_m; _matrix_minor_helper_<matrix, minor, _C, _R, _S - 1, _S - 1>::get(_m, l_m);
	return l_m;
}

template <typename _T, uint _I>
struct _matrix_product_sign_helper_ { static inline _T get(_T _a, _T _b)
{
	return _a * -_b;
}};
template <typename _T>
struct _matrix_product_sign_helper_<_T, 0> { static inline _T get(_T _a, _T _b)
{
	return _a * _b;
}};

template <typename _T, uint _S, uint _E, uint _I = _S, uint _J = _S>
struct _matrix_determinant_helper_ { static inline _T get(const matrix_<_T, _S, _S, _E> &_m)
{
	return _matrix_determinant_helper_<_T, _S, _E, _I - 1, _J>::get(_m) + _matrix_product_sign_helper_<_T, (_I - 1 + _J - 1) % 2>::get(determinant(minor_<_I - 1, _J - 1>(_m)), _m.cell_<_I - 1, _J - 1>());
}};
template <typename _T, uint _S, uint _E, uint _J>
struct _matrix_determinant_helper_<_T, _S, _E, 1, _J> { static inline _T get(const matrix_<_T, _S, _S, _E> &_m)
{
	return _matrix_product_sign_helper_<_T, (_J - 1) % 2>::get(determinant(minor_<0, _J - 1>(_m)), _m.cell_<0, _J - 1>());
}};
template <typename _T, uint _S, uint _E>
struct _matrix_determinant_helper_<_T, _S, _E, 1, 1> { static inline _T get(const matrix_<_T, _S, _S, _E> &_m)
{
	return _m.cell_<0, 0>();
}};
template <typename _T, uint _S, uint _E>
inline const _T determinant(const matrix_<_T, _S, _S, _E> &_m)
{
	return _matrix_determinant_helper_<_T, _S, _E>::get(_m);
}

template <typename _T, uint _S, uint _E, uint _I = _S, uint _J = _S>
struct _matrix_inverse_helper_ { static inline void get(const matrix_<_T, _S, _S, _E> &_m, matrix_<_T, _S, _S, _E> &_im, _T _d)
{
	_matrix_inverse_helper_<_T, _S, _E, _I - 1, _J>::get(_m, _im, _d);
	_im.cell_<_J - 1, _I - 1>() = _matrix_product_sign_helper_<_T, (_I - 1 + _J - 1) % 2>::get(determinant(minor_<_I - 1, _J - 1>(_m)), _d);
}};
template <typename _T, uint _S, uint _E, uint _J>
struct _matrix_inverse_helper_<_T, _S, _E, 0, _J> { static inline void get(const matrix_<_T, _S, _S, _E> &_m, matrix_<_T, _S, _S, _E> &_im, _T _d)
{
	_matrix_inverse_helper_<_T, _S, _E, _S, _J - 1>::get(_m, _im, _d);
}};
template <typename _T, uint _S, uint _E>
struct _matrix_inverse_helper_<_T, _S, _E, _S, 0> { static inline void get(const matrix_<_T, _S, _S, _E> &_m, matrix_<_T, _S, _S, _E> &_im, _T _d)
{}};
template <typename _T, uint _S, uint _E>
inline bool inverse(const matrix_<_T, _S, _S, _E> &_m, matrix_<_T, _S, _S, _E> &_im)
{
	_T l_d = determinant(_m);
	if(l_d < eps && l_d > -eps) return false;
	_matrix_inverse_helper_<_T, _S, _E>::get(_m, _im, _T(1) / l_d);
	return true;
}
template <typename _T, uint _S, uint _E>
inline const matrix_<_T, _S, _S, _E> inverse(const matrix_<_T, _S, _S, _E> &_m)
{
	matrix_<_T, _S, _S, _E> l_m;
	if(!inverse(_m, l_m)) return _m;
	return l_m;
}

// matrix_ multiply

template <typename _T, uint _C, uint _M, uint _R, uint _Ea, uint _Eb>
inline const matrix_<_T, _C, _R> mul(matrix_<_T, _M, _R, _Ea> &_a, matrix_<_T, _C, _M, _Eb> &_b)
{
	matrix_<_T, _C, _R> l_m; mul(_a, _b, l_m);
	return l_m;
}
