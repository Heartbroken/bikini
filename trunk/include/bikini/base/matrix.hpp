/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
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

	_matrix_& operator - ();
	_matrix_& operator = (const _matrix_ &_m);
	_matrix_& operator += (const _matrix_ &_m);
	_matrix_& operator -= (const _matrix_ &_m);
	_matrix_& operator *= (const _matrix_ &_m);
	_matrix_& operator /= (const _matrix_ &_m);
	_matrix_& operator *= (const _Element &_s);
	_matrix_& operator /= (const _Element &_s);

	template <uint _C, uint _R> _Element& cell_() { return ((_Element*)this)[_R * _Columns + _C]; }
	template <uint _C, uint _R> const _Element& cell_() const { return ((const _Element*)this)[_R * _Columns + _C]; }

	struct _row
	{
		const _Element& operator [] (uint _i) const { return ((const _Element*)this)[_i]; }
		_Element& operator [] (uint _i) { return ((_Element*)this)[_i]; }
	};

	const _row& operator [] (uint _i) const;
	_row& operator [] (uint _i);

	operator const _Matrix& () const { return *(const _Matrix*)this; }
	operator _Matrix& () { return *(_Matrix*)this; }

};

template <typename _Type, uint _Columns, uint _Rows, uint _Extra = 0>
struct matrix__
:
	_matrix_<matrix__<_Type, _Columns, _Rows>, _Type, _Columns, _Rows, sizeof(_Type) * (_Columns + _Extra)>
{
	_Type m[_Rows][_Columns + _Extra];
};

template <typename _Type>
struct matrix__<_Type, 1, 1>
:
	_matrix_<matrix__<_Type, 1, 1>, _Type, 1, 1>
{
	_Type m11;
};

template <typename _Type>
struct matrix__<_Type, 2, 2>
:
	_matrix_<matrix__<_Type, 2, 2>, _Type, 2, 2>
{
	_Type m11, m12,
		  m21, m22;
};

template <typename _Type>
struct matrix__<_Type, 3, 3>
:
	_matrix_<matrix__<_Type, 3, 3>, _Type, 3, 3>
{
	_Type m11, m12, m13,
		  m21, m22, m23,
		  m31, m32, m33;
};

template <typename _Type>
struct matrix__<_Type, 4, 4>
:
	_matrix_<matrix__<_Type, 4, 4>, _Type, 4, 4>
{
	_Type m11, m12, m13, m14,
		  m21, m22, m23, m24,
		  m31, m32, m33, m34,
		  m41, m42, m43, m44;
};


template <typename _Ma, typename _Mi, uint _C, uint _R, uint _I, uint _J>
struct _matrix__minor_helper_ { static inline void get(const _Ma &_a, _Mi &_b)
{
	_matrix__minor_helper_<_Ma,_Mi, _C, _R, _I - 1, _J>::get(_a, _b);
	_b.cell_<_I - 1, _J - 1>() = _a.cell_<(_I > _C ? _I : _I - 1), (_J > _R ? _J : _J - 1)>();
}};
template <typename _Ma, typename _Mi, uint _C, uint _R, uint _J>
struct _matrix__minor_helper_<_Ma, _Mi, _C, _R, 0, _J> { static inline void get(const _Ma &_a, _Mi &_b)
{
	_matrix__minor_helper_<_Ma,_Mi, _C, _R, _Ma::columns, _J - 1>::get(_a, _b);
}};
template <typename _Ma, typename _Mi, uint _C, uint _R>
struct _matrix__minor_helper_<_Ma, _Mi, _C, _R, 0, 0> { static inline void get(const _Ma &_a, _Mi &_b)
{}};
template <uint _C, uint _R, typename _T, uint _S, uint _E>
inline matrix__<_T, _S - 1, _S - 1> minor_(const matrix__<_T, _S, _S, _E> &_m)
{
	typedef matrix__<_T, _S, _S, _E> matrix;
	typedef matrix__<_T, _S - 1, _S - 1> minor;
	minor l_m; _matrix__minor_helper_<matrix, minor, _C, _R, _S - 1, _S - 1>::get(_m, l_m);
	return l_m;
}

template <typename _T, uint _S, uint _E, uint _I = _S, uint _J = _S>
struct _matrix__determinant_helper_ { static inline void get(const matrix__<_T, _S, _S, _E> &_m, _T &_r)
{
	_matrix__determinant_helper_<_T, _S, _E, _I - 1, _J>::get(_m, _r);
}};
template <typename _T, uint _S, uint _E, uint _J>
struct _matrix__determinant_helper_<_T, _S, _E, 0, _J> { static inline void get(const matrix__<_T, _S, _S, _E> &_m, _T &_r)
{
	_matrix__determinant_helper_<_T, _S, _E, _S, _J - 1>::get(_m, _r);
}};
template <typename _T, uint _S, uint _E>
struct _matrix__determinant_helper_<_T, _S, _E, 0, 0> { static inline void get(const matrix__<_T, _S, _S, _E> &_m, _T &_r)
{}};
template <typename _T, uint _S, uint _E>
inline const _T determinant(const matrix__<_T, _S, _S, _E> &_m)
{
	_T l_r = 0; _matrix__determinant_helper_<_T, _S, _E>::get(_m, l_r);
	return l_r;
}

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
	const _Element& operator [] (uint _i) const;
	_Element& operator [] (uint _i);
};

template <typename _Type, uint _Size, uint _Extra = 0>
struct vector__
:
	_vector_<vector__<_Type, _Size>, _Type, _Size>
{
	_Type v[_Size + _Extra];
};

template <typename _Type>
struct vector__<_Type, 1>
:
	_vector_<vector__<_Type, 1>, _Type, 1>
{
	_Type x;
};

template <typename _Type>
struct vector__<_Type, 2>
:
	_vector_<vector__<_Type, 2>, _Type, 2>
{
	_Type x, y;
};

template <typename _Type>
struct vector__<_Type, 3>
:
	_vector_<vector__<_Type, 3>, _Type, 3>
{
	_Type x, y, z;

	vector__()
	{}
	vector__(const _Type &_x, const _Type &_y, const _Type &_z)
	:
		x(_x), y(_y), z(_z)
	{}
};

template <typename _Type>
struct vector__<_Type, 4>
:
	_vector_<vector__<_Type, 4>, _Type, 4>
{
	_Type x, y, z, w;
};



///	Uber-matrix row template. Used internally by matrix_ template.
/**	Each _matrix_row_<_Size, _Type> struct has one member varable m_cell of cell_type type,
	and also inherits _Size - 1 cells from it's parent type _matrix_row_<_Size - 1, _Type>
 */
template<uint _Size, typename _Type>
struct _matrix_row_ : _matrix_row_<_Size - 1, _Type> {
	/// parent type
	typedef _matrix_row_<_Size - 1, _Type> parent_type;
	/// cell type
	typedef _Type cell_type;
	/// constructor
	inline _matrix_row_();
	/// copy constructor
	inline _matrix_row_(const _matrix_row_ &_r);
	/// construct from parent type
	inline _matrix_row_(const parent_type &_r);
	/// construct from longer row
	template<uint _Size2> inline _matrix_row_(const _matrix_row_<_Size2, _Type> &_r);
	/// construct from row with defferent cell type
	template<typename _Type2> explicit inline _matrix_row_(const _matrix_row_<_Size, _Type2> &_r);
	/// one cell row constructor
	inline _matrix_row_(_Type _cell0);
	/// two cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1);
	/// three cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2);
	/// four cells row constructor
	inline _matrix_row_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	/// last cell accessor
	inline const _Type& cell() const;
	/// last cell accessor
	inline _Type& cell();
	/// i-th cell accessor
	template<uint _I> inline const _Type& cell() const;
	/// i-th cell accessor
	template<uint _I> inline _Type& cell();
	/// get i-th row cell
	inline const _Type& operator [] (uint _i) const;
	/// get i-th row cell
	inline _Type& operator [] (uint _i);
	// some aux functions
	inline void _set(const _matrix_row_ &_b);
	inline void _get(_matrix_row_ &_c) const;
	inline void _neg(_matrix_row_ &_c) const;
	inline void _add(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void _sub(const _matrix_row_ &_b, _matrix_row_ &_c) const;
	inline void _mul(_Type _s, _matrix_row_ &_c) const;
	inline void _div(_Type _s, _matrix_row_ &_c) const;
	inline bool _cmp(const _matrix_row_ &_b) const;
private:
	cell_type m_cell;
};
// _matrix_row_ terminator
template<typename _Type>
struct _matrix_row_<0, _Type> {
	inline void _set(const _matrix_row_ &_b) {}
	inline void _get(_matrix_row_ &_c) const {}
	inline void _neg(_matrix_row_ &_c) const {}
	inline void _add(const _matrix_row_&, _matrix_row_&) const {}
	inline void _sub(const _matrix_row_&, _matrix_row_&) const {}
	inline void _mul(_Type, _matrix_row_&) const {}
	inline void _div(_Type, _matrix_row_&) const {}
	inline bool _cmp(const _matrix_row_ &_b) const { return true; }
};

///	Uber-matrix template
/**	This template is used for all matrices and vectors types.
	Each matrix_<_Height, _Width, _Type> struct has one member varable m_row of row_type type,
	and also inherits _Height - 1 rows from it's parent type matrix_<_Height - 1, _Width, _Type>
 */
template<uint _Height, uint _Width, typename _Type>
struct matrix_ : matrix_<_Height - 1, _Width, _Type> {
	/// parent type
	typedef matrix_<_Height - 1, _Width, _Type> parent_type;
	/// row type
	typedef _matrix_row_<_Width, _Type> row_type;
	/// cell type
	typedef _Type cell_type;
	/// one row same width matrix
	typedef matrix_<1, _Width, _Type> row_matrix;
	/// component type
	typedef typename select_<_Height == 1 || _Width == 1, cell_type, row_type>::type component_type;
	/// cross product type
	typedef typename select_<_Width == 1, cell_type, row_matrix>::type cross_type;
	/// constructor
	inline matrix_();
	/// copy constructor
	inline matrix_(const matrix_ &_m);
	/// construct from parent type
	inline matrix_(const parent_type &_m);
	/// construct from bigger matrix
	template<uint _Height2, uint _Width2> inline matrix_(const matrix_<_Height2, _Width2, _Type> &_m);
	/// construct from matrix with different cell type
	template<typename _Type2> inline matrix_(const matrix_<_Height, _Width, _Type2> &_m);
	/// one row with one cell matrix constructor
	inline matrix_(_Type _cell0);
	/// one row with two cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1);
	/// one row with three cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2);
	/// one row with four cells matrix constructor
	inline matrix_(_Type _cell0, _Type _cell1, _Type _cell2, _Type _cell3);
	/// two rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1);
	/// three rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2);
	/// four rows matrix constructor
	inline matrix_(const row_matrix &_row0, const row_matrix &_row1, const row_matrix &_row2, const row_matrix &_row3);
	/// last row accessor
	inline const row_type& row() const;
	/// last row accessor
	inline row_type& row();
	/// i-th row accessor
	template<uint _I> inline const row_type& row() const;
	/// i-th row accessor
	template<uint _I> inline row_type& row();
	/// (i,j)-th cell accessor
	template<uint _I, uint _J> inline const _Type& cell() const;
	/// (i,j)-th cell accessor
	template<uint _I, uint _J> inline _Type& cell();
	/// (0,j)-th cell accessor for matrices w/ one row (vectors)
	template<uint _J> inline const _Type& cell() const;
	/// (0,j)-th cell accessor for matrices w/ one row (vectors)
	template<uint _J> inline _Type& cell();
	/// first component accessor
	inline const component_type& x() const;
	/// first component accessor
	inline component_type& x();
	/// second component accessor
	inline const component_type& y() const;
	/// second component accessor
	inline component_type& y();
	/// third component accessor
	inline const component_type& z() const;
	/// third component accessor
	inline component_type& z();
	/// fourth component accessor
	inline const component_type& w() const;
	/// fourth component accessor
	inline component_type& w();
	/// get i-th matrix row
	inline const row_type& operator [] (uint _i) const;
	/// get i-th matrix row
	inline row_type& operator [] (uint _i);
	/// assign matrix
	inline matrix_& operator = (const matrix_ &_b);
	/// unary minus
	inline const matrix_ operator - () const;
	/// add
	template<u8> friend inline const matrix_ operator + (const matrix_ &_a, const matrix_ &_b);
	/// add assign
	inline matrix_& operator += (const matrix_ &_b);
	/// subtract
	template<u8> friend inline const matrix_ operator - (const matrix_ &_a, const matrix_ &_b);
	/// subtract assign
	inline matrix_& operator -= (const matrix_ &_b);
	/// multiply by scalar
	template<u8> friend inline const matrix_ operator * (const matrix_ &_a, _Type _b);
	/// multiply by scalar
	template<u8> friend inline const matrix_ operator * (_Type _a, const matrix_ &_b);
	/// multiply assign
	inline matrix_& operator *= (_Type _b);
	/// multiply martices
	template<uint _W2> friend inline const matrix_<_Height, _W2, _Type> operator * (const matrix_ &_a, const matrix_<_Width, _W2, _Type> &_b);
	/// get transposed matrix
	inline const matrix_<_Width, _Height, _Type> operator ~ () const;
	/// dot product
	template<u8> friend inline const _Type operator | (const matrix_ &_a, const matrix_ &_b);
	/// cross product
	template<u8> friend inline const cross_type operator ^ (const matrix_ &_a, const matrix_ &_b);
	/// compare matrices
	template<u8> friend inline bool operator == (const matrix_ &_a, const matrix_ &_b);
	///
	inline operator const row_type () const;
	// some aux functions
	inline void _set(const matrix_ &_b);
	inline void _get(matrix_ &_c) const;
	inline void _neg(matrix_ &_c) const;
	inline void _add(const matrix_ &_b, matrix_ &_c) const;
	inline void _sub(const matrix_ &_b, matrix_ &_c) const;
	inline void _mul(_Type _s, matrix_ &_c) const;
	inline void _div(_Type _s, matrix_ &_c) const;
	template<uint _W2> inline void _mul(const matrix_<_Width, _W2, _Type> &_b, matrix_<_Height, _W2, _Type> &_c) const;
	inline void _mul(const _matrix_row_<_Height, _Type> &_b, _matrix_row_<_Width, _Type> &_c) const;
	template<uint _W2> inline void _xgt(matrix_<_Width, _W2, _Type> &_b) const;
	template<uint _I> inline void _cst(const _matrix_row_<_Height, _Type> &_b);
	inline bool _cmp(const matrix_ &_b) const;
private:
	row_type m_row;
};
// matrix_ terminator
template<uint _Width, typename _Type>
struct matrix_<0, _Width, _Type> {
	inline matrix_() {}
	template<uint _Width2, uint _Height2> inline matrix_(const matrix_<_Height2, _Width2, _Type> &_m) {}
	inline void _set(const matrix_ &_b) {}
	inline void _get(matrix_ &_c) const {}
	inline void _neg(matrix_ &_c) const {}
	inline void _add(const matrix_ &_b, matrix_ &_c) const {}
	inline void _sub(const matrix_ &_b, matrix_ &_c) const {}
	inline void _mul(_Type _s, matrix_ &_c) const {}
	inline void _div(_Type _s, matrix_ &_c) const {}
	template<uint _W2> inline void _mul(const matrix_<_Width, _W2, _Type> &_b, matrix_<0, _W2, _Type> &_c) const {}
	inline void _mul(const _matrix_row_<0, _Type> &_b, _matrix_row_<_Width, _Type> &_c) const {}
	template<uint _W2> inline void _xgt(matrix_<_Width, _W2, _Type> &_b) const {}
	template<uint _I> inline void _cst(const _matrix_row_<0, _Type> &_b) {}
	inline bool _cmp(const matrix_ &_b) const { return true; }
};

/// matrix minor
template<uint _I, uint _J, uint _Size, typename _Type>
inline const matrix_<_Size - 1, _Size - 1, _Type> minor(const matrix_<_Size, _Size, _Type> &_m);

/// matrix determinant
template<uint _Size, typename _Type>
inline const _Type determinant(const matrix_<_Size, _Size, _Type> &_m);

/// matrix inverse
template<uint _Size, typename _Type>
inline bool inverse(const matrix_<_Size, _Size, _Type> &_a, matrix_<_Size, _Size, _Type> &_c);
template<uint _Size, typename _Type>
inline const matrix_<_Size, _Size, _Type> inverse(const matrix_<_Size, _Size, _Type> &_m);

/// vectors dot product
template<uint _Size, typename _Type>
inline const _Type dot(const matrix_<1, _Size, _Type> &_a, const matrix_<1, _Size, _Type> &_b);

/// vector length
template<uint _Size, typename _Type>
inline const _Type length(const matrix_<1, _Size, _Type> &_a);

/// vector length square
template<uint _Size, typename _Type>
inline const _Type length2(const matrix_<1, _Size, _Type> &_a);

/// vector normalization
template<uint _Size, typename _Type>
inline const matrix_<1, _Size, _Type> normalized(const matrix_<1, _Size, _Type> &_a);

/// vectors cross product
template<typename _Type>
inline const matrix_<1, 2, _Type> cross(const matrix_<1, 2, _Type> &_a);
template<typename _Type>
inline const _Type cross(const matrix_<1, 2, _Type> &_a, const matrix_<1, 2, _Type> &_b);
template<typename _Type>
inline const matrix_<1, 3, _Type> cross(const matrix_<1, 3, _Type> &_a, const matrix_<1, 3, _Type> &_b);
template<typename _Type>
inline const _Type cross(const matrix_<1, 3, _Type> &_a, const matrix_<1, 3, _Type> &_b, const matrix_<1, 3, _Type> &_c);

/// 1x1 matrix of real
typedef matrix_<1, 1, real> r1x1, real1;
/// 1x2 matrix of real
typedef matrix_<1, 2, real> r1x2, real2;
/// 1x3 matrix of real
typedef matrix_<1, 3, real> r1x3, real3;
/// 1x4 matrix of real
typedef matrix_<1, 4, real> r1x4, real4;
/// 2x2 matrix of real
typedef matrix_<2, 2, real> r2x2;
/// 2x3 matrix of real
typedef matrix_<2, 3, real> r2x3;
/// 2x4 matrix of real
typedef matrix_<2, 4, real> r2x4;
/// 3x2 matrix of real
typedef matrix_<3, 2, real> r3x2;
/// 3x3 matrix of real
typedef matrix_<3, 3, real> r3x3;
/// 4x2 matrix of real
typedef matrix_<4, 2, real> r4x2;
/// 4x3 matrix of real
typedef matrix_<4, 3, real> r4x3;
/// 4x4 matrix of real
typedef matrix_<4, 4, real> r4x4;

/// zero 1x1 matrix of real
const r1x1 r1x1_0(r_0), real1_0(r_0);
/// unit 1x1 matrix of real
const r1x1 r1x1_1(r_1), real1_1(r_1);
/// [0 0] vector of real
const r1x2 r1x2_0(r_0, r_0), real2_0(r_0, r_0);
/// [1 1] vector of real
const r1x2 r1x2_1(r_1, r_1), real2_1(r_1, r_1);
/// [1 0] vector of real
const r1x2 r1x2_x(r_1, r_0), real2_x(r_1, r_0);
/// [0 1] vector of real
const r1x2 r1x2_y(r_0, r_1), real2_y(r_0, r_1);
/// [0 0 0] vector of real
const r1x3 r1x3_0(r_0, r_0, r_0), real3_0(r_0, r_0, r_0);
/// [1 1 1] vector of real
const r1x3 r1x3_1(r_1, r_1, r_1), real3_1(r_1, r_1, r_1);
/// [1 0 0] vector of real
const r1x3 r1x3_x(r_1, r_0, r_0), real3_x(r_1, r_0, r_0);
/// [0 1 0] vector of real
const r1x3 r1x3_y(r_0, r_1, r_0), real3_y(r_0, r_1, r_0);
/// [0 0 1] vector of real
const r1x3 r1x3_z(r_0, r_0, r_1), real3_z(r_0, r_0, r_1);
/// [0 0 0 0] vector of real
const r1x4 r1x4_0(r_0, r_0, r_0, r_0), real4_0(r_0, r_0, r_0, r_0);
/// [1 1 1 1] vector of real
const r1x4 r1x4_1(r_1, r_1, r_1, r_1), real4_1(r_1, r_1, r_1, r_1);
/// [1 0 0 0] vector of real
const r1x4 r1x4_x(r_1, r_0, r_0, r_0), real4_x(r_1, r_0, r_0, r_0);
/// [0 1 0 0] vector of real
const r1x4 r1x4_y(r_0, r_1, r_0, r_0), real4_y(r_0, r_1, r_0, r_0);
/// [0 0 1 0] vector of real
const r1x4 r1x4_z(r_0, r_0, r_1, r_0), real4_z(r_0, r_0, r_1, r_0);
/// [0 0 0 1] vector of real
const r1x4 r1x4_w(r_0, r_0, r_0, r_1), real4_w(r_0, r_0, r_0, r_1);
/// zero 2x2 matrix of real
const r2x2 r2x2_0(r1x2_0, r1x2_0);
/// unit 2x2 matrix of real
const r2x2 r2x2_1(r1x2_x, r1x2_y);
/// unit 3x2 matrix of real
const r3x2 r3x2_1(r1x2_x, r1x2_y, r1x2_0);
/// zero 3x3 matrix of real
const r3x3 r3x3_0(r1x3_0, r1x3_0, r1x3_0);
/// unit 3x3 matrix of real
const r3x3 r3x3_1(r1x3_x, r1x3_y, r1x3_z);
/// zero 4x3 matrix of real
const r4x3 r4x3_0(r1x3_0, r1x3_0, r1x3_0, r1x3_0);
/// unit 4x3 matrix of real
const r4x3 r4x3_1(r1x3_x, r1x3_y, r1x3_z, r1x3_0);
/// zero 4x4 matrix of real
const r4x4 r4x4_0(r1x4_0, r1x4_0, r1x4_0, r1x4_0);
/// unit 4x4 matrix of real
const r4x4 r4x4_1(r1x4_x, r1x4_y, r1x4_z, r1x4_w);

/// 1x1 matrix of sint
typedef matrix_<1, 1, sint> s1x1, sint1;
/// 1x2 matrix of sint
typedef matrix_<1, 2, sint> s1x2, sint2;

/// zero 1x1 matrix of sint
const s1x1 s1x1_0(s_0);
/// unit 1x1 matrix of sint
const s1x1 s1x1_1(s_1);
/// [0 0] vector of sint
const s1x2 s1x2_0(s_0, s_0), sint2_0(s_0, s_0);
/// [1 1] vector of sint
const s1x2 s1x2_1(s_1, s_1), sint2_1(s_1, s_1);
/// [1 0] vector of sint
const s1x2 s1x2_x(s_1, s_0), sint2_x(s_1, s_0);
/// [0 1] vector of sint
const s1x2 s1x2_y(s_0, s_1), sint2_y(s_0, s_1);

#include "matrix.inl"
