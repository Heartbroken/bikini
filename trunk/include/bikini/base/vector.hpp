/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace vm { enum vector_major { row = 1, column = 2 }; }

template<typename _Type, uint _Size, vm::vector_major _Major = vm::row>
struct vector_ : vector_<_Type, _Size - 1, _Major>
{
	typedef vector_<_Type, _Size, _Major> this_type;
	typedef _Type element_type;
	typedef vector_<_Type, _Size, vm::row> row_type;
	typedef vector_<_Type, _Size, vm::column> column_type;

	static const uint size = _Size;
	static const vm::vector_major major = _Major;
	static const vm::vector_major other_major = major == vm::row ? vm::column : vm::row;

private:
	element_type m_element;
};
template<typename _Type, vm::vector_major _Major>
struct vector_<_Type, 1, _Major>
{
	typedef _Type element_type;

	typedef typename make_typelist_<
		u8, s8, u16, s16, u32, s32, u64, s64, f32, f64
	>::type numbers;

	template<typename _Type1, typename _Type2>
	struct _select_better_
	{
		typedef typename select_<
			(numbers::type_<_Type2>::index > numbers::type_<_Type1>::index),
			_Type2, _Type1
		>::type type;
	};

	template<typename _Type1, typename _Type2>
	struct _mul_
	{
		typedef typename _select_better_<_Type1, _Type2>::type result;
	};
	template<typename _Type1, typename _Type2, uint _Size, vm::vector_major _Major>
	struct _mul_<vector_<_Type1, _Size, _Major>, _Type2>
	{
		typedef vector_<_Type1, _Size, _Major> vector1;
		typedef typename _mul_<typename vector1::element_type, _Type2>::result new_element_type;
		typedef vector_<new_element_type, _Size, _Major> result;
	};
	template<typename _Type1, typename _Type2, uint _Size, vm::vector_major _Major>
	struct _mul_<_Type1, vector_<_Type2, _Size, _Major> >
	{
		typedef vector_<_Type2, _Size, _Major> vector2;
		typedef typename _mul_<_Type1, typename vector2::element_type>::result new_element_type;
		typedef vector_<new_element_type, _Size, _Major> result;
	};
	template<typename _Type1, typename _Type2, uint _Size, vm::vector_major _Major>
	struct _mul_<vector_<_Type1, _Size, _Major>, vector_<_Type2, _Size, _Major> >
	{
		typedef vector_<_Type1, _Size, _Major> vector1;
		typedef vector_<_Type2, _Size, _Major> vector2;
		typedef typename _mul_<typename vector1::element_type, typename vector2::element_type>::result new_element_type;
		typedef vector_<new_element_type, _Size, _Major> result;
	};
	template<typename _Type1, typename _Type2, uint _Size>
	struct _mul_<vector_<_Type1, _Size, vm::row>, vector_<_Type2, _Size, vm::column> >
	{
		typedef vector_<_Type1, _Size, vm::row> vector1;
		typedef vector_<_Type2, _Size, vm::column> vector2;
		typedef typename _mul_<typename vector1::element_type, typename vector2::element_type>::result result;
	};
	template<typename _Type1, typename _Type2, uint _Size>
	struct _mul_<vector_<_Type1, _Size, vm::column>, vector_<_Type2, _Size, vm::row> >
	{
		typedef vector_<_Type1, _Size, vm::column> vector1;
		typedef vector_<_Type2, _Size, vm::row> vector2;
		typedef typename _mul_<typename vector1::element_type, vector2>::result new_element_type;
		typedef vector_<new_element_type, _Size, vm::column> result;
	};

private:
	element_type m_element;
};
