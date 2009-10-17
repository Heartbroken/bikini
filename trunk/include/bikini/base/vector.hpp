/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace vm { enum vector_major { row, column };}

template<typename _Type, uint _Size, vm::vector_major _Major = vm::row>
struct vector_
{
	typedef _Type element;
	typedef vector_<_Type, _Size, vm::row> row;
	typedef vector_<_Type, _Size, vm::column> column;

	typedef typename make_typelist<
		u8, s8, u16, s16, u32, s32, u64, s64, f32, f64
	>::type numbers;

	template<typename _Type1, typename _Type2>
	struct _select_better_
	{
		c_assert(numbers::type_<_Type1>::exists && numbers::type_<_Type2>::exists);
		typedef typename select_<numbers::type_<_Type2>::index > numbers::type_<_Type1>::index, _Type2, _Type1>::type;
	};

	template<typename _Type1, vm::vector_major _Major1, typename _Type2, vm::vector_major _Major2>
	struct _mul_result_
	{
	};
};