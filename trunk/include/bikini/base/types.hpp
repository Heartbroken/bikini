/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// types with exact size
typedef unsigned char		u8, byte;
typedef char				s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;
typedef unsigned __int64	u64;
typedef __int64				s64;
typedef float				f32;
typedef double				f64;

/// unsigned integer number
typedef uintptr_t			uint;
/// signed integer number
typedef intptr_t			sint;
/// big unsigned integer number
typedef unsigned __int64	ubig;
/// big signed integer number
typedef __int64				sbig;
/// big real number
typedef double				rbig;
/// real number
#if defined(BIKINI_REAL_IS_DOUBLE)
typedef double				real;
#else
typedef float				real;
#endif

typedef void*				handle;
typedef const void*			pointer;

typedef char				achar;
typedef wchar_t				wchar;

typedef std::string			astring;
typedef std::wstring		wstring;

/// array class template
template<typename _Type, typename _Allocator = std::allocator<_Type> >
struct array_ : std::vector<_Type, _Allocator> {
	typedef _Type value_type;
	typedef _Allocator allocator_type;
	typedef std::vector<value_type, allocator_type> parent_type;
	typedef parent_type& parent_type_ref;
	typedef const parent_type& parent_type_const_ref;
	inline array_() {}
	inline array_(const parent_type &_right) : parent_type(_right) {}
	inline array_(const allocator_type &_allocator) : parent_type(_allocator) {}
	inline array_(uint _count) : parent_type(_count) {}
	inline array_(uint _count, const value_type &_value) : parent_type(_count, _value) {}
	inline array_(uint _count, const value_type &_value, const allocator_type &_allocator) : parent_type(_count, _value, _allocator) {}
	inline array_(const array_ &_right) : parent_type(static_cast<const parent_type&>(_right)) {}
	template<typename _Iterator> inline array_(_Iterator _first, _Iterator _last) : parent_type(_first, _last) {}
	template<typename _Iterator> inline array_(_Iterator _first, _Iterator _last, const allocator_type &_allocator) : parent_type(_first, _last, _allocator) {}
	inline operator parent_type_ref () { return static_cast<parent_type&>(*this); }
	inline operator parent_type_const_ref () const { return static_cast<const parent_type&>(*this); }
};

///
typedef array_<byte> byte_array;
typedef array_<uint> uint_array;
typedef array_<sint> sint_array;
typedef array_<real> real_array;
typedef array_<rbig> rbig_array;
typedef array_<achar> achar_array;
typedef array_<wchar> wchar_array;
typedef array_<astring> astring_array;
typedef array_<wstring> wstring_array;

///
inline const achar* utf8(const wstring &_s)
{
	uint l_wlength = _s.length() + 1;
	uint l_alength = WideCharToMultiByte(CP_UTF8, 0, _s.c_str(), l_wlength, 0, 0, 0, 0);
	static achar_array l_data; l_data.resize(l_alength);
	WideCharToMultiByte(CP_UTF8, 0, _s.c_str(), l_wlength, &l_data[0], l_alength, 0, 0);
	return &l_data[0];
}
inline const wchar* utf8(const astring &_s)
{
	uint l_alength = _s.length() + 1;
	uint l_wlength = MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), l_alength, 0, 0);
	static wchar_array l_data; l_data.resize(l_wlength);
	MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), l_alength, &l_data[0], l_wlength);
	return &l_data[0];
}
inline const achar* format(const achar* _format, ...)
{
	va_list l_args;
	va_start(l_args, _format);

	const uint l_buffer_max = 1024;
	achar l_buffer[l_buffer_max];

	sint l_length = vsprintf_s(l_buffer, _format, l_args);
	
	if (l_length <= 0) return 0;

	l_buffer[l_length] = 0;

	static achar_array l_data;
	l_data.assign(l_buffer, l_buffer + l_length + 1);

	va_end(l_args);

	return &l_data[0];
}
inline const wchar* format(const wchar* _format, ...)
{
	va_list l_args;
	va_start(l_args, _format);

	const uint l_buffer_max = 1024;
	wchar l_buffer[l_buffer_max];

	sint l_length = vswprintf_s(l_buffer, _format, l_args);
	
	if (l_length <= 0) return 0;

	l_buffer[l_length] = 0;

	static wchar_array l_data;
	l_data.assign(l_buffer, l_buffer + l_length + 1);

	va_end(l_args);

	return &l_data[0];
}

/// type selector template
template<bool _C, typename _T0, typename _T1>
struct select_ {
	typedef _T0 type;
};
template<typename _T0, typename _T1>
struct select_<false, _T0, _T1> {
	typedef _T1 type;
};

/// noncopyable type
struct noncopyable {
	inline noncopyable() {}
private:
	inline noncopyable(const noncopyable&);
	inline noncopyable& operator = (const noncopyable&);
};

/// notype type
struct notype {};
