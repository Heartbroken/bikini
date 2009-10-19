/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct _vector_base
{
	enum arrange { row, column };

	typedef make_typelist_<
		s8, u8, s16, u16, s32, u32, s64, u64, f32, f64
	>::type numbers;

	template<typename _Type1, typename _Type2>
	struct more_exact_
	{
		typedef typename select_<
			(numbers::type_<_Type2>::index > numbers::type_<_Type1>::index), _Type2, _Type1
		>::type type;
	};

	template<typename _Type1, typename _Type2>
	struct mul_
	{
		typedef typename more_exact_<_Type1, _Type2>::type result;
	};
	template<typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template<typename, uint, arrange> class _Vector_>
	struct mul_<_Vector_<_Type1, _Size, _Arrange>, _Type2>
	{
		typedef _Vector_<_Type1, _Size, _Arrange> vector1;
		typedef typename mul_<typename vector1::element, _Type2>::result new_element;
		typedef _Vector_<new_element, _Size, _Arrange> result;
	};
	template<typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template<typename, uint, arrange> class _Vector_>
	struct mul_<_Type1, _Vector_<_Type2, _Size, _Arrange> >
	{
		typedef _Vector_<_Type2, _Size, _Arrange> vector2;
		typedef typename mul_<_Type1, typename vector2::element>::result new_element;
		typedef _Vector_<new_element, _Size, _Arrange> result;
	};
	template<typename _Type1, typename _Type2, uint _Size, arrange _Arrange, template<typename, uint, arrange> class _Vector_>
	struct mul_<_Vector_<_Type1, _Size, _Arrange>, _Vector_<_Type2, _Size, _Arrange> >
	{
		typedef _Vector_<_Type1, _Size, _Arrange> vector1;
		typedef _Vector_<_Type2, _Size, _Arrange> vector2;
		typedef typename mul_<typename vector1::element, typename vector2::element>::result new_element;
		typedef _Vector_<new_element, _Size, _Arrange> result;
	};
	template<typename _Type1, typename _Type2, uint _Size, template<typename, uint, arrange> class _Vector_>
	struct mul_<_Vector_<_Type1, _Size, row>, _Vector_<_Type2, _Size, column> >
	{
		typedef _Vector_<_Type1, _Size, row> vector1;
		typedef _Vector_<_Type2, _Size, column> vector2;
		typedef typename mul_<typename vector1::element, typename vector2::element>::result result;
	};
	template<typename _Type1, typename _Type2, uint _Size, template<typename, uint, arrange> class _Vector_>
	struct mul_<_Vector_<_Type1, _Size, column>, _Vector_<_Type2, _Size, row> >
	{
		typedef _Vector_<_Type1, _Size, column> vector1;
		typedef _Vector_<_Type2, _Size, row> vector2;
		typedef typename mul_<typename vector1::element, vector2>::result new_element;
		typedef _Vector_<new_element, _Size, column> result;
	};
};

template<typename _Type, uint _Size, _vector_base::arrange _Arrange = _vector_base::row>
struct vector_ : vector_<_Type, _Size - 1, _Arrange>
{
	typedef _Type element;
	typedef vector_<_Type, _Size - 1, _Arrange> parent;
	typedef vector_<_Type, _Size, _vector_base::row> row;
	typedef vector_<_Type, _Size, _vector_base::column> column;

	element X;

	inline vector_();
	//inline vector_(const column &_v);
	template<typename _Type2>
	explicit inline vector_(const _Type2 &_0);
	template<typename _Type2>
	inline vector_(const _Type2 &_0, const _Type2 &_1);
	template<typename _Type2>
	inline vector_(const _Type2 &_0, const _Type2 &_1, const _Type2 &_2);

	//
	inline operator row& () { return static_cast<row&>(*this); }
	inline operator column& () { return static_cast<column&>(*this); }

	//
	template<typename _Type2, _vector_base::arrange _Arrange2>
	inline void add(const vector_<_Type2, _Size, _Arrange2> &_b, vector_<typename _vector_base::more_exact_<_Type, _Type2>::type, _Size, _Arrange> &_c) const;
	//
	template<typename _Type2, _vector_base::arrange _Arrange2>
	inline vector_<typename _vector_base::more_exact_<_Type, _Type2>::type, _Size, _Arrange>
	operator + (const vector_<_Type2, _Size, _Arrange2> &_b) const;

};
template<typename _Type, _vector_base::arrange _Arrange>
struct vector_<_Type, 0, _Arrange>
{
};

// inlines

//
template<typename _T, uint _S, _vector_base::arrange _A>
inline vector_<_T, _S, _A>::vector_()
{}
//template<typename _T, uint _S, _vector_base::arrange _A>
//inline vector_<_T, _S, _A>::vector_(const column &_v)
//:
//	parent(column::parent(_v))
//{}
template<typename _T, uint _S, _vector_base::arrange _A> template<typename _T2>
inline vector_<_T, _S, _A>::vector_(const _T2 &_0)
:
	X(static_cast<_T>(_0))
{
	c_assert(_S == 1)
}
template<typename _T, uint _S, _vector_base::arrange _A> template<typename _T2>
inline vector_<_T, _S, _A>::vector_(const _T2 &_0, const _T2 &_1)
:
	parent(_0), X(static_cast<_T>(_1))
{
	c_assert(_S == 2)
}
template<typename _T, uint _S, _vector_base::arrange _A> template<typename _T2>
inline vector_<_T, _S, _A>::vector_(const _T2 &_0, const _T2 &_1, const _T2 &_2)
:
	parent(_0, _1), X(static_cast<_T>(_2))
{
	c_assert(_S == 3)
}

//
template<typename _Va, typename _Vb, typename _Vc>
struct _vector_add_helper_
{
	static inline void add(const _Va &_a, const _Vb &_b, _Vc &_c)
	{
		typedef typename _Va::parent _Pa;
		typedef typename _Vb::parent _Pb;
		typedef typename _Vc::parent _Pc;
		_vector_add_helper_<_Pa, _Pb, _Pc>::add(_a, _b, _c);
		_c.X = _a.X + _b.X;
	}
};
template<typename _Ta, typename _Tb, typename _Tc, _vector_base::arrange _A>
struct _vector_add_helper_<vector_<_Ta, 1, _A>, vector_<_Tb, 1, _A>, vector_<_Tc, 1, _A> > {
	typedef vector_<_Ta, 1, _A> _Va;
	typedef vector_<_Tb, 1, _A> _Vb;
	typedef vector_<_Tc, 1, _A> _Vc;
	static inline void add(const _Va &_a, const _Vb &_b, _Vc &_c)
	{
		_c.X = _a.X + _b.X;
	}
};
template<typename _T, uint _S, _vector_base::arrange _A> template<typename _T2, _vector_base::arrange _A2>
inline void vector_<_T, _S, _A>::add(const vector_<_T2, _S, _A2> &_b, vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> &_c) const
{
	typedef vector_<_T, _S, _A> _Va;
	typedef vector_<_T2, _S, _A2> _Vb;
	typedef vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> _Vc;
	_vector_add_helper_<_Va, _Vb, _Vc>::add(*this, _b, _c);
}
//
template<typename _T, uint _S, _vector_base::arrange _A> template<typename _T2, _vector_base::arrange _A2>
inline vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A>
vector_<_T, _S, _A>::operator + (const vector_<_T2, _S, _A2> &_b) const
{
	vector_<typename _vector_base::more_exact_<_T, _T2>::type, _S, _A> l_c;
	add(_b, l_c);
	return l_c;
}
