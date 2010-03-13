/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// color

template<typename _Type>
struct color_
:
	_vector_<color_<_Type>, _Type, 4>
{
	_Type r, g, b, a;

	inline color_();
	inline color_(_Type _r, _Type _g, _Type _b, _Type _a = _Type(1));
	inline color_(u8 _r, u8 _g, u8 _b, u8 _a = u8(255));
	inline color_(u32 _c);
	inline operator vector_<_Type, 4> () const;
	inline operator u32 () const;
};
typedef color_<real> color;

const color white(r_1, r_1, r_1);
const color black(r_0, r_0, r_0);
const color grey(r_05, r_05, r_05);
const color red(r_1, r_0, r_0);
const color green(r_0, r_1, r_0);
const color blue(r_0, r_0, r_1);
const color yellow(r_1, r_1, r_0);
const color cyan(r_0, r_1, r_1);
const color magenta(r_1, r_0, r_1);

/// cxform
template<typename _Type> struct cxform_
{
	typedef color_<_Type> color;
	inline cxform_();
	inline cxform_(const color &_mul, const color &_add);
	inline const color transform(const color &_c) const;

private:
	color m_mul, m_add;
};
typedef cxform_<real> cxform;

#include "color.inl"
