/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

typedef make_typelist_<u8, u16, u32, u64, uint, ubig>::type unsigneds;
typedef make_typelist_<s8, s16, s32, s64, sint, sbig>::type signeds;
typedef make_typelist_<bool>::type boolean;
typedef make_typelist_<f32, f64, real, rbig>::type floats;
typedef make_typelist_<bool, u8, u16, u32, u64, uint, ubig, s8, s16, s32, s64, sint, sbig, f32, f64, real, rbig>::type fundamentals;

/// traits
/**	[TODO]
 */
template<typename _Type> struct traits_ {
private:
	template<typename _T> struct pointer_traits_ { static const bool yes = false; typedef _T type; };
	template<typename _T> struct pointer_traits_<_T*> { static const bool yes = true; typedef _T type; };

	template<typename _T> struct reference_traits_ { static const bool yes = false; typedef _T type; };
	template<typename _T> struct reference_traits_<_T&> { static const bool yes = true; typedef _T type; };
	template<typename _T> struct reference_traits_<const _T&> { static const bool yes = true; typedef _T type; };

	template<typename _T> struct parameter_traits_ { typedef const _T& type; };
	template<typename _T> struct parameter_traits_<_T&> { typedef _T& type; };

	template<typename _T> struct member_ptr_traits_ { static const bool yes = false; };
	template<typename _T, typename _M> struct member_ptr_traits_<_T _M::*> { static const bool yes = true; };
	template<typename _T, typename _M> struct member_ptr_traits_<_T _M::*&> { static const bool yes = true; };

	template<typename _T> struct const_traits_ { static const bool yes = false; typedef _T type; };
	template<typename _T> struct const_traits_<const _T> { static const bool yes = true; typedef _T type; };

	template<typename _T> struct function_traits_ { static const bool yes = false; };
	template<typename _T> struct function_traits_<_T (&)> { static const bool yes = true; };
	template<typename _T> struct function_traits_<_T (*)> { static const bool yes = true; };

	template<typename _T> struct array_traits_ { static const bool yes = false; typedef _T type; };
	template<typename _T, uint _N> struct array_traits_<_T[_N]> { static const bool yes = true; typedef _T type; };

public:
	static const bool is_pointer = pointer_traits_<_Type>::yes;
	typedef typename pointer_traits_<_Type>::type pointed;

	static const bool is_reference = reference_traits_<_Type>::yes;
	typedef typename reference_traits_<_Type>::type referred;

	static const bool is_member_pointer = member_ptr_traits_<_Type>::yes;

	static const bool is_array = array_traits_<_Type>::yes;
	typedef typename array_traits_<_Type>::type element;

	static const bool is_const = const_traits_<_Type>::yes;
	typedef typename const_traits_<_Type>::type nonconst;

	static const bool is_unsigned = unsigneds::type_<_Type>::exists;
	static const bool is_signed = signeds::type_<_Type>::exists;
	static const bool is_boolean = boolean::type_<_Type>::exists;
	static const bool is_integer = is_unsigned || is_signed || is_boolean;
	static const bool is_float = floats::type_<_Type>::exists;
	static const bool is_arithmetical = is_integer || is_float;
	static const bool is_fundamental = is_arithmetical /*|| typelist<void>::type<_Type>::exists*/;

	typedef typename select_<
		is_arithmetical || is_pointer || is_member_pointer,
		_Type,
		typename parameter_traits_<_Type>::type
	>::type parameter;

	static const bool is_function = function_traits_<_Type>::yes;
};