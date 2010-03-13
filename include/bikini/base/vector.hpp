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

	inline vector__();
	//{}
	explicit inline vector__(_Type _x);
	//:
	//	x(_x)
	//{}
};

template <typename _Type>
struct vector__<_Type, 2>
:
	_vector_<vector__<_Type, 2>, _Type, 2>
{
	_Type x, y;

	inline vector__();
	//{}
	inline vector__(_Type _x, _Type _y);
	//:
	//	x(_x), y(_y)
	//{}
};

template <typename _Type>
struct vector__<_Type, 3>
:
	_vector_<vector__<_Type, 3>, _Type, 3>
{
	_Type x, y, z;

	inline vector__();
	//{}
	inline vector__(_Type _x, _Type _y, _Type _z);
	//:
	//	x(_x), y(_y), z(_z)
	//{}
};

template <typename _Type>
struct vector__<_Type, 4>
:
	_vector_<vector__<_Type, 4>, _Type, 4>
{
	_Type x, y, z, w;

	inline vector__();
	//{}
	inline vector__(_Type _x, _Type _y, _Type _z, _Type _w);
	//:
	//	x(_x), y(_y), z(_z), w(_w)
	//{}
};

//template <typename _T, uint _S, uint _E, uint _I = _S>
//struct _vector__dot_helper_ { static inline const _T get(const vector__<_T, _S, _E> &_a, const vector__<_T, _S, _E> &_b)
//{
//	return _vector__dot_helper_<_T, _S, _E, _I - 1>::get(_a, _b) + _a.cell_<_I - 1, 0>() * _b.cell_<_I - 1, 0>();
//}};
//template <typename _T, uint _S, uint _E>
//struct _vector__dot_helper_<_T, _S, _E, 0> { static inline const _T get(const vector__<_T, _S, _E> &_a, const vector__<_T, _S, _E> &_b)
//{
//	return 0;
//}};
template <typename _T, uint _S, uint _E>
inline const _T dot(const vector__<_T, _S, _E> &_a, const vector__<_T, _S, _E> &_b);
//{
//	return _vector__dot_helper_<_T, _S, _E>::get(_a, _b);
//}

template <typename _T, uint _S, uint _E>
inline const _T length(const vector__<_T, _S, _E> &_a);
//{
//	return sqrt(dot(_a, _a));
//}
template <typename _T, uint _S, uint _E>
inline const _T length2(const vector__<_T, _S, _E> &_a);
//{
//	return dot(_a, _a);
//}

template <typename _T, uint _S, uint _E>
inline const vector__<_T, _S, _E> normalize(const vector__<_T, _S, _E> &_a);
//{
//	_T l_length = length(_a);
//	return l_length > eps ? _a * (_T(1) / l_length) : _a;
//}

template <typename _T, uint _E>
inline const vector__<_T, 2, _E> cross(const vector__<_T, 2, _E> &_a);
//{
//	return vector__<_T, 2, _E>(_a.y, -_a.x);
//}
template <typename _T, uint _E>
inline const _T cross(const vector__<_T, 2, _E> &_a, const vector__<_T, 2, _E> &_b);
//{
//	return _a.x * _b.y - _a.y * _b.x;
//}
template <typename _T, uint _E>
inline const vector__<_T, 3, _E> cross(const vector__<_T, 3, _E> &_a, const vector__<_T, 3, _E> &_b);
//{
//	return vector__<_T, 3, _E>(_a.y * _b.z - _a.z * _b.y, _a.z * _b.x - _a.x * _b.z, _a.x * _b.y - _a.y * _b.z);
//}
template <typename _T, uint _E>
inline const _T cross(const vector__<_T, 3, _E> &_a, const vector__<_T, 3, _E> &_b, const vector__<_T, 3, _E> &_c);
//{
//	return dot(cross(_a, _b), _c);
//}

template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector__<_T, _C> mul(const vector__<_T, _R, _Ea> &_a, const matrix__<_T, _C, _R, _Eb> &_b);
//{
//	vector__<_T, _C> l_v; mul(_a, _b, l_v);
//	return l_v;
//}
template <typename _T, uint _C, uint _R, uint _Ea, uint _Eb>
inline const vector__<_T, _R> mul(const matrix__<_T, _C, _R, _Eb> &_a, const vector__<_T, _C, _Ea> &_b);
//{
//	vector__<_T, _R> l_v; mul(_b, transpose(_a), l_v);
//	return l_v;
//}

typedef vector__<float, 2> float2;
typedef vector__<float, 3> float3;
typedef vector__<float, 4> float4;
typedef vector__<real, 2> real2;
typedef vector__<real, 3> real3;
typedef vector__<real, 4> real4;

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



///////////////////////////////////////////////////////////////////////////////////////////////////


//struct _vector_base
//{
//	enum arrange { row, column };
//
//	typedef make_typelist_<
//		s8, u8, s16, u16, s32, u32, s64, u64, f32, f64
//	>::type numbers;
//
//	template <typename _Type1, typename _Type2>
//	struct more_exact_
//	{
//		typedef typename select_<
//			(numbers::type_<_Type2>::index > numbers::type_<_Type1>::index), _Type2, _Type1
//		>::type type;
//	};
//
//	template <typename _Type1, typename _Type2>
//	struct mul_
//	{
//		typedef typename more_exact_<_Type1, _Type2>::type result;
//	};
//	template <typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template <typename, uint, arrange> class _Vector_>
//	struct mul_<_Vector_<_Type1, _Size, _Arrange>, _Type2>
//	{
//		typedef typename mul_<_Type1, _Type2>::result new_element;
//		typedef _Vector_<new_element, _Size, _Arrange> result;
//	};
//	template <typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template <typename, uint, arrange> class _Vector_>
//	struct mul_<_Type1, _Vector_<_Type2, _Size, _Arrange> >
//	{
//		typedef typename mul_<_Type1, _Type2>::result new_element;
//		typedef _Vector_<new_element, _Size, _Arrange> result;
//	};
//	template <typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template <typename, uint, arrange> class _Vector_>
//	struct mul_<_Vector_<_Type1, _Size, _Arrange>, _Vector_<_Type2, _Size, _Arrange> >
//	{
//		typedef typename mul_<_Type1, _Type2>::result new_element;
//		typedef _Vector_<new_element, _Size, _Arrange> result;
//	};
//	template <typename _Type1, typename _Type2, uint _Size, template <typename, uint, arrange> class _Vector_>
//	struct mul_<_Vector_<_Type1, _Size, row>, _Vector_<_Type2, _Size, column> >
//	{
//		typedef typename mul_<_Type1, _Type2>::result result;
//	};
//	template <typename _Type1, typename _Type2, uint _Size, template <typename, uint, arrange> class _Vector_>
//	struct mul_<_Vector_<_Type1, _Size, column>, _Vector_<_Type2, _Size, row> >
//	{
//		typedef typename mul_<_Type1, _Vector_<_Type2, _Size, row> >::result new_element;
//		typedef _Vector_<new_element, _Size, column> result;
//	};
//};
//
//template <typename _Type, uint _Size, _vector_base::arrange _Arrange = _vector_base::row>
//struct vector_ : vector_<_Type, _Size - 1, _Arrange>
//{
//	typedef _Type element;
//	typedef vector_<_Type, _Size - 1, _Arrange> parent;
//	typedef vector_<_Type, _Size, _vector_base::row> row;
//	typedef vector_<_Type, _Size, _vector_base::column> column;
//
//	element X;
//
//	inline vector_();
//	inline vector_(const vector_ &_v);
//	template <typename _Type2, _vector_base::arrange _Arrange2>
//	inline vector_(const vector_<_Type2, _Size, _Arrange2> &_v);
//	explicit inline vector_(const _Type &_0);
//	inline vector_(const _Type &_0, const _Type &_1);
//	inline vector_(const _Type &_0, const _Type &_1, const _Type &_2);
//
//	//
//	inline operator row& () { return reinterpret_cast<row&>(*this); }
//	inline operator column& () { return reinterpret_cast<column&>(*this); }
//
//	//
//	template <typename _Type2, _vector_base::arrange _Arrange2>
//	inline void add(const vector_<_Type2, _Size, _Arrange2> &_b, vector_<typename _vector_base::more_exact_<_Type, _Type2>::type, _Size, _Arrange> &_c) const;
//	//
//	template <typename _Type2, _vector_base::arrange _Arrange2>
//	inline vector_<typename _vector_base::more_exact_<_Type, _Type2>::type, _Size, _Arrange>
//	operator + (const vector_<_Type2, _Size, _Arrange2> &_b) const;
//
//};
//template <typename _Type, _vector_base::arrange _Arrange>
//struct vector_<_Type, 0, _Arrange>
//{
//	inline vector_() {}
//	inline vector_(const vector_ &_v) {}
//	template <typename _Type2, _vector_base::arrange _Arrange2>
//	inline vector_(const vector_<_Type2, 0, _Arrange2> &_v) {}
//};
//
//// inlines
//
////
//template <typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_()
//{}
//template <typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_(const vector_ &_v)
//:
//	parent(_v), X(_v.X)
//{}
//template <typename _T, uint _S, _vector_base::arrange _A> template <typename _T2, _vector_base::arrange _A2>
//inline vector_<_T, _S, _A>::vector_(const vector_<_T2, _S, _A2> &_v)
//:
//	parent(vector_<_T2, _S, _A2>::parent(_v)), X(_v.X)
//{}
//template <typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_(const _T &_0)
//:
//	X(_0)
//{
//	c_assert(_S == 1)
//}
//template <typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_(const _T &_0, const _T &_1)
//:
//	parent(_0), X(_1)
//{
//	c_assert(_S == 2)
//}
//template <typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_(const _T &_0, const _T &_1, const _T &_2)
//:
//	parent(_0, _1), X(_2)
//{
//	c_assert(_S == 3)
//}
//
////
//template <typename _Va, typename _Vb, typename _Vc>
//struct _vector_add_helper_
//{
//	static inline void add(const _Va &_a, const _Vb &_b, _Vc &_c)
//	{
//		typedef typename _Va::parent _Pa;
//		typedef typename _Vb::parent _Pb;
//		typedef typename _Vc::parent _Pc;
//		_vector_add_helper_<_Pa, _Pb, _Pc>::add(_a, _b, _c);
//		_c.X = _a.X + _b.X;
//	}
//};
//template <typename _Ta, typename _Tb, typename _Tc, _vector_base::arrange _A>
//struct _vector_add_helper_<vector_<_Ta, 1, _A>, vector_<_Tb, 1, _A>, vector_<_Tc, 1, _A> > {
//	typedef vector_<_Ta, 1, _A> _Va;
//	typedef vector_<_Tb, 1, _A> _Vb;
//	typedef vector_<_Tc, 1, _A> _Vc;
//	static inline void add(const _Va &_a, const _Vb &_b, _Vc &_c)
//	{
//		_c.X = _a.X + _b.X;
//	}
//};
//template <typename _T, uint _S, _vector_base::arrange _A> template <typename _T2, _vector_base::arrange _A2>
//inline void vector_<_T, _S, _A>::add(const vector_<_T2, _S, _A2> &_b, vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> &_c) const
//{
//	typedef vector_<_T, _S, _A> _Va;
//	typedef vector_<_T2, _S, _A2> _Vb;
//	typedef vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> _Vc;
//	_vector_add_helper_<_Va, _Vb, _Vc>::add(*this, _b, _c);
//}
////
//template <typename _T, uint _S, _vector_base::arrange _A> template <typename _T2, _vector_base::arrange _A2>
//inline vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A>
//vector_<_T, _S, _A>::operator + (const vector_<_T2, _S, _A2> &_b) const
//{
//	vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> l_c;
//	add(_b, l_c);
//	return l_c;
//}
