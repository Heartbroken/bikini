/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	typelist template
/**	[TODO]

 */
template<typename _First, typename _Rest = notype> struct typelist_;
template<typename _First, typename _Second, typename _Third> struct typelist_<_First, typelist_<_Second, _Third> >
{
	/// First type of the list
	typedef _First first;
	/// The rest of the list
	typedef typelist_<_Second, _Third> rest;
	/// Types count
	static const uint count = 1 + rest::count;
	/// The biggest type size
	static const uint max_size = sizeof(first) > rest::max_size ? sizeof(first) : rest::max_size;
	/// List item info
	template<uint _Index> struct item_
	{
		/// Item type
		typedef typename rest::item_<_Index - 1>::type type;
		/// Item size
		static const uint size = sizeof(type);
#		ifdef _DEBUG
		type value;
#		endif
	};
	template<> struct item_<0>
	{
		typedef first type;
		static const uint size = sizeof(type);
#		ifdef _DEBUG
		type value;
#		endif
	};
	/// Type info
	template<typename _Type> struct type_
	{
		// _check_rest helper
		typedef typename rest::type_<_Type> _check_rest;
		/// Type index in the list
		static const uint index = _check_rest::index == bad_ID ? bad_ID : 1 + (s32)_check_rest::index;
		/// Type presence in the list
		static const bool exists = _check_rest::exists;
	};
	template<> struct type_<first>
	{
		static const uint index = 0;
		static const bool exists = true;
	};
	/// Append a type to the list
	template<typename _Type> struct append_
	{
		typedef typelist_<first, typename rest::append_<_Type>::result> result;
	};
	/// Other typelist info
	template<typename _Otherlist> struct otherlist_
	{
		/// If other typelist types are contained in the list
		static const bool belong = type_<typename _Otherlist::first>::exists && otherlist_<typename _Otherlist::rest>::belong;
		/// Remap type index in other list to index in the list
		inline static uint remap(uint _i);
	};
	template<> struct otherlist_<typelist_<notype> >
	{
		static const bool belong = true;
		inline static uint remap(uint _i) { return bad_ID; }
	};
	/// The size of the i-th type in the list
	inline static uint size(uint _i);
	/// Allocate and construct an object of the i-th type in the list
	inline static handle construct(uint _i);
	/// Allocate and construct an object of the i-th type in the list, copy the pointed object
	inline static handle construct(uint _i, pointer _v);
	/// Construct an object of the i-th type in the list
	inline static handle construct(handle _h, uint _i);
	/// Construct an object of the i-th type in the list, copy the pointed object
	inline static handle construct(handle _h, uint _i, pointer _v);
	/// Destruct the pointed object. Free memory if needed
	inline static void destruct(handle _h, uint _i, bool _and_free = true);
	/// Compare two pointed objects of i-th type
	inline static bool compare(uint _i, pointer _a, pointer _b);
};
template<> struct typelist_<notype>
{
	static const uint count = 0;
	static const uint max_size = 0;
	template<uint _Index> struct item_ { typedef typename notype type; static const uint size = 0; };
	template<typename _Type> struct type_ { static const uint index = bad_ID; static const bool exists = false; };
	template<typename _Type> struct append_ { typedef typelist_<_Type, typelist_<notype> > result; };
	template<typename _First, typename _Rest> struct append_<typelist_<_First, _Rest> > { typedef typelist_<_First, _Rest> result; };
	inline static uint size(uint _i) { return 0; }
	inline static handle construct(uint _i) { return 0; }
	inline static handle construct(uint _i, pointer _v) { return 0; }
	inline static handle construct(handle _h, uint _i, pointer _v) { return 0; }
	inline static handle construct(handle _h, uint _i) { return 0; }
	inline static void destruct(handle _h, uint _i, bool _and_free = true) {}
	inline static bool compare(uint _i, pointer _a, pointer _b) { return false; }
};

///	make_typelist template
/**

 */
template
<
	typename _Type0,
	typename _Type01 = notype, typename _Type02 = notype, typename _Type03 = notype, typename _Type04 = notype, typename _Type05 = notype,
	typename _Type06 = notype, typename _Type07 = notype, typename _Type08 = notype, typename _Type09 = notype, typename _Type10 = notype,
	typename _Type11 = notype, typename _Type12 = notype, typename _Type13 = notype, typename _Type14 = notype, typename _Type15 = notype,
	typename _Type16 = notype, typename _Type17 = notype, typename _Type18 = notype, typename _Type19 = notype, typename _Type20 = notype,
	typename _Type21 = notype, typename _Type22 = notype, typename _Type23 = notype, typename _Type24 = notype, typename _Type25 = notype,
	typename _Type26 = notype, typename _Type27 = notype, typename _Type28 = notype, typename _Type29 = notype, typename _Type30 = notype,
	typename _Type31 = notype, typename _Type32 = notype, typename _Type33 = notype, typename _Type34 = notype, typename _Type35 = notype,
	typename _Type36 = notype, typename _Type37 = notype, typename _Type38 = notype, typename _Type39 = notype, typename _Type40 = notype,
	typename _Type41 = notype, typename _Type42 = notype, typename _Type43 = notype, typename _Type44 = notype, typename _Type45 = notype,
	typename _Type46 = notype, typename _Type47 = notype, typename _Type48 = notype, typename _Type49 = notype, typename _Type50 = notype
>
struct make_typelist_
{
	typedef typelist_<
		_Type0,
		typename make_typelist_<
			_Type01, _Type02, _Type03, _Type04, _Type05, _Type06, _Type07, _Type08, _Type09, _Type10,
			_Type11, _Type12, _Type13, _Type14, _Type15, _Type16, _Type17, _Type18, _Type19, _Type20,
			_Type21, _Type22, _Type23, _Type24, _Type25, _Type26, _Type27, _Type28, _Type29, _Type30,
			_Type31, _Type32, _Type33, _Type34, _Type35, _Type36, _Type37, _Type38, _Type39, _Type40,
			_Type41, _Type42, _Type43, _Type44, _Type45, _Type46, _Type47, _Type48, _Type49, _Type50
		>::type
	> type;
};
template<> struct make_typelist_<notype>
{
	typedef typelist_<notype> type;
};

#include "typelist.inl"