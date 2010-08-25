/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	A variant type template
/**	[TODO]
 */
template<typename _Typelist, bool _Dynamic = true> struct variant_
{
	/// A list of types a variant can contain
	typedef _Typelist types;
	/// Default constructor
	inline variant_();
	/// Construct a variant another similar variant
	inline variant_(const variant_ &_v);
	/// Construct a variant from a value. Type of a value must be in the list of types
	template<typename _Type> inline variant_(const _Type & _v);
	/// Construct a variant from another variant with different type list
	template<typename _Typelist2, bool _Dynamic2> inline variant_(const variant_<_Typelist2, _Dynamic2> &_v);
	/// Destruct a variant
	inline ~variant_();
	/// Current value type (index in the type list)
	inline uint type() const;
	/// Pointer to value's data
	inline pointer data() const;
	/// Construct a variant of specified type from specified data
	inline void construct(uint _type, pointer _data);
	/// Destruct a variant
	inline void destruct();
	/// Assign
	inline variant_& operator = (const variant_ &_v);
	/// Assign
	template<typename _Type> inline variant_& operator = (const _Type & _v);
	/// Assign
	template<typename _Typelist2, bool _Dynamic2> inline variant_& operator = (const variant_<_Typelist2, _Dynamic2> &_v);
	/// Test if equal
	inline bool operator == (const variant_ &_v) const;
	/// Test if equal
	template<typename _Type> inline bool operator == (const _Type & _v) const;
	/// Test if equal
	template<typename _Typelist2, bool _Dynamic2> inline bool operator == (const variant_<_Typelist2, _Dynamic2> &_v) const;
	/// Test if not equal
	template<typename _Type> inline bool operator != (const _Type & _v) const;
	/// Test if a variant can take specified type
	template<typename _Type> inline static bool can_take();
	/// Test if a variant can take specified type by value
	template<typename _Type> inline static bool can_take(const _Type & _v);
	/// Test if a variant can take current type fo another variant
	template<typename _Typelist2, bool _Dynamic2> inline static bool can_take(const variant_<_Typelist2, _Dynamic2> &_v);
	/// Test if a variant has no value
	inline bool is_nothing() const;
	/// Chech a type of a variant
	template<typename _Type> inline bool is_() const;
	/// Get a variant's value
	template<typename _Type> inline _Type & get_();
	template<typename _Type> inline const _Type & get_() const;
	/// Get a variant value. If there is no value return default value
	template<typename _Type> inline const _Type & def(const _Type & _def) const;

	//struct _types;
private:
	uint m_type;
	typedef handle dynamic_data_type;
	typedef u8 static_data_type[types::max_size];
	typedef typename select_<_Dynamic, dynamic_data_type, static_data_type>::type data_type;
	data_type m_data;

	//template<uint _I> struct type_
	//{
	//	typedef typename types::rest::item_<_I - 1>::type type;
	//	type value;
	//};
	//template<> struct type_<0>
	//{
	//	typedef typename types::item_<0>::type type;
	//	type value;
	//};
	//static type_<types::count - 1> _types;
};
//template<typename _T, bool _D>
//struct variant_<_T, _D>::_types
//{
//	typename types::item_<0>::type type0;
//	typename types::item_<1>::type type1;
//	typename types::item_<2>::type type2;
//};

//template<typename _T, bool _D>
//typename variant_<_T, _D>::type_<_T::count - 1> variant_<_T, _D>::_types;

typedef variant_<fundamentals> variant;

#include "variant.inl"
