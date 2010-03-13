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




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//// _matrix_row_
//
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_() {
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(const _matrix_row_ &_r) : parent_type(_r), m_cell(_r.cell()) {
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(const parent_type &_r) : parent_type(_r) {
//}
//template<uint _S, typename _T> template<uint _S2>
//inline _matrix_row_<_S, _T>::_matrix_row_(const _matrix_row_<_S2, _T> &_r) : parent_type(_r), m_cell(_r.cell<_S - 1>()) {
//	c_assert(_S2 > _S);
//}
//template<uint _S, typename _T> template<typename _T2>
//inline _matrix_row_<_S, _T>::_matrix_row_(const _matrix_row_<_S, _T2> &_r) : parent_type(_r), m_cell(_r.cell()) {
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0) : m_cell(_cell0) {
//	c_assert(_S == 1);
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1) : parent_type(_cell0), m_cell(_cell1) {
//	c_assert(_S == 2);
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1, _T _cell2) : parent_type(_cell0, _cell1), m_cell(_cell2) {
//	c_assert(_S == 3);
//}
//template<uint _S, typename _T>
//inline _matrix_row_<_S, _T>::_matrix_row_(_T _cell0, _T _cell1, _T _cell2, _T _cell3) : parent_type(_cell0, _cell1, _cell2), m_cell(_cell3) {
//	c_assert(_S == 4);
//}
//template<uint _S, typename _T>
//inline const _T& _matrix_row_<_S, _T>::cell() const {
//	return m_cell;
//}
//template<uint _S, typename _T>
//inline _T& _matrix_row_<_S, _T>::cell() {
//	return m_cell;
//}
//template<uint _S, typename _T> template<uint _I>
//inline const _T& _matrix_row_<_S, _T>::cell() const {
//	c_assert(_I < _S);
//	return *(&static_cast<const _matrix_row_<_I + 1, _T>&>(*this).cell());
//}
//template<uint _S, typename _T> template<uint _I>
//inline _T& _matrix_row_<_S, _T>::cell() {
//	c_assert(_I < _S);
//	return *(&static_cast<_matrix_row_<_I + 1, _T>&>(*this).cell());
//}
//template<uint _S, typename _T>
//inline const _T& _matrix_row_<_S, _T>::operator [] (uint _i) const {
//	assert(_i < _S);
//	return *(&cell<0>() + _i);
//}
//template<uint _S, typename _T>
//inline _T& _matrix_row_<_S, _T>::operator [] (uint _i) {
//	assert(_i < _S);
//	return *(&cell<0>() + _i);
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_set(const _matrix_row_ &_b) {
//	parent_type::_set(_b); m_cell = _b.cell();
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_get(_matrix_row_ &_c) const {
//	parent_type::_get(_c); _c.cell() = m_cell;
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_neg(_matrix_row_ &_c) const {
//	parent_type::_neg(_c); _c.cell() = -m_cell;
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_add(const _matrix_row_ &_b, _matrix_row_ &_c) const {
//	parent_type::_add(_b, _c); _c.cell() = m_cell + _b.cell();
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_sub(const _matrix_row_ &_b, _matrix_row_ &_c) const {
//	parent_type::_sub(_b, _c); _c.cell() = m_cell - _b.cell();
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_mul(_T _s, _matrix_row_ &_c) const {
//	parent_type::_mul(_s, _c); _c.cell() = m_cell * _s;
//}
//template<uint _S, typename _T>
//inline void _matrix_row_<_S, _T>::_div(_T _s, _matrix_row_ &_c) const {
//	parent_type::_div(_s, _c); _c.cell() = m_cell + _s;
//}
//template<uint _S, typename _T>
//inline bool _matrix_row_<_S, _T>::_cmp(const _matrix_row_ &_b) const {
//	return m_cell == _b.cell() && parent_type::_cmp(_b);
//}
//
//// matrix
//
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_() {
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(const matrix_ &_m) : parent_type(_m), m_row(_m.row()) {
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(const parent_type &_m) : parent_type(_m) {
//}
//template<uint _H, uint _W, typename _T> template<uint _H2, uint _W2>
//inline matrix_<_H, _W, _T>::matrix_(const matrix_<_H2, _W2, _T> &_m) : parent_type(_m), m_row(_m.row<_H - 1>()) {
//	c_assert(_H2 >= _H && _W2 >= _W);
//}
//template<uint _H, uint _W, typename _T> template<typename _T2>
//inline matrix_<_H, _W, _T>::matrix_(const matrix_<_H, _W, _T2> &_m) : parent_type(_m), m_row(_m.row()) {
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(_T _cell0) : m_row(_cell0) {
//	c_assert(_H == 1 && _W == 1);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1) : m_row(_cell0, _cell1) {
//	c_assert(_H == 1 && _W == 2);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1, _T _cell2) : m_row(_cell0, _cell1, _cell2) {
//	c_assert(_H == 1 && _W == 3);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(_T _cell0, _T _cell1, _T _cell2, _T _cell3) : m_row(_cell0, _cell1, _cell2, _cell3) {
//	c_assert(_H == 1 && _W == 4);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1) : parent_type(_row0), m_row(_row1.row()) {
//	c_assert(_H == 2);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2) : parent_type(_row0, _row1), m_row(_row2.row()) {
//	c_assert(_H == 3);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2, const row_matrix &_row3) : parent_type(_row0, _row1, _row2), m_row(_row3.row()) {
//	c_assert(_H == 4);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() const {
//	return m_row;
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() {
//	return m_row;
//}
//template<uint _H, uint _W, typename _T> template<uint _I>
//inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() const {
//	c_assert(_I < _H);
//	return static_cast<const matrix_<_I + 1, _W, _T>&>(*this).row();
//}
//template<uint _H, uint _W, typename _T> template<uint _I>
//inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::row() {
//	c_assert(_I < _H);
//	return static_cast<matrix_<_I + 1, _W, _T>&>(*this).row();
//}
//template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
//inline const _T& matrix_<_H, _W, _T>::cell() const {
//	c_assert(_I < _H && _J < _W);
//	return row<_I>().cell<_J>();
//}
//template<uint _H, uint _W, typename _T> template<uint _I, uint _J>
//inline _T& matrix_<_H, _W, _T>::cell() {
//	c_assert(_I < _H && _J < _W);
//	return row<_I>().cell<_J>();
//}
//template<uint _H, uint _W, typename _T> template<uint _J>
//inline const _T& matrix_<_H, _W, _T>::cell() const {
//	c_assert(1 == _H && _J < _W);
//	return row<0>().cell<_J>();
//}
//template<uint _H, uint _W, typename _T> template<uint _J>
//inline _T& matrix_<_H, _W, _T>::cell() {
//	c_assert(1 == _H && _J < _W);
//	return row<0>().cell<_J>();
//}
//template<uint _H, uint _W, typename _T> struct _component_access_helper_ {
//	template<uint _I> static inline typename matrix_<_H, _W, _T>::component_type& get(matrix_<_H, _W, _T> &_m) { return _m.row<_I>(); }
//	template<uint _I> static inline const typename matrix_<_H, _W, _T>::component_type& get(const matrix_<_H, _W, _T> &_m) { return _m.row<_I>(); }
//};
//template<uint _H, typename _T> struct _component_access_helper_<_H, 1, _T> {
//	template<uint _I> static inline typename matrix_<_H, 1, _T>::component_type& get(matrix_<_H, 1, _T> &_m) { return _m.cell<_I, 0>(); }
//	template<uint _I> static inline const typename matrix_<_H, 1, _T>::component_type& get(const matrix_<_H, 1, _T> &_m) { return _m.cell<_I, 0>(); }
//};
//template<uint _W, typename _T> struct _component_access_helper_<1, _W, _T> {
//	template<uint _I> static inline typename matrix_<1, _W, _T>::component_type& get(matrix_<1, _W, _T> &_m) { return _m.cell<0, _I>(); }
//	template<uint _I> static inline const typename matrix_<1, _W, _T>::component_type& get(const matrix_<1, _W, _T> &_m) { return _m.cell<0, _I>(); }
//};
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::x() const {
//	return _component_access_helper_<_H, _W, _T>::get<0>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::x() {
//	return _component_access_helper_<_H, _W, _T>::get<0>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::y() const {
//	return _component_access_helper_<_H, _W, _T>::get<1>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::y() {
//	return _component_access_helper_<_H, _W, _T>::get<1>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::z() const {
//	return _component_access_helper_<_H, _W, _T>::get<2>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::z() {
//	return _component_access_helper_<_H, _W, _T>::get<2>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::w() const {
//	return _component_access_helper_<_H, _W, _T>::get<3>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::component_type& matrix_<_H, _W, _T>::w() {
//	return _component_access_helper_<_H, _W, _T>::get<3>(*this);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) const {
//	assert(_i < _H);
//	return *(&row<0>() + _i);
//}
//template<uint _H, uint _W, typename _T>
//inline typename matrix_<_H, _W, _T>::row_type& matrix_<_H, _W, _T>::operator [] (uint _i) {
//	assert(_i < _H);
//	return *(&row<0>() + _i);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator = (const matrix_ &_b) {
//	_set(_b);
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> matrix_<_H, _W, _T>::operator - () const {
//	matrix_ l_c;
//	_neg(l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> operator + (const matrix_<_H, _W, _T> &_a, const matrix_<_H, _W, _T> &_b) {
//	matrix_<_H, _W, _T> l_c;
//	_a._add(_b, l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator += (const matrix_ &_b) {
//	_add(_b, *this);
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> operator - (const matrix_<_H, _W, _T> &_a, const matrix_<_H, _W, _T> &_b) {
//	matrix_<_H, _W, _T> l_c;
//	_a._sub(_b, l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator -= (const matrix_ &_b) {
//	_sub(_b, *this);
//	return *this;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> operator * (const matrix_<_H, _W, _T> &_a, _T _b) {
//	matrix_<_H, _W, _T> l_c;
//	_a._mul(_b, l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_H, _W, _T> operator * (_T _a, const matrix_<_H, _W, _T> &_b) {
//	matrix_<_H, _W, _T> l_c;
//	_b._mul(_a, l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>& matrix_<_H, _W, _T>::operator *= (_T _b) {
//	_mul(_b, *this);
//	return *this;
//}
//template<uint _H, uint _W, uint _W2, typename _T>
//inline const matrix_<_H, _W2, _T> operator * (const matrix_<_H, _W, _T> &_a, const matrix_<_W, _W2, _T> &_b) {
//	matrix_<_H, _W2, _T> l_c;
//	_a._mul(_b, l_c);
//	return l_c;
//}
//template<uint _H, uint _W, typename _T>
//inline const matrix_<_W, _H, _T> matrix_<_H, _W, _T>::operator ~ () const {
//	matrix_<_W, _H, _T> l_m;
//	_xgt(l_m);
//	return l_m;
//}
//template<uint _H, uint _W, typename _T>
//inline const _T operator | (const matrix_<_H, _W, _T> &_a, const matrix_<_H, _W, _T> &_b) {
//	c_assert(_H == 1);
//	return dot(_a, _b);
//}
//template<uint _H, uint _W, typename _T>
//inline const typename matrix_<_H, _W, _T>::cross_type operator ^ (const matrix_<_H, _W, _T> &_a, const matrix_<_H, _W, _T> &_b) {
//	c_assert(_H == 1 && (_W == 2 || _W == 3));
//	return cross(_a, _b);
//}
//template<uint _H, uint _W, typename _T>
//inline bool operator == (const matrix_<_H, _W, _T> &_a, const matrix_<_H, _W, _T> &_b) {
//	return _a._cmp(_b);
//}
//template<uint _H, uint _W, typename _T>
//inline matrix_<_H, _W, _T>::operator const typename matrix_<_H, _W, _T>::row_type () const {
//	c_assert(_H == 1);
//	return m_row;
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_set(const matrix_ &_b) {
//	parent_type::_set(_b); m_row._set(_b.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_get(matrix_ &_c) const {
//	parent_type::_get(_c); m_row._get(_c.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_neg(matrix_ &_c) const {
//	parent_type::_neg(_c); m_row._neg(_c.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_add(const matrix_ &_b, matrix_ &_c) const {
//	parent_type::_add(_b, _c); m_row._add(_b.row(), _c.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_sub(const matrix_ &_b, matrix_ &_c) const {
//	parent_type::_sub(_b, _c); m_row._sub(_b.row(), _c.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_mul(_T _s, matrix_ &_c) const {
//	parent_type::_mul(_s, _c); m_row._mul(_s, _c.row());
//}
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_div(_T _s, matrix_ &_c) const {
//	parent_type::_div(_s, _c); m_row._div(_s, _c.row());
//}
//template<uint _H, uint _W, typename _T> template<uint _W2>
//inline void matrix_<_H, _W, _T>::_mul(const matrix_<_W, _W2, _T> &_b, matrix_<_H, _W2, _T> &_c) const {
//	parent_type::_mul(_b, _c);
//	_b._mul(m_row, _c.row());
//}
//template<uint _H, uint _W, typename _T> struct _matrix_row_mul_helper_ { static inline void mul(const _matrix_row_<_W, _T> &_a, const _matrix_row_<_H, _T> &_b, _matrix_row_<_W, _T> &_c) {
//	_matrix_row_<_W, _T> l_c; _a._mul(_b.cell(), l_c); l_c._add(_c, _c);
//}};
//template<uint _W, typename _T> struct _matrix_row_mul_helper_<1, _W, _T> { static inline void mul(const _matrix_row_<_W, _T> &_a, const _matrix_row_<1, _T> &_b, _matrix_row_<_W, _T> &_c) {
//	_a._mul(_b.cell(), _c);
//}};
//template<uint _H, uint _W, typename _T>
//inline void matrix_<_H, _W, _T>::_mul(const _matrix_row_<_H, _T> &_b, _matrix_row_<_W, _T> &_c) const {
//	parent_type::_mul(_b, _c);
//	_matrix_row_mul_helper_<_H, _W, _T>::mul(m_row, _b, _c);
//}
//template<uint _H, uint _W, typename _T> template<uint _W2> 
//inline void matrix_<_H, _W, _T>::_xgt(matrix_<_W, _W2, _T> &_b) const {
//	parent_type::_xgt(_b); _b._cst<_H - 1>(m_row);
//}
//template<uint _H, uint _W, typename _T> template<uint _I>
//inline void matrix_<_H, _W, _T>::_cst(const _matrix_row_<_H, _T> &_b) {
//	parent_type::_cst<_I>(_b); m_row.cell<_I>() = _b.cell();
//}
//template<uint _H, uint _W, typename _T>
//inline bool matrix_<_H, _W, _T>::_cmp(const matrix_ &_b) const {
//	return m_row._cmp(_b.row()) && parent_type::_cmp(_b);
//}
//
//// matrix minor
//template<uint _W, uint _J, typename _T>
//struct _matrix_minor_row_helper_ { static inline void get(const _matrix_row_<_W + 1, _T> &_a, _matrix_row_<_W, _T> &_c) {
//	_matrix_minor_row_helper_<_W - 1, _J, _T>::get(_a, _c);
//	_c.cell() = _a.cell<_J >= _W ? _W - 1 : _W>();
//}};
//template<uint _J, typename _T>
//struct _matrix_minor_row_helper_<1, _J, _T> { static inline void get(const _matrix_row_<2, _T> &_a, _matrix_row_<1, _T> &_c) {
//	_c.cell() = _a.cell<_J >= 1 ? 0 : 1>();
//}};
//template<uint _H, uint _W, uint _I, uint _J, typename _T>
//struct _matrix_minor_helper_ { static inline void get(const matrix_<_H + 1, _W + 1, _T> &_a, matrix_<_H, _W, _T> &_c) {
//	_matrix_minor_helper_<_H - 1, _W, _I, _J, _T>::get(_a, _c);
//	_matrix_minor_row_helper_<_W, _J, _T>::get(_a.row<_I >= _H ? _H - 1 : _H>(), _c.row());
//}};
//template<uint _W, uint _I, uint _J, typename _T>
//struct _matrix_minor_helper_<1, _W, _I, _J, _T> { static inline void get(const matrix_<2, _W + 1, _T> &_a, matrix_<1, _W, _T> &_c) {
//	_matrix_minor_row_helper_<_W, _J, _T>::get(_a.row<_I >= 1 ? 0 : 1>(), _c.row());
//}};
//template<uint _I, uint _J, uint _S, typename _T>
//inline const matrix_<_S - 1, _S - 1, _T> minor(const matrix_<_S, _S, _T> &_m) {
//	matrix_<_S - 1, _S - 1, _T> l_m;
//	_matrix_minor_helper_<_S - 1, _S - 1, _I, _J, _T>::get(_m, l_m);
//	return l_m;
//}
//
//// matrix determinant
//template<uint _I, typename _T> struct _matrix_determinant_sign_ {
////	static inline _T value() { return _T(-1); }
//	static inline _T sign(const _T &_a, const _T &_b) { return  _a * -_b; }
//};
//template<typename _T> struct _matrix_determinant_sign_<0, _T> {
////	static inline _T value() { return _T(1); }
//	static inline _T sign(const _T &_a, const _T &_b) { return  _a * _b; }
//};
//template<uint _C, uint _S, typename _T>
//struct _matrix_determinant_helper_ { static inline _T get(const matrix_<_S, _S, _T> &_a) {
////	return _matrix_determinant_helper_<_C - 1, _S, _T>::get(_a) + determinant(minor<_C - 1, _S - 1>(_a)) * _a.cell<_C - 1, _S - 1>() * _matrix_determinant_sign_<(_C - 1 + _S - 1) % 2, _T>::value();
//	return _matrix_determinant_helper_<_C - 1, _S, _T>::get(_a) + _matrix_determinant_sign_<(_C - 1 + _S - 1) % 2, _T>::sign(determinant(minor<_C - 1, _S - 1>(_a)), _a.cell<_C - 1, _S - 1>());
//}};
//template<uint _S, typename _T>
//struct _matrix_determinant_helper_<1, _S, _T> { static inline _T get(const matrix_<_S, _S, _T> &_a) {
////	return determinant(minor<0, _S - 1>(_a)) * _a.cell<0, _S - 1>() * _matrix_determinant_sign_<(_S - 1) % 2, _T>::value();
//	return _matrix_determinant_sign_<(_S - 1) % 2, _T>::sign(determinant(minor<0, _S - 1>(_a)), _a.cell<0, _S - 1>());
//}};
//template<typename _T>
//struct _matrix_determinant_helper_<1, 1, _T> { static inline _T get(const matrix_<1, 1, _T> &_a) {
//	return _a.cell<0, 0>();
//}};
//template<uint _S, typename _T>
//inline const _T determinant(const matrix_<_S, _S, _T> &_m) {
//	return _matrix_determinant_helper_<_S, _S, _T>::get(_m);
//}
//
//// matrix inverse
//template<uint _I, typename _T> struct _matrix_inverse_sign_ {
////	static inline _T value() { return _T(-1); }
//	static inline _T sign(const _T &_a, const _T &_b) { return  _a * -_b; }
//};
//template<typename _T> struct _matrix_inverse_sign_<0, _T> {
////	static inline _T value() { return _T(1); }
//	static inline _T sign(const _T &_a, const _T &_b) { return  _a * _b; }
//};
//template<uint _I, uint _J, uint _S, typename _T>
//struct _matrix_inverse_row_helper_ { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, const _T &_d) {
//	_matrix_inverse_row_helper_<_I, _J - 1, _S, _T>::get(_a, _c, _d);
////	_c.cell<_J - 1, _I - 1>() = determinant(minor<_I - 1, _J - 1>(_a)) * _d * _matrix_inverse_sign_<(_I - 1 + _J - 1) % 2, _T>::value();
//	_c.cell<_J - 1, _I - 1>() = _matrix_inverse_sign_<(_I - 1 + _J - 1) % 2, _T>::sign(determinant(minor<_I - 1, _J - 1>(_a)), _d);
//}};
//template<uint _I, uint _S, typename _T>
//struct _matrix_inverse_row_helper_<_I, 0, _S, _T> { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, const _T &_d) {
//}};
//template<uint _I, uint _J, uint _S, typename _T>
//struct _matrix_inverse_helper_ { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, const _T &_d) {
//	_matrix_inverse_helper_<_I - 1, _J, _S, _T>::get(_a, _c, _d);
//	_matrix_inverse_row_helper_<_I, _J, _S, _T>::get(_a, _c, _d);
//}};
//template<uint _J, uint _S, typename _T>
//struct _matrix_inverse_helper_<0, _J, _S, _T> { static inline void get(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c, const _T &_d) {
//}};
//template<uint _S, typename _T>
//inline bool inverse(const matrix_<_S, _S, _T> &_a, matrix_<_S, _S, _T> &_c) {
//	_T l_d = determinant(_a);
//	if(l_d < eps && l_d > -eps) return false;
//	_matrix_inverse_helper_<_S, _S, _S, _T>::get(_a, _c, r_1 / l_d);
//	return true;
//}
//template<uint _S, typename _T>
//inline const matrix_<_S, _S, _T> inverse(const matrix_<_S, _S, _T> &_m) {
//	matrix_<_S, _S, _T> l_m;
//	if(!inverse(_m, l_m)) return _m;
//	return l_m;
//}
//
//// vectors dot product
//template<uint _S, typename _T>
//struct _vector_dot_helper_ { static inline const _T dot(const matrix_<1, _S, _T> &_a, const matrix_<1, _S, _T> &_b) {
//	return _vector_dot_helper_<_S - 1, _T>::dot(_a, _b) + _a.row().cell() * _b.row().cell();
//}};
//template<typename _T>
//struct _vector_dot_helper_<1, _T> { static inline const _T dot(const matrix_<1, 1, _T> &_a, const matrix_<1, 1, _T> &_b) {
//	return _a.row().cell() * _b.row().cell();
//}};
//template<uint _S, typename _T>
//inline const _T dot(const matrix_<1, _S, _T> &_a, const matrix_<1, _S, _T> &_b) {
//	return _vector_dot_helper_<_S, _T>::dot(_a, _b);
//}
//
//// vector length
//template<uint _S, typename _T>
//inline const _T length(const matrix_<1, _S, _T> &_a) {
//	return sqrt(dot(_a, _a));
//}
//
//// vector length square
//template<uint _S, typename _T>
//inline const _T length2(const matrix_<1, _S, _T> &_a) {
//	return dot(_a, _a);
//}
//
///// vector normalization
//template<uint _S, typename _T>
//inline const matrix_<1, _S, _T> normalized(const matrix_<1, _S, _T> &_a) {
//	_T l_len = length(_a);
//	return l_len > eps ? _a * (_T(1) / l_len) : _a;
//}
//
//// vectors cross product
//template<typename _T>
//inline const matrix_<1, 2, _T> cross(const matrix_<1, 2, _T> &_a) {
//	return matrix_<1, 2, _T>(_a.y(), -_a.x());
//}
//template<typename _T>
//inline const _T cross(const matrix_<1, 2, _T> &_a, const matrix_<1, 2, _T> &_b) {
//	return _a.x() * _b.y() - _a.y() * _b.x();
//}
//template<typename _T>
//inline const matrix_<1, 3, _T> cross(const matrix_<1, 3, _T> &_a, const matrix_<1, 3, _T> &_b) {
//	return matrix_<1, 3, _T>(_a.y() * _b.z() - _a.z() * _b.y(), _a.z() * _b.x() - _a.x() * _b.z(), _a.x() * _b.y() - _a.y() * _b.z());
//}
//template<typename _T>
//inline const _T cross(const matrix_<1, 3, _T> &_a, const matrix_<1, 3, _T> &_b, const matrix_<1, 3, _T> &_c) {
//	return dot(cross(_a, _b), _c);
//}
