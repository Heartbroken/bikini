/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

namespace vm { enum vector_major { row, column }; }

template<typename _Type, uint _Size, vm::vector_major _Major = vm::row>
struct vector_ : vector_<_Type, _Size - 1, _Major>
{
	typedef vector_<_Type, _Size, _Major> this_type;
	typedef vector_<_Type, 1, _Major == vm::row ? vm::column : vm::row> element_type;
	typedef vector_<_Type, _Size, vm::row> row_type;
	typedef vector_<_Type, _Size, vm::column> column_type;

	static const uint size = _Size;
	static const vm::vector_major major = _Major;

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

	template<typename _Othertype> struct _mul_;
	template<> struct _mul_<this_type>
	{
		typedef this_type result;
	};
	template<> struct _mul_<row_type>
	{
		typedef typename select_<
			major == vm::row,
			this_type, typename element_type::_mul_<column_type::element_type>
		>::type result;
	};
	//template<typename _Type1, typename _Type2>
	//struct _mul_<_Type1, vm::row, _Type2, vm::row>
	//{
	//	typedef typename _select_better_<_Type, _Type2>::type result;
	//};

private:
	element_type m_element;
};
template<typename _Type, vm::vector_major _Major>
struct vector_<_Type, 0, _Major>
{
};
